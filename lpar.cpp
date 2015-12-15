#include "lpar.h"

Lpar::Lpar(QWidget *parent,
           std::string rack_input,
           std::string name_input,
           std::string serial_input,
           std::string string_ip,
           Hmc * hmc_input,
           Server * physical_server,
           std::string app_input,
           std::string description_input,
           std::string type_input,
           std::string model_input,
           std::string proc_input,
           std::string mem_input) : QPushButton(parent)
{
    this->rack=rack_input;
    this->name=name_input;
    this->serial_number=serial_input;
    this->ip_string = string_ip;
    this->hmc_manager = hmc_input;
    this->my_server = physical_server;
    this->application=app_input;
    this->description=description_input;
    this->type=type_input;
    this->model=model_input;

    this->processors=proc_input;
    this->memory=mem_input;
    setMouseTracking(true);

}

void Lpar::mouseMoveEvent ( QMouseEvent * e ){
    emit hovered("LOGICAL PARTITION\n\n"+this->toString());
    //qDebug()<< "LPar mouseevent fired";
}


std::string Lpar::getName(){
    return this->name;
}
std::string Lpar::getRack(){
    return this->rack;
}

std::string Lpar::getSerialNum(){
    return this->serial_number;
}
Server * Lpar::getServer(){
    return this->my_server;
}

std::string Lpar::getIP(){
    return this->ip_string;
}

Hmc * Lpar::getHmc(){
    return this->hmc_manager;
}

std::string Lpar::getDescription(){
    return this->description;
}
std::string Lpar::getApplication(){
    return this->application;
}

std::string Lpar::getType(){
    return this->type;
}

std::string Lpar::getModel(){
    return this->model;
}

std::string Lpar::getPower(){
    return this->power;
}

std::string Lpar::getProcessors(){
    return this->processors;
}

std::string Lpar::getMemory(){
    return this->memory;
}
bool Lpar::compareToLparIP(Lpar* param){
   // //qDebug()<<"Starting Comparison\nmy_string: " + QString::fromStdString(ip_string) + " vs " + QString::fromStdString(param->getIP());
    QStringList my_list = QString::fromStdString(ip_string).split(".");
    QStringList other_list = QString::fromStdString(param->getIP()).split(".");

    if(my_list.size() == 1){return false;}
    if(other_list.size() == 1){return true;}
    QString my_string;
    QString other_string;

    for(int x = 0; x< 4; x++){
        my_string = my_list.at(x);
        other_string = other_list.at(x);
        ////qDebug()<<"comparing "+ my_string+ " to " + other_string;
        if(my_string != other_string){
            ////qDebug()<<"not equal";
            if(my_string.toInt() < other_string.toInt()){
                ////qDebug()<<my_string+ "<"+ other_string;
            }//else{//qDebug()<<my_string+ ">"+ other_string;}
            return (my_string.toInt() < other_string.toInt());
        }
        //else{             ////qDebug()<<"equal, moving on";}

    }
    return false;

}

bool Lpar::compareToHmcIP(Hmc* param){
    ////qDebug()<<"Starting Comparison\nmy_string: " + QString::fromStdString(ip_string) + " vs " + QString::fromStdString(param->getIP());
    QStringList my_list = QString::fromStdString(ip_string).split(".");
    QStringList other_list = QString::fromStdString(param->getIP()).split(".");

    if(my_list.size() == 1){ return false;}
    if(other_list.size() == 1){return true;}
    QString my_string;
    QString other_string;

    for(int x = 0; x< 4; x++){
        my_string = my_list.at(x);
        other_string = other_list.at(x);
        ////qDebug()<<"comparing "+ my_string+ " to " + other_string;
        if(my_string != other_string){
            ////qDebug()<<"not equal";
            return (my_string.toInt() < other_string.toInt());
        }
        //else{             //qDebug()<<"equal, moving on";}

    }
    return false;

}


std::string Lpar::toString(){
    std::string to_return = "";
    to_return += "rack:                      "+this->rack+"\n";
    to_return += "name:                   "+this->name+"\n";
    to_return += "serial number:   "+this->serial_number+"\n";
    to_return += "ip:                          "+this->getIP()+"\n";
    to_return += "application:        "+this->application+"\n";
    if(this->description.size() > 30){
        QString to_transform(QString::fromStdString(this->description));
        to_return+= "description:        ";
        int index = 0;
        int next_index = 0;
        int d=32;
        while(index < to_transform.size()){
            next_index = to_transform.indexOf((char)d, index+15);
                //find((char)d, index+15);
            if(next_index == -1){
                to_return +=to_transform.toStdString().substr(index, this->description.size());
                break;
            }
            //qDebug()<<"\n\nindex = "+QString::number(index)+" adding \\"+QString::fromStdString(this->description.substr(index, next_index)) +"\\\n";
            to_return +=to_transform.toStdString().substr(index, next_index)+"\n\t";
            index = next_index;
            //qDebug()<<"newindex = "+ QString::number(index)+"\nTo_return up to " +QString::number(index)+":\n"+QString::fromStdString(to_return)+"\n";
        }
        to_return+="\n";
        //qDebug()<<"to_return final = "+QString::fromStdString(to_return)+"\nvs.\n"+QString::fromStdString(this->getDescription())+"\n";
    }
    else{to_return += "description:        "+this->description+"\n";}
    to_return += "type:                      "+this->type+"\n";
    to_return += "model:                  "+this->model+"\n";
    to_return += "processors:         "+this->processors+" CPUs\n";
    to_return += "memory:              "+this->memory + " GB";


    return to_return;
}




