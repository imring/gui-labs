#ifndef LAB3_MAINWINDOW_HPP
#define LAB3_MAINWINDOW_HPP

#include <QtWidgets>

struct Notice {
    QString name;
    QDate   date;
    QTime   time;
    int     promptTime;
    bool    prompt;
};

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    void initializeTable();
    void updateTable();
    void clearInputs();
    void addNotice();

    QList<Notice> notices;
    QTableWidget *table;

    QPlainTextEdit *eventEdit;
    QDateTimeEdit  *dateEdit;
    QTimeEdit      *timeEdit;
    QSpinBox       *promptEdit;
    QCheckBox      *promptCheckout;
    QPushButton    *addButton;
};

#endif // LAB3_MAINWINDOW_HPP