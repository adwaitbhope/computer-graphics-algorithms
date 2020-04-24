#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qApp->installEventFilter(this);
    status = 0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter p(this);

    if (status >= 1) {
        p.setPen(QPen(Qt::black, 2));
        p.drawRect(rect_x1, rect_y1, rect_x2 - rect_x1, rect_y2 - rect_y1);
    }
    if (status <= 3) {
        p.setPen(QPen(Qt::red, 2));
        p.drawLine(line_x1, line_y1, line_x2, line_y2);
    }
    else if (status <= 5) {
        p.setPen(QPen(Qt::red, 2));
        p.drawLine(clipped_x1, clipped_y1, clipped_x2, clipped_y2);
    }

}
bool MainWindow::eventFilter(QObject *watched, QEvent *event) {
    if (event->type() == QEvent::MouseMove) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);

        switch (status) {
            case 1:
                rect_x2 = mouseEvent->x();
                rect_y2 = mouseEvent->y() + 15;
                update();
                break;
            case 3:
                line_x2 = mouseEvent->x();
                line_y2 = mouseEvent->y() + 15;
                update();
                break;
        }
    }
      return false;
}

void MainWindow::fixCoordinates() {
    if (rect_x1 > rect_x2) {
        std::swap(rect_x1, rect_x2);
        std::swap(rect_y1, rect_y2);
    }
    if (line_x1 > line_x2) {
        std::swap(line_x1, line_x2);
        std::swap(line_y1, line_y2);
    }
}

void MainWindow::mousePressEvent(QMouseEvent *e) {
    switch (status) {
    case 0:
        //selecting rect point 1
        rect_x1 = e->x();
        rect_y1 = e->y();
        status = 1;
        break;
    case 1:
        //selecting rect point 2
        status = 2;
        break;
    case 2:
        //selecting line point 1
        line_x1 = e->x();
        line_y1 = e->y();
        status = 3;
        break;
    case 3:
        //selecting line point
        fixCoordinates();
        update();
        clipped_x1 = line_x1;
        clipped_x2 = line_x2;
        clipped_y1 = line_y1;
        clipped_y2 = line_y2;
        status = 4;
        break;
    case 5:
    case 6:
        //selecting new line point 1
        line_x1 = e->x();
        line_y1 = e->y();
        line_x2 = line_x1;
        line_y2 = line_y1;
        status = 3;
        update();
        break;

    }
}

void MainWindow::on_clip_button_clicked()
{
    if (status != 4) return;
    status = 5;

    bool code_1[4], code_2[4], result[4];
    code_1[0] = line_y1 < rect_y1;
    code_1[1] = line_y1 > rect_y2;
    code_1[2] = line_x1 > rect_x2;
    code_1[3] = line_x1 < rect_x1;

    code_2[0] = line_y2 < rect_y1;
    code_2[1] = line_y2 > rect_y2;
    code_2[2] = line_x2 > rect_x2;
    code_2[3] = line_x2 < rect_x1;

    for (int i = 0; i < 4; i++)
        result[i] = code_1[i] && code_2[i];

    for (int i = 0; i < 4; i++) {
        if (result[i]) {
            status = 6;
        }
    }

    float m = (line_y2 - line_y1) / (line_x2 - line_x1);

    if (code_1[0]) {
        clipped_x1 = (rect_y1 - clipped_y1 + m*clipped_x1) / m;
        clipped_y1 = rect_y1;
    }
    if (code_1[1]) {
        clipped_x1 = (rect_y2 - clipped_y1 + m*clipped_x1) / m;
        clipped_y1 = rect_y2;
    }
    if (code_1[2]) {
        if (clipped_x2 > rect_x2) {
            clipped_y1 = m * (rect_x2 - clipped_x1) + clipped_y1;
            clipped_x1 = rect_x2;
        }
    }
    if (code_1[3]) {
        if (clipped_x1 < rect_x1) {
            clipped_y1 = m * (rect_x1 - clipped_x1) + clipped_y1;
            clipped_x1 = rect_x1;
        }
    }

    if (code_2[0]) {
        clipped_x2 = (rect_y1 - clipped_y2 + m*clipped_x2) / m;
        clipped_y2 = rect_y1;
    }
    if (code_2[1]) {
        clipped_x2 = (rect_y2 - clipped_y2 + m*clipped_x2) / m;
        clipped_y2 = rect_y2;
    }
    if (code_2[2]) {
        if (clipped_x2 > rect_x2) {
            clipped_y2 = m * (rect_x2 - clipped_x2) + clipped_y2;
            clipped_x2 = rect_x2;
        }
    }
    if (code_2[3]) {
        if (clipped_x1 < rect_x1) {
            clipped_y2 = m * (rect_x2 - clipped_x2) + clipped_y2;
            clipped_x2 = rect_x2;
        }
    }

    update();
}
