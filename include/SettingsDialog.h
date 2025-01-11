#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QLabel>

class SettingsDialog : public QDialog {
    Q_OBJECT

public:
    explicit SettingsDialog(QWidget *parent = nullptr, const QString &currentLinkPrefix = "");
    QString getLinkPrefix() const;

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QLineEdit *linkPrefixEdit;
    QLineEdit *currentLinkEdit;
    QPoint m_dragPosition; // Для перемещения окна
    QWidget *createTitleBar(); // Метод для создания кастомного заголовка
    int ButtonSize = 20;
};

#endif // SETTINGSDIALOG_H
