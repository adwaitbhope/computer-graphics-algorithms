#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    int buttonId;

public:
    void paintEvent(QPaintEvent *);
    void circle(int, int, int, Qt::GlobalColor);
    void putpixels(int, int, int, int, Qt::GlobalColor);
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_button_audi_clicked();

    void on_button_olympic_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
