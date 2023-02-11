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

    QHBoxLayout *mainLayout      = new QHBoxLayout;
    QVBoxLayout *leftPanelLayout = new QVBoxLayout;
    QHBoxLayout *formulasLayout  = new QHBoxLayout;

    QLabel *text = new QLabel{"Select a formula:"};

    for (auto it = formulas.begin(); it < formulas.end(); it++) {
        const int     idx = it - formulas.begin();
        QRadioButton *b   = new QRadioButton{QString::fromStdString(it->text)};
        connect(b, &QRadioButton::clicked, [this, idx]() {
            selected = idx;
        });
        formulasLayout->addWidget(b);

        if (idx == selected) {
            b->setChecked(true);
        }
    }

    QHBoxLayout *minLayout = new QHBoxLayout;
    QLabel      *xEqual    = new QLabel{"min"};
    minval                 = new QDoubleSpinBox;
    minval->setRange(-std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
    minLayout->addWidget(xEqual);
    minLayout->addWidget(minval);

    QHBoxLayout *maxLayout = new QHBoxLayout;
    QLabel      *yEqual    = new QLabel{"max"};
    maxval                 = new QDoubleSpinBox;
    maxval->setRange(-std::numeric_limits<double>::max(), std::numeric_limits<double>::max());
    maxLayout->addWidget(yEqual);
    maxLayout->addWidget(maxval);

    QHBoxLayout *intervalLayout = new QHBoxLayout;
    QLabel      *numPoints      = new QLabel{"Number of points"};
    points                      = new QSpinBox;
    points->setRange(2, std::numeric_limits<int>::max());
    intervalLayout->addWidget(numPoints);
    intervalLayout->addWidget(points);

    QPushButton *button = new QPushButton{"Calculate"};
    connect(button, &QPushButton::clicked, this, &MainWindow::calculate);

    leftPanelLayout->addWidget(text);
    leftPanelLayout->addLayout(formulasLayout);
    leftPanelLayout->addLayout(minLayout);
    leftPanelLayout->addLayout(maxLayout);
    leftPanelLayout->addLayout(intervalLayout);
    leftPanelLayout->addWidget(button);

    tablefunc = new QTableWidget;
    tablefunc->verticalHeader()->hide();
    tablefunc->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    tablefunc->setSelectionBehavior(QAbstractItemView::SelectRows);
    tablefunc->setColumnCount(3);
    QStringList header;
    header << "Point"
           << "x"
           << "y";
    tablefunc->setHorizontalHeaderLabels(header);

    mainLayout->addLayout(leftPanelLayout);
    mainLayout->addWidget(tablefunc);
    wid->setLayout(mainLayout);
}

void MainWindow::calculate() {
    if (selected < 0 || selected >= formulas.size()) { // unknown formula
        return;
    }
    if (minval->value() >= maxval->value()) {
        QMessageBox::warning(this, "Error", "Minimum is higher than maximum.", QMessageBox::Ok, QMessageBox::NoButton);
        return;
    }
    if (points->value() < 2) {
        QMessageBox::warning(this, "Error", "Number of points less than 2.", QMessageBox::Ok, QMessageBox::NoButton);
        return;
    }

    tablefunc->clearContents();
    tablefunc->setRowCount(points->value());
    const double interval = (maxval->value() - minval->value()) / (static_cast<double>(points->value()) - 1);
    for (int i = 0; i < points->value(); i++) {
        QTableWidgetItem *point = new QTableWidgetItem{QString::number(i + 1)};
        point->setFlags(point->flags() & ~Qt::ItemIsEditable);
        tablefunc->setItem(i, 0, point);

        const double      val = minval->value() + interval * i;
        QTableWidgetItem *x   = new QTableWidgetItem{QString::number(val)};
        x->setFlags(x->flags() & ~Qt::ItemIsEditable);
        tablefunc->setItem(i, 1, x);

        QTableWidgetItem *y;
        const double      yv = formulas[selected].func(val);
        if (yv >= std::numeric_limits<double>::infinity()) {
            QMessageBox::warning(this, "Warning", QStringLiteral("Number for x = %1 doesn't seem to exist.").arg(val), QMessageBox::Ok, QMessageBox::NoButton);
            y = new QTableWidgetItem{"-"};
        } else {
            y = new QTableWidgetItem{QString::number(yv)};
        }
        y->setFlags(x->flags() & ~Qt::ItemIsEditable);
        tablefunc->setItem(i, 2, y);
    }
}