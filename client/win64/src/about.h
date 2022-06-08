#ifndef ABOUT_H
#define ABOUT_H

#include <QWidget>
#include <QDesktopServices>
#include <QUrl>

namespace Ui {
class about;
}

class about : public QWidget
{
    Q_OBJECT

public:
    explicit about(QWidget *parent = nullptr);
    ~about();

private slots:
    void on_pushButton_clicked();

    void on_commandLinkButton_clicked();

private:
    Ui::about *ui;
};

#endif // ABOUT_H
