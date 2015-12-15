#include "lparlabel.h"

LparLabel::LparLabel(QWidget *parent, Lpar * correlated_lpar) :
    QLabel(parent)
{
    setMouseTracking(true);
    my_lpar = correlated_lpar;

}

void LparLabel::mousePressEvent ( QMouseEvent * event )
{
    emit lpar_focus(my_lpar->getServer());
}

void LparLabel::mouseMoveEvent ( QMouseEvent * e ){
    emit hovered("PHYSICAL SERVER\n\n"+my_lpar->toString());

}


