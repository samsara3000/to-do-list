#include "AboutDialog.h"
#include "TemplateDialog.inl"

#include <QApplication>
#include <QClipboard>
#include <QVBoxLayout>

void AboutDialog::initUi ()
{
  descriptionLabel = new QLabel (bodyWidget);  // Создаём содержимое внутри bodyWidget
  descriptionLabel->setTextFormat (Qt::RichText);
  descriptionLabel->setText (
      "Information about the application<br>"
      "GitHub: <a href=\"https://github.com/samsara3000/to-do-list\" "
      "style=\"color:#5c7cfa;\">https://github.com/samsara3000/to-do-list</a>");
  descriptionLabel->setOpenExternalLinks (true);
  descriptionLabel->setStyleSheet ("QLabel { color: #ABB2BF; font-size: 12px;}");

  auto *bodyLayout = new QVBoxLayout (bodyWidget);
  bodyLayout->addWidget (descriptionLabel);


  auto *buttonsLayout = new QHBoxLayout ();
  buttonsLayout->setContentsMargins (2, 2, 2, 2);  // Отступы вокруг кнопок
  buttonsLayout->setSpacing (10);                  // Расстояние между кнопками
  buttonsLayout->addStretch ();
  buttonsLayout->addWidget (copyButton);
  buttonsLayout->addWidget (closeButton);

  bodyLayout->addLayout (buttonsLayout);
}

void AboutDialog::copyAndClose ()
{
  const auto clipboard = QApplication::clipboard ();
  clipboard->setText ("https://github.com/samsara3000/to-do-list");
  this->close ();
}

void AboutDialog::create_buttons ()
{
  const auto style = getPushButtonStyle ();
  closeButton = new QPushButton (bodyWidget);
  closeButton->setText ("Close");
  closeButton->setStyleSheet (style);
  closeButton->setFixedSize (90, 27);
  connect (closeButton, &QPushButton::clicked, this, &QDialog::close);

  copyButton = new QPushButton (bodyWidget);
  copyButton->setText ("Copy and Close");
  copyButton->setStyleSheet (style);
  copyButton->setFixedSize (90, 27);
  connect (copyButton, &QPushButton::clicked, this, &AboutDialog::copyAndClose);
}

AboutDialog::AboutDialog (QWidget *parent, const Theme &theme, std::bitset<4> buttonVisibility, const QString &title)
  : TemplateDialog (parent, theme, buttonVisibility, title)
{
  create_buttons ();
  initUi ();
}
