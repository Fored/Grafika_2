#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTime"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    ui->setupUi(this);
    d_plot = new QwtPlot( ui->widget );
    d_plot->resize(500,500);
    d_plot->setCanvasBackground( Qt::white ); // цвет фона
    // Включить сетку
    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setMajorPen(QPen( Qt::gray, 2 )); // цвет линий и толщина
    grid->attach( d_plot ); // добавить сетку к полю графика
    // Кривая
    QwtPlotCurve *curve = new QwtPlotCurve();
    QwtPlotCurve *curve2 = new QwtPlotCurve();
    curve2->setStyle(QwtPlotCurve:: Dots);
    //QwtPlotCurve::setStyle(QwtPlotCurve:: Dots);
    curve->setPen( Qt::blue, 6 ); // цвет и толщина кривой
    curve->setRenderHint( QwtPlotItem::RenderAntialiased, true ); // сглаживание
    // Маркеры кривой
    QwtSymbol *symbol = new QwtSymbol( QwtSymbol::Ellipse,
        QBrush( Qt::yellow ), QPen( Qt::red, 2 ), QSize( 8, 8 ) );
    curve2->setSymbol( symbol );
    gsch();
    beze(splayn_x[0],splayn_y[0],splayn_x[1],splayn_y[1],splayn_x[2],splayn_y[2],(splayn_x[2]+splayn_x[3])/2,(splayn_y[2]+splayn_y[3])/2);
    for (int i = 2; i<11; i = i + 2)
    {
        beze((splayn_x[i]+splayn_x[i+1])/2,(splayn_y[i]+splayn_y[i+1])/2, splayn_x[i+1],splayn_y[i+1],splayn_x[i+2],splayn_y[i+2],(splayn_x[i+2]+splayn_x[i+3])/2,(splayn_y[i+2]+splayn_y[i+3])/2);
    }
    beze((splayn_x[12]+splayn_x[13])/2,(splayn_y[12]+splayn_y[13])/2, splayn_x[13],splayn_y[13], splayn_x[14],splayn_y[14], splayn_x[14],splayn_y[14]);



    curve->setSamples( points ); // ассоциировать набор точек с кривой
    curve->attach( d_plot ); // отобразить кривую на график
    curve2->setSamples( points2 );
    curve2->attach( d_plot );
    // Включить возможность приближения/удаления графика
    QwtPlotMagnifier *magnifier = new QwtPlotMagnifier(d_plot->canvas());
    // клавиша, активирующая приближение/удаление
    magnifier->setMouseButton(Qt::MidButton);
    // Включить возможность перемещения по графику
    QwtPlotPanner *d_panner = new QwtPlotPanner( d_plot->canvas() );
    // клавиша, активирующая перемещение
    d_panner->setMouseButton( Qt::RightButton );
}
void MainWindow:: beze(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3)
{
    double x,y;
    points2 << QPointF(x0, y0) << QPointF(x1, y1) << QPointF(x2, y2) << QPointF(x3, y3);
    for (double t = 0; t < 1; t = t + 0.01 )
    {
        x = (1-t)*(1-t)*(1-t)*x0 + 3*t*(1-t)*(1-t)*x1 + 3*t*t*(1-t)*x2 + t*t*t*x3;
        y = (1-t)*(1-t)*(1-t)*y0 + 3*t*(1-t)*(1-t)*y1 + 3*t*t*(1-t)*y2 + t*t*t*y3;
        points << QPointF(x, y);
    }
}
void MainWindow::gsch()
{
    for (int i = 0; i < 15; i++)
    {
        splayn_x[i] = qrand() % 100;
        splayn_y[i] = qrand() % 100;
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
