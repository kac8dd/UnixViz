#ifndef LPARBUTTON_H
#define LPARBUTTON_H

#include <QPushButton>
#include <lpar.h>

class LparButton : public QPushButton
{
    Q_OBJECT
public:
    LparButton(QWidget *parent, Lpar * correlated_lpar);
    Lpar *  my_lpar;

    void mouseMoveEvent(QMouseEvent * e);

signals:
    void lpar_focus(Server * param);
    void hovered(std::string param);

public slots:
    void handleButton();

};

#endif // LPARBUTTON_H
