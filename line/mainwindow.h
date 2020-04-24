#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <math.h>
#include <QString>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    int buttonId, len, x1, x2, y1, y2;
    bool hidden;

public:
    void paintEvent(QPaintEvent *p);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void dda (float, float, float, float);
    void bresenham (int, int, int, int);
    int sign (float);
    std::string shw, hde;
    QString show_text, hide_text;

private slots:
    void on_button_dda_clicked();

    void on_button_exit_clicked();

    void on_button_bresenham_clicked();

    void on_visibility_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
