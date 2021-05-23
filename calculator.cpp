#include "calculator.h"
#include "ui_calculator.h"

double calcVal = 0.0;
double memVal = 0.0;

bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;

Calculator::Calculator(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton * numButtons[10];
    for(int i = 0; i < 10; ++i) {
        QString buttonName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *> (buttonName);
        connect(numButtons[i], SIGNAL(released()), this,
                SLOT(numPressed()));
    }

    // math buttons
    connect(ui->Add, SIGNAL(released()), this,
            SLOT(mathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this,
            SLOT(mathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this,
            SLOT(mathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this,
            SLOT(mathButtonPressed()));

    // equals- , change-sign- and clear-button
    connect(ui->Equals, SIGNAL(released()), this,
            SLOT(equalButtonPressed()));
    connect(ui->ChangeSign, SIGNAL(released()), this,
            SLOT(changeNumberSign()));
    connect(ui->Clear, SIGNAL(released()), this,
            SLOT(clearDisplay()));

    // memory buttons
    connect(ui->MemGet, SIGNAL(released()), this,
            SLOT(getMemory()));
    connect(ui->MemAdd, SIGNAL(released()), this,
            SLOT(addMemory()));
    connect(ui->MemClear, SIGNAL(released()), this,
            SLOT(clearMemory()));
}

Calculator::~Calculator()
{
    delete ui;
}


void Calculator::numPressed() {

    if( addTrigger || subTrigger || multTrigger || divTrigger) {
        ui->Display->setText("");
    }

    QPushButton * button = (QPushButton *) sender();
    QString buttonVal = button->text();
    QString displayVal = ui->Display->text();

    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)) {
        ui->Display->setText(buttonVal);
    }
    else {
        QString newVal = displayVal + buttonVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }
}

void Calculator::mathButtonPressed() {

    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton * button = (QPushButton *) sender();
    QString buttonVal = button->text();

    if(QString::compare(buttonVal, "/", Qt::CaseSensitive) == 0) {
        divTrigger = true;
    }
    else if(QString::compare(buttonVal, "*", Qt::CaseSensitive) == 0) {
        multTrigger = true;
    }
    else if(QString::compare(buttonVal, "+", Qt::CaseSensitive) == 0) {
        addTrigger = true;
    }
    else if(QString::compare(buttonVal, "-", Qt::CaseSensitive) == 0) {
        subTrigger = true;
    }

    // ui->Display->setText("");
}


void Calculator::equalButtonPressed() {
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    double solution = dblDisplayVal;

    if( addTrigger || subTrigger || multTrigger || divTrigger) {

        if(addTrigger)
            solution = calcVal + dblDisplayVal;
        else if(subTrigger)
            solution = calcVal - dblDisplayVal;
        else if(multTrigger)
            solution = calcVal * dblDisplayVal;
        else if(divTrigger && (dblDisplayVal != 0.0 || dblDisplayVal != 0))
            solution = calcVal / dblDisplayVal;
    }

    if(divTrigger && (dblDisplayVal == 0.0 || dblDisplayVal == 0)) {
        ui->Display->setText("Forget it!");
        return;
    }

    ui->Display->setText(QString::number(solution));
}


void Calculator::changeNumberSign() {

    /*
    QString displayVal = ui->Display->text();
    QRegularExpression reg("[-]?[0-9.]*");
    QRegularExpressionMatch match = reg.match(displayVal);
    if(match.hasMatch()) {
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->Display->setText(QString::number(dblDisplayValSign));
    }
    */

    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    dblDisplayVal = dblDisplayVal * (-1.0);
    ui->Display->setText(QString::number(dblDisplayVal));
}


void Calculator::clearDisplay() {
    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    ui->Display->setText(QString::number(0.0));
}


double Calculator::getMemory() {
    ui->Display->setText(QString::number(memVal));
    return memVal;
}


void Calculator::addMemory() {
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    memVal = dblDisplayVal;
}


void Calculator::clearMemory() {
    memVal = 0.0;
}

