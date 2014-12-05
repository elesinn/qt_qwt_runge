#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <functional>
#include <qwt_plot.h>
#include <qwt_plot_marker.h>
#include "qwt_plot_curve.h"

#include <qwt_plot_grid.h>

#include <qwt_legend.h>

#include <qwt_plot_curve.h>
#include <qwt_symbol.h>

#include <qwt_plot_magnifier.h>

#include <qwt_plot_panner.h>

#include <qwt_plot_picker.h>

#include <qwt_picker_machine.h>
using namespace std;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    void rk();
    int dim;

    typedef void (*func)(double *x, double t, double *P, double *y);
    double *K1, *K2, *K3, *K4, *K5, *K6, *Z, *R, *P, *x, *T;
    double err,tau,t,x0,x1,y0;
    void F(double *x, double t, double *P, double *y);

    int RKt(double *x, double &t, double err, double tau, int d);
    void ToScreen(double X, double Y, int& xs, int& ys);
    void ToWorld(int xs, int ys, double& X, double& Y);
    void DrawLine(double x1, double y1, double x2, double y2);
    double Xmin, Xmax, Ymin, Ymax;
    int N,K;
    void addPlot();
    void addPlotGrid();
    void Runge4(QMouseEvent *event);
    ~MainWindow();
private slots:
protected:
     virtual void mousePressEvent(QMouseEvent *event);
private:
    Ui::MainWindow *ui;
    QwtPlotCurve *curve;

   // QwtPlot *plot;



};

#endif // MAINWINDOW_H
