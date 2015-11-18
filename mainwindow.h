#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <qwt_plot.h>
#include <qwt_plot_grid.h>

#include <qwt_legend.h>

#include <qwt_plot_curve.h>
#include <qwt_symbol.h>

#include <qwt_plot_magnifier.h>

#include <qwt_plot_panner.h>

#include <qwt_plot_picker.h>
#include <qwt_picker_machine.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QwtPlot *d_plot;
    QPolygonF points;
    QPolygonF points2;
    double splayn_x[15];
    double splayn_y[15];
    void beze(double x0, double y0, double x1, double y1, double x2, double y2, double x3, double y3);
    void gsch();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
