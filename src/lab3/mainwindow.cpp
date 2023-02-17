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
                                         return std::pow(5.0, 1.0 + x * x) - std::pow(5.0, 1.0 - x * x);
                                     }},
                                    {"y=1+1/(1-sin^(-1)(2*x+8*pi/13))", [](double x) {
                                         return 1.0 + 1.0 / (1.0 - std::pow(std::sin(2.0 * x + 8.0 * pi / 13.0), -1));
                                     }}};

const QList<QPair<QString, Qt::PenStyle>> penStyles = {
    {"None", Qt::NoPen},  {"Solid", Qt::SolidLine},      {"Dash", Qt::DashLine},
    {"Dot", Qt::DotLine}, {"Dash dot", Qt::DashDotLine}, {"Dash dot dot", Qt::DashDotDotLine},
};

MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent} {
    QWidget *wid = new QWidget{this};
    setCentralWidget(wid);

    QHBoxLayout *mainLayout       = new QHBoxLayout;
    QVBoxLayout *leftPanelLayout  = new QVBoxLayout;
    QVBoxLayout *rightPanelLayout = new QVBoxLayout;
    QHBoxLayout *formulasLayout   = new QHBoxLayout;

    QLabel *text = new QLabel{"Select a formula:"};
    text->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

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

    QPushButton *calc = new QPushButton{"Calculate"};
    connect(calc, &QPushButton::clicked, this, &MainWindow::calculate);

    leftPanelLayout->addWidget(text);
    leftPanelLayout->addLayout(formulasLayout);
    leftPanelLayout->addLayout(minLayout);
    leftPanelLayout->addLayout(maxLayout);
    leftPanelLayout->addLayout(intervalLayout);
    leftPanelLayout->addWidget(calc);

    graphPen.setStyle(Qt::SolidLine);
    graphPen.setWidth(1);
    graphPen.setColor(QColor(180, 180, 180));

    QHBoxLayout *thicknessLayout = new QHBoxLayout;
    QLabel      *thicknessText   = new QLabel{"Thickness"};
    thickness                    = new QSpinBox{};
    thickness->setValue(1);
    thickness->setMinimum(1);
    thicknessLayout->addWidget(thicknessText);
    thicknessLayout->addWidget(thickness);
    connect(thickness, &QSpinBox::valueChanged, this, &MainWindow::updatePen);

    graph = new QCustomPlot;
    connect(graph->xAxis, SIGNAL(rangeChanged(QCPRange)), graph->xAxis2, SLOT(setRange(QCPRange)));
    connect(graph->yAxis, SIGNAL(rangeChanged(QCPRange)), graph->yAxis2, SLOT(setRange(QCPRange)));
    graph->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

    QPushButton *editcol = new QPushButton{"Edit line color"};
    connect(editcol, &QPushButton::clicked, [this]() {
        const QColor col = QColorDialog::getColor(graphPen.color(), this, "Graph line color");
        if (col.isValid()) {
            graphPen.setColor(col);
            updatePen();
        }
    });

    QHBoxLayout *stylePenLayout = new QHBoxLayout;
    QLabel      *stylePenText   = new QLabel{"Pen style"};
    stylePen                    = new QComboBox{};
    QStringList stylePenList;
    for (const auto &v: penStyles) {
        stylePenList.append(v.first);
    }
    stylePen->addItems(stylePenList);
    stylePen->setCurrentIndex(1);
    stylePenLayout->addWidget(stylePenText);
    stylePenLayout->addWidget(stylePen);
    connect(stylePen, &QComboBox::currentIndexChanged, this, &MainWindow::updatePen);

    rightPanelLayout->addWidget(graph, 1);
    rightPanelLayout->addLayout(thicknessLayout);
    rightPanelLayout->addWidget(editcol);
    rightPanelLayout->addLayout(stylePenLayout);

    mainLayout->addLayout(leftPanelLayout);
    mainLayout->addLayout(rightPanelLayout, 1);
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

    graph->clearGraphs();
    graph->addGraph();
    updatePen();
    const double interval = (maxval->value() - minval->value()) / (static_cast<double>(points->value()) - 1);
    for (int i = 0; i < points->value(); i++) {
        const double x = minval->value() + interval * i;
        const double y = formulas[selected].func(x);
        if (y >= std::numeric_limits<double>::infinity()) {
            QMessageBox::warning(this, "Warning", QStringLiteral("Number for x = %1 doesn't seem to exist.").arg(x), QMessageBox::Ok, QMessageBox::NoButton);
        }
        graph->graph(0)->addData(x, y);
    }
    graph->replot();
}

void MainWindow::updatePen() {
    if (graph->graphCount() == 0)
        return;

    graphPen.setWidth(thickness->value());
    graphPen.setStyle(penStyles.at(stylePen->currentIndex()).second);
    graph->graph(0)->setPen(graphPen);
    graph->replot();
}