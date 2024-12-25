#include "ToDoList.h"
#include <QColorDialog>
#include <QDateTime>
#include <QDesktopServices>
#include <QFileDialog>
#include <QInputDialog>
#include <QMenu>
#include <QMessageBox>
#include <QTextStream>
#include <QVBoxLayout>

QString get_icon_path (buttons button)
{
  switch (button)
    {
      case buttons::add:
        return ":/icons/add.png";
      case buttons::remove:
        return ":/icons/delete.png";
      case buttons::save:
        return ":/icons/save.png";
      case buttons::load:
        return ":/icons/load.png";
      case buttons::add_link:
        return ":/icons/add_link.png";
      case buttons::none:
        return "";
    };
  return "";
}

ToDoList::ToDoList (QWidget *parent) : QMainWindow (parent)
{
  createWidgets ();
  createLayout ();
  createConnections ();
  setWindowTitle ("To-Do List");

  setMaximumSize (300, 300);
  // Set the window to stay on top of all other windows
  setWindowFlags (windowFlags () | Qt::WindowStaysOnTopHint);

  QIcon appIcon (":/icons/to_do.png");
  setWindowIcon (appIcon);

  // Set the background color to a dark theme similar to CLion
  setStyleSheet("background-color: #2b2b2b; color: #a9b7c6;");
  taskList->setStyleSheet("background-color: #3c3f41; color: #a9b7c6;");
  taskInput->setStyleSheet("background-color: #3c3f41; color: #a9b7c6;");
  searchInput->setStyleSheet("background-color: #3c3f41; color: #a9b7c6;");
  addButton->setStyleSheet("background-color: #2b2b2b; color: #a9b7c6; padding: 0px; margin: 0px; border: none;");
  removeButton->setStyleSheet("background-color: #2b2b2b; color: #a9b7c6; padding: 0px; margin: 0px; border: none;");
  saveButton->setStyleSheet("background-color: #2b2b2b; color: #a9b7c6; padding: 0px; margin: 0px; border: none;");
  loadButton->setStyleSheet("background-color: #2b2b2b; color: #a9b7c6; padding: 0px; margin: 0px; border: none;");
  addLinkButton->setStyleSheet("background-color: #2b2b2b; color: #a9b7c6; padding: 0px; margin: 0px; border: none;");
}

void ToDoList::createWidgets ()
{
  auto add_icon = [] (auto button, buttons button_type) {
    QIcon icon (get_icon_path (button_type));
    button->setIcon (icon);
    button->setIconSize (QSize (30, 30));
  };
  taskList = new CustomListWidget (this);
  taskList->setDragEnabled (true);
  taskList->setAcceptDrops (true);
  taskList->setDropIndicatorShown (true);
  taskList->setDragDropMode (QAbstractItemView::InternalMove);

  taskInput = new QLineEdit (this);
  searchInput = new QLineEdit (this);
  addButton = new QToolButton (this);
  add_icon (addButton, buttons::add);
  removeButton = new QToolButton (this);
  add_icon (removeButton, buttons::remove);
  saveButton = new QToolButton (this);
  add_icon (saveButton, buttons::save);
  loadButton = new QToolButton (this);
  add_icon (loadButton, buttons::load);
  addLinkButton = new QToolButton (this);
  add_icon (addLinkButton, buttons::add_link);
  addButton->setFixedSize (25, 25);
  removeButton->setFixedSize (25, 25);
  saveButton->setFixedSize (25, 25);
  loadButton->setFixedSize (25, 25);
  addLinkButton->setFixedSize (25, 25);
  taskList->setContextMenuPolicy (Qt::CustomContextMenu);
  searchInput->setPlaceholderText ("Search...");
}

void ToDoList::createLayout ()
{
  QVBoxLayout *layout = new QVBoxLayout;
  layout->addWidget (searchInput);
  layout->addWidget (taskList);
  layout->addWidget (taskInput);
  QHBoxLayout *buttonLayout = new QHBoxLayout;
  buttonLayout->addWidget (loadButton);
  buttonLayout->addStretch ();
  buttonLayout->addWidget (addButton);
  buttonLayout->addWidget (addLinkButton);
  buttonLayout->addWidget (removeButton);
  buttonLayout->addStretch ();
  buttonLayout->addWidget (saveButton);




  layout->addLayout (buttonLayout);

  QWidget *centralWidget = new QWidget (this);
  centralWidget->setLayout (layout);
  setCentralWidget (centralWidget);
}

void ToDoList::createConnections ()
{
  connect (addButton, &QToolButton::clicked, this, &ToDoList::addTask);
  connect (removeButton, &QToolButton::clicked, this, &ToDoList::removeTask);
  connect (saveButton, &QToolButton::clicked, this, &ToDoList::saveTasks);
  connect (loadButton, &QToolButton::clicked, this, &ToDoList::loadTasks);
  connect (taskInput, &QLineEdit::returnPressed, this, &ToDoList::addTask);

  connect (taskList, &CustomListWidget::customContextMenuRequested, this, &ToDoList::showContextMenu);
  connect (searchInput, &QLineEdit::textChanged, this, &ToDoList::searchTasks);
  connect (addLinkButton, &QToolButton::clicked, this, &ToDoList::addTaskWithLink);
  connect (taskList, &CustomListWidget::itemClicked, this, &ToDoList::openLink);
}

