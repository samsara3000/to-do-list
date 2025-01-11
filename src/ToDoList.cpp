#include "ToDoList.h"

#include <QApplication>
#include <QColorDialog>
#include <QDesktopServices>
#include <QFileDialog>
#include <QInputDialog>
#include <QLabel>
#include <QMenu>
#include <QMessageBox>
#include <QPainter>
#include <QTextStream>
#include <QToolButton>
#include <QVBoxLayout>
#include <iostream>

QString get_icon_path (const buttons button)
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
      case buttons::maximize:
        return ":/icons/header/maximize.png";
      case buttons::minimize:
        return ":/icons/header/minimize.png";
      case buttons::close:
        return ":/icons/header/close.png";
      case buttons::main_menu:
        return ":/icons/header/settings.png";
      case buttons::none:
        return "";
    };
  return "";
}

QString get_tool_tip_name (const buttons button)
{
  switch (button)
    {
      case buttons::add:
        return "Add Text Task";
      case buttons::remove:
        return "Delete Task";
      case buttons::save:
        return "Save Tasks to File";
      case buttons::load:
        return "Load Tasks from File";
      case buttons::add_link:
        return "Add Task with Redmine Link";
      case buttons::maximize:
        return "Maximize";
      case buttons::minimize:
        return "Minimize";
      case buttons::close:
        return "Close";
      case buttons::main_menu:
        return "Main Menu";
      case buttons::none:
        return "";
    };
  return "";
}

ToDoList::ToDoList (QWidget *parent) : QMainWindow (parent)
{
  setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
#ifdef _WIN32
  setAttribute (Qt::WA_PaintOnScreen, true);
#else
#endif
  setAttribute (Qt::WA_NoSystemBackground, false);

  QFont defaultFont = QApplication::font ();
  defaultFont.setPointSize (11);
  QApplication::setFont (defaultFont);
  createWidgets ();
  createLayout ();
  createConnections ();
  setWindowTitle ("To-Do List");

  // setMaximumSize (400, 300);
  //  Set the window to stay on top of all other windows
  setWindowFlags (windowFlags () | Qt::WindowStaysOnTopHint);

  const QIcon appIcon (":/icons/to_do.png");
  setWindowIcon (appIcon);
  // Set the background color to a dark theme similar to CLion
  setStyleSheet ("background-color: #21252b; color: #ffffff;");
  const QColor focusColor (0x5c7cfa);

  taskList->setStyleSheet (QStringLiteral (
                               "QListWidget {"
                               "background-color: #282c34; color: #a9b7c6; "
                               "border: 1px solid #3c3f41; "
                               "border-radius: 3px; "
                               "padding: 2px; "
                               "margin: 2px; "
                               "outline: none; "
                               "selection-background-color: #404859; "
                               "selection-color: #ffffff; "
                               "} "
                               "QListWidget:focus {"
                               "border: 1px solid %1; "
                               "} "
                               "QListWidget::item:hover {"
                               "    background-color: #404859;"
                               "}"
                               "QListWidget::item:selected:active {"
                               "background-color: #404859; "
                               "}"
                               "QLineEdit {"
                               "    background-color: #404859;"
                               "    color: #ffffff;"
                               "    border: none;"
                               "}")
                               .arg (focusColor.name ()));
  taskInput->setPlaceholderText ("Add new task...");
  taskInput->setStyleSheet (QStringLiteral (
                                "QLineEdit {"
                                "background-color: #282c34; color: #a9b7c6; "
                                "border: 1px solid #3c3f41; "
                                "border-radius: 3px; "
                                "padding: 2px; "
                                "margin: 2px; "
                                "outline: none; "
                                "selection-background-color: #404859; "
                                "selection-color: #ffffff; "
                                "} "
                                "QLineEdit:focus {"
                                "border: 1px solid %1; "
                                "} "
                                "QLineEdit::item:selected:active {"
                                "background-color: #404859; "
                                "}"
                                "QLineEdit:focus::placeholder {"
                                "font-size: 12px;"
                                "color: #a9b7c6;"
                                "}")
                                .arg (focusColor.name ()));
  searchInput->setPlaceholderText ("Search...");
  searchInput->setStyleSheet (QStringLiteral (
                                  "QLineEdit {"
                                  "background-color: #282c34; color: #a9b7c6; "
                                  "border: 1px solid #3c3f41; "
                                  "border-radius: 3px; "
                                  "padding: 2px; "
                                  "margin: 2px; "
                                  "outline: none; "
                                  "selection-background-color: #404859; "
                                  "selection-color: #ffffff; "
                                  "} "
                                  "QLineEdit:focus {"
                                  "border: 1px solid %1; "
                                  "} "
                                  "QLineEdit::item:selected:active {"
                                  "background-color: #404859; "
                                  "}"
                                  "QLineEdit:focus::placeholder {"
                                  "font-size: 12px;"
                                  "color: #a9b7c6;"
                                  "}")
                                  .arg (focusColor.name ()));

  addButton->setStyleSheet ("background-color: #21252b; color: #ffffff; padding: 0px; margin: 0px; border: none;");
  removeButton->setStyleSheet ("background-color: #21252b; color: #ffffff; padding: 0px; margin: 0px; border: none;");
  saveButton->setStyleSheet ("background-color: #21252b; color: #ffffff; padding: 0px; margin: 0px; border: none;");
  loadButton->setStyleSheet ("background-color: #21252b; color: #ffffff; padding: 0px; margin: 0px; border: none;");
  addLinkButton->setStyleSheet ("background-color: #21252b; color: #ffffff; padding: 0px; margin: 0px; border: none;");

  qApp->setStyleSheet (
      "QInputDialog {"
      "background-color: #282c34; color: #ffffff; "
      "} "
      "QColorDialog {"
      "background-color: #282c34; color: #ffffff; "
      "} "
      "QMessageBox {"
      "background-color: #282c34; color: #ffffff; "
      "} "
      "QMenu {"
      "background-color: #282c34; color: #ffffff; "
      "} "
      "QToolTip {"
      "background-color: #282c34; color: #ffffff; "
      "}");
  setStyleSheet (
      "QMainWindow {"
      "background-color: #21252b;"
      "}"
      "QListWidget {"
      "background-color: #282c34; color: #a9b7c6; "
      "border: 1px solid #3c3f41; "
      "border-radius: 3px; "
      "padding: 2px; "
      "margin: 2px; "
      "}");
}

