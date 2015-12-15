#ifndef SERVER_H
#define SERVER_H
#include <string>
#include <QPushButton>
#include <QDebug>
class Hmc;
class Lpar;

class Server : public QPushButton
{
    Q_OBJECT
    inline bool operator < (const Server * server_2)
    {

        return (this->getRack() < server_2->getRack());
    }
public:
    Server(QWidget *parent,
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
           std::string mem_input);

    std::string getName();
    std::string getRack() const;
    std::string getSerialNum();
    std::string getStringIP();
    std::string getDescription();
    std::string getType();
    std::string getModel();
    std::string getPower();
    std::string getProcessors();
    std::string getMemory();


    std::string toString();


    std::vector<Lpar *> lpar_vector;

    void mouseMoveEvent ( QMouseEvent * e );

    bool deduct_processors(int to_deduct);
    std::string processors_available;
    std::string memory_available;

private:
    std::string rack;
    std::string name;
    std::string serial_number;
    std::string string_ip;
    Hmc * hmc_manager;
    std::string description;
    std::string type;
    std::string model;
    std::string power;
    std::string processors;
    std::string memory;

signals:
   void hovered(std::string param);
   void clicked_on(Server *);

public slots:
   void clickSlot();


};

#endif // SERVER_H
