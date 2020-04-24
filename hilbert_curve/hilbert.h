#ifndef HILBERT_H
#define HILBERT_H
#include<QPainter>
#include <QMainWindow>

namespace Ui {
    class hilbert;
}

class hilbert : public QMainWindow {
    Q_OBJECT
public:
    hilbert(QWidget *parent = 0);
    ~hilbert();
     int flag,p1,p2;
     void paintEvent(QPaintEvent *);
     void move(int,int,int&,int&);
     void  hil(int,int,int,int,int,int,int&,int&);


private:
    Ui::hilbert *ui;

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
};

#endif // HILBERT_H
