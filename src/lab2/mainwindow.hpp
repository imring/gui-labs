#ifndef LAB2_MAINWINDOW_HPP
#define LAB2_MAINWINDOW_HPP

#include <QtWidgets>
#include <QTableWidget>
#include <QDoubleSpinBox>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

public slots:
    void calculate();

private:
    int selected = 0;

    QDoubleSpinBox *minval;
    QDoubleSpinBox *maxval;
    QSpinBox *points;
    QTableWidget *tablefunc;
};

#endif // LAB2_MAINWINDOW_HPP