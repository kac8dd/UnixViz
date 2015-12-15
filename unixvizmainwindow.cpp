#include "unixvizmainwindow.h"
#include "ui_unixvizmainwindow.h"
#include "thread"



//worker thread functions

using namespace QXlsx;


UnixVizMainWindow::UnixVizMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::UnixVizMainWindow)
{
    //////
    //create the ui and the vector of objects to delete
    ui->setupUi(this);

    //////
    //read excel file

    readSpreadsheet();

    //////
    //properly size the main window
    QRect rec = QApplication::desktop()->screenGeometry();
    this->main_window_height = rec.height()-100;
    this->main_window_width = rec.width()-100;
    this->setGeometry(0,20, this->main_window_width, this->main_window_height);

    //////
    //make the background pixmap objects
    this->original_bkgnd = new QPixmap(":/images/server_rows.jpg");
    this->current_bkgnd = new QPixmap(original_bkgnd->scaled(this->size(), Qt::IgnoreAspectRatio));

    //////
    //set the palette as the current background
    this->palette.setBrush(QPalette::Background, *current_bkgnd);
    this->setPalette(palette);


    //make and show the start button
    start_button = new QPushButton("Open UnixVix", this);
    start_button->setIcon(QIcon(":/images/Fleur_icon.png"));
    start_button->setIconSize(QSize(60, 30));
    connect(start_button, SIGNAL (released()),this, SLOT (enterDashboard()));
    start_button->show();

    //FSM variables
    home_screen = true;
    hmc_screen = false;
    rack_screen = false;
    subnet_screen = false;
    server_focus = false;
    hmc_focus = false;



}

void UnixVizMainWindow::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);

   //get the new size and dimensions
   QRect rec = this->geometry();
   this->main_window_height = rec.height();
   this->main_window_width = rec.width();

   //replace the background
   delete this->current_bkgnd;
   this->current_bkgnd = new QPixmap(original_bkgnd->scaled(this->size(), Qt::IgnoreAspectRatio));

   this->palette.setBrush(QPalette::Background, *current_bkgnd);
   this->setPalette(palette);

   this->start_button->setVisible(!start_button->isHidden());

   if(home_screen){
       //re-place the start button
       this->start_button->setGeometry(this->main_window_width/2-90, this->main_window_height/2-25, 180, 50);
   }
   if(hmc_screen){
       info_panel->setGeometry(main_window_width/4*3-20, main_window_height/5, main_window_width/4+20, main_window_height/5*4-30);
       hmc_view->setGeometry(main_window_width/25, main_window_height/5, main_window_width/4*3-80, main_window_height/5*4-30);
       search_line_edit->setGeometry(main_window_width*3/4+60,main_window_height/6, main_window_width/4-80,20); ///, main_window_height/5*2, 80, 20);
       search_label->setGeometry(main_window_width*3/4-7,main_window_height/6, 60, 20);

   }
   if(rack_screen){
       info_panel->setGeometry(main_window_width/4*3-20, main_window_height/5, main_window_width/4+20, main_window_height/5*4-30);
       rack_view->setGeometry(main_window_width/25, main_window_height/5, main_window_width/4*3-80, main_window_height/5*4-30);
       search_line_edit->setGeometry(main_window_width*3/4+60,main_window_height/6, main_window_width/4-80,20); ///, main_window_height/5*2, 80, 20);
       search_label->setGeometry(main_window_width*3/4-7,main_window_height/6, 60, 20);
   }



}


////////////////////////////////////////////////////////////////////////
/// SLOTS
///
///
void UnixVizMainWindow::serverFocus(Server * param){

   emit reset();
   hmc_view->hide();
   rack_view->hide();
   subnet_view->hide();
   server_focus = true;
   hmc_screen = false;
   subnet_screen = false;

   focus_view->hide();
   focus_view->serverFocus(param);
   focus_view->show();

   emit setServer(param->toString());

}
void UnixVizMainWindow::hmcFocus(Hmc * param){

    hmc_view->hide();
    rack_view->hide();
    subnet_view->hide();
    //tabbed_hmc_display_area->hide();
    hmc_screen = false;

    hmc_focus = true;

    focus_view->hmcFocus(param);
    focus_view->show();
    return;

}
#include <hmcdisplay.h>
void UnixVizMainWindow::switchToHmcView(){


    if(server_focus){
        server_focus = false;
        focus_view->hide();
    }
    if(hmc_focus){
        hmc_focus = false;
        focus_view->hide();
    }
    if(rack_screen){
        rack_screen = false;
        rack_view->hide();
    }
    if(subnet_screen){
        subnet_screen = false;
        subnet_view->hide();
    }
    hmc_view->show();
    hmc_screen = true;
    //tabbed_hmc_display_area->show();

}

