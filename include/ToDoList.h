#ifndef TODOLIST_H
#define TODOLIST_H
#include "CustomListWidget.h"
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QObject>
#include <QToolButton>
enum class buttons
{
  add,
  remove,
  save,
  load,
  add_link,
  none
};

class ToDoList : public QMainWindow
{
  Q_OBJECT

public:
  explicit ToDoList (QWidget *parent = nullptr);

private slots:
  void addTask ();
  void removeTask ();
  void saveTasks ();
  void loadTasks ();
  void editTask (QListWidgetItem *item);
  void changeTaskColor ();
  void changeFontSize ();
  void showContextMenu (const QPoint &pos);
  void searchTasks (const QString &text);
  void addTaskWithLink ();
  void openLink (QListWidgetItem *item);

private:
  void createWidgets ();
  void createLayout ();
  void createConnections ();

  CustomListWidget *taskList;
  QLineEdit *taskInput;
  QLineEdit *searchInput;
  QToolButton *addButton;
  QToolButton *removeButton;
  QToolButton *saveButton;
  QToolButton *loadButton;
  QToolButton *addLinkButton;
};

#endif  // TODOLIST_H