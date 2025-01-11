#include "CustomListWidget.h"

CustomListWidget::CustomListWidget (QWidget *parent) : QListWidget (parent) {}

void CustomListWidget::mousePressEvent (QMouseEvent *event)
{
  if (event->button () == Qt::LeftButton)
    {
      if (QListWidgetItem *item = itemAt (event->pos ()))
        {
          QRect checkboxRect = visualItemRect (item);
          checkboxRect.setWidth (style ()->pixelMetric (QStyle::PM_IndicatorWidth));
          if (checkboxRect.contains (event->pos ()))
            {
              // Обработка нажатия на чекбокс
              item->setCheckState (item->checkState () == Qt::Checked ? Qt::Unchecked : Qt::Checked);
              event->ignore ();
              return;
            }
        }
    }
  QListWidget::mousePressEvent (event);
}


// Включите сгенерированный MOC файл
#include "moc_CustomListWidget.cpp"