void UnixVizMainWindow::switchToRackView(){

    //tabbed_hmc_display_area->hide();

    if(hmc_focus){
        hmc_focus = false;
        hmc_view->hide();
    }
    if(server_focus){
        server_focus = false;
        focus_view->hide();
    }
    if(hmc_screen){
        hmc_screen = false;
        hmc_view->hide();
    }
    if(subnet_screen){
        subnet_screen = false;
        subnet_view->hide();
    }
    rack_view->show();
    //tabbed_server_display_area->show();
    rack_screen = true;
}
void UnixVizMainWindow::switchToSubnetView(){
    hmc_view->hide();
    rack_view->hide();
    focus_view->hide();
    //tabbed_hmc_display_area->hide();

    if(hmc_focus){
        hmc_focus = false;
        hmc_view->hide();
    }
    if(server_focus){
        server_focus = false;
        focus_view->hide();
    }
    if(hmc_screen){
        hmc_screen = false;
        hmc_view->hide();
    }
    if(rack_screen){
        rack_screen = false;
        rack_view->hide();
    }
    subnet_view->show();
    //tabbed_server_display_area->show();
    subnet_screen = true;

}

/////////////////////////////////////////////////////////
////sort functions to sort hmc and server vectors by rack
/// and then IP
bool compareHmc(Hmc* hmc_1, Hmc* hmc_2){
    return (hmc_1->getRack() < hmc_2->getRack());
}

bool compareServer(Server* server_1, Server* server_2){
    return (server_1->getRack() < server_2->getRack());
}

bool compareHmcIP(Hmc* hmc_1, Hmc* hmc_2){

    return (hmc_1->compareToHmcIP(hmc_2));
}

