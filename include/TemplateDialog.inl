#ifndef TEMPLATE_DIALOG_INL
#define TEMPLATE_DIALOG_INL
#include "TemplateDialog.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QToolButton>

// Структура для хранения параметров общей темы оформления

template<typename T>
void TemplateDialog<T>::setCustomStyleSheet ()
{
  const auto styleSheet = QString (
                              "background-color: %1; color: %2;"
                              "QLabel {"
                              "color: %3;"
                              "font-size: %4;"
                              "}"
                              "QDialog {"
                              "background-color: %5; color: %6;"
                              "}")
                              .arg (m_theme.backgroundColor)
                              .arg (m_theme.textColor)
                              .arg (m_theme.labelTextColor)
                              .arg (m_theme.labelFontSize)
                              .arg (m_theme.dialogBackgroundColor)
                              .arg (m_theme.dialogTextColor);
  setStyleSheet (styleSheet);
}

template<typename T>
void TemplateDialog<T>::initUi ()
{
  auto *layout = new QVBoxLayout (this);
  layout->setContentsMargins (0, 0, 0, 0);
  layout->setSpacing (0);
  layout->addWidget (createTitleBar ());

  bodyWidget = new QWidget (this);
  layout->addWidget (bodyWidget);
}

template<typename T>
QToolButton *TemplateDialog<T>::getButtonByIndex (int index) const
{
  switch (index)
    {
      case 0:
        return mainMenuButton;
      case 3:
        return closeButton;
      case 2:
        return maximizeButton;
      case 1:
        return minimizeButton;

      default:
        return nullptr;
    }
}

template<typename T>
void TemplateDialog<T>::setButtonVisible (const std::bitset<4> buttonVisibility) const
{
  for (int i = 0; i < 4; i++)
    getButtonByIndex (i)->setVisible (buttonVisibility.test (i));
}

template<typename T>
TemplateDialog<T>::TemplateDialog (QWidget *parent, const Theme &theme, const std::bitset<4> buttonVisibility, const QString &title)
  : QDialog (parent), m_theme (theme), m_title (title)
{
  setWindowFlags (Qt::FramelessWindowHint | Qt::Window);
  setCustomStyleSheet ();
  initUi ();
  setButtonVisible (buttonVisibility);
}

template<typename T>
void TemplateDialog<T>::setTitle (const QString &title)
{
  setWindowTitle (title);
}

template<typename T>
void TemplateDialog<T>::setTitleBarStyleSheet (QWidget *titleBar) const
{
  titleBar->setStyleSheet ("background-color: " + m_theme.titleBarBackgroundColor + "; color: " + m_theme.titleBarTextColor + ";");
}

template<typename T>
QString TemplateDialog<T>::getButtonStyle () const
{
  auto str = "QToolButton { "
             "background-color: "
             + m_theme.buttonBackgroundColor
             + "; "
               "color: "
             + m_theme.buttonTextColor
             + "; "
               "border: "
             + m_theme.buttonBorder
             + "; "
               "} "
               "QToolButton:hover { "
               "background-color: "
             + m_theme.buttonHoverColor
             + "; "
               "} "
               "QToolButton::menu-indicator { "
               "image: none; "
               "} "
               "QToolTip { "
               "background-color: "
             + m_theme.toolTipBackgroundColor
             + "; "
               "color: "
             + m_theme.toolTipTextColor
             + "; "
               "border: 1px solid "
             + m_theme.toolTipBorderColor
             + "; "
               "}";
  return str;
}

template<typename T>
QString TemplateDialog<T>::getPushButtonStyle () const
{
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
  return buttonStyle;
}

template<typename T>
QLabel *TemplateDialog<T>::createIconLabel (QWidget *titleBar) const
{
  auto *iconLabel = new QLabel (titleBar);

  const QIcon icon (get_icon_path (icons::to_do));
  const QPixmap pixmap = icon.pixmap (ButtonSize, ButtonSize);

  iconLabel->setPixmap (pixmap);
  return iconLabel;
}

template<typename T>
QLabel *TemplateDialog<T>::createTitleLabel (QWidget *titleBar) const
{
  const auto titleLabel = new QLabel (m_title, titleBar);
  titleLabel->setStyleSheet (
      " color: " + m_theme.titleBarTextColor
      + ";"
        " font-size: "
      + m_theme.titleBarFontSize + ";");
  return titleLabel;
}

template<typename T>
void TemplateDialog<T>::addIcon (const int index, const icons icon) const
{
  const auto button = getButtonByIndex (index);
  const QIcon buttonIcon (get_icon_path (icon));
  button->setIcon (buttonIcon);
  button->setIconSize (QSize (ButtonSize, ButtonSize));
  button->setToolTip (get_tool_tip (icon));
  const QString buttonStyle = getButtonStyle ();
  button->setStyleSheet (buttonStyle);
}

template<typename T>
void TemplateDialog<T>::createButtons ()
{
  closeButton = new QToolButton (this);
  minimizeButton = new QToolButton (this);
  maximizeButton = new QToolButton (this);
  mainMenuButton = new QToolButton (this);
  addIcon (0, icons::main_menu);
  addIcon (1, icons::minimize);
  addIcon (2, icons::maximize);
  addIcon (3, icons::close);
}

template<typename T>
void TemplateDialog<T>::createButtonsConnections ()
{
  connect (closeButton, &QPushButton::clicked, this, &QDialog::close);
  connect (minimizeButton, &QToolButton::clicked, this, &QDialog::showMinimized);
  connect (maximizeButton, &QToolButton::clicked, this, &QDialog::showMaximized);
}

template<typename T>
void TemplateDialog<T>::setMenu (QMenu *menu) const
{
  mainMenuButton->setMenu (menu);
  mainMenuButton->setPopupMode (QToolButton::InstantPopup);
}

template<typename T>
QWidget *TemplateDialog<T>::createTitleBar ()
{
  auto titleBar = new QWidget (this);
  setTitleBarStyleSheet (titleBar);

  auto *titleLayout = new QHBoxLayout (titleBar);
  titleLayout->setContentsMargins (2, 2, 2, 2);

  createButtons ();
  createButtonsConnections ();

  titleLayout->addWidget (createIconLabel (titleBar));
  titleLayout->addWidget (createTitleLabel (titleBar), 1);
  for (int i = 0; i < 4; i++)
    titleLayout->addWidget (getButtonByIndex (i));
  titleBar->setFixedHeight (30);

  return titleBar;
}

template<typename T>
void TemplateDialog<T>::mousePressEvent (QMouseEvent *event)
{
  if (event->button () == Qt::LeftButton)
    {
      m_dragPosition = event->globalPosition ().toPoint () - frameGeometry ().topLeft ();
      event->accept ();
    }
}

template<typename T>
void TemplateDialog<T>::mouseMoveEvent (QMouseEvent *event)
{
  if (event->buttons () & Qt::LeftButton)
    {
      move (event->globalPosition ().toPoint () - m_dragPosition);
      event->accept ();
    }
}

#endif // TEMPLATE_DIALOG_INL