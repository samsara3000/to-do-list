#ifndef TODOLIST_H
#define TODOLIST_H
#include "CustomListWidget.h"
#include "SettingsDialog.h"
#include "AboutDialog.h"
#include <QLineEdit>
#include <QListWidget>
#include <QMainWindow>
#include <QStack>

enum class buttons
{
  add,
  remove,
  save,
  load,
  add_link,
  main_menu,
  minimize,
  maximize,
  close,
  none
};

class ToDoList : public QMainWindow
{
  Q_OBJECT

public:
  explicit ToDoList (QWidget *parent = nullptr);
  static void add_icon (QToolButton *button, buttons button_type);
  void createHeaderWidget ();


public slots:
  void undo ();
  void redo ();
private slots:
  void addTask ();
  void removeTask ();
  void saveTasks ();
  void loadTasks ();
  void editTask (QListWidgetItem *item);
  void changeTaskColor ();
  void changeFontSize ();
  void showContextMenu (const QPoint &pos);
  void searchTasks (const QString &text) const;
  void addTaskWithLink ();
  static void openLink (const QListWidgetItem *item);
  void showAbout ();
  void openSettings ();

private:
  void applyState (const QStringList &state) const;
  void createWidgets ();
  void createLayout ();
  void createConnections ();
  [[nodiscard]] QStringList getCurrentState () const;
  void save_state ();

  CustomListWidget *taskList{};
  QLineEdit *taskInput{};
  QLineEdit *searchInput{};
  QToolButton *addButton{};
  QToolButton *removeButton{};
  QToolButton *saveButton{};
  QToolButton *loadButton{};
  QToolButton *addLinkButton{};

  QToolButton *mainMenuButton{};
  QToolButton *minimizeButton{};
  QToolButton *maximizeButton{};
  QToolButton *closeButton{};

  QStack<QStringList> undoStack;
  QStack<QStringList> redoStack;
  bool dragging = false;
  QPoint dragStartPosition;

  int buttonSize = 20;
  int marginsSize = 5;

  QString linkPrefix = "https://redmine.rfdyn.ru/issues/";

protected:
  void keyPressEvent (QKeyEvent *event) override;
  void paintEvent (QPaintEvent *event) override;
  void drawHeader (QPainter *painter) const;
  void drawIcon (QPainter *painter, const QString &iconPath, const QRect &rect) const;
  void drawIcon (QPainter *painter, const QString &iconPath, const QRect &rect);
  void drawButtons () const;
  void mousePressEvent (QMouseEvent *event) override;
  void mouseMoveEvent (QMouseEvent *event) override;
  void mouseReleaseEvent (QMouseEvent *event) override;
};

#endif  // TODOLIST_H