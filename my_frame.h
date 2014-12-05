#ifndef MY_FRAME_H
#define MY_FRAME_H

#include <QWidget>
#include <QMouseEvent>
#include <QDebug>
#include <QEvent>

class my_frame : public QWidget
{
    Q_OBJECT
public:
    explicit my_frame(QWidget *parent = 0);

    void mousePressEvent(QMouseEvent *ev,int xs, int ys);
    void mouseMoveEvent(QMouseEvent *ev);

    int x,y;

signals:
    void Mouse_Pressed();
    void Mouse_Pos();


public slots:

};

#endif // MY_FRAME_H
