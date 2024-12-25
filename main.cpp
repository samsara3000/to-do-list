#include "ToDoList.h"

#include <QApplication>

int main (int argc, char *argv[])
{
  QApplication app (argc, argv);
  ToDoList toDoList;
  toDoList.show ();
  return app.exec ();
}