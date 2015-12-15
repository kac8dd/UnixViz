#ifndef HMCDISPLAY_H
#define HMCDISPLAY_H

#include <QTabWidget>
#include <server.h>
#include <hmc.h>
#include <QFrame>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QGridLayout>
#include <hmcbutton.h>
#include <serverbutton.h>
#include <infopane.h>
#include <hmclabel.h>

class UnixVizMainWindow;

class HmcDisplay : public QTabWidget
{
    Q_OBJECT
public:
    HmcDisplay(UnixVizMainWindow * parent, int width, int height, std::vector<Hmc*> edc_hmc_vector, std::vector<Hmc*> sfmc_hmc_vector, InfoPane * info_panel);
    QFrame * edc_hmc_frame;
    QFrame * sfmc_hmc_frame;
    QScrollArea * edc_scroll_area;
    QScrollArea * sfmc_scroll_area;
    QGridLayout * edc_hmc_grid_layout;
    QGridLayout * sfmc_hmc_grid_layout;
    std::vector<HmcButton*> hmc_buttons;
    std::vector<HmcLabel*> hmc_labels;
    std::vector<ServerButton*> server_buttons;
    std::vector<HmcButton*> add_server_buttons;


signals:

public slots:

};

#endif // HMCDISPLAY_H
