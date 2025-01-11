#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include "TemplateDialog.h"
#include <QLabel>

class AboutDialog : public TemplateDialog<AboutDialog>
{
public:
  void initUi ();
  void copyAndClose ();
  void create_buttons ();
  explicit AboutDialog(QWidget *parent = nullptr, const Theme &theme = darkTheme, std::bitset<4> buttonVisibility = std::bitset<4>("1000"), const QString &title = "About");
private:
  QLabel *descriptionLabel{};
  QPushButton *copyButton{};
  QPushButton *closeButton{};
};

#endif // ABOUTDIALOG_H