#ifndef HMC_H
#define HMC_H
#include <string>
#include "QPushButton"
#include "QScrollArea"
#include "QVBoxLayout"
#include "QFrame"
#include "QDebug"
#include "QStringList"


class Server;

class Hmc : public QPushButton
{
    Q_OBJECT

inline bool operator < (const Hmc * hmc_2)
{

    return (this->getRack() < hmc_2->getRack());
}

inline bool operator > (const Hmc * hmc_2)
{
    qDebug() << "doing comparison";
    exit(0);
    return (this->getRack() < hmc_2->getRack());
}
public:
    Hmc(QWidget *parent,
        std::string rack_input,
        std::string name_input,
        std::string serial_input,
        std::string description_input,
        std::string ip_string);

    std::string getRack() const;
    std::string getName();
    std::string getSerialNum();
    std::string getDescription();
    std::string getIP();
    std::string toString();

    std::vector<Server *> getServerVector();

    std::vector<Server *> server_vector;




    void mouseMoveEvent ( QMouseEvent * e );
    void clicked(  QPushButton* );

    bool compareToHmcIP(Hmc* param);


private:
    std::string rack;
    std::string name;
    std::string serial_number;
    std::string description;
    std::string string_ip;

public slots:
   void receiveClick();

signals:
   void hovered(std::string param);
   void hmc_focus(Hmc *);

};

#endif // HMC_H
