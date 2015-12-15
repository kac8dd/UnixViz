#include "infopane.h"
#include "qdebug.h"
#include "serverlabel.h"
#include "lparlabel.h"
#include "hmclabel.h"

InfoPane::InfoPane(QWidget *parent, int width, int height) :
    QScrollArea(parent)
{
    info_frame = new QFrame(this);
    this->setWidget(info_frame);
    search_results = false;
}

void InfoPane::changeText(std::string param){
    search_results = false;
    delete info_frame;
    info_frame = new QFrame(this);
    vertical_layout = new QVBoxLayout(this);
    vertical_layout->setSizeConstraint(QLayout::SetMinimumSize);
    this->setWidget(info_frame);
    info_frame->setLayout(vertical_layout);
    //info_frame->setFixedWidth(this->width()-20);
    //info_frame->setFixedHeight(this->height()-20);

    QLabel * info_label = new QLabel(this);
    info_label->setStyleSheet("color: rgba(0,200,0);");

    info_label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    info_label->setText(QString::fromStdString(param));
    vertical_layout->addWidget(info_label);
}

void InfoPane::reset(){

    delete info_frame;
    server_vector.clear();
    lpar_vector.clear();
    hmc_vector.clear();

    search_results = true;
    info_frame = new QFrame(this);
    vertical_layout = new QVBoxLayout(this);
    vertical_layout->setSizeConstraint(QLayout::SetMinimumSize);
    this->setWidget(info_frame);
    info_frame->setLayout(vertical_layout);
}

void InfoPane::addHmc(Hmc * param){
    //qDebug()<<"Info pane received signal correctly";
    //check if its the first returned search result
   //qDebug()<<"final spot test for info pane slot";

    HmcLabel * hmc_label = new HmcLabel(this, param);
    hmc_label->setStyleSheet("color: rgba(0,200,0); border: 2px solid red");

    hmc_label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    hmc_label->setText(QString::fromStdString(param->toString()));
    vertical_layout->addWidget(hmc_label);
    hmc_vector.push_back(hmc_label);
}


void InfoPane::addServer(Server* param){

    ServerLabel * server_label = new ServerLabel(this, param);
    server_label->setStyleSheet("color: rgba(0,200,0); border: 2px solid red; ");
    server_label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    server_label->setText(QString::fromStdString(param->toString()));
    vertical_layout->addWidget(server_label);
    qDebug()<<"server_vector.size() before = "+QString::number(server_vector.size());
    server_vector.push_back(server_label);
    qDebug()<<"server_vector.size() after = "+QString::number(server_vector.size());
}

void InfoPane::addLpar(Lpar* param){

    LparLabel * lpar_label = new LparLabel(this, param);
    lpar_label->setStyleSheet("color: rgba(0,200,0); border: 2px solid red; ");
    lpar_label->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    lpar_label->setText(QString::fromStdString(param->toString()));
    vertical_layout->addWidget(lpar_label);
    lpar_vector.push_back(lpar_label);
}