void ToDoList::add_icon (QToolButton *button, buttons button_type)
{
  const QIcon icon (get_icon_path (button_type));
  button->setIcon (icon);
  button->setIconSize (QSize (30, 30));
  button->setToolTip (get_tool_tip_name (button_type));
}

void ToDoList::createHeaderWidget ()
{
  mainMenuButton = new QToolButton (this);
  add_icon (mainMenuButton, buttons::main_menu);
  minimizeButton = new QToolButton (this);
  add_icon (minimizeButton, buttons::minimize);
  maximizeButton = new QToolButton (this);
  add_icon (maximizeButton, buttons::maximize);
  closeButton = new QToolButton (this);
  add_icon (closeButton, buttons::close);

  const QString buttonStyle = "QToolButton { background-color: #282c34; color: #ffffff; border: none; }"
                              "QToolButton:hover { background-color: #323844; }"
                              "QToolButton::menu-indicator { image: none; }"
                              "QToolTip { background-color: #282c34; color: #ffffff; border: 1px solid #3c3f41; }";
  mainMenuButton->setStyleSheet (buttonStyle);
  minimizeButton->setStyleSheet (buttonStyle);
  maximizeButton->setStyleSheet (buttonStyle);
  closeButton->setStyleSheet (buttonStyle);

  auto menu = new QMenu (this);
  QIcon icon_settings (":/icons/header/settings_.png");
  QIcon icon_about (":/icons/header/about.png");
  menu->addAction (icon_settings, "Settings...", this, SLOT (openSettings ()));
  menu->addAction (icon_about, "About", this, SLOT (showAbout ()));
  menu->addSeparator ();
  menu->addAction ("Exit", this, SLOT (close ()));
  menu->setStyleSheet (
      "QMenu {"
      "    border: 1px solid #333841;" /* Задаем цвет рамки */
      "    margin: 0px;"               /* Убираем отступы вокруг меню для соединения с сепаратором */
      "}"
      "QMenu::separator {"
      "    height: 1px;"
      "    background: #333841;" /* Задаем тот же цвет, что и у рамки */
      "    margin: 0px;"         /* Убираем отступы, чтобы сепаратор соединялся с рамкой */
      "    padding: 0px;"
      "}"
      "QMenu::item:selected {"
      "    background-color: #323844;"
      "    color: white;"
      "    border-radius: 8px;" /* Округляем углы */
      "}");
  // Подключение меню к кнопке
  mainMenuButton->setMenu (menu);
  mainMenuButton->setPopupMode (QToolButton::InstantPopup);
}

