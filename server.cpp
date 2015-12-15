#include "server.h"

Server::Server(QWidget *parent,
               std::string rack_input,
               std::string name_input,
               std::string serial_input,
               std::string ip_string,
               Hmc * hmc_input,
               std::string description_input,
               std::string type_input,
               std::string model_input,
               std::string power_input,
               std::string proc_input,
               std::string mem_input) : QPushButton(parent)
{

    this->rack=rack_input;
    this->name=name_input;
    this->serial_number=serial_input;
    this->string_ip = ip_string;
    this->hmc_manager = hmc_input;
    this->description=description_input;
    this->type=type_input;
    this->model=model_input;
    this->power=power_input;
    this->processors=proc_input;
    this->memory=mem_input;
    this->processors_available = proc_input;
    this->memory_available = mem_input;
    setMouseTracking(true);
    connect(this, SIGNAL(clicked()), this, SLOT(clickSlot()));

}

void Server::mouseMoveEvent ( QMouseEvent * e ){
    emit hovered("PHYSICAL SERVER\n\n"+this->toString());

}

void Server::clickSlot(){
    qDebug()<<"clicked_on emitted";
    emit clicked_on(this);
}

std::string Server::getName(){
    return this->name;
}
std::string Server::getRack() const{
    return this->rack;
}

std::string Server::getSerialNum(){
    return this->serial_number;
}

std::string Server::getStringIP(){
    return this->string_ip;
}

std::string Server::getDescription(){
    return this->description;
}

std::string Server::getType(){
    return this->type;
}

std::string Server::getModel(){
    return this->model;
}

std::string Server::getPower(){
    return this->power;
}

std::string Server::getProcessors(){
    return this->processors;
}

std::string Server::getMemory(){
    return this->memory;
}

std::string Server::toString(){
    std::string to_return = "";
    to_return += "rack:\t\t"+this->rack+"\n";
    to_return += "name:\t\t"+this->name+"\n";
    to_return += "serial number:\t"+this->serial_number+"\n";
    to_return += "hmc ip:\t\t"+this->string_ip+"\n";
    to_return += "description:\t"+this->description+"\n";
    to_return += "type:\t\t"+this->type+"\n";
    to_return += "model:\t\t"+this->model+"\n";
    to_return += "power:\t\t"+this->power+"\n";
    to_return += "processors:\t"+this->processors+" CPUs\n";
    to_return += "memory:\t\t"+this->memory+" GB";

    return to_return;
}

/*
std::string Server::toString(){
    std::string to_return = "";
    to_return += "rack:                      "+this->rack+"\n";
    to_return += "name:                   "+this->name+"\n";
    to_return += "serial number:   "+this->serial_number+"\n";
    to_return += "hmc ip:                 "+this->string_ip+"\n";
    to_return += "description:        "+this->description+"\n";
    to_return += "type:                      "+this->type+"\n";
    to_return += "model:                  "+this->model+"\n";
    to_return += "power:                  "+this->power+"\n";
    to_return += "processors:         "+this->processors+" CPUs\n";
    to_return += "memory:              "+this->memory+" GB";

    return to_return;
}

*/
