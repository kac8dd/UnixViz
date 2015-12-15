#ifndef LPAR_H
#define LPAR_H
#include <string>
#include <QPushButton>
#include <qdebug.h>
#include <hmc.h>

class Server;

class Lpar : public QPushButton
{
    Q_OBJECT
public:
    Lpar(QWidget *parent,
         std::string rack_input,
         std::string name_input,
         std::string serial_input,
         std::string ip_string,
         Hmc * hmc_input,
         Server * physical_server,

         std::string app_input,
         std::string description_input,
         std::string type_input,
         std::string model_input,

         std::string proc_input,
         std::string mem_input);
         void mouseMoveEvent ( QMouseEvent * e );

    //GETs
    std::string getRack();
    std::string getName();
    std::string getSerialNum();
    std::string getIP();
    std::string getApplication();
    std::string getDescription();
    std::string getType();
    std::string getModel();
    std::string getPower();
    std::string getProcessors();
    std::string getMemory();
    std::string toString();

    Hmc * getHmc();
    Server * getServer();

    bool compareToLparIP(Lpar * param);
    bool compareToHmcIP(Hmc* param);



private:
    //string fields
    std::string rack;
    std::string name;
    std::string serial_number;
    std::string ip_string;
    Hmc * hmc_manager;
    Server * my_server;
    std::string application;
    std::string description;
    std::string type;
    std::string model;
    std::string power;
    std::string processors;
    std::string memory;

    //On screen button
    QPushButton* lpar_button;

signals:
   void hovered(std::string param);

};

#endif // LPAR_H
