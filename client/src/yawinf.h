#ifndef YAWINF_H
#define YAWINF_H

#include <QWidget>

namespace Ui {
class yawinf;
}

class yawinf : public QWidget
{
    Q_OBJECT

public:
    explicit yawinf(QWidget *parent = nullptr);
    ~yawinf();

private:
    Ui::yawinf *ui;
};

#endif // YAWINF_H
