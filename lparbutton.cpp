#include "lparbutton.h"

LparButton::LparButton(QWidget *parent, Lpar * correlated_lpar) :
    QPushButton(parent)
{
    connect(this, SIGNAL(released()), this, SLOT(handleButton()));
    my_lpar = correlated_lpar;

    setMouseTracking(true);

}

void LparButton::handleButton(){
    emit lpar_focus(my_lpar->getServer());
}

void LparButton::mouseMoveEvent(QMouseEvent *e){
    emit hovered("Logical Partition\n\n"+my_lpar->toString());
}
