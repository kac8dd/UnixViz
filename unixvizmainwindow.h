#ifndef UNIXVIZMAINWINDOW_H
#define UNIXVIZMAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QRect>
#include <QDesktopWidget>
#include <vector>
#include <QPixmap>
#include <QIcon>
#include <QPalette>
#include <QDebug>
#include <string>
#include <pthread.h>
#include <QtXlsx>
#include <QtWidgets>
#include "xlsxdocument.h"
#include "xlsxworksheet.h"
#include "xlsxcellrange.h"
#include "lpar.h"
#include "hmc.h"
#include "server.h"
#include "infopane.h"
#include "qscrollarea.h"
#include <QGridLayout>
#include <QHBoxLayout>
#include "hmcbutton.h"
#include <QInputDialog>
#include <hmcdisplay.h>
#include <rackdisplay.h>
#include <hmclabel.h>
#include <focusdisplay.h>
#include <subnetdisplay.h>
#include <lparlabel.h>

namespace Ui {
class UnixVizMainWindow;
}

class UnixVizMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit UnixVizMainWindow(QWidget *parent = 0);
    void resizeEvent(QResizeEvent* event);
    void * readSpreadsheet();

    std::vector<Hmc*> edc_hmc_vector;
    std::vector<Server*> edc_server_vector;
    std::vector<Lpar*> edc_lpar_vector;
    std::vector<Hmc*> sfmc_hmc_vector;
    std::vector<Server*> sfmc_server_vector;
    std::vector<Lpar*> sfmc_lpar_vector;

    ~UnixVizMainWindow();
    InfoPane *info_panel;
    QScrollArea * scroll_panel_info_area;
    QTabWidget * tabbed_hmc_display_area;
    QTabWidget * tabbed_server_display_area;
    HmcDisplay * hmc_view;
    RackDisplay * rack_view;
    FocusDisplay * focus_view;
    SubnetDisplay * subnet_view;

private:
    //objects
    Ui::UnixVizMainWindow *ui;
    int main_window_width;
    int main_window_height;
    QPixmap BSHSI_pixmap;
    QIcon BSHSI_icon;
    QPalette palette;
    QPixmap * current_bkgnd;
    QPixmap * original_bkgnd;

    QPushButton * start_button;
    std::string state;


    QGridLayout * edc_server_grid_layout;
    QGridLayout * sfmc_server_grid_layout;

    //the focus frame
    QFrame * focus_frame;
    QScrollArea * focus_frame_scroll_area;
    QPushButton * home_button;


    //boolean state variables
    bool home_screen;
    bool hmc_screen;
    bool rack_screen;
    bool subnet_screen;
    bool server_focus;
    bool hmc_focus;


    QLineEdit * search_line_edit;
    QLabel * search_label;

    QFrame * view_selection_frame;
    void search_thread();

    QString search_string;



public slots:
    void enterDashboard();
    void serverFocus(Server *);
    void hmcFocus(Hmc *);
    void switchToHmcView();
    void switchToRackView();
    void switchToSubnetView();
    void search(QString param);


signals:

    void reset();
    void foundHmcResult(Hmc*);
    void foundServerResult(Server*);
    void foundLparResult(Lpar*);
    void setServer(std::string);

};

#endif // UNIXVIZMAINWINDOW_H