void ToDoList::createWidgets ()
{
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

  createHeaderWidget ();
}

void ToDoList::createLayout ()
{
  auto *layout = new QVBoxLayout;
  layout->setContentsMargins (marginsSize, 33, marginsSize, marginsSize);
  layout->addWidget (searchInput);
  layout->addWidget (taskList);
  layout->addWidget (taskInput);
  auto *buttonLayout = new QHBoxLayout;
  buttonLayout->addWidget (loadButton);
  buttonLayout->addStretch ();
  buttonLayout->addWidget (addButton);
  buttonLayout->addWidget (addLinkButton);
  buttonLayout->addWidget (removeButton);
  buttonLayout->addStretch ();
  buttonLayout->addWidget (saveButton);


  layout->addLayout (buttonLayout);

  auto *centralWidget = new QWidget (this);
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
  connect (taskList, &CustomListWidget::itemDoubleClicked, this, &ToDoList::openLink);

  connect (minimizeButton, &QToolButton::clicked, this, [this] () { showMinimized (); });
  connect (closeButton, &QToolButton::clicked, this, [this] () { close (); });
}

void ToDoList::addTask ()
{
  save_state ();
  if (QString task = taskInput->text (); !task.isEmpty ())
    {
      auto item = new QListWidgetItem (task, taskList);
      item->setFlags (item->flags () | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
      item->setCheckState (Qt::Unchecked);
      taskInput->clear ();
    }
}

void ToDoList::removeTask ()
{
  save_state ();
  delete taskList->currentItem ();
}

void ToDoList::saveTasks ()
{
  save_state ();
  QString currentDate = QDateTime::currentDateTime ().toString ("dd_MM_yy");
#ifdef _WIN32
  // Ваше действие для Windows
#else
  currentDate = currentDate + ".txt";
#endif
  const QString fileName = QFileDialog::getSaveFileName (this, "Save Tasks", currentDate, "Text Files (*.txt);;All Files (*)");
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
  save_state ();
  const QString fileName = QFileDialog::getOpenFileName (this, "Load Tasks", "", "Text Files (*.txt);;All Files (*)");
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
          if (QStringList parts = line.split ("|"); parts.size () == 3)
            {
              auto *item = new QListWidgetItem (parts[0], taskList);
              item->setFlags (item->flags () | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
              item->setCheckState (parts[1] == "1" ? Qt::Checked : Qt::Unchecked);
              item->setData (Qt::UserRole, parts[2]);
              if (!parts[2].isEmpty ())
                {
                  item->setText (QString ("%2").arg (parts[0]));
                  item->setForeground (QColor (0x00bfff));
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

void ToDoList::editTask (QListWidgetItem *item)
{
  save_state ();
  taskList->editItem (item);
}

void ToDoList::showContextMenu (const QPoint &pos)
{
  if (QListWidgetItem *item = taskList->itemAt (pos))
    {
      QMenu contextMenu;
      contextMenu.setStyleSheet ("background-color: #21252b; color: #ffffff;");
      const QAction *changeColorAction = contextMenu.addAction ("Изменить цвет");
      const QAction *changeFontSizeAction = contextMenu.addAction ("Изменить размер шрифта");
      const QAction *editAction = contextMenu.addAction ("Редактировать");
      connect (editAction, &QAction::triggered, [this, item] () { editTask (item); });
      connect (changeColorAction, &QAction::triggered, this, &ToDoList::changeTaskColor);
      connect (changeFontSizeAction, &QAction::triggered, this, &ToDoList::changeFontSize);
      contextMenu.exec (taskList->mapToGlobal (pos));
    }
}

void ToDoList::changeTaskColor ()
{
  save_state ();
  if (QListWidgetItem *item = taskList->currentItem ())
    {
      if (const auto color = QColorDialog::getColor (item->foreground ().color (), this, "Выберите цвет"); color.isValid ())
        {
          item->setForeground (color);
        }
    }
}
void ToDoList::changeFontSize ()
{
  save_state ();
  if (QListWidgetItem *item = taskList->currentItem ())
    {
      bool ok;
      const auto fontSize
          = QInputDialog::getInt (this, "Изменить размер шрифта", "Введите размер шрифта:", item->font ().pointSize (), 1, 100, 1, &ok);
      if (ok)
        {
          QFont font = item->font ();
          font.setPointSize (fontSize);
          item->setFont (font);
        }
    }
}

void ToDoList::searchTasks (const QString &text) const
{
  for (int i = 0; i < taskList->count (); ++i)
    {
      QListWidgetItem *item = taskList->item (i);
      item->setHidden (!item->text ().contains (text, Qt::CaseInsensitive));
    }
}

void ToDoList::addTaskWithLink ()
{
  save_state ();
  if (QString task = taskInput->text (); !task.isEmpty ())
    {
      bool ok;
      if (QString link = QInputDialog::getText (this, "Add Link", "Enter number of tickets", QLineEdit::Normal, "", &ok);
          ok && !link.isEmpty ())
        {
          const auto item = new QListWidgetItem (taskList);
          auto full_link = linkPrefix + link;
          item->setData (Qt::UserRole, full_link);
          item->setFlags (item->flags () | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
          item->setCheckState (Qt::Unchecked);
          const QString coloredText = QString ("%1 - %2").arg (link, task);
          item->setText (coloredText);
          item->setForeground (QColor (0x00bfff));
          item->setToolTip (link);
          taskInput->clear ();
        }
    }
}

void ToDoList::openLink (const QListWidgetItem *item)
{
  if (const QString link = item->data (Qt::UserRole).toString (); !link.isEmpty ())
    {
      QDesktopServices::openUrl (QUrl (link));
    }
}

void ToDoList::undo ()
{
  if (!undoStack.isEmpty ())
    {
      redoStack.push (getCurrentState ());
      applyState (undoStack.pop ());
    }
}

void ToDoList::redo ()
{
  if (!redoStack.isEmpty ())
    {
      undoStack.push (getCurrentState ());
      applyState (redoStack.pop ());
    }
}

QStringList ToDoList::getCurrentState () const
{
  QStringList state;
  for (int i = 0; i < taskList->count (); ++i)
    {
      const QListWidgetItem *item = taskList->item (i);
      QString task = item->text ();
      QString link = item->data (Qt::UserRole).toString ();
      QString checked = (item->checkState () == Qt::Checked) ? "1" : "0";
      state << QString ("%1|%2|%3").arg (task, checked, link);
    }
  return state;
}

void ToDoList::applyState (const QStringList &state) const
{
  taskList->clear ();
  for (const QString &line : state)
    {
      if (QStringList parts = line.split ('|'); parts.size () == 3)
        {
          auto *item = new QListWidgetItem (parts[0], taskList);
          item->setFlags (item->flags () | Qt::ItemIsUserCheckable | Qt::ItemIsEditable);
          item->setCheckState (parts[1] == "1" ? Qt::Checked : Qt::Unchecked);
          item->setData (Qt::UserRole, parts[2]);
          if (!parts[2].isEmpty ())
            {
              item->setText (QString ("%1").arg (parts[0]));
              item->setForeground (QColor (0x00bfff));
              item->setToolTip (parts[2]);
            }
        }
    }
}

void ToDoList::save_state ()
{
  undoStack.push (getCurrentState ());
  redoStack.clear ();
}

void ToDoList::keyPressEvent (QKeyEvent *event)
{
  if (event->modifiers () & Qt::ControlModifier)
    {
      if (event->key () == Qt::Key_Z)
        {
          undo ();
          event->accept ();
          return;
        }
      else if (event->key () == Qt::Key_X)
        {
          redo ();
          event->accept ();
          return;
        }
    }
  QMainWindow::keyPressEvent (event);
}
void ToDoList::paintEvent (QPaintEvent *event)
{
  QMainWindow::paintEvent (event);  // Вызов базовой реализации

  QPainter painter (this);
  painter.setRenderHint (QPainter::Antialiasing);
  painter.setRenderHint (QPainter::TextAntialiasing);

  // Пользовательский код рисования
  drawHeader (&painter);
  drawButtons ();
}

void ToDoList::drawHeader (QPainter *painter) const
{
  const QRect headerRect (0, 0, width (), 30);
  painter->setBrush (QColor (0x282c34));
  painter->drawRect (headerRect);

  painter->setPen (QColor (0x283348));
  painter->drawRect (headerRect);

  drawIcon (painter, ":/icons/to_do.png", QRect (marginsSize, marginsSize, buttonSize, buttonSize));

  painter->setPen (QColor (0xffffff));
  painter->drawText (QRect (90, 0, width () - 100, 30), Qt::AlignVCenter, "To-Do List");
}

void ToDoList::drawIcon (QPainter *painter, const QString &iconPath, const QRect &rect) const
{
  QIcon icon (iconPath);
  QPixmap pixmap = icon.pixmap (buttonSize, buttonSize);
  painter->drawPixmap (rect, pixmap);
}

void ToDoList::drawButtons () const
{
  const int buttonWidth = buttonSize + 2;

  minimizeButton->setGeometry (width () - 2 * buttonWidth, marginsSize, buttonWidth, buttonSize);
  closeButton->setGeometry (width () - buttonWidth, marginsSize, buttonWidth, buttonSize);
  mainMenuButton->setGeometry (27, marginsSize, buttonSize, buttonSize);
  mainMenuButton->raise ();
  minimizeButton->raise ();
  closeButton->raise ();
  maximizeButton->raise ();
  maximizeButton->setVisible (false);
}


void ToDoList::mousePressEvent (QMouseEvent *event)
{
  if (event->button () == Qt::LeftButton && event->pos ().y () <= 30)
    {
      dragging = true;
      dragStartPosition = event->globalPosition ().toPoint () - frameGeometry ().topLeft ();
      event->accept ();
    }
}

void ToDoList::mouseMoveEvent (QMouseEvent *event)
{
  if (dragging)
    {
      move (event->globalPosition ().toPoint () - dragStartPosition);
      event->accept ();
    }
}

void ToDoList::mouseReleaseEvent (QMouseEvent *event)
{
  if (event->button () == Qt::LeftButton)
    {
      dragging = false;
      event->accept ();
    }
}

void ToDoList::openSettings ()
{
  SettingsDialog dialog (this, linkPrefix);
  if (dialog.exec () == QDialog::Accepted)
    {
      linkPrefix = dialog.getLinkPrefix ();
    }
}

void ToDoList::showAbout ()
{
  std::bitset<4> bitsetArg("1000");
  AboutDialog dialog (this, darkTheme, bitsetArg, "About To-Do List");
  dialog.exec();
}
// Include the MOC file
#include "moc_ToDoList.cpp"
