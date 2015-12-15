#include "hmcdisplay.h"
#include "vector"
#include <qpainter.h>

HmcDisplay::HmcDisplay(UnixVizMainWindow * parent, int width, int height, std::vector<Hmc*> edc_hmc_vector, std::vector<Hmc*> sfmc_hmc_vector, InfoPane * info_panel) :
    QTabWidget((QWidget*)parent)
{
    Hmc* tmp_hmc;
    HmcLabel * tmp_hmc_label;
    ServerButton* tmp_server_button;
    Server* tmp_server;
    this->setFixedSize(width/4*3-80, height/5*4-30);

    this->setStyleSheet("background-color : rgba(0,0,0,0%); background: transparent; color : rgba(0,200,0);");

    edc_hmc_frame = new QFrame(this);
    edc_scroll_area = new QScrollArea(this);
    edc_scroll_area->setWidget(edc_hmc_frame);
    edc_scroll_area->show();

    sfmc_hmc_frame = new QFrame(this);
    sfmc_scroll_area = new QScrollArea(this);
    sfmc_scroll_area->setWidget(sfmc_hmc_frame);
    sfmc_scroll_area->show();

    edc_hmc_grid_layout = new QGridLayout();
    edc_hmc_grid_layout->setAlignment(Qt::AlignCenter);
    sfmc_hmc_grid_layout = new QGridLayout();
    sfmc_hmc_grid_layout->setAlignment(Qt::AlignCenter);

    edc_hmc_frame->setStyleSheet("background-color : rgba(0,0,0,100%); color : rgba(0,200,0);");
    edc_hmc_frame->setLayout(edc_hmc_grid_layout);
    sfmc_hmc_frame->setStyleSheet("background-color : rgba(0,0,0,100%); color : rgba(0,200,0);");
    sfmc_hmc_frame->setLayout(sfmc_hmc_grid_layout);

    int boxes_wide = (width/4*3-80)/180;

    this->addTab(edc_scroll_area, "EDC");
    this->addTab(sfmc_scroll_area, "SFMC");

    QFrame * tmp_outer_frame;
    QFrame * tmp_inner_frame;
    QScrollArea * tmp_scroll_area;

    QVBoxLayout * tmp_outer_vboxlayout;
    QVBoxLayout * tmp_inner_vboxlayout;
    std::vector<Hmc *> tmp_hmc_vector;
    QGridLayout * tmp_grid_layout;
    HmcButton * tmp_button;


    //for both frames
    for(int y = 0; y < 2; y++){
        int count = 0;

        //set temporary pointers
        if(y==0){
            tmp_hmc_vector = edc_hmc_vector;
            tmp_grid_layout = edc_hmc_grid_layout;
        }else{
            tmp_hmc_vector = sfmc_hmc_vector;
            tmp_grid_layout = sfmc_hmc_grid_layout;
        }

        //build each hmc and all their servers
        for(int x = 0; x < tmp_hmc_vector.size(); x++){
            //qDebug()<<QString::fromStdString("makeing hmc: ")+QString::number(x);
            tmp_hmc = tmp_hmc_vector.at(x);

            //build the frame the hmc button resides in
            tmp_outer_frame = new QFrame(this);
            tmp_outer_frame->setMaximumWidth(200);
            tmp_outer_frame->setMinimumWidth(200);
            tmp_outer_frame->setMinimumHeight(320);
            tmp_outer_frame->setMaximumHeight(320);

            tmp_outer_frame->setStyleSheet("background-color : rgba(50,0,0,100%);");
            tmp_grid_layout->addWidget(tmp_outer_frame, count/boxes_wide, count%boxes_wide, Qt::AlignTop );

            //make and configure a new layout for the outer frame
            tmp_outer_vboxlayout = new QVBoxLayout();
            tmp_outer_frame->setLayout(tmp_outer_vboxlayout);
            tmp_outer_frame->show();


            tmp_hmc_label = new HmcLabel(this, tmp_hmc);
            tmp_hmc_label->setText(QString::fromStdString(tmp_hmc->getRack())+" - HMC: "+QString::fromStdString(tmp_hmc->getIP()));
            tmp_hmc_label->setStyleSheet("background-color : rgba(0,0,0,0%); color : rgba(0,200,0); ");
            tmp_hmc_label->setFixedHeight(15);
            tmp_outer_vboxlayout->addWidget(tmp_hmc_label, Qt::AlignTop);

            tmp_hmc_label = new HmcLabel(this, tmp_hmc);

            //build the hmc as a label
            tmp_hmc_label->setStyleSheet("background-color : rgba(0,0,0,0%); color : rgba(0,200,0); ");
            //tmp_hmc_label->setAlignment(Qt::AlignCenter);
            QPixmap pixmap(":/images/hmc.png");
            pixmap = pixmap.scaledToWidth(160);

            tmp_hmc_label->setPixmap(pixmap);
            //tmp_hmc_label->setText(QString::fromStdString(tmp_hmc->getRack())+" - HMC \n"+QString::fromStdString(tmp_hmc->getStringIP()));

            tmp_hmc_label->setMinimumWidth(160);
            tmp_hmc_label->setMaximumWidth(160);
            tmp_hmc_label->setMinimumHeight(pixmap.height());
            tmp_hmc_label->setMaximumHeight(pixmap.height());
            tmp_hmc_label->show();



            //add hmc label to its layout
            tmp_outer_vboxlayout->addWidget(tmp_hmc_label, Qt::AlignTop);

            connect(tmp_hmc_label, SIGNAL(hovered(std::string)), info_panel, SLOT(changeText(std::string)));

            hmc_labels.push_back(tmp_hmc_label);

            //make a new scroll area for the servers and add it to the layout
            tmp_scroll_area = new QScrollArea(this);
            tmp_scroll_area->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
            tmp_scroll_area->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
            tmp_scroll_area->lower();

            tmp_outer_vboxlayout->addWidget(tmp_scroll_area, Qt::AlignTop);

            //make frame the scroll area will encompass
            tmp_inner_frame = new QFrame(tmp_outer_frame);

            tmp_scroll_area->setWidget(tmp_inner_frame);
            tmp_inner_frame->lower();
            //make a layout for this frame
            tmp_inner_vboxlayout = new QVBoxLayout();
            tmp_inner_vboxlayout->setAlignment(Qt::AlignVCenter);
            tmp_inner_frame->setLayout(tmp_inner_vboxlayout);
            tmp_inner_frame->show();
            tmp_inner_frame->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);


            count++;




            std::vector<Server *> servers = tmp_hmc->getServerVector();

            edc_hmc_frame->adjustSize();
            sfmc_hmc_frame->adjustSize();

            tmp_button = new HmcButton(tmp_outer_frame, tmp_hmc);
            tmp_button->setStyleSheet("background-color : rgba(0,0,0,100%);");
            tmp_button->setGeometry(tmp_outer_frame->width()-23, tmp_outer_frame->height()-23, 21, 21);
            tmp_button->setText(">");
            add_server_buttons.push_back(tmp_button);
            //connect(tmp_button, SIGNAL(hmc_focus(Hmc*)), parent, SLOT(hmcFocus(Hmc*)));
            tmp_button->show();


            //for each server attached to that hmc
            //qDebug()<<"HMC "+QString::fromStdString(tmp_hmc->getRack())+" has "+QString::number(tmp_hmc->getServerVector().size()) +" servers on it\n";
            for(int y = 0; y < tmp_hmc->getServerVector().size(); y++){

                //get current server and set parameters
                tmp_server=servers.at(y);
                tmp_server_button = new ServerButton(this, tmp_server);
                server_buttons.push_back(tmp_server_button);
                connect(tmp_server_button, SIGNAL(hovered(std::string)), info_panel, SLOT(changeText(std::string)));



                tmp_server_button->setMinimumWidth(150);
                tmp_server_button->setMaximumWidth(150);
                tmp_server_button->setMinimumHeight(40);
                tmp_server_button->setMaximumHeight(40);
                tmp_server_button->setStyleSheet("background-color : rgba(0,0,100,70%); color : rgb(0,200,0); ");
                tmp_server_button->setText(QString::fromStdString(tmp_server->getName()));

                tmp_inner_vboxlayout->addWidget(tmp_server_button);//, Qt::AlignVCenter);


                tmp_server_button->show();
            }

            tmp_inner_frame->adjustSize();
            tmp_outer_frame->adjustSize();



        }
    }



}
