#include "hmc.h"

Hmc::Hmc(QWidget *parent,
         std::string rack_input,
         std::string name_input,
         std::string serial_input,
         std::string description_input,
         std::string ip_string) : QPushButton(parent)
{

    this->rack=rack_input;
    this->name=name_input;
    this->serial_number=serial_input;
    this->description=description_input;

    this->string_ip = ip_string;
    setMouseTracking(true);

    connect(this, SIGNAL(released()), this, SLOT(receiveClick()));

}

void Hmc::receiveClick(){
    emit hmc_focus(this);
}
 void Hmc::mouseMoveEvent ( QMouseEvent * e ){
     emit hovered("HMC\n\n"+this->toString());


 }

 void clicked(  QPushButton* ){
     return;
 }


std::string Hmc::getName(){
    return name;
}

std::string Hmc::getRack() const{
    return rack;
}

std::string Hmc::getSerialNum(){
    return serial_number;
}

std::string Hmc::getDescription(){
    return description;
}



std::string Hmc::getIP(){
    return this->string_ip;
}


std::vector<Server *> Hmc::getServerVector(){
       return this->server_vector;
}

bool Hmc::compareToHmcIP(Hmc* param){
    //qDebug()<<"Starting Comparison\nmy_string: " + QString::fromStdString(string_ip) + " vs " + QString::fromStdString(param->getIP());
    QStringList my_list = QString::fromStdString(string_ip).split(".");
    QStringList other_list = QString::fromStdString(param->getIP()).split(".");

    if(my_list.size() == 0){ return false;}
    if(other_list.size() == 0){return true;}
    QString my_string;
    QString other_string;

    for(int x = 0; x< 4; x++){
        my_string = my_list.at(x);
        other_string = other_list.at(x);
        //qDebug()<<"comparing "+ my_string+ " to " + other_string;
        if(my_string != other_string){
            //qDebug()<<"not equal";
            return (my_string.toInt() < other_string.toInt());
        }
        //else{             qDebug()<<"equal, moving on";}

    }
    return false;

}

std::string Hmc::toString(){
    std::string to_return = "";
    to_return += "rack:\t\t"+this->rack+"\n";
    to_return += "name:\t\t"+this->name+"\n";
    to_return += "ip:\t\t"+this->string_ip+"\n";
    to_return += "description:\t"+this->description+"\n\0";


    return to_return;
}



