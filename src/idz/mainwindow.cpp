#include <string>
#include <functional>
#include <unordered_map>

#include <QHBoxLayout>

#include "mainwindow.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow{parent} {
    QWidget *wid = new QWidget{this};
    setCentralWidget(wid);

    QVBoxLayout *mainLayout        = new QVBoxLayout;
    QHBoxLayout *topPanelLayout    = new QHBoxLayout;
    QHBoxLayout *bottomPanelLayout = new QHBoxLayout;

    QVBoxLayout *eventLayout = new QVBoxLayout;
    {
        QLabel *label = new QLabel{"Event"};
        eventEdit     = new QPlainTextEdit;
        eventLayout->addWidget(label);
        eventLayout->addWidget(eventEdit);
    }
    topPanelLayout->addLayout(eventLayout);

    QVBoxLayout *dateTimeLayout = new QVBoxLayout;
    {
        QLabel *dateLabel = new QLabel{"Date"};
        dateEdit          = new QDateTimeEdit;
        dateEdit->setDisplayFormat("dd.MM.yyyy");
        dateTimeLayout->addWidget(dateLabel);
        dateTimeLayout->addWidget(dateEdit);

        QLabel *timeLayout = new QLabel{"Time"};
        timeEdit           = new QTimeEdit;
        timeEdit->setDisplayFormat("hh:mm:ss");
        dateTimeLayout->addWidget(timeLayout);
        dateTimeLayout->addWidget(timeEdit);
    }
    topPanelLayout->addLayout(dateTimeLayout, 1);

    QVBoxLayout *promptAddLayout = new QVBoxLayout;
    QHBoxLayout *promptLayout    = new QHBoxLayout;
    {
        QLabel *promptLabel = new QLabel{"Prompt time (ms)"};
        promptEdit          = new QSpinBox;
        promptCheckout      = new QCheckBox{"Prompt"};
        promptEdit->setMaximum(std::numeric_limits<int>::max());
        promptLayout->addWidget(promptEdit);
        promptLayout->addWidget(promptCheckout);
        promptAddLayout->addWidget(promptLabel);
        promptAddLayout->addLayout(promptLayout);

        // FIXME
        QLabel *crutch = new QLabel{""};
        promptAddLayout->addWidget(crutch);

        addButton = new QPushButton{"Add"};
        promptAddLayout->addWidget(addButton);
    }
    topPanelLayout->addLayout(promptAddLayout, 1);
    topPanelLayout->setContentsMargins(10, 10, 10, 10);

    initializeTable();
    bottomPanelLayout->addWidget(table);

    mainLayout->addLayout(topPanelLayout);
    mainLayout->addLayout(bottomPanelLayout, 1);
    wid->setLayout(mainLayout);

    clearInputs();
    connect(addButton, &QPushButton::clicked, this, &MainWindow::addNotice);
}

void MainWindow::initializeTable() {
    table = new QTableWidget;
    table->verticalHeader()->hide();
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setAlternatingRowColors(true);
    table->setStyleSheet("alternate-background-color: #f0f0f0; background-color: white;");

    table->setColumnCount(5);
    QStringList header;
    header << "name"
           << "date"
           << "time"
           << "promptTime"
           << "prompt";
    table->setHorizontalHeaderLabels(header);
}

void MainWindow::updateTable() {
    table->clearContents();
    table->setRowCount(notices.size());
    for (int i = 0; i < notices.size(); i++) {
        const auto &notice = notices[i];

        QTableWidgetItem *nameItem       = new QTableWidgetItem(notice.name);
        QTableWidgetItem *dateItem       = new QTableWidgetItem(notice.date.toString("dd.MM.yyyy"));
        QTableWidgetItem *timeItem       = new QTableWidgetItem(notice.time.toString("hh:mm:ss"));
        QTableWidgetItem *promptTimeItem = new QTableWidgetItem(QString::number(notice.promptTime));
        QTableWidgetItem *promptItem     = new QTableWidgetItem(notice.prompt ? "true" : "false");

        table->setItem(i, 0, nameItem);
        table->setItem(i, 1, dateItem);
        table->setItem(i, 2, timeItem);
        table->setItem(i, 3, promptTimeItem);
        table->setItem(i, 4, promptItem);
    }
}

void MainWindow::clearInputs() {
    const QDateTime current = QDateTime::currentDateTime();
    eventEdit->clear();
    dateEdit->setDate(current.date());
    timeEdit->setTime(current.time());
    promptEdit->setValue(0);
    promptCheckout->setChecked(false);
}

void MainWindow::addNotice() {
    const QString event       = eventEdit->toPlainText();
    const QDate   date        = dateEdit->date();
    const QTime   time        = timeEdit->time();
    const int     promptValue = promptEdit->value();
    const bool    promptBool  = promptCheckout->isChecked();
    const Notice  notice{event, date, time, promptValue, promptBool};

    const QDateTime currentDateTime = QDateTime::currentDateTime();
    const QString   dateTimeString  = date.toString("yyyy-MM-dd") + " " + time.toString("hh:mm:ss");
    QDateTime       dateTime        = QDateTime::fromString(dateTimeString, "yyyy-MM-dd hh:mm:ss");
    if (promptCheckout->isChecked()) {
        dateTime = dateTime.addMSecs(promptEdit->value());
    }
    if (currentDateTime > dateTime) {
        QMessageBox::warning(this, "Error", "You can't specify a time in the past.", QMessageBox::Ok, QMessageBox::NoButton);
        return;
    }

    qint64 msec = currentDateTime.msecsTo(dateTime);
    QTimer::singleShot(msec, std::bind([&](const Notice &notice) {
        notices.append(notice);
        updateTable();
    }, notice));
    clearInputs();
}