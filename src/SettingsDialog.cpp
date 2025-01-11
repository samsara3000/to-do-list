#include "SettingsDialog.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QPainter>
#include <QStyleOption>
#include <QToolButton>

SettingsDialog::SettingsDialog (QWidget *parent, const QString &currentLinkPrefix) : QDialog (parent)
{
  setWindowFlags (Qt::FramelessWindowHint | Qt::Window);  // Убираем стандартный заголовок
  setWindowTitle ("Settings");

  setFixedSize (QSize (250, 200));
  auto *layout = new QVBoxLayout (this);
  layout->setContentsMargins (0, 0, 0, 0);
  layout->setSpacing (0);
  // Создаем кастомный заголовок
  layout->addWidget (createTitleBar ());
  const QColor focusColor (0x5c7cfa);
  auto *currentLinkLabel = new QLabel ("Current Link Prefix:", this);
  currentLinkLabel->setStyleSheet ("font-size: 11px;");
  currentLinkEdit = new QLineEdit (this);
  currentLinkEdit->setText (currentLinkPrefix);
  currentLinkEdit->setReadOnly (true);
  auto lineEditStyle = QStringLiteral (
                           "QLineEdit {"
                           "background-color: #282c34; color: #a9b7c6; "
                           "border: 1px solid #3c3f41; "
                           "border-radius: 3px; "
                           "padding: 2px; "
                           "margin: 0px; "
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
                           .arg (focusColor.name ());
  currentLinkEdit->setStyleSheet (lineEditStyle);

  auto *newLinkLabel = new QLabel ("New Link Prefix:", this);
  newLinkLabel->setStyleSheet ("font-size: 11px;");
  linkPrefixEdit = new QLineEdit (this);
  linkPrefixEdit->setPlaceholderText ("Enter new link prefix...");
  linkPrefixEdit->setStyleSheet (lineEditStyle);

  auto *okButton = new QPushButton ("Apply", this);
  connect (okButton, &QPushButton::clicked, this, &QDialog::accept);

  auto *cancelButton = new QPushButton ("Cancel", this);
  connect (cancelButton, &QPushButton::clicked, this, &QDialog::close);

  // Настройка размеров кнопок
  okButton->setFixedSize (60, 27);  // Устанавливаем фиксированные размеры
  cancelButton->setFixedSize (60, 27);

  // Стили для кнопок
  const QString buttonStyle = "QPushButton {"
                              "    background-color: #3c3f41; color: white;"
                              "    border: 1px solid #555555; border-radius: 5px;"
                              "    font-size: 12px;"  // Уменьшенный шрифт для соответствия размеру
                              "}"
                              "QPushButton:hover {"
                              "    background-color: #4c4f51;"
                              "}"
                              "QPushButton:pressed {"
                              "    background-color: #2c2f31;"
                              "}";

  okButton->setStyleSheet (buttonStyle);
  cancelButton->setStyleSheet (buttonStyle);

  // Размещение кнопок
  auto *buttonsLayout = new QHBoxLayout ();
  buttonsLayout->setContentsMargins (2, 2, 2, 2);  // Отступы вокруг кнопок
  buttonsLayout->setSpacing (10);                  // Расстояние между кнопками
  buttonsLayout->addStretch ();
  buttonsLayout->addWidget (okButton);
  buttonsLayout->addWidget (cancelButton);

  auto *contentLayout = new QVBoxLayout ();
  // contentLayout->setContentsMargins(0, 0, 0, 0); // Устанавливаем отступы в 0
  contentLayout->setSpacing (0);
  contentLayout->addWidget (currentLinkLabel);
  contentLayout->addWidget (currentLinkEdit);
  contentLayout->addWidget (newLinkLabel);
  contentLayout->addWidget (linkPrefixEdit);
  contentLayout->addSpacing (10);
  contentLayout->addLayout (buttonsLayout);

  auto *contentWidget = new QWidget (this);
  contentWidget->setLayout (contentLayout);
  layout->addWidget (contentWidget);

  // Стили
  setStyleSheet (
      "background-color: #21252b; color: #ffffff;"
      "QLabel {"
      "color: #ffffff;"
      "font-size: 11px;"
      "}"
      "QDialog {"
      "background-color: #282c34; color: #ffffff;"
      "}"
      "QLineEdit {"

      "background-color: #404859; color: #ffffff;"
      "border: 1px solid #3c3f41; border-radius: 3px; padding: 2px;"
      "}"
      "QPushButton {"
      "background-color: #3c3f41; color: #ffffff; border: none; padding: 5px;"
      "}"
      "QPushButton:hover {"
      "background-color: #4c4f51;"
      "}");
}

QWidget *SettingsDialog::createTitleBar ()
{
  auto *titleBar = new QWidget (this);
  titleBar->setStyleSheet ("background-color: #282c34; color: white;");  // Цвет как у окна

  auto *layout = new QHBoxLayout (titleBar);
  layout->setContentsMargins (2, 2, 2, 2);  // Уменьшенные отступы

  // Иконка
  auto *iconLabel = new QLabel (titleBar);
  QIcon icon (":/icons/to_do.png");
  QPixmap pixmap = icon.pixmap (ButtonSize, ButtonSize);
  iconLabel->setPixmap (pixmap);

  auto *titleLabel = new QLabel ("Settings", titleBar);
  titleLabel->setStyleSheet ("color: white; font-size: 14px;");

  auto *closeButton = new QToolButton (this);
  QIcon close_icon (":/icons/header/close.png");
  closeButton->setIcon (close_icon);
  closeButton->setIconSize (QSize (ButtonSize, ButtonSize));
  closeButton->setToolTip ("Close");
  const QString buttonStyle = "QToolButton { background-color: #282c34; color: #ffffff; border: none; }"
                              "QToolButton:hover { background-color: #3c3f41; }"
                              "QToolButton::menu-indicator { image: none; }"
                              "QToolTip { background-color: #282c34; color: #ffffff; border: 1px solid #3c3f41; }";
  closeButton->setStyleSheet (buttonStyle);
  connect (closeButton, &QPushButton::clicked, this, &QDialog::close);

  layout->addWidget (iconLabel);
  layout->addWidget (titleLabel, 1);
  layout->addWidget (closeButton);

  titleBar->setFixedHeight (30);  // Высота заголовка

  return titleBar;
}

QString SettingsDialog::getLinkPrefix () const { return linkPrefixEdit->text (); }

void SettingsDialog::mousePressEvent (QMouseEvent *event)
{
  if (event->button () == Qt::LeftButton)
    {
      m_dragPosition = event->globalPosition ().toPoint () - frameGeometry ().topLeft ();
      event->accept ();
    }
}

void SettingsDialog::mouseMoveEvent (QMouseEvent *event)
{
  if (event->buttons () & Qt::LeftButton)
    {
      move (event->globalPosition ().toPoint () - m_dragPosition);
      event->accept ();
    }
}


// Include the generated MOC file
#include "moc_SettingsDialog.cpp"