#include "rackdisplay.h"



RackDisplay::RackDisplay(UnixVizMainWindow *parent, int width, int height, std::vector<Hmc*> edc_hmc_vector, std::vector<Hmc*> sfmc_hmc_vector, std::vector<Server*> edc_server_vector, std::vector<Server*> sfmc_server_vector, InfoPane* info_panel) :
    QTabWidget((QWidget*)parent)
{
    Hmc* tmp_hmc;
    HmcButton* tmp_hmc_button;
    ServerButton* tmp_server_button;
    Server* tmp_server;
    QLabel * tmp_label;

    this->setFixedSize(width/4*3-80, height/5*4-30);

    this->setStyleSheet("background-color : rgba(0,0,0,100%); color : rgba(0,200,0);");

    edc_rack_frame = new QFrame(this);
    edc_scroll_area = new QScrollArea(this);
    edc_rack_frame->setStyleSheet("background-color : rgba(50,0,0,100%);  color : rgba(0,200,0);");
    edc_scroll_area->setWidget(edc_rack_frame);
    edc_scroll_area->show();


    sfmc_rack_frame = new QFrame(this);
    sfmc_scroll_area = new QScrollArea(this);
    sfmc_scroll_area->setWidget(sfmc_rack_frame);
    sfmc_scroll_area->show();


    edc_server_grid_layout = new QGridLayout();
    edc_server_grid_layout->setAlignment(Qt::AlignCenter);
    sfmc_server_grid_layout = new QGridLayout();
    sfmc_server_grid_layout->setAlignment(Qt::AlignCenter);

    edc_rack_frame->setStyleSheet("background-color : rgba(0,0,0,100%); color : rgba(0,200,0);");
    edc_rack_frame->setLayout(edc_server_grid_layout);
    sfmc_rack_frame->setStyleSheet("background-color : rgba(0,0,0,100%); color : rgba(0,200,0);");
    sfmc_rack_frame->setLayout(sfmc_server_grid_layout);

    int boxes_wide = (width/4*3-80)/180;
    ////qDebug()<<"boxes_wide = " + QString::number(boxes_wide);

    this->addTab(edc_scroll_area, "EDC");
    this->addTab(sfmc_scroll_area, "SFMC");


    std::vector<Server *> tmp_server_vector;
    std::vector<Hmc *> tmp_hmc_vector;

    QFrame * tmp_rack_frame;
    QFrame * tmp_outer_frame;
    QScrollArea * tmp_scroll_area;

    QVBoxLayout * tmp_rack_vboxlayout;
    QGridLayout * tmp_grid_layout;

    //for both frames
    for(int y = 0; y < 2; y++){
        int count = 0;

        //set temporary pointers
        if(y==0){
            tmp_hmc_vector = edc_hmc_vector;
            tmp_server_vector = edc_server_vector;
            tmp_grid_layout = edc_server_grid_layout;
            tmp_outer_frame = edc_rack_frame;
        }else{
            tmp_hmc_vector = sfmc_hmc_vector;
            tmp_server_vector = sfmc_server_vector;
            tmp_grid_layout = sfmc_server_grid_layout;
            tmp_outer_frame = sfmc_rack_frame;
        }

        int hmc_index = 0;
        int server_index = 0;
        QString current_rack = "";
        QString previous_rack = "";
        //qDebug()<<"first entries: \n"+QString::fromStdString(tmp_hmc_vector.at(0)->toString())+"\n\nAND\n\n"+QString::fromStdString(tmp_server_vector.at(0)->toString())+")\nhmc_index,server_index) = "+QString::number(hmc_index)+","+QString::number(server_index)+")";

        tmp_server = tmp_server_vector.at(0);
        tmp_hmc = tmp_hmc_vector.at(0);


        //each iteration of this loop will make a new rack
        while(hmc_index < tmp_hmc_vector.size() || server_index < tmp_server_vector.size()){

            ////qDebug()<<"hmc_index = "+QString::number(hmc_index)+"/"+QString::number(tmp_hmc_vector.size());
            ////qDebug()<<"server_index = "+QString::number(server_index)+"/"+QString::number(tmp_server_vector.size());


            if(tmp_server->getRack() < tmp_hmc->getRack()){
                current_rack = QString::fromStdString(tmp_server->getRack());
                ////qDebug()<<"current_rack1 = "+ current_rack;
            }
            else{
                current_rack = QString::fromStdString(tmp_hmc->getRack());
                ////qDebug()<<"current_rack2 = "+ current_rack;
            }
            if(current_rack != previous_rack){
                //qDebug()<<"Found new rack: "+ current_rack;
                previous_rack = current_rack;
                current_rack = QString::fromStdString(tmp_server->getRack());

                tmp_rack_vboxlayout = new QVBoxLayout(this);

                tmp_rack_frame = new QFrame();
                tmp_rack_frame->setLayout(tmp_rack_vboxlayout);

                tmp_scroll_area = new QScrollArea();
                tmp_scroll_area->setWidget(tmp_rack_frame);

                tmp_scroll_area->setStyleSheet("background-color : rgba(50,0,0,100%);");
                tmp_scroll_area->setMaximumWidth(200);
                tmp_scroll_area->setMinimumWidth(200);
                tmp_scroll_area->setMinimumHeight(320);
                tmp_scroll_area->setMaximumHeight(320);
                //tmp_rack_frame->setMinimumWidth(200);
                //tmp_rack_frame->setMinimumHeight(320);
                tmp_scroll_area->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
                tmp_scroll_area->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
                tmp_grid_layout->addWidget(tmp_scroll_area, count/boxes_wide, count%boxes_wide, Qt::AlignTop);
                tmp_scroll_area->show();
                tmp_outer_frame->adjustSize();

                tmp_label = new QLabel(this);
                tmp_label->setStyleSheet("color : rgba(0,200,0);");
                tmp_label->setText(current_rack);
                tmp_rack_vboxlayout->addWidget(tmp_label, 0, Qt::AlignLeft);

                count++;
            }

            //while the next hmc matches the current_rack
            while(QString::fromStdString(tmp_hmc->getRack()).contains(current_rack, Qt::CaseInsensitive) && hmc_index < tmp_hmc_vector.size()){
                //build the hmc button
                tmp_hmc_button = new HmcButton(this, tmp_hmc);
                tmp_hmc_button->setStyleSheet("background-color : rgba(0,0,0,100%); color : rgba(0,200,0); ");
                tmp_hmc_button->setText(QString::fromStdString(tmp_hmc->getRack())+" - HMC \n"+QString::fromStdString(tmp_hmc->getIP()));
                tmp_hmc_button->setMinimumWidth(160);
                tmp_hmc_button->setMaximumWidth(160);
                tmp_hmc_button->setMinimumHeight(40);
                tmp_hmc_button->setMaximumHeight(40);
                connect(tmp_hmc_button, SIGNAL(hovered(std::string)), info_panel, SLOT(changeText(std::string)));
                tmp_rack_vboxlayout->addWidget(tmp_hmc_button);//, Qt::AlignTop);
                tmp_hmc_button->show();
                hmc_buttons.push_back(tmp_hmc_button);

                //qDebug()<<"adding " + QString::fromStdString(tmp_hmc->getRack()+"-"+tmp_hmc->getName());
                hmc_index++;
                if(hmc_index == tmp_hmc_vector.size()){break;}
                tmp_hmc = tmp_hmc_vector.at(hmc_index);

            }

            //while the next server matches the current rack
            while((QString::fromStdString(tmp_server->getRack()).contains(current_rack, Qt::CaseInsensitive) && server_index < tmp_server_vector.size()) || hmc_index == tmp_hmc_vector.size()){
                //if we've got a new rack, make a new frame
                if(QString::fromStdString(tmp_server->getRack()) != current_rack){
                    previous_rack = current_rack;
                    current_rack = QString::fromStdString(tmp_server->getRack());
                    //qDebug()<<"Found new rack: "+ current_rack;
                    tmp_rack_vboxlayout = new QVBoxLayout(this);

                    tmp_rack_frame = new QFrame();
                    tmp_rack_frame->setLayout(tmp_rack_vboxlayout);

                    tmp_scroll_area = new QScrollArea();
                    tmp_scroll_area->setWidget(tmp_rack_frame);

                    tmp_scroll_area->setStyleSheet("background-color : rgba(50,0,0,100%);");
                    tmp_scroll_area->setMaximumWidth(200);
                    tmp_scroll_area->setMinimumWidth(200);
                    tmp_scroll_area->setMinimumHeight(320);
                    tmp_scroll_area->setMaximumHeight(320);
                    tmp_scroll_area->setHorizontalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
                    tmp_scroll_area->setVerticalScrollBarPolicy( Qt::ScrollBarAlwaysOn );
                    tmp_grid_layout->addWidget(tmp_scroll_area, count/boxes_wide, count%boxes_wide, Qt::AlignTop);
                    tmp_scroll_area->show();
                    tmp_outer_frame->adjustSize();

                    tmp_label = new QLabel(this);
                    tmp_label->setStyleSheet("color : rgba(0,200,0);");
                    tmp_label->setText(current_rack);
                    tmp_rack_vboxlayout->addWidget(tmp_label, 0, Qt::AlignLeft);

                    count++;
                }
                //qDebug()<<"adding " + QString::fromStdString(tmp_server->getRack()+"-"+tmp_server->getName());
                //build the hmc button
                tmp_server_button = new ServerButton(this, tmp_server);
                tmp_server_button->setStyleSheet("background-color : rgba(0,0,100,70%); color : rgb(0,200,0);");
                tmp_server_button->setText(QString::fromStdString(tmp_server->getName()));

                tmp_server_button->setMinimumWidth(160);
                tmp_server_button->setMaximumWidth(160);
                tmp_server_button->setMinimumHeight(40);
                tmp_server_button->setMaximumHeight(40);
                /*QPixmap pixmap(":/images/p750.png");
                //pixmap = pixmap.scaledToWidth(160);
                tmp_server_button->setIcon(QIcon(pixmap));
                tmp_server_button->setIconSize(QSize(tmp_server_button->width(), tmp_server_button->height()));
                */tmp_rack_vboxlayout->addWidget(tmp_server_button, Qt::AlignTop);
                connect(tmp_server_button, SIGNAL(hovered(std::string)), info_panel, SLOT(changeText(std::string)));
                tmp_server_button->show();
                server_buttons.push_back(tmp_server_button);
                tmp_rack_frame->adjustSize();
                server_index++;
                if(server_index == tmp_server_vector.size()){break;}
                tmp_server = tmp_server_vector.at(server_index);

            }




        }


    }

}
