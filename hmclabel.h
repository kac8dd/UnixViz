#ifndef HMCLABEL_H
#define HMCLABEL_H

#include <QLabel>
#include <hmc.h>

class HmcLabel : public QLabel
{
    Q_OBJECT
public:
    HmcLabel(QWidget *parent, Hmc * correlated_hmc);
    Hmc * my_hmc;

    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);

signals:
    void hmc_focus(Hmc * param);
    void hovered(std::string param);

public slots:

};

#endif // HMCLABEL_H
