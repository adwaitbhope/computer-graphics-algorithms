#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    buttonId = 0;
    hidden = false;
    shw = "Show";
    hde = "Hide";
    show_text = QString::fromStdString(shw);
    hide_text = QString::fromStdString(hde);

    }

MainWindow::~MainWindow()
{
    delete ui;
}

int MainWindow::sign (float x) {
    if (x > 0)
        return 1;
    else if (x < 0)
        return -1;
    else
        return 0;
}

void MainWindow::on_button_dda_clicked()
{

    buttonId = 1;
    update();
}

void MainWindow::on_button_bresenham_clicked()
{
    buttonId = 2;
    update();
}

void MainWindow::on_button_exit_clicked()
{
    exit(0);
}

void MainWindow::dda(float x1, float y1, float x2, float y2) {
    QPainter p(this);
    p.setPen(Qt::red);
    float dx = x2 - x1;
    float dy = y2 - y1;

    len = std::max(abs(dx), abs(dy));
    float xi = dx/len;
    float yi = dy/len;

    x1 += 0.5;
    y1 += 0.5;

    for (int i = 0; i < len; i++) {      
        p.drawPoint(floor(x1), floor(y1));
        x1 += xi;
        y1 += yi;
    }
}

void MainWindow::bresenham(int x1, int y1, int x2, int y2) {
    QPainter p(this);
    p.setPen(Qt::blue);

    bool condition = abs(x2 - x1) >= abs (y2 - y1);
    int len = condition ? abs(x2 - x1) : abs(y2 - y1);

    int m = condition ? x1 : y1;
    int n = condition ? y1 : x1;
    int dm = condition ? (x2 - x1) : (y2 - y1);
    int dn = condition ? (y2 - y1) : (x2 - x1);

    int d = 2*abs(dn) - abs(dm);

    for (int i = 0; i < len; i++) {
        condition ? (p.drawPoint(m, n)) : (p.drawPoint(n, m));
        if (d >= 0) {
            m += sign(dm);
            n += sign(dn);
            d += 2*abs(dn) - 2*abs(dm);
        }
        else {
            m += sign(dm);
            d += 2*abs(dn);
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *) {
    x1 = ui->x1->toPlainText().toInt();
    y1 = ui->y1->toPlainText().toInt();
    x2 = ui->x2->toPlainText().toInt();
    y2 = ui->y2->toPlainText().toInt();

    switch (buttonId) {
        case 1:
            dda(x1, y1, x2, y2);
//            ui->button_dda->hide();
            break;
        case 2:
            bresenham(x1, y1, x2, y2);
          break;
    }
}

void MainWindow::on_visibility_clicked()
{
    if (hidden) {
        ui->button_bresenham->show();
        ui->button_dda->show();
        ui->button_exit->show();
        ui->label->show();
        ui->label_2->show();
        ui->label_3->show();
        ui->label_4->show();
        ui->x1->show();
        ui->y1->show();
        ui->x2->show();
        ui->y2->show();
        ui->visibility->setText(hide_text);
        hidden = false;
    }
    else {
        ui->button_bresenham->hide();
        ui->button_dda->hide();
        ui->button_exit->hide();
        ui->label->hide();
        hide_text = QString::fromStdString(hde);
        hide_text = QString::fromStdString(hde);
        hide_text = QString::fromStdString(hde);
        hide_text = QString::fromStdString(hde);
        hide_text = QString::fromStdString(hde);
        hide_text = QString::fromStdString(hde);
        hide_text = QString::fromStdString(hde);
        hide_text = QString::fromStdString(hde);
        hide_text = QString::fromStdString(hde);
        ui->label_2->hide();
        ui->label_3->hide();
        ui->label_4->hide();
        ui->x1->hide();
        ui->y1->hide();
        ui->x2->hide();
        ui->y2->hide();
        ui->visibility->setText(show_text);
        hidden = true;
    }
}
