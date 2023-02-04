#include <string>
#include <functional>
#include <unordered_map>

#include <QHBoxLayout>
#include <QRadioButton>

#include "mainwindow.hpp"

const double pi = std::acos(-1);

struct Formula {
    std::string                   text;
    std::function<double(double)> func;
};

const std::vector<Formula> formulas{{"y=5^(1+x^2)-5^(1-x^2)",
                                     [](double x) {
                                         return std::pow(5, 1 + x * x) - std::pow(5, 1 - x * x);
                                     }},
                                    {"y=1+1/(1-sin^(-1)(2*x+8*pi/13))", [](double x) {
                                         return 1 + 1 / (1 - std::pow(std::sin(2 * x + 8 * pi / 13), -1));
                                     }}};

MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent} {
    QWidget *wid = new QWidget{this};
    setCentralWidget(wid);

    QVBoxLayout *mainLayout     = new QVBoxLayout;
    QHBoxLayout *formulasLayout = new QHBoxLayout;

    QLabel *text = new QLabel{"Select a formula:"};

    for (auto it = formulas.begin(); it < formulas.end(); it++) {
        const int     idx = it - formulas.begin();
        QRadioButton *b   = new QRadioButton{QString::fromStdString(it->text)};
        connect(b, &QRadioButton::clicked, [this, idx]() {
            selected = idx;
        });
        formulasLayout->addWidget(b);

        if (idx == 0) {
            b->setChecked(true);
        }
    }
    
    QHBoxLayout *xLayout = new QHBoxLayout;
    QLabel *xEqual = new QLabel{"x ="};
    xval = new QDoubleSpinBox;
    xval->setMinimum(-std::numeric_limits<double>::max());
    xval->setMaximum(std::numeric_limits<double>::max());
    xLayout->addWidget(xEqual);
    xLayout->addWidget(xval);
    
    QHBoxLayout *yLayout = new QHBoxLayout;
    QLabel *yEqual = new QLabel{"y ="};
    yval = new QDoubleSpinBox;
    yval->setMinimum(-std::numeric_limits<double>::max());
    yval->setMaximum(std::numeric_limits<double>::max());
    yval->setReadOnly(true);
    yLayout->addWidget(yEqual);
    yLayout->addWidget(yval);

    QPushButton *button = new QPushButton{"Calculate"};
    connect(button, &QPushButton::clicked, this, &MainWindow::calculate);

    mainLayout->addWidget(text);
    mainLayout->addLayout(formulasLayout);
    mainLayout->addLayout(xLayout);
    mainLayout->addLayout(yLayout);
    mainLayout->addWidget(button);
    wid->setLayout(mainLayout);
}

void MainWindow::calculate() {
    if (selected < 0 || selected >= formulas.size()) { // unknown formula
        return;
    }

    const double x = xval->value();
    const double y = formulas[selected].func(x);
    QMessageBox msg;
    if (y >= std::numeric_limits<double>::infinity()) {
        msg.setText("Something is wrong. Possibly the number is too huge.");
    } else {
        yval->setValue(y);
        msg.setText(QString::fromStdString(std::format("x = {}, y = {}", x, y)));
    }
    msg.setIcon(QMessageBox::NoIcon);
    msg.exec();
}