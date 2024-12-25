#ifndef CUSTOMLISTWIDGET_H
#define CUSTOMLISTWIDGET_H

#include <QListWidget>
#include <QMouseEvent>

class CustomListWidget : public QListWidget
{
  Q_OBJECT

public:
  explicit CustomListWidget(QWidget *parent = nullptr);

protected:
  void mousePressEvent(QMouseEvent *event) override;
};

#endif // CUSTOMLISTWIDGET_H