#include "hilbert.h"
#include "ui_hilbert.h"

hilbert::hilbert(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::hilbert)
{
    ui -> setupUi(this);
}

hilbert::~hilbert() {
    delete ui;
}

void hilbert ::paintEvent(QPaintEvent *) {
    int x, y, r = 2, d = 3, l = 4, u = 1, n, h = 10;
    n = ui -> plainTextEdit -> toPlainText().toInt();
    p1 = x = 50;
    p2 = y = 150;

    hil(r, d, l, u, n, h, x, y);
}
void hilbert::move(int j,int h,int &x,int &y) {

    QPainter p(this);
    p.setPen(Qt::blue);
    p1 = x;
    p2 = y;
    if (j == 1)
        y -= h;
    else if (j == 2)
        x += h;
    else if (j == 3)
        y += h;
    else if (j == 4)
        x -= h;
    p.drawLine(p1, p2, x, y);
}

void hilbert :: hil(int r, int d, int l, int u, int i, int h, int &x, int &y) {
    if(i-- > 0) {
        hil(d, r, u, l, i, h, x, y);
        move(r, h, x, y);

        hil(r, d, l, u, i, h, x, y);
        move(d, h, x, y);

        hil(r, d, l, u, i, h, x, y);
        move(l, h, x, y);

        hil(u, l, d, r, i, h, x, y);
    }
}

void hilbert::on_pushButton_clicked() {
    flag = 0;
    update();
}

void hilbert::on_pushButton_2_clicked() {
    exit(0);
}