void ToDoList::addTask ()
{
  QString task = taskInput->text ();
  if (!task.isEmpty ())
    {
      QListWidgetItem *item = new QListWidgetItem (task, taskList);
      item->setFlags (item->flags () | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
      item->setCheckState (Qt::Unchecked);
      taskInput->clear ();
    }
}

void ToDoList::removeTask () { delete taskList->currentItem (); }

void ToDoList::saveTasks ()
{
  QString currentDate = QDateTime::currentDateTime ().toString ("dd_MM_yy");
  QString fileName = QFileDialog::getSaveFileName (this, "Save Tasks", currentDate, "Text Files (*.txt);;All Files (*)");
  if (fileName.isEmpty ())
    {
      return;
    }

  QFile file (fileName);
  if (file.open (QFile::WriteOnly | QFile::Text))
    {
      QTextStream out (&file);
      for (int i = 0; i < taskList->count (); ++i)
        {
          QListWidgetItem *item = taskList->item (i);
          QString link = item->data (Qt::UserRole).toString ();
          out << item->text () << "|" << (item->checkState () == Qt::Checked ? "1" : "0") << "|" << link << "\n";
        }
      file.close ();
    }
  else
    {
      QMessageBox::warning (this, "Error", "Cannot save tasks");
    }
}

void ToDoList::loadTasks ()
{
  QString fileName = QFileDialog::getOpenFileName (this, "Load Tasks", "", "Text Files (*.txt);;All Files (*)");
  if (fileName.isEmpty ())
    {
      return;
    }

  QFile file (fileName);
  if (file.open (QFile::ReadOnly | QFile::Text))
    {
      QTextStream in (&file);
      taskList->clear ();
      while (!in.atEnd ())
        {
          QString line = in.readLine ();
          QStringList parts = line.split ("|");
          if (parts.size () == 3)
            {
              QListWidgetItem *item = new QListWidgetItem (parts[0], taskList);
              item->setFlags (item->flags () | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
              item->setCheckState (parts[1] == "1" ? Qt::Checked : Qt::Unchecked);
              item->setData (Qt::UserRole, parts[2]);
              if (!parts[2].isEmpty ())
                {
                  item->setText (QString ("%2").arg (parts[0]));
                  item->setForeground (Qt::blue);
                  item->setToolTip (parts[2]);
                }
            }
        }
      file.close ();
    }
  else
    {
      QMessageBox::warning (this, "Error", "Cannot load tasks");
    }
}
void ToDoList::editTask (QListWidgetItem *item) { taskList->editItem (item); }

void ToDoList::showContextMenu (const QPoint &pos)
{
  QListWidgetItem *item = taskList->itemAt (pos);
  if (item)
    {
      QMenu contextMenu;
      contextMenu.setStyleSheet("background-color: #2b2b2b; color: #a9b7c6;");
      QAction *changeColorAction = contextMenu.addAction ("Изменить цвет");
      QAction *changeFontSizeAction = contextMenu.addAction ("Изменить размер шрифта");
      QAction *editAction = contextMenu.addAction ("Редактировать");
      connect (editAction, &QAction::triggered, [this, item]() { editTask(item); });
      connect (changeColorAction, &QAction::triggered, this, &ToDoList::changeTaskColor);
      connect (changeFontSizeAction, &QAction::triggered, this, &ToDoList::changeFontSize);
      contextMenu.exec (taskList->mapToGlobal (pos));
    }
}

void ToDoList::changeTaskColor ()
{
  QListWidgetItem *item = taskList->currentItem ();
  if (item)
    {
      QColor color = QColorDialog::getColor (item->foreground ().color (), this, "Выберите цвет");
      if (color.isValid ())
        {
          item->setForeground (color);
        }
    }
}
void ToDoList::changeFontSize ()
{
  QListWidgetItem *item = taskList->currentItem ();
  if (item)
    {
      bool ok;
      int fontSize
          = QInputDialog::getInt (this, "Изменить размер шрифта", "Введите размер шрифта:", item->font ().pointSize (), 1, 100, 1, &ok);
      if (ok)
        {
          QFont font = item->font ();
          font.setPointSize (fontSize);
          item->setFont (font);
        }
    }
}

void ToDoList::searchTasks (const QString &text)
{
  for (int i = 0; i < taskList->count (); ++i)
    {
      QListWidgetItem *item = taskList->item (i);
      item->setHidden (!item->text ().contains (text, Qt::CaseInsensitive));
    }
}

void ToDoList::addTaskWithLink ()
{
  QString task = taskInput->text ();
  if (!task.isEmpty ())
    {
      bool ok;
      QString link = QInputDialog::getText (this, "Add Link", "Enter number of tickets", QLineEdit::Normal, "", &ok);
      if (ok && !link.isEmpty ())
        {
          QListWidgetItem *item = new QListWidgetItem (task, taskList);
          auto full_link = "https://redmine.rfdyn.ru/issues/" + link;
          item->setData (Qt::UserRole, full_link);
          item->setFlags (item->flags () | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
          item->setCheckState (Qt::Unchecked);
          item->setText (QString ("%1 - %2").arg (link, task));
          item->setForeground (QColor("#00bfff"));
          item->setToolTip (link);
          taskInput->clear ();
        }
    }
}

void ToDoList::openLink (QListWidgetItem *item)
{
  QString link = item->data (Qt::UserRole).toString ();
  if (!link.isEmpty ())
    {
      QDesktopServices::openUrl (QUrl (link));
    }
}




// Include the MOC file
#include "moc_ToDoList.cpp"