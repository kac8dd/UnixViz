#ifndef HMCBUTTON_H
#define HMCBUTTON_H

#include <QPushButton>
#include <QDebug>
#include <hmc.h>
#include <server.h>


class HmcButton : public QPushButton
{
    Q_OBJECT
public:
    HmcButton(QWidget *parent = 0, Hmc * correlated_hmc = 0);
    Hmc * my_hmc;

    void mouseMoveEvent ( QMouseEvent * e );

signals:
    void hmc_focus(Hmc * param);
    void hovered(std::string param);

public slots:
    void handleButton();
};

#endif // HMCBUTTON_H
