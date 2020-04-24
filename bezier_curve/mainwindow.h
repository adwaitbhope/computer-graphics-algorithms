#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QList>
#include <QDebug>
#include <math.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    int iterations;
    QList<float> x1, x2, x3, x4;
    QList<float> y1, y2, y3, y4;

public:
    explicit MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    QList<float> bezier(QList<float> a);
    QList<float> petal_x(float, float, float, float);
    QList<float> petal_y(float, float, float, float);
    ~MainWindow();

private slots:
    void on_draw_curve_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
