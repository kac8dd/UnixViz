#ifndef SUBNETDISPLAY_H
#define SUBNETDISPLAY_H

#include <QTabWidget>
#include "QDebug"
#include <hmc.h>
#include <server.h>
#include <lpar.h>
#include <infopane.h>
#include <qframe.h>
#include <infopane.h>
#include <QGridLayout>
#include <QVBoxLayout>
#include <hmcbutton.h>
#include <serverbutton.h>
#include <hmclabel.h>
#include <lparbutton.h>
#include <QScrollArea>
#include <QFont>

class UnixVizMainWindow;

class SubnetDisplay : public QTabWidget
{
    Q_OBJECT
public:
    SubnetDisplay(QWidget *parent, int width, int height, std::vector<Hmc*> edc_hmc_vector, std::vector<Hmc*> sfmc_hmc_vector, std::vector<Lpar*> edc_lpar_vector, std::vector<Lpar*> sfmc_lpar_vector, InfoPane* info_panel);
    QFrame * edc_subnet_frame;
    QFrame * sfmc_subnet_frame;
    QScrollArea * edc_scroll_area;
    QScrollArea * sfmc_scroll_area;
    QVBoxLayout * edc_subnet_vbox_layout;
    QVBoxLayout * sfmc_subnet_vbox_layout;
    std::vector<HmcButton*> hmc_buttons;
    std::vector<LparButton*> lpar_buttons;
signals:

public slots:

};

#endif // SUBNETDISPLAY_H
