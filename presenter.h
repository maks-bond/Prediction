#ifndef PRESENTER_H
#define PRESENTER_H

#include <QWidget>

namespace Ui {
class Presenter;
}

class Presenter : public QWidget
{
    Q_OBJECT
    
public:
    explicit Presenter(QWidget *parent = 0);
    ~Presenter();
    
private:
    Ui::Presenter *ui;
};

#endif // PRESENTER_H
