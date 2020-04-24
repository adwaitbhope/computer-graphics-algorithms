#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui -> setupUi(this);
    numPoints = 0;
    pointsDrawn = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *a) {
    QPainter p(this);
    QList<float> m_temp;

    if (!pointsDrawn) {
        // fill is not yet clicked
        for(int i = 0; i < x_input.size(); i++) {
            p.drawLine(x_input.at(i), y_input.at(i), x_input.at((i +1) %x_input.size()), y_input.at((i +1) %y_input.size()));

            // checking size to avoid division by zero
            if (x_input.size() > 1) {
                // calculate slope
                m_temp.append((y_input.at((i +1) %y_input.size()) - y_input.at(i)) / (x_input.at((i +1) %x_input.size()) - x_input.at(i)));
            }
        }
        //store all slopes
        m = m_temp;
        numPoints++;
    }
    else {
        //fill button is clicked
        for(int i = 0; i < x_input.size(); i++) {
            // redraw the polygon
            p.drawLine(x_input.at(i), y_input.at(i), x_input.at((i +1) %x_input.size()), y_input.at((i +1) %y_input.size()));
        }

        for (int i = 0; i < x_paint.size(); i += 2) {
            //draw horizontal lines between them
            p.drawLine(x_paint.at(i), y_paint.at(i), x_paint.at(i +1), y_paint.at(i +1));
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {

    if(pointsDrawn) {
        // to handle the case of redrawing after clicking fill
        x_input.clear();
        y_input.clear();
        x_paint.clear();
        y_paint.clear();
        m.clear();
        yMin = 5000;
        yMax = 0;
        numPoints = 0;
        pointsDrawn = false;
    }

    x_input.append(event->x());
    y_input.append(event->y());
    update();

}

void MainWindow::calculateMinMax() {
    yMin = 5000;
    yMax = 0;
    for (int i = 0; i < y_input.size(); i++) {
        if (y_input.at(i) < yMin) {
            yMin = y_input.at(i);
        }
        if (y_input.at(i) > yMax) {
            yMax = y_input.at(i);
        }
    }
}

void MainWindow::on_button_fill_clicked()
{
    pointsDrawn = true;                 //to control execution in paintEvent()
    MainWindow::calculateMinMax();      //calculate min and max y for scanline

    for (int cur_y = yMin; cur_y < yMax; cur_y++) {
        int x_temp[x_input.size()];           //temp container for x coords for sorting them per y coordinate
        int xIndex = 0;                 //index to maintain size filled

        // loop over all points
        for (int i = 0; i < x_input.size(); i++) {
            // check for active edges
            if ((cur_y >= y_input.at(i) && cur_y < y_input.at((i +1) %x_input.size())) || (cur_y < y_input.at(i) && cur_y >= y_input.at((i +1) %x_input.size())) ) {
                // calculate x coord by using y coord and slope stored in m
                x_temp[xIndex++] = x_input.at(i) + ((cur_y - y_input.at(i)) / m.at(i));
            }
        }

        // sort x coords
        for (int i = 0; i < xIndex; i++) {
            for (int j = 0; j < i; j++) {
                if (x_temp[i] < x_temp[j]) {
                    std::swap(x_temp[i], x_temp[j]);
                }
            }
        }

        // store sorted x coords along with current y coord for painting
        for (int i = 0; i < xIndex; i++) {
            x_paint.append(x_temp[i]);
            y_paint.append(cur_y);
        }

    }
    update();
}
