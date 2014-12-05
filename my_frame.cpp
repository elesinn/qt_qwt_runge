#include "my_frame.h"

my_frame::my_frame(QWidget *parent) :
    QWidget(parent)
{
}

void my_frame::mousePressEvent(QMouseEvent *ev,int xs, int ys)
{
   xs=ev->x();
   ys=ev->y();
   emit Mouse_Pressed();
}

void my_frame::mouseMoveEvent(QMouseEvent *ev)
{
    this->x=ev->x();
    this->y=ev->y();
    emit Mouse_Pos();
}
