#ifndef SERVERBUTTON_H
#define SERVERBUTTON_H

#include <QPushButton>
#include <server.h>

class ServerButton : public QPushButton
{
    Q_OBJECT
public:
    ServerButton(QWidget *parent = 0, Server * correlated_hmc = 0);
    Server * my_server;

    void mouseMoveEvent(QMouseEvent * e);

signals:
    void server_focus(Server * param);
    void hovered(std::string param);

public slots:
    void handleButton();

};

#endif // SERVERBUTTON_H