bool compareLparIP(Lpar* lpar_1, Lpar* lpar_2){

    return (lpar_1->compareToLparIP(lpar_2));
}
////////////////////////////////////////////////////
/// initalize function
void UnixVizMainWindow::enterDashboard(){

    home_screen=false;
    hmc_screen=true;

    focus_view = new FocusDisplay(this, main_window_width, main_window_height);

    this->start_button->hide();

    //make search box and label
    search_line_edit = new QLineEdit(this);
    search_line_edit->setGeometry(main_window_width*3/4+60,main_window_height/6, main_window_width/4-80,20); ///, main_window_height/5*2, 80, 20);

    search_line_edit->show();
    search_label = new QLabel("Search: ",this);
    search_label->setGeometry(main_window_width*3/4-7,main_window_height/6, 60, 20);
    search_label->setStyleSheet("background-color : rgba(0,0,0,0%); color : rgba(0,200,0,100%); border: 2px solid");
    search_label->show();

    connect(search_line_edit, SIGNAL(textEdited(QString)), this, SLOT(search(QString)));

    //make button to switch to rack_mode
    view_selection_frame = new QFrame(this);
    view_selection_frame->setGeometry(main_window_width/2-185, 18, 370, 50);


    QHBoxLayout *view_selection_layout = new QHBoxLayout();
    view_selection_frame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    view_selection_frame->setObjectName("switch_view_mode");
    view_selection_frame->setStyleSheet("#switch_view_mode {background-color : rgba(0,0,0,60%); color : rgba(0,200,0,100%); border: 2px solid green;}");
    view_selection_frame->setLayout(view_selection_layout);
    view_selection_frame->show();

    QLabel * view_mode_label = new QLabel("Select view: ");
    view_mode_label->setFrameStyle(QFrame::StyledPanel);
    view_mode_label->setStyleSheet("background-color : rgba(0,0,0,0%); color : rgba(0,200,0);");
    view_mode_label->setFixedSize(100, 30);
    view_selection_layout->addWidget(view_mode_label, Qt::AlignLeft);
    //view_mode_label->raise();

    QPushButton * rack_mode = new QPushButton(this);
    rack_mode->setText("rack");
    rack_mode->setStyleSheet("background-color : rgba(100,100,100,%80;");
    view_selection_layout->addWidget(rack_mode, Qt::AlignLeft);

    rack_mode->setFixedSize(80, 30);
    connect(rack_mode, SIGNAL(released()), this, SLOT(switchToRackView()));
    rack_mode->show();
    rack_mode->raise();

    QPushButton * hmc_mode = new QPushButton(this);
    hmc_mode->setText("hmc");
    hmc_mode->setStyleSheet("background-color : rgba(100,100,100,%80;");
    view_selection_layout->addWidget(hmc_mode, Qt::AlignLeft);

    hmc_mode->setFixedSize(80, 30);
    connect(hmc_mode, SIGNAL(released()), this, SLOT(switchToHmcView()));
    hmc_mode->show();
    hmc_mode->raise();

    QPushButton * subnet_mode = new QPushButton(this);
    subnet_mode->setText("subnet");
    subnet_mode->setStyleSheet("background-color : rgba(100,100,100,%80;");
    view_selection_layout->addWidget(subnet_mode, Qt::AlignLeft);

    subnet_mode->setFixedSize(80, 30);
    connect(subnet_mode, SIGNAL(released()), this, SLOT(switchToSubnetView()));
    subnet_mode->show();
    subnet_mode->raise();

    //make the scroll area
    /*scroll_panel_info_area = new QScrollArea(this);
    scroll_panel_info_area->setGeometry(main_window_width/4*3, main_window_height/5, main_window_width/4-30, main_window_height/5*4-30);
    scroll_panel_info_area->setStyleSheet("background-color : rgba(0,0,0,70%); color : green;");
    scroll_panel_info_area->setContentsMargins(50,50,50,50);
*/
    //make the expandable QLabel to go inside it
    info_panel = new InfoPane(this,main_window_width, main_window_height);
    info_panel->setGeometry(main_window_width/4*3-20, main_window_height/5, main_window_width/4+20, main_window_height/5*4-30);
    info_panel->setStyleSheet("background-color : rgba(0,0,0,70%); color : green;");
    info_panel->setContentsMargins(50,50,50,50);

    connect(this, SIGNAL(reset()),  info_panel, SLOT(reset()));
    connect(this, SIGNAL(foundHmcResult(Hmc*)), info_panel, SLOT(addHmc(Hmc*)));
    connect(this, SIGNAL(foundServerResult(Server*)), info_panel, SLOT(addServer(Server*)));
    connect(this, SIGNAL(foundLparResult(Lpar*)), info_panel, SLOT(addLpar(Lpar*)));
    connect(this, SIGNAL(foundHmcResult(Hmc*)), info_panel, SLOT(addHmc(Hmc*)));
    connect(this, SIGNAL(setServer(std::string)), info_panel, SLOT(changeText(std::string)));


    info_panel->show();

    std::sort(edc_hmc_vector.begin(), edc_hmc_vector.end(), &compareHmc);
    std::sort(sfmc_hmc_vector.begin(), sfmc_hmc_vector.end(), &compareHmc);
    std::sort(edc_server_vector.begin(), edc_server_vector.end(), &compareServer);
    std::sort(sfmc_server_vector.begin(), sfmc_server_vector.end(), &compareServer);

    hmc_view = new HmcDisplay(this, main_window_width, main_window_height, edc_hmc_vector, sfmc_hmc_vector, info_panel);
    for(int x = 0; x< hmc_view->hmc_labels.size(); x++){
        connect(hmc_view->hmc_labels.at(x), SIGNAL(hmc_focus(Hmc*)), this, SLOT(hmcFocus(Hmc*)));
    }
    for(int y = 0; y<hmc_view->server_buttons.size(); y++){
        connect(hmc_view->server_buttons.at(y), SIGNAL(server_focus(Server*)), this, SLOT(serverFocus(Server*)));
    }

    hmc_view->setGeometry(main_window_width/25, main_window_height/5, main_window_width/4*3-80, main_window_height/5*4-30);

    hmc_view->show();

    rack_view = new RackDisplay(this, main_window_width, main_window_height, edc_hmc_vector, sfmc_hmc_vector, edc_server_vector, sfmc_server_vector, info_panel);
    for(int x = 0; x< rack_view->hmc_buttons.size(); x++){
        connect(rack_view->hmc_buttons.at(x), SIGNAL(hmc_focus(Hmc*)), this, SLOT(hmcFocus(Hmc*)));
    }
    for(int y = 0; y<rack_view->server_buttons.size(); y++){
        connect(rack_view->server_buttons.at(y), SIGNAL(server_focus(Server*)), this, SLOT(serverFocus(Server*)));
    }
    rack_view->setGeometry(main_window_width/25, main_window_height/5, main_window_width/4*3-80, main_window_height/5*4-30);
            //buildHmcView();

    std::sort(sfmc_hmc_vector.begin(), sfmc_hmc_vector.end(), &compareHmcIP);
    std::sort(edc_hmc_vector.begin(), edc_hmc_vector.end(), &compareHmcIP);
    std::sort(edc_lpar_vector.begin(), edc_lpar_vector.end(), &compareLparIP);
    std::sort(sfmc_lpar_vector.begin(), sfmc_lpar_vector.end(), &compareLparIP);


    subnet_view = new SubnetDisplay(this, main_window_width, main_window_height, edc_hmc_vector, sfmc_hmc_vector, edc_lpar_vector, sfmc_lpar_vector, info_panel);
    subnet_view->setGeometry(main_window_width/25, main_window_height/5, main_window_width/4*3-80, main_window_height/5*4-30);

    for(int y = 0; y<subnet_view->hmc_buttons.size(); y++){
        //qDebug()<<"connecting hmc button #"+ QString::number(y);
        connect(subnet_view->hmc_buttons.at(y), SIGNAL(hmc_focus(Hmc*)), this, SLOT(hmcFocus(Hmc*)));
    }
    for(int y = 0; y<subnet_view->lpar_buttons.size(); y++){
        //qDebug()<<"connecting hmc button #"+ QString::number(y);
        connect(subnet_view->lpar_buttons.at(y), SIGNAL(lpar_focus(Server*)), this, SLOT(serverFocus(Server*)));
    }
}

///////////////////////////////////////////
/// \brief readSpreadsheet
/// \param param
/// \return void *
///     This is the worker thread that reads the spreadsheet
///     and constructs the objects in memory
void * UnixVizMainWindow::readSpreadsheet(){

    UnixVizMainWindow * main_window = this;

    //open up the spreadsheet
    QString filePath = QString("/home/webmin/QT_PROJECTS/UnixViz/Unix_Master_Spreadsheet.xlsx");

    QXlsx::Document xlsx(filePath);

    for(int x=0; x < 2; x++){

        if(x==0){xlsx.selectSheet(QString("EDC"));}
        if(x==1){xlsx.selectSheet(QString("SFMC"));}


        int row = 2;
        Hmc * last_hmc;
        Server * last_server;
        Lpar * last_lpar;



        while(true) {
            //grab the next row in the book and use it, break if finished
            if (QXlsx::Cell *cell=xlsx.cellAt(row, 2)){

                //if not an empty row, then parse it and create an object
                if(cell->value().toString() != ""){

                    //if its an hmc, then make an hmc object
                    if (cell->value().toString().contains("HMC") || cell->value().toString().contains("hmc") || cell->value().toString().contains("Hmc")){
                        //qDebug()<<"Found an HMC - "+cell->value().toString();

                        ////////////////////////////////////////////////////////
                        //parse the ip address

                        std::string ip_string = xlsx.cellAt(row, 5)->value().toString().toStdString();
                        //qDebug()<<"ip address = "+QString::fromStdString(ip_string);


                        last_hmc = new Hmc(main_window,
                                    xlsx.cellAt(row, 1)->value().toString().toStdString(),
                                    xlsx.cellAt(row, 2)->value().toString().toStdString(),
                                    xlsx.cellAt(row, 3)->value().toString().toStdString(),
                                    xlsx.cellAt(row, 7)->value().toString().toStdString(),
                                    ip_string);

                        last_hmc->setVisible(false);
                        //qDebug()<<"\ntoString yeilds :"+QString::fromStdString(last_hmc->toString()) + "\n\n";

                        if(x==0){
                            edc_hmc_vector.push_back(last_hmc);
                        }else{
                            sfmc_hmc_vector.push_back(last_hmc);
                        }
                    }

                    //if its an LPAR, then make a new lpar object
                    else if(xlsx.cellAt(row, 2)->value().toString().contains("edc", Qt::CaseInsensitive) ||xlsx.cellAt(row, 9)->value().toString() == "LPAR" || xlsx.cellAt(row, 9)->value().toString() == "lpar" || xlsx.cellAt(row, 9)->value().toString() == "Lpar"){
                        //qDebug()<<"Found an lpar - "+cell->value().toString();

                        std::string ip_string = xlsx.cellAt(row, 4)->value().toString().toStdString();
                        //qDebug()<<"ip address = "+QString::fromStdString(ip_string);


                        std::string proc;
                        std::string mem;

                        //try catch for empty rows
                        try{
                            proc = xlsx.cellAt(row, 11)->value().toString().toStdString();
                        }
                        catch(int error_code){
                            proc = "";
                        }
                        try{
                            mem = xlsx.cellAt(row, 12)->value().toString().toStdString();
                        }
                        catch(int error_code){
                            mem = "";
                        }

                        last_lpar = new Lpar(main_window,
                            xlsx.cellAt(row, 1)->value().toString().toStdString(),
                            xlsx.cellAt(row, 2)->value().toString().toStdString(),
                            xlsx.cellAt(row, 3)->value().toString().toStdString(),
                            ip_string,
                            last_hmc,
                            last_server,
                            xlsx.cellAt(row, 6)->value().toString().toStdString(),
                            xlsx.cellAt(row, 7)->value().toString().toStdString(),
                            xlsx.cellAt(row, 8)->value().toString().toStdString(),
                            xlsx.cellAt(row, 9)->value().toString().toStdString(),
                            proc, mem);
                        last_lpar->setVisible(false);

                            last_server->lpar_vector.push_back(last_lpar);

                            if(x==0){
                                edc_lpar_vector.push_back(last_lpar);
                            }else{
                                sfmc_lpar_vector.push_back(last_lpar);
                            }



                            //qDebug() << QString::number(last_server->getLparVector().size()) + " lpars so far on this server";
                            //qDebug()<< "NEW LPAR AS STRING \n" +QString::fromStdString(last_lpar->toString());






                    }
                    //otherwise its a physical server, make a new server object
                    else{
                        ////////////////////////////////////////////////////////
                        //parse the ip address

                        std::string ip_string = xlsx.cellAt(row, 5)->value().toString().toStdString();
                        //qDebug()<<"Found server\nip address = "+QString::fromStdString(ip_string);


                        //qDebug()<<"current row - "+QString::number(row);

                        std::string proc;
                        std::string mem;


                            proc = xlsx.cellAt(row, 11)->value().toString().toStdString();

                        try{
                            mem = xlsx.cellAt(row, 12)->value().toString().toStdString();
                        }
                        catch(int error_code){
                            mem = "";
                        }

                        last_server = new Server(main_window,
                            xlsx.cellAt(row, 1)->value().toString().toStdString(),
                            xlsx.cellAt(row, 2)->value().toString().toStdString(),
                            xlsx.cellAt(row, 3)->value().toString().toStdString(),
                            ip_string,
                            last_hmc,
                            xlsx.cellAt(row, 7)->value().toString().toStdString(),
                            xlsx.cellAt(row, 8)->value().toString().toStdString(),
                            xlsx.cellAt(row, 9)->value().toString().toStdString(),
                            xlsx.cellAt(row, 10)->value().toString().toStdString(),
                            proc, mem);


                        last_server->setVisible(false);
                        last_hmc->server_vector.push_back(last_server);
                        if(x==0){
                            edc_server_vector.push_back(last_server);
                           // //qDebug()<<"edc_server_vector.size() = "+QString::number(edc_server_vector.size());
                        }else{
                            sfmc_server_vector.push_back(last_server);
                            //qDebug()<<"sfmc_server_vector.size() = "+QString::number(sfmc_server_vector.size());
                        }

                    }

                }
                row++;
            }
            else break;
        }
    }

}

