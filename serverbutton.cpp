#include "serverbutton.h"

ServerButton::ServerButton(QWidget *parent, Server * correlated_server) :
    QPushButton(parent)
{
    connect(this, SIGNAL(released()), this, SLOT(handleButton()));
    my_server = correlated_server;

    setMouseTracking(true);
}

void ServerButton::handleButton(){
    emit server_focus(my_server);
}

void ServerButton::mouseMoveEvent(QMouseEvent *e){
    emit hovered("PHYSICAL SERVER\n\n"+my_server->toString());
}
