#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    x1 = petal_x(210, 200, 350, 200);
    y1 = petal_y(210, 200, 350, 200);

    x2 = petal_x(200, 190, 200, 50);
    y2 = petal_y(200, 190, 200, 50);

    x3 = petal_x(200, 210, 200, 350);
    y3 = petal_y(200, 210, 200, 350);

    x4 = petal_x(190, 200, 50, 200);
    y4 = petal_y(190, 200, 50, 200);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *) {
    QPainter p(this);

    for (int i = 0; i < x1.size() -1; i++)
        p.drawLine(x1.at(i), y1.at(i), x1.at(i +1), y1.at(i +1));
    for (int i = 0; i < x2.size() -1; i++)
        p.drawLine(x2.at(i), y2.at(i), x2.at(i +1), y2.at(i +1));
    for (int i = 0; i < x3.size() -1; i++)
        p.drawLine(x3.at(i), y3.at(i), x3.at(i +1), y3.at(i +1));
    for (int i = 0; i < x4.size() -1; i++)
        p.drawLine(x4.at(i), y4.at(i), x4.at(i +1), y4.at(i +1));
    p.drawEllipse(190, 190, 20, 20);
}

QList<float> MainWindow::bezier(QList<float> a) {
    for (int i = 0; i < iterations; i++) {
        QList<float> a_temp;
        for (int j = 0; j < a.size() -1; j++)
            a_temp.append((a.at(j) + a.at(j +1)) / 2);
        a_temp.insert(0, a.at(0));
        a_temp.append(a.at(a.size() -1));
        a = a_temp;
    }
    return a;
}

QList<float> MainWindow::petal_x(float x1, float y1, float x2, float y2) {
    QList<float> a;
    int open = 5;
    int mid = 25;
    int dist = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
    float mp_x = x1 - (-x2+x1)*0.3;

    a.append(x1 + ((y2-y1)*open/dist));
    a.append(mp_x + ((y2-y1)*mid/dist));
    a.append(x2);
    a.append(mp_x - ((y2-y1)*mid/dist));
    a.append(x1 - ((y2-y1)*open/dist));
    return a;
}

QList<float> MainWindow::petal_y(float x1, float y1, float x2, float y2) {
    QList<float> a;
    int open = 5;
    int mid = 25;
    float dist = sqrt(pow(x2-x1, 2) + pow(y2-y1, 2));
    float mp_y = y1 + (y2-y1)*0.3;

    a.append(y1 + ((-x2+x1)*open/dist));
    a.append(mp_y + ((-x2+x1)*mid/dist));
    a.append(y2);
    a.append(mp_y - ((-x2+x1)*mid/dist));
    a.append(y1 - ((-x2+x1)*open/dist));
    return a;
}

void MainWindow::on_draw_curve_clicked()
{
    iterations = 1;

    x1 = bezier(x1);
    y1 = bezier(y1);

    x2 = bezier(x2);
    y2 = bezier(y2);

    x3 = bezier(x3);
    y3 = bezier(y3);

    x4 = bezier(x4);
    y4 = bezier(y4);

    update();
}
