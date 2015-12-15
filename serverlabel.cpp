#include "serverlabel.h"

ServerLabel::ServerLabel(QWidget *parent, Server * correlated_server) :
    QLabel(parent)
{
    setMouseTracking(true);
    my_server = correlated_server;
}

void ServerLabel::mousePressEvent ( QMouseEvent * event )
{
    emit server_focus(my_server);
}

void ServerLabel::mouseMoveEvent ( QMouseEvent * e ){
    emit hovered("PHYSICAL SERVER\n\n"+my_server->toString());

}

