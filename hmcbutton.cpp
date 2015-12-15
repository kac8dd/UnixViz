#include "hmcbutton.h"

HmcButton::HmcButton(QWidget *parent, Hmc* correlated_hmc) :
    QPushButton(parent)
{
   connect(this, SIGNAL (released()), this, SLOT (handleButton()));
   my_hmc = correlated_hmc;

   setMouseTracking(true);
}

void HmcButton::handleButton(){
    qDebug()<<"hmc_button clicked on\n";
    emit hmc_focus(my_hmc);
}

void HmcButton::mouseMoveEvent ( QMouseEvent * e ){
    emit hovered("HMC\n\n"+my_hmc->toString());
}
