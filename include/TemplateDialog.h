#ifndef TEMPLATEDIALOG_H
#define TEMPLATEDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QMouseEvent>
#include <QToolButton>
#include <bitset>

struct Theme
{
  // Общие стили
  QString backgroundColor;
  QString textColor;

  // Стили для QLabel
  QString labelTextColor;
  QString labelFontSize;

  // Стили для QDialog
  QString dialogBackgroundColor;
  QString dialogTextColor;

  // Стили для заголовка (Title Bar)
  QString titleBarBackgroundColor;
  QString titleBarTextColor;
  QString titleBarFontSize;

  // Стили для кнопки закрытия
  QString buttonBackgroundColor;
  QString buttonTextColor;
  QString buttonHoverColor;
  QString buttonBorder;

  // Стили для ToolTip
  QString toolTipBackgroundColor;
  QString toolTipTextColor;
  QString toolTipBorderColor;
};

// Пример темной темы
const Theme darkTheme{
    // Общие стили
    "#21252b",  // backgroundColor
    "#ffffff",  // textColor

    // Стили для QLabel
    "#ffffff",  // labelTextColor
    "12px",     // labelFontSize

    // Стили для QDialog
    "#282c34",  // dialogBackgroundColor
    "#ffffff",  // dialogTextColor

    // Стили для заголовка (Title Bar)
    "#282c34",  // titleBarBackgroundColor
    "#ffffff",  // titleBarTextColor
    "14px",     // titleBarFontSize

    // Стили для кнопки закрытия
    "#282c34",  // buttonBackgroundColor
    "#ffffff",  // buttonTextColor
    "#3c3f41",  // buttonHoverColor
    "none",     // buttonBorder

    // Стили для ToolTip
    "#282c34",  // toolTipBackgroundColor
    "#ffffff",  // toolTipTextColor
    "#3c3f41"   // toolTipBorderColor
};
enum class icons
{
  to_do,
  main_menu,
  minimize,
  maximize,
  close,
  none
};

inline QString get_icon_path (const icons icon)
{
  switch (icon)
    {
      case icons::to_do:
        return ":/icons/to_do.png";
      case icons::main_menu:
        return ":/icons/settings.png";
      case icons ::minimize:
        return ":/icons/header/minimize.png";
      case icons::maximize:
        return ":/icons/header/maximize.png";
      case icons::close:
        return ":/icons/header/close.png";
      case icons::none:
        return "";
    }
  return "";
}

inline QString get_tool_tip (const icons icon)
{
  switch (icon)
    {
      case icons::to_do:
        return "";
      case icons::main_menu:
        return "Main Menu";
      case icons ::minimize:
        return "Minimize";
      case icons::maximize:
        return "Maximize";
      case icons::close:
        return "Close";
      case icons::none:
        return "";
    }
  return "";
}

template<typename T>
class TemplateDialog : public QDialog
{
  void addIcon (int index, icons icon) const;
  void createButtons ();
  void createButtonsConnections ();
  QLabel *createIconLabel (QWidget *titleBar) const;
  QLabel *createTitleLabel (QWidget *titleBar) const;
  [[nodiscard]] QToolButton *getButtonByIndex (int index) const;

  void initUi ();
  void setButtonVisible (std::bitset<4> buttonVisibility) const;
  void setCustomStyleSheet ();
  void setMenu (QMenu *menu) const;
  void setTitle (const QString &title);
  void setTitleBarStyleSheet (QWidget *titleBar) const;

public:
  [[nodiscard]] QString getButtonStyle () const;
  [[nodiscard]] QString getPushButtonStyle () const;
  explicit TemplateDialog (
      QWidget *parent = nullptr, const Theme &theme = darkTheme, std::bitset<4> buttonVisibility = std::bitset<4> ("1000"),
      const QString &title = "Title");

protected:
  void mousePressEvent (QMouseEvent *event) override;
  void mouseMoveEvent (QMouseEvent *event) override;
  QWidget * bodyWidget;

private:
  QToolButton *mainMenuButton;
  QToolButton *minimizeButton;
  QToolButton *maximizeButton;
  QToolButton *closeButton;
  QPoint m_dragPosition;
  QWidget *createTitleBar ();

  int ButtonSize = 20;
  int buttonWidth = 22;
  int marginsSize = 5;
  const Theme &m_theme;
  const QString &m_title;
};

#endif  // TEMPLATEDIALOG_H