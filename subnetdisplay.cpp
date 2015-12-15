#include "subnetdisplay.h"

SubnetDisplay::SubnetDisplay(QWidget *parent, int width, int height, std::vector<Hmc*> edc_hmc_vector, std::vector<Hmc*> sfmc_hmc_vector, std::vector<Lpar*> edc_lpar_vector, std::vector<Lpar*> sfmc_lpar_vector, InfoPane* info_panel) :
    QTabWidget(parent)
{
    Hmc* tmp_hmc;
    Lpar* tmp_lpar;
    HmcButton* tmp_hmc_button;
    LparButton* tmp_lpar_button;
    QLabel * tmp_label;


    this->setFixedSize(width/4*3-80, height/5*4-30);

    this->setStyleSheet("background-color : rgba(0,0,0,100%); color : rgba(0,200,0);");

    edc_subnet_frame = new QFrame(this);
    edc_scroll_area = new QScrollArea(this);
    edc_subnet_frame->setStyleSheet("background-color : rgba(50,0,0,100%);  color : rgba(0,200,0);");
    edc_scroll_area->setWidget(edc_subnet_frame);
    edc_scroll_area->show();

    sfmc_subnet_frame = new QFrame(this);
    sfmc_scroll_area = new QScrollArea(this);
    sfmc_subnet_frame->setStyleSheet("background-color : rgba(50,0,0,100%);  color : rgba(0,200,0);");
    sfmc_scroll_area->setWidget(sfmc_subnet_frame);
    sfmc_scroll_area->show();

    edc_subnet_vbox_layout = new QVBoxLayout();
    edc_subnet_vbox_layout->setContentsMargins(1,1,1,1);
    edc_subnet_vbox_layout->setAlignment(Qt::AlignLeft);
    sfmc_subnet_vbox_layout = new QVBoxLayout();
    sfmc_subnet_vbox_layout->setContentsMargins(1,1,1,1);
    sfmc_subnet_vbox_layout->setAlignment(Qt::AlignLeft);

    edc_subnet_frame->setStyleSheet("background-color : rgba(0,0,0,100%); color : rgba(0,200,0);");
    edc_subnet_frame->setLayout(edc_subnet_vbox_layout);
    sfmc_subnet_frame->setStyleSheet("background-color : rgba(0,0,0,100%); color : rgba(0,200,0);");
    sfmc_subnet_frame->setLayout(sfmc_subnet_vbox_layout);

    int boxes_wide = (width/4*3-80)/180;
    ////qDebug()<<"boxes_wide = " + QString::number(boxes_wide);

    this->addTab(edc_scroll_area, "EDC");
    this->addTab(sfmc_scroll_area, "SFMC");


    std::vector<Lpar *> tmp_lpar_vector;
    std::vector<Hmc *> tmp_hmc_vector;

    QFrame * tmp_inner_frame;
    QFrame * tmp_outer_frame;
    QScrollArea * tmp_scroll_area;

    QHBoxLayout * tmp_hbox_layout;
    QVBoxLayout * tmp_vbox_layout;

    //for both frames
    for(int y = 0; y < 2; y++){
        int count = 0;

        //set temporary pointers
        if(y==0){
            tmp_hmc_vector = edc_hmc_vector;
            tmp_lpar_vector = edc_lpar_vector;
            tmp_vbox_layout = edc_subnet_vbox_layout;
            tmp_outer_frame = edc_subnet_frame;
        }else{
            tmp_hmc_vector = sfmc_hmc_vector;
            tmp_lpar_vector = sfmc_lpar_vector;
            tmp_vbox_layout = sfmc_subnet_vbox_layout;
            tmp_outer_frame = sfmc_subnet_frame;
        }
        int hmc_index = 0;
        int lpar_index = 0;
        QStringList subnet_list = QString("0.0.0.0").split(".");
        QStringList tmp_list;
        QFont tmp_font;

        while (lpar_index < tmp_lpar_vector.size() || hmc_index < tmp_hmc_vector.size()){
            if(lpar_index < tmp_lpar_vector.size()){
                tmp_lpar = tmp_lpar_vector.at(lpar_index);
            }
            if(hmc_index < tmp_hmc_vector.size()){
                tmp_hmc = tmp_hmc_vector.at(hmc_index);
            }

            if((tmp_lpar->compareToHmcIP(tmp_hmc) && lpar_index < (tmp_lpar_vector.size())) || (hmc_index == tmp_hmc_vector.size() && lpar_index < tmp_lpar_vector.size())){
                ////qDebug()<<"LPAR - " + QString::fromStdString(tmp_lpar->getIP());
                //check for new  subnet
                tmp_list =QString::fromStdString(tmp_lpar->getIP()).split(".");
                if(tmp_list.size()!=4){
                    //qDebug()<<"\t\t\t" +QString::fromStdString(tmp_lpar->getName());
                }
                else{
                    if(tmp_list.at(0) != subnet_list.at(0)){
                        subnet_list.replace(0, tmp_list.at(0));
                        tmp_label = new QLabel(this);
                        tmp_label->setStyleSheet("color: rgb(0,200,0);");
                        tmp_label->setText("\t"+subnet_list.at(0)+".0.0.0/8");
                        tmp_font = tmp_label->font();
                        tmp_font.setPointSize(20);
                        tmp_label->setFont(tmp_font);
                        tmp_vbox_layout->addWidget(tmp_label);
                        tmp_label->show();

                        //qDebug()<<"New subnet: "+subnet_list.at(0)+".0.0.0/8";
                    }
                    if(tmp_list.at(1) != subnet_list.at(1)){
                        subnet_list.replace(1, tmp_list.at(1));
                        tmp_label = new QLabel(this);
                        tmp_label->setStyleSheet("color: rgba(0,200,0);");
                        tmp_label->setText("\t\t"+subnet_list.at(0)+"."+subnet_list.at(1)+".0.0/16");
                        tmp_font = tmp_label->font();
                        tmp_font.setPointSize(20);
                        tmp_label->setFont(tmp_font);
                        tmp_vbox_layout->addWidget(tmp_label);
                        tmp_label->show();
                        //qDebug()<<"New subnet: \t\t\t"+subnet_list.at(0)+"."+subnet_list.at(1)+".0.0/16";
                    }
                    if(tmp_list.at(2) != subnet_list.at(2)){
                        subnet_list.replace(2, tmp_list.at(2));
                        tmp_label = new QLabel(this);
                        tmp_label->setStyleSheet("color: rgba(0,200,0);");
                        tmp_label->setText("\t\t\t"+subnet_list.at(0)+"."+subnet_list.at(1)+"."+subnet_list.at(2)+".0/24");
                        tmp_font = tmp_label->font();
                        tmp_font.setPointSize(20);
                        tmp_label->setFont(tmp_font);
                        tmp_vbox_layout->addWidget(tmp_label);
                        tmp_label->show();
                        //qDebug()<<"New subnet: \t\t\t\t"+subnet_list.at(0)+"."+subnet_list.at(1)+"."+subnet_list.at(2)+".0/24";

                    }
                    tmp_inner_frame = new QFrame(this);
                    //tmp_inner_frame->setStyleSheet("background-color : rgba(0,200,0,100%);");
                    tmp_vbox_layout->addWidget(tmp_inner_frame);
                    tmp_hbox_layout = new QHBoxLayout(this);
                    tmp_hbox_layout->setContentsMargins(1,1,1,1);
                    tmp_inner_frame->setLayout(tmp_hbox_layout);
                    tmp_label = new QLabel("\t\t\t\t\t\t");
                    tmp_hbox_layout->addWidget(tmp_label);
                    tmp_lpar_button = new LparButton(this, tmp_lpar);
                    lpar_buttons.push_back(tmp_lpar_button);
                    tmp_lpar_button->setStyleSheet("background-color : rgba(200,0,0,100%); color : rgba(0,0,0);");
                    if(tmp_lpar->getApplication() != ""){
                        tmp_lpar_button->setText(QString::fromStdString(tmp_lpar->getApplication()+"\n"+tmp_lpar->getName())+"\n"+QString::fromStdString(tmp_lpar->getIP()));
                    }else{
                        tmp_lpar_button->setText(QString::fromStdString(tmp_lpar->getName())+"\n"+QString::fromStdString(tmp_lpar->getIP()));
                    }
                    connect(tmp_lpar_button, SIGNAL(hovered(std::string)), info_panel, SLOT(changeText(std::string)));
                    tmp_hbox_layout->addWidget(tmp_lpar_button);
                    tmp_inner_frame->show();
                    tmp_inner_frame->setFixedHeight(tmp_lpar_button->height()+27);
                    tmp_lpar_button->setFixedHeight(tmp_lpar_button->height()+25);


                     //qDebug()<<"\t\t\t\t" + QString::fromStdString(tmp_lpar->getIP());

                }

                lpar_index++;


            }else {
                ////qDebug()<<"HMC - " + QString::fromStdString(tmp_hmc->getIP());
                tmp_list = QString::fromStdString(tmp_hmc->getIP()).split(".");

                //qDebug()<<tmp_list;
                if(tmp_list.size()!=4){
                    //qDebug()<<"\t\t\t"+QString::fromStdString(tmp_hmc->getName());
                }
                else{
                    if(tmp_list.at(0) != subnet_list.at(0)){
                        subnet_list.replace(0, tmp_list.at(0));
                        tmp_label = new QLabel(this);
                        tmp_label->setStyleSheet("color: rgb(200,0,0);");
                        tmp_label->setText("\t"+subnet_list.at(0)+".0.0.0/8");
                        tmp_font = tmp_label->font();
                        tmp_font.setPointSize(20);
                        tmp_label->setFont(tmp_font);
                        tmp_vbox_layout->addWidget(tmp_label);
                        tmp_label->show();

                        //qDebug()<<"New subnet: \t\t"+subnet_list.at(0)+".0.0.0/8";
                    }
                    if(tmp_list.at(1) != subnet_list.at(1)){
                        subnet_list.replace(1, tmp_list.at(1));
                        tmp_label = new QLabel(this);
                        tmp_label->setStyleSheet("color: rgb(0,200,0);");
                        tmp_label->setText("\t\t"+subnet_list.at(0)+"."+subnet_list.at(1)+".0.0/16");
                        tmp_font = tmp_label->font();
                        tmp_font.setPointSize(20);
                        tmp_label->setFont(tmp_font);
                        tmp_vbox_layout->addWidget(tmp_label);
                        tmp_label->show();

                        //qDebug()<<"New subnet: \t\t\t"+subnet_list.at(0)+"."+subnet_list.at(1)+".0.0/16";
                    }
                    if(tmp_list.at(2) != subnet_list.at(2)){
                        subnet_list.replace(2, tmp_list.at(2));
                        tmp_label = new QLabel(this);
                        tmp_label->setStyleSheet("color: rgb(0,200,0);");
                        tmp_label->setText("\t\t\t"+subnet_list.at(0)+"."+subnet_list.at(1)+"."+subnet_list.at(2)+".0/24");
                        tmp_font = tmp_label->font();
                        tmp_font.setPointSize(20);
                        tmp_label->setFont(tmp_font);
                        tmp_vbox_layout->addWidget(tmp_label);
                        tmp_label->show();

                        //qDebug()<<"New subnet: \t\t\t\t"+subnet_list.at(0)+"."+subnet_list.at(1)+"."+subnet_list.at(2)+".0/24";
                    }
                    tmp_inner_frame = new QFrame(this);
                    tmp_vbox_layout->addWidget(tmp_inner_frame);
                    tmp_hbox_layout = new QHBoxLayout(this);
                    tmp_hbox_layout->setContentsMargins(1,1,1,1);
                    tmp_inner_frame->setLayout(tmp_hbox_layout);
                    tmp_label = new QLabel("\t\t\t\t\t\t");
                    tmp_hbox_layout->addWidget(tmp_label);
                    tmp_hmc_button = new HmcButton(this, tmp_hmc);
                    hmc_buttons.push_back(tmp_hmc_button);
                    tmp_hmc_button->setStyleSheet("background-color : rgba(0,0,0,100%); color : rgba(0,200,0);");
                    tmp_hmc_button->setText(QString::fromStdString(tmp_lpar->getName())+"\n"+QString::fromStdString(tmp_hmc->getIP()));
                    connect(tmp_hmc_button, SIGNAL(hovered(std::string)), info_panel, SLOT(changeText(std::string)));
                    tmp_hbox_layout->addWidget(tmp_hmc_button);
                    tmp_inner_frame->show();
                    tmp_inner_frame->setFixedHeight(tmp_hmc_button->height()+12);
                    tmp_hmc_button->setFixedHeight(tmp_hmc_button->height()+10);

                    ////qDebug()<<"\t\t\t\t" + QString::fromStdString(tmp_lpar->getIP());

                }
                hmc_index++;
            }
            tmp_outer_frame->adjustSize();

        }
        //qDebug()<<"finished with a data center";

    }
}
