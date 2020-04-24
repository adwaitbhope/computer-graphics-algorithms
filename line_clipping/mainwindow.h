#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    float rect_x1, rect_x2, rect_y1, rect_y2;
    float line_x1, line_x2, line_y1, line_y2;
    float clipped_x1, clipped_x2, clipped_y1, clipped_y2;
    int status;

public:
    explicit MainWindow(QWidget *parent = 0);
    void mousePressEvent(QMouseEvent *e);
    bool eventFilter(QObject *watched, QEvent *event);
    void paintEvent(QPaintEvent *);
    void fixCoordinates();
    ~MainWindow();

private slots:
    void on_clip_button_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
