#ifndef LAB3_MAINWINDOW_HPP
#define LAB3_MAINWINDOW_HPP

#include <QtWidgets>
#include <QDoubleSpinBox>

#include "qcustomplot.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

public slots:
    void calculate();

private:
    void updatePen();

    int selected = 0;

    QDoubleSpinBox *minval;
    QDoubleSpinBox *maxval;
    QSpinBox       *points;

    QPen         graphPen;
    QCustomPlot *graph;
    QComboBox   *stylePen;

    QSpinBox *thickness;
};

#endif // LAB3_MAINWINDOW_HPP