#ifndef INFOPANE_H
#define INFOPANE_H

#include <QLabel>
#include <QScrollArea>
#include <QVBoxLayout>
#include <server.h>
#include <hmc.h>
#include <lpar.h>
#include <vector>
#include <hmclabel.h>
#include <serverlabel.h>
#include <lparlabel.h>

class InfoPane : public QScrollArea
{
    Q_OBJECT
public:
    InfoPane(QWidget *parent, int width, int height);
    QFrame * info_frame;
    QVBoxLayout * vertical_layout;
    bool search_results;

    std::vector<ServerLabel*> server_vector;
    std::vector<LparLabel*> lpar_vector;
    std::vector<HmcLabel*> hmc_vector;

signals:

public slots:
    void changeText(std::string param);
    void addServer(Server* param);
    void addLpar(Lpar* param);
    void addHmc(Hmc* param);
    void reset();

};

#endif // INFOPANE_H
