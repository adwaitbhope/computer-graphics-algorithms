#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QMouseEvent>
#include <list>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    int numPoints;
    int yMin, yMax;
    QList<float> x_input;
    QList<float> y_input;
    QList<float> m;
    QList<int> x_paint;
    QList<int> y_paint;
    QList<int> xIndex_array;
    bool pointsDrawn;

public:
    explicit MainWindow(QWidget *parent = 0);
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *e);
    void calculateMinMax();
    ~MainWindow();

private slots:
//    void on_button_new_point_clicked();

    void on_button_fill_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
