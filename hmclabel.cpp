#include "hmclabel.h"

HmcLabel::HmcLabel(QWidget *parent, Hmc* correlated_hmc) :
    QLabel(parent)
{

    setMouseTracking(true);
    my_hmc = correlated_hmc;
}

void HmcLabel::mousePressEvent ( QMouseEvent * event )
{
    emit hmc_focus(my_hmc);
}

void HmcLabel::mouseMoveEvent ( QMouseEvent * e ){
    emit hovered("HMC\n\n"+my_hmc->toString());

}


