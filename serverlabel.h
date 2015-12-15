#ifndef SERVERLABEL_H
#define SERVERLABEL_H

#include <QLabel>
#include <server.h>

class ServerLabel : public QLabel
{
    Q_OBJECT
public:
    ServerLabel(QWidget *parent, Server* param);
    Server * my_server;
    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);

signals:
    void server_focus(Server * param);
    void hovered(std::string param);

public slots:

};

#endif // SERVERLABEL_H
