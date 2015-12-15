#include "focusdisplay.h"

FocusDisplay::FocusDisplay(QWidget *parent, int width, int height) :
    QScrollArea(parent)
{
    this->height = height;
    this->width = width;
    focus_frame = new QFrame(this);
    this->setGeometry(width/25, height/5, width/4*3-80, height/5*4-30);
    this->setStyleSheet("background-color : rgba(0,0,0,0%);");
    grid_layout = new QGridLayout();
    num_rows = 3;

    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
}

void FocusDisplay::serverFocus(Server *param){



    //rebuild the focus frame
    delete focus_frame;
    focus_frame = new QFrame(this);
    focus_frame->setMinimumSize(this->width/4*3-80, this->height/5*4-30);
    this->setWidget(focus_frame);

    grid_layout = new QGridLayout();
    focus_frame->setLayout(grid_layout);

    QLabel * server_info = new QLabel(this);
    server_info->setMaximumHeight(this->height/2);
    server_info->setMaximumWidth(300);
    server_info->setStyleSheet("background-color : rgba(0,0,0,70%); color : rgba(0,200,0); border: 2px solid");

    grid_layout->addWidget(server_info,0,0,1,1, Qt::AlignBottom);


    right_scroll_area = new QScrollArea(this);
    right_scroll_area->setStyleSheet("background-color : rgba(0,0,0,0%);");
    right_scroll_area->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    right_scroll_area->setFixedWidth(this->width/3-20);
    //right_scroll_area->setFixedHeight(focus_frame->height()-20);

    QFrame * right_frame = new QFrame(this);
    right_frame->setStyleSheet("background-color : rgba(10,10,10,30%);");
    //right_frame->setWindowIconText("LOGICAL PARTITIONS: ");
    right_frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    //right_frame->setMaximumHeight(300);
    right_frame->setMinimumWidth(right_scroll_area->width()-50);
    //qDebug()<<QString("right frame scroll area width = "+QString::number(right_scroll_area->width()));
    if(QString::fromStdString(param->getName()).contains("710")){
            num_rows = 4;
    }
    else if(QString::fromStdString(param->getName()).contains("720")){
        num_rows = 3;
    }
    else if(QString::fromStdString(param->getName()).contains("720")){
        num_rows = 3;
    }
    else if(QString::fromStdString(param->getName()).contains("730")){
        num_rows = 3;
    }
    else if(QString::fromStdString(param->getName()).contains("740")){
        num_rows = 3;
    }
    else if(QString::fromStdString(param->getName()).contains("750")){
        num_rows = 3;
    }
    else if(QString::fromStdString(param->getName()).contains("770")){
        num_rows = 3;
    }
    else if(QString::fromStdString(param->getName()).contains("780")){
        num_rows = 3;
    }
    else if(QString::fromStdString(param->getName()).contains("p5") && QString::fromStdString(param->getName()).contains("570")){
        num_rows = 4;
    }
    else if(QString::fromStdString(param->getName()).contains("p6") && QString::fromStdString(param->getName()).contains("570")){
        num_rows = 3;
    }
    grid_layout->addWidget(right_scroll_area,0,1,num_rows,1, Qt::AlignTop);

    QVBoxLayout * right_layout = new QVBoxLayout(this);
    right_scroll_area->setWidget(right_frame);
    right_frame->setLayout(right_layout);

    right_frame->setGeometry(0,0, right_scroll_area->height(), right_scroll_area->width()-50);

    param->memory_available = param->getMemory();
    param->processors_available = param->getProcessors();
    Lpar * tmp_lpar;
    QLabel * tmp_label;

    if(param->lpar_vector.size() == 0){
        tmp_label = new QLabel(this);
        tmp_label->setStyleSheet("background-color : rgba(0,0,100,70%); color : rgba(200,0,0); border: 4px solid Red; text-align: center");
        tmp_label->setMaximumHeight(190);
        tmp_label->setMinimumHeight(190);

        tmp_label->setText("NO LPARS FOUND");
        tmp_label->setMinimumWidth(350);


        right_layout->addWidget(tmp_label);
    }

    for(int x = 0; x < param->lpar_vector.size(); x++){

        tmp_lpar = param->lpar_vector.at(x);
        //qDebug()<<"processors_available: "+QString::fromStdString(param->processors_available);
        //qDebug()<<"this server's processors: "+QString::fromStdString(tmp_lpar->getProcessors())+"\n\n\n";
        param->processors_available = QString::number(QString::fromStdString(param->processors_available).toInt()-QString::fromStdString(tmp_lpar->getProcessors()).toInt()).toStdString();
        param->memory_available = QString::number(QString::fromStdString(param->memory_available).toInt()-QString::fromStdString(tmp_lpar->getMemory()).toInt()).toStdString();
        tmp_label = new QLabel(this);
        tmp_label->setStyleSheet("background-color : rgba(0,0,100,70%); color : rgba(0,200,0); border: 4px solid green;");
        tmp_label->setMaximumHeight(190);
        tmp_label->setMinimumHeight(190);

        //tmp_label->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
        tmp_label->setText(QString::fromStdString(tmp_lpar->toString()));
        tmp_label->setMinimumWidth(350);

        right_layout->addWidget(tmp_label);

        right_frame->adjustSize();
        right_layout->setAlignment(tmp_label, Qt::AlignLeft);
        tmp_label->show();
    }

    server_info->setText(QString::fromStdString(param->getName()+"\nCores available:\t\t"+param->processors_available+"/"+param->getProcessors()+"\nGB available: \t\t"+param->memory_available+"/"+param->getMemory()+"\n"));

    addPictures(param);


}
void FocusDisplay::hmcFocus(Hmc * param){

    //rebuild the focus frame
    delete focus_frame;
    focus_frame = new QFrame(this);
    focus_frame->setMinimumSize(this->width/4*3-80, this->height/5*4-30);
    this->setWidget(focus_frame);

    grid_layout = new QGridLayout();
    focus_frame->setLayout(grid_layout);


    QLabel * hmc_info = new QLabel(this);
    hmc_info->setMaximumHeight(this->height/2);
    hmc_info->setMaximumWidth(300);
    hmc_info->setText(QString::fromStdString(param->toString()));
    hmc_info->setStyleSheet("background-color : rgba(0,0,0,70%); color : rgba(0,200,0); border: 2px solid");
    grid_layout->addWidget(hmc_info, 0,0,1,1,Qt::AlignTop);

    QScrollArea * right_scroll_area = new QScrollArea(this);
    right_scroll_area->setStyleSheet("background-color : rgba(0,0,0,0%);");
    right_scroll_area->setFixedWidth(this->width/3-20);
    right_scroll_area->setFixedHeight(focus_frame->height()-10);


    QPixmap  front_pixmap(":/images/hmc.png");
    front_pixmap = front_pixmap.scaledToWidth(focus_frame->width()*2/5);


    QLabel * tmp_label = new QLabel(this);
    tmp_label->setFixedSize(front_pixmap.size());
    tmp_label->setPixmap(front_pixmap);
    grid_layout->addWidget(tmp_label,1,0,1,1,Qt::AlignTop);

    QPixmap  logical_pixmap(":/images/hmc_diagram.jpg");
    logical_pixmap = logical_pixmap.scaledToWidth(focus_frame->width()*2/5);


    tmp_label = new QLabel(this);
    tmp_label->setFixedSize(logical_pixmap.size());
    tmp_label->setPixmap(logical_pixmap);
    grid_layout->addWidget(tmp_label,2,0,1,1,Qt::AlignTop);

    QFrame * right_frame = new QFrame(this);
    right_frame->setStyleSheet("background-color : rgba(0,0,100,50%);");
    right_scroll_area->setWidget(right_frame);
    right_frame->setMinimumWidth(right_scroll_area->width()-50);


    QVBoxLayout * right_layout = new QVBoxLayout();
    right_frame->setLayout(right_layout);

    grid_layout->addWidget(right_scroll_area,0,1,4,1,Qt::AlignTop);


    //qDebug()<<"finding error\n";
    //right_frame->setFixedWidth(400);


    if(param->server_vector.size() == 0){
        tmp_label = new QLabel(this);
        tmp_label->setStyleSheet("background-color : rgba(0,0,100,70%); color : rgba(200,0,0); border: 4px solid Red; text-align: center");
        tmp_label->setMaximumHeight(190);
        tmp_label->setMinimumHeight(190);

        tmp_label->setText("NO SERVERS FOUND");
        tmp_label->setMinimumWidth(350);


        right_layout->addWidget(tmp_label);
    }

    Server * tmp_server;
    for(int x = 0; x < param->server_vector.size(); x++){

        tmp_server = param->server_vector.at(x);
        tmp_label = new QLabel(this);
        tmp_label->setStyleSheet("background-color : rgba(0,0,100,70%); color : rgba(0,200,0); border: 4px solid green;");
        tmp_label->setMaximumHeight(190);
        tmp_label->setMinimumHeight(190);

        tmp_label->setText(QString::fromStdString(tmp_server->toString()));
        tmp_label->setMinimumWidth(350);


        right_layout->addWidget(tmp_label);

        right_frame->adjustSize();
        right_layout->setAlignment(tmp_label, Qt::AlignLeft);
        tmp_label->show();
    }
}
/*
QPixmap  pixmap(":/images/hmc.png");
pixmap = pixmap.scaledToWidth(focus_frame->width()/2);


QLabel * tmp_label = new QLabel(this);
tmp_label->setFixedSize(pixmap.size());
tmp_label->setPixmap(pixmap);
grid_layout->addWidget(tmp_label,1,0,2,1,Qt::AlignTop);
*/
void FocusDisplay::addPictures(Server *param){
    QLabel * tmp_label = new QLabel(this);
    //QPixmap * tmp_pixmap = new QPixmap(this);
    QString server_name(QString::fromStdString(param->getName()));

    if(server_name.contains("710", Qt::CaseInsensitive)){

        QLabel * server_front = new QLabel(this);
        QPixmap front_pix(":/images/p710.png");
        front_pix = front_pix.scaledToWidth(focus_frame->width()*2/5);
        server_front->setPixmap(front_pix);
        server_front->setFixedSize(front_pix.width()+10, front_pix.height()+10);
        grid_layout->addWidget(server_front,1,0,1,1, Qt::AlignLeft);
        QLabel * server_back = new QLabel(this);
        QPixmap back_pix(":/images/p710_rear.png");
        back_pix = back_pix.scaledToWidth(focus_frame->width()*2/5);
        server_back->setPixmap(back_pix);
        server_back->setFixedSize(back_pix.width()+10, back_pix.height()+10);
        server_back->setStyleSheet("color: rbga(0,200,0 %100); border 2x solid green;");
        grid_layout->addWidget(server_back,2,0,1,1, Qt::AlignLeft);
        focus_frame->adjustSize();
        server_back->show();

    }
    if(server_name.contains("720", Qt::CaseInsensitive)){
        QLabel * server_front = new QLabel(this);
        QPixmap front_pix(":/images/p720.png");
        front_pix = front_pix.scaledToWidth(focus_frame->width()*2/5);
        server_front->setPixmap(front_pix);
        server_front->setFixedSize(front_pix.width()+10, front_pix.height()+10);
        grid_layout->addWidget(server_front,1,0,1,1, Qt::AlignLeft);
        QLabel * server_back = new QLabel(this);
        QPixmap back_pix(":/images/p720_rear.png");
        back_pix = back_pix.scaledToWidth(focus_frame->width()*2/5);
        server_back->setPixmap(back_pix);
        server_back->setFixedSize(back_pix.width()+10, back_pix.height()+10);
        server_back->setStyleSheet("color: rbga(0,200,0 %100); border 2x solid green;");
        grid_layout->addWidget(server_back,2,0,1,1, Qt::AlignLeft);
        focus_frame->adjustSize();
        server_back->show();
    }

    if(server_name.contains("730", Qt::CaseInsensitive)){
        QLabel * server_front = new QLabel(this);
        QPixmap front_pix(":/images/p730.png");
        front_pix = front_pix.scaledToWidth(focus_frame->width()*2/5);
        server_front->setPixmap(front_pix);
        server_front->setFixedSize(front_pix.width()+10, front_pix.height()+10);
        grid_layout->addWidget(server_front,1,0,1,1, Qt::AlignLeft);

        QLabel * server_back = new QLabel(this);
        QPixmap back_pix(":/images/p730_rear.png");
        back_pix = back_pix.scaledToWidth(focus_frame->width()*2/5);
        server_back->setPixmap(back_pix);
        server_back->setFixedSize(back_pix.width()+10, back_pix.height()+10);
        server_back->setStyleSheet("color: rbga(0,200,0 %100); border 2x solid green;");
        grid_layout->addWidget(server_back,2,0,1,1, Qt::AlignLeft);
        focus_frame->adjustSize();
        server_back->show();
    }


    if(server_name.contains("740", Qt::CaseInsensitive)){
        QLabel * server_front = new QLabel(this);
        QPixmap front_pix(":/images/p740.png");
        front_pix = front_pix.scaledToWidth(focus_frame->width()*2/5);
        server_front->setPixmap(front_pix);
        server_front->setFixedSize(front_pix.width()+10, front_pix.height()+10);
        grid_layout->addWidget(server_front,1,0,1,1, Qt::AlignLeft);

        QLabel * server_back = new QLabel(this);
        QPixmap back_pix(":/images/p740_rear.png");
        back_pix = back_pix.scaledToWidth(focus_frame->width()*2/5);
        server_back->setPixmap(back_pix);
        server_back->setFixedSize(back_pix.width()+10, back_pix.height()+10);
        server_back->setStyleSheet("color: rbga(0,200,0 %100); border 2x solid green;");
        grid_layout->addWidget(server_back,2,0,1,1, Qt::AlignLeft);
        focus_frame->adjustSize();
        server_back->show();
    }
    if(server_name.contains("750", Qt::CaseInsensitive)){
        QLabel * server_front = new QLabel(this);
        QPixmap front_pix(":/images/p750.png");
        front_pix = front_pix.scaledToWidth(focus_frame->width()*2/5);
        server_front->setPixmap(front_pix);
        server_front->setFixedSize(front_pix.width()+10, front_pix.height()+10);
        grid_layout->addWidget(server_front,1,0,1,1, Qt::AlignLeft);

        QLabel * server_back = new QLabel(this);
        QPixmap back_pix(":/images/p750_rear.png");
        back_pix = back_pix.scaledToWidth(focus_frame->width()*2/5);
        server_back->setPixmap(back_pix);
        server_back->setFixedSize(back_pix.width()+10, back_pix.height()+10);
        //server_back->setStyleSheet("color: rbga(0,200,0 %100); border 2x solid green;");
        grid_layout->addWidget(server_back,2,0,1,1, Qt::AlignLeft);
        focus_frame->adjustSize();
        server_back->show();

        QLabel * server_top = new QLabel(this);
        QPixmap top_pix(":/images/p750_top.png");
        //top_pix = top_pix.scaledToWidth(focus_frame->width()*2/5);
        server_top->setPixmap(top_pix);
        server_top->setFixedSize(top_pix.width()+10, top_pix.height()+10);
        //server_top->setStyleSheet("color: rbga(0,200,0 %100); border 2x solid green;");
        server_top->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        grid_layout->addWidget(server_top,3,0,1,2, Qt::AlignCenter);

        focus_frame->adjustSize();
        server_top->show();
    }
    if(server_name.contains("770", Qt::CaseInsensitive)){
        QLabel * server_front = new QLabel(this);
        QPixmap front_pix(":/images/p770.png");
        front_pix = front_pix.scaledToWidth(focus_frame->width()*2/5);
        server_front->setPixmap(front_pix);
        server_front->setFixedSize(front_pix.width()+10, front_pix.height()+10);
        grid_layout->addWidget(server_front,1,0,1,1, Qt::AlignLeft);

        QLabel * server_back = new QLabel(this);
        QPixmap back_pix(":/images/p770_rear.png");
        back_pix = back_pix.scaledToWidth(focus_frame->width()*2/5);
        server_back->setPixmap(back_pix);
        server_back->setFixedSize(back_pix.width()+10, back_pix.height()+10);
        server_back->setStyleSheet("color: rbga(0,200,0 %100); border 2x solid green;");
        grid_layout->addWidget(server_back,2,0,1,1, Qt::AlignLeft);
        focus_frame->adjustSize();
        server_back->show();

        QLabel * server_top = new QLabel(this);
        QPixmap top_pix(":/images/p770_top.png");
        //top_pix = top_pix.scaledToWidth(focus_frame->width()*2/5);
        server_top->setPixmap(top_pix);
        server_top->setFixedSize(top_pix.width()+10, top_pix.height()+10);
        //server_top->setStyleSheet("color: rbga(0,200,0 %100); border 2x solid green;");
        grid_layout->addWidget(server_top,3,0,1,2, Qt::AlignCenter);
        focus_frame->adjustSize();
        server_top->show();
    }
    if(server_name.contains("780", Qt::CaseInsensitive)){
        QLabel * server_front = new QLabel(this);
        QPixmap front_pix(":/images/p780.png");
        front_pix = front_pix.scaledToWidth(focus_frame->width()*2/5);
        server_front->setPixmap(front_pix);
        server_front->setFixedSize(front_pix.width()+10, front_pix.height()+10);
        grid_layout->addWidget(server_front,1,0,1,1, Qt::AlignLeft);

        QLabel * server_back = new QLabel(this);
        QPixmap back_pix(":/images/p780_rear.png");
        back_pix = back_pix.scaledToWidth(focus_frame->width()*2/5);
        server_back->setPixmap(back_pix);
        server_back->setFixedSize(back_pix.width()+10, back_pix.height()+10);
        server_back->setStyleSheet("color: rbga(0,200,0 %100); border 2x solid green;");
        grid_layout->addWidget(server_back,2,0,1,1, Qt::AlignLeft);
        focus_frame->adjustSize();
        server_back->show();

        QLabel * server_top = new QLabel(this);
        QPixmap top_pix(":/images/p780_top.png");
        //top_pix = top_pix.scaledToWidth(focus_frame->width()*2/5);
        server_top->setPixmap(top_pix);
        server_top->setFixedSize(top_pix.width()+10, top_pix.height()+10);
        grid_layout->addWidget(server_top,3,0,1,2, Qt::AlignCenter);
        focus_frame->adjustSize();
        server_top->show();
    }

    if(server_name.contains("p6", Qt::CaseInsensitive) && server_name.contains("570", Qt::CaseInsensitive)){
        QLabel * server_front = new QLabel(this);
        QPixmap front_pix(":/images/p6-570_both.png");
        front_pix = front_pix.scaledToWidth(focus_frame->width()*2/5);
        server_front->setPixmap(front_pix);
        server_front->setFixedSize(front_pix.width()+10, front_pix.height()+10);
        grid_layout->addWidget(server_front,1,0,1,1, Qt::AlignLeft);

        QLabel * server_back = new QLabel(this);
        server_back->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        QPixmap back_pix(":/images/p6-570.png");
        //back_pix = back_pix.scaledToWidth(focus_frame->width()*2/5);
        server_back->setPixmap(back_pix);
        server_back->setFixedSize(back_pix.width()+10, back_pix.height()+10);
        grid_layout->addWidget(server_back,2,0,1,2, Qt::AlignCenter);

        server_back->show();
        focus_frame->adjustSize();

    }

    if(server_name.contains("p5", Qt::CaseInsensitive) && server_name.contains("570", Qt::CaseInsensitive)){

        QLabel * server_back = new QLabel(this);
        QPixmap back_pix(":/images/p5-570.png");
        back_pix = back_pix.scaledToWidth(focus_frame->width()/2);
        server_back->setPixmap(back_pix);
        server_back->setFixedSize(back_pix.width()+10, back_pix.height()+10);
        grid_layout->addWidget(server_back,2,0,1,1, Qt::AlignLeft);
        server_back->show();
        right_scroll_area->adjustSize();
        focus_frame->adjustSize();

    }

}
