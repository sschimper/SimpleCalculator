#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    Calculator(QWidget *parent = nullptr);
    ~Calculator();

private:
    Ui::Calculator *ui;

private slots:
    void numPressed();
    void mathButtonPressed();
    void equalButtonPressed();
    void changeNumberSign();
    void clearDisplay();

    void getMemory();
    void addMemory();
    void clearMemory();
};
#endif // CALCULATOR_H
