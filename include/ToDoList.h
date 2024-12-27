#ifndef TODOLIST_H
#define TODOLIST_H
#include "CustomListWidget.h"
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>

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
  void addTask () const;
  void removeTask () const;
  void saveTasks ();
  void loadTasks ();
  void editTask (QListWidgetItem *item) const;
  void changeTaskColor ();
  void changeFontSize ();
  void showContextMenu (const QPoint &pos);
  void searchTasks (const QString &text) const;
  void addTaskWithLink ();
  static void openLink (const QListWidgetItem *item);

private:
  void createWidgets ();
  void createLayout ();
  void createConnections ();

  CustomListWidget *taskList{};
  QLineEdit *taskInput{};
  QLineEdit *searchInput{};
  QToolButton *addButton{};
  QToolButton *removeButton{};
  QToolButton *saveButton{};
  QToolButton *loadButton{};
  QToolButton *addLinkButton{};
};

#endif  // TODOLIST_H