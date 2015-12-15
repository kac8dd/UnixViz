#ifndef FOCUSDISPLAY_H
#define FOCUSDISPLAY_H

#include <QScrollArea>
#include <server.h>
#include <lpar.h>
#include <hmc.h>
#include <qframe.h>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QLabel>

class FocusDisplay : public QScrollArea
{
    Q_OBJECT
public:
    FocusDisplay(QWidget *parent, int width, int height);\

    QFrame * focus_frame;
    QGridLayout * grid_layout;
    QScrollArea * right_scroll_area;
    int width;
    int height;
    int num_rows;
    void serverFocus(Server * param);
    void hmcFocus(Hmc* param);
    void addPictures(Server * param);

signals:

public slots:

};

#endif // FOCUSDISPLAY_H
