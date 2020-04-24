#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    buttonId = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::putpixels(int x, int y, int x1, int y1, Qt::GlobalColor color) {
    QPainter p(this);
    p.setPen(color);
    p.drawPoint(x+x1, y+y1);
    p.drawPoint(x+x1, y-y1);
    p.drawPoint(x-x1, y+y1);
    p.drawPoint(x-x1, y-y1);
    p.drawPoint(x+y1, y+x1);
    p.drawPoint(x+y1, y-x1);
    p.drawPoint(x-y1, y+x1);
    p.drawPoint(x-y1, y-x1);
}

void MainWindow::circle(int x, int y, int rad, Qt::GlobalColor color) {
    int dp = 3 - 2*rad;

    for (int x1=0, y1=rad; x1 >= -y1; x1--) {
        if (dp <= 0) {
            dp += (4*abs(x1)) + 20;
        }
        else {
            dp += 4*(abs(x1)-y1) + 10;
            y1--;
        }
        putpixels(x, y, x1, y1, color);
    }
}

void MainWindow::paintEvent(QPaintEvent *a) {
    QPainter p(this);
    int x = ui->x->toPlainText().toInt();
    int y = ui->y->toPlainText().toInt();
    int rad = ui->radius->toPlainText().toInt();

    if (buttonId == 1) {
        Qt::GlobalColor color = Qt::black;
        circle(x - 2.4*rad, y, rad, color);
        circle(x - 0.8*rad, y, rad, color);
        circle(x + 0.8*rad, y, rad, color);
        circle(x + 2.4*rad, y, rad, color);
    }
    else if (buttonId == 2) {
        circle(x - 2.2*rad, y, rad, Qt::blue);
        circle(x, y, rad, Qt::black);
        circle(x + 2.2*rad, y, rad, Qt::red);
        circle(x - 1.1*rad, y +rad, rad, Qt::yellow);
        circle(x + 1.1*rad, y +rad, rad, Qt::darkGreen);
    }
}

void MainWindow::on_button_audi_clicked()
{
    buttonId = 1;
    update();
}

void MainWindow::on_button_olympic_clicked()
{
    buttonId = 2;
    update();
}
