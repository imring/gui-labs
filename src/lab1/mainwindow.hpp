#ifndef LAB1_MAINWINDOW_HPP
#define LAB1_MAINWINDOW_HPP

#include <QtWidgets>
#include <QDoubleSpinBox>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

public slots:
    void calculate();

private:
    int selected = 0;

    QDoubleSpinBox *xval;
    QDoubleSpinBox *yval;
};

#endif // LAB1_MAINWINDOW_HPP