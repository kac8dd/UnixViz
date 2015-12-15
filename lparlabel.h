#ifndef LPARLABEL_H
#define LPARLABEL_H

#include <QLabel>
#include <lpar.h>

class LparLabel : public QLabel
{
    Q_OBJECT
public:
    LparLabel(QWidget *parent, Lpar * param);
    Lpar * my_lpar;

    void mouseMoveEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);

signals:
    void lpar_focus(Server * param);
    void hovered(std::string param);


public slots:

};

#endif // LPARLABEL_H