void UnixVizMainWindow::search(QString param){


    search_string = param;
    std::thread t(&UnixVizMainWindow::search_thread, this);
    t.detach();


}

void UnixVizMainWindow::search_thread(){

    QString param(this->search_string);
    //QString param(thread_param*);
    //qDebug()<<"Searching for \""+param+"\"";

        if(param.length() > 2){
            //qDebug()<<"criteria matched";
            emit(reset());//info_panel->reset();

            for(int x = 0; x < edc_hmc_vector.size(); x++){
                if(QString::fromStdString(edc_hmc_vector.at(x)->toString()).contains(param, Qt::CaseInsensitive)){
                    //qDebug()<<"Found match: "+QString::fromStdString(edc_hmc_vector.at(x)->toString());
                    emit foundHmcResult(edc_hmc_vector.at(x));
                }
            }
            for(int x = 0; x < sfmc_hmc_vector.size(); x++){
                if(QString::fromStdString(sfmc_hmc_vector.at(x)->toString()).contains(param, Qt::CaseInsensitive)){
                    //qDebug()<<"Found match: "+QString::fromStdString(sfmc_hmc_vector.at(x)->toString());
                    emit foundHmcResult(sfmc_hmc_vector.at(x));

                }
            }
            for(int x = 0; x < edc_server_vector.size(); x++){
                if(QString::fromStdString(edc_server_vector.at(x)->toString()).contains(param, Qt::CaseInsensitive)){
                    //qDebug()<<"Found match: "+QString::fromStdString(edc_server_vector.at(x)->toString());
                    emit foundServerResult(edc_server_vector.at(x));
                }

                for(int y = 0; y < edc_server_vector.at(x)->lpar_vector.size(); y++){
                    if(QString::fromStdString(edc_server_vector.at(x)->lpar_vector.at(y)->toString()).contains(param, Qt::CaseInsensitive)){
                        emit foundLparResult(edc_server_vector.at(x)->lpar_vector.at(y));
                    }

                }
            }
            for(int x = 0; x < sfmc_server_vector.size(); x++){
                if(QString::fromStdString(sfmc_server_vector.at(x)->toString()).contains(param, Qt::CaseInsensitive)){
                    //qDebug()<<"Found match: "+QString::fromStdString(sfmc_server_vector.at(x)->toString());
                    emit foundServerResult(sfmc_server_vector.at(x));

                }
                for(int y = 0; y < edc_server_vector.at(x)->lpar_vector.size(); y++){
                    if(QString::fromStdString(edc_server_vector.at(x)->lpar_vector.at(y)->toString()).contains(param, Qt::CaseInsensitive)){
                        emit foundLparResult(edc_server_vector.at(x)->lpar_vector.at(y));
                    }

                }
            }
            std::this_thread::sleep_for(std::chrono::seconds(2));
            //qDebug()<<"size = "+QString::number(info_panel->server_vector.size());
            for(int x = 0; x < info_panel->server_vector.size();x++){
                connect(info_panel->server_vector.at(x), SIGNAL(server_focus(Server*)), this, SLOT(serverFocus(Server*)));
            }
            for(int x = 0; x < info_panel->hmc_vector.size();x++){
                connect(info_panel->hmc_vector.at(x), SIGNAL(hmc_focus(Hmc*)), this, SLOT(hmcFocus(Hmc*)));
            }
            for(int x = 0; x < info_panel->lpar_vector.size();x++){
                //qDebug()<<"connecting lparlabel # "+ QString::number(x);
                connect(info_panel->lpar_vector.at(x), SIGNAL(lpar_focus(Server*)), this, SLOT(serverFocus(Server*)));
            }
        }
}



UnixVizMainWindow::~UnixVizMainWindow(){

}
