#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "math.h"
#include <qwt_plot.h>
#include <qwt_plot_marker.h>
#include <QPainter>
#include <QMouseEvent>
#include <QPolygonF>
#include <QPointF>
#include "qwt_plot_curve.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    dim=5;
    K1=new double(dim);
    K2=new double(dim);
    K3=new double(dim);
    K4=new double(dim);
    K5=new double(dim);
    K6=new double(dim);
    Z=new double(dim);
    R=new double(dim);
    P=new double(dim);
    x=new double(dim);
    T=new double(dim);
    Xmin = -5, Xmax =5  , Ymin = -5, Ymax = 5;
    err=0.01;
    tau=0.1;
    t=1;
    N=60;
    addPlot();
    addPlotGrid();
    setCentralWidget(ui->Qwt_widget);
    ui->Qwt_widget->setAxisScale(QwtPlot::xBottom, Xmin,Xmax,1);
    ui->Qwt_widget->setAxisScale(QwtPlot::yLeft, Ymin, Ymax,1);
}

void MainWindow::addPlot()
{
    ui->Qwt_widget->setTitle( "График" );
    ui->Qwt_widget->setCanvasBackground( Qt::white );
    // Параметры осей координат
    ui->Qwt_widget->setAxisTitle(QwtPlot::yLeft, "Y");
    ui->Qwt_widget->setAxisTitle(QwtPlot::xBottom, "X");
    ui->Qwt_widget->insertLegend( new QwtLegend() );
}

void MainWindow::addPlotGrid()
{

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setMajorPen(QPen( Qt::gray, 2 ));
    grid->attach( ui->Qwt_widget );
}


void MainWindow::F(double *x, double t, double *P, double *y)
{
        y[0]=x[1];
        y[1]=-x[0]+sin(t);
}
int MainWindow::RKt(double *x, double &t, double err, double tau, int d)
{
int i;
double Rmax=0;
F(x,t,P,K1);
for(i=0;i<d;i++)
Z[i]=K1[i]*tau/2.+x[i];
F(Z,t+tau/2,P,K2);
for(i=0;i<d;i++)
Z[i]=(K1[i]+K2[i])*tau/4.+x[i];
F(Z,t+tau/2.,P,K3);
for(i=0;i<d;i++)
Z[i]=x[i]-tau*K2[i]+2*tau*K3[i];
F(Z,t+tau,P,K4);
for(i=0;i<d;i++)
Z[i]=x[i]+tau/27.*(7*K1[i]+10*K2[i]+K4[i]);
F(Z,t+2./3*tau,P,K5);
for(i=0;i<d;i++)
Z[i]=x[i]+tau/625.*(28*K1[i]-125*K2[i]+546*K3[i]+54*K4[i]-378*K5[i]);
F(Z,t+tau/5,P,K6);

for(i=0;i<d;i++)
{
R[i]=tau/336*(42*K1[i]+224*K3[i]+21*K4[i]-162*K5[i]-125*K6[i]);
if(R[i]>Rmax)Rmax=R[i];
}
if(Rmax>err)return 1;
else
{
for(i=0;i<d;i++)
 x[i]=x[i]+tau/6*(K1[i]+4*K3[i]+K4[i]);
t+=tau;
return 0;
}
}

void MainWindow::ToScreen(double X, double Y, int &xs, int &ys)
{
    xs = (X-Xmin)/(Xmax-Xmin)*ui->Qwt_widget->size().width();
    ys = (Ymax-Y)/(Ymax-Ymin)*ui->Qwt_widget->size().height();
}

void MainWindow::ToWorld(int xs, int ys, double &X, double &Y)
{

        X = Xmin+xs*(Xmax-Xmin)/ui->Qwt_widget->size().width();
        Y = Ymax-ys*(Ymax-Ymin)/ui->Qwt_widget->size().height();

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Runge4(QMouseEvent *event)
{
    curve =new QwtPlotCurve();
    curve->setRenderHint(QwtPlotItem::RenderAntialiased);
    curve->setPen(QPen(Qt::blue));
    QPolygonF points;
    double x0, x1, t0;
    int rk;
    QPoint click=  event->pos();
    int xScreen = click.x();
    int yScreen = click.y();
    double xWorld;
    double yWorld;
    ToWorld(xScreen, yScreen, xWorld, yWorld);
    x[0] = xWorld;
    x[1] = yWorld;
    for(int i = 0; i < N; i++)
    {

        x0 = x[0];
        x1 = x[1];
        t0 = t;
        rk = RKt(x, t0, err, tau, 2);
        t = t0;

        if(rk == 0)
        {
           points<<QPointF(x0,x1)<<QPointF(x[0],x[1]);
              curve->setSamples(points);
              curve->attach(ui->Qwt_widget);
        }
        else
        {
            break;
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
                   Runge4(event);
    }
    ui->Qwt_widget->replot();
    ui->Qwt_widget->show();
}


