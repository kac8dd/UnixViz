#ifndef RACKDISPLAY_H
#define RACKDISPLAY_H

#include <QTabWidget>
#include "QDebug"
#include <hmc.h>
#include <server.h>
#include <infopane.h>
#include <qframe.h>
#include <infopane.h>
#include <QGridLayout>
#include <hmcbutton.h>
#include <serverbutton.h>
#include <hmclabel.h>
#include <QScrollArea>

class UnixVizMainWindow;

class RackDisplay : public QTabWidget
{
    Q_OBJECT
public:
    RackDisplay(UnixVizMainWindow *parent, int width, int height, std::vector<Hmc*> edc_hmc_vector, std::vector<Hmc*> sfmc_hmc_vector, std::vector<Server*> edc_server_vector, std::vector<Server*> sfmc_server_vector, InfoPane* info_panel);
    QFrame * edc_rack_frame;
    QFrame * sfmc_rack_frame;
    QScrollArea * edc_scroll_area;
    QScrollArea * sfmc_scroll_area;
    QGridLayout * edc_server_grid_layout;
    QGridLayout * sfmc_server_grid_layout;
    std::vector<HmcButton*> hmc_buttons;
    std::vector<ServerButton*> server_buttons;

signals:

public slots:

};

#endif // SERVERDISPLAY_H
