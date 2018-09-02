#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QString>
#include <QWidget>
#include <QMainWindow>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QVector>
#include <QRadioButton>
#include <QGroupBox>
#include <QLabel>
#include "Custom/QCustomBtn.h"

//forward declaration
class binController;

class MainWindow : public QMainWindow{
    Q_OBJECT
private:
    binController* ctrl;
    QString currDataT;
    QVector<QString> currStream;

    QWidget* centralWidget;
    QGridLayout* winLayout;
    QGroupBox* dataTypeBox;
    QLabel* prova;
    QLineEdit* display;
    QVector<QCustomBtn*> btns;
    QVector<QRadioButton*> rbtns;

    void keyPressEvent(QKeyEvent*);

public:
    MainWindow(binController*, QWidget *parent = 0);
    ~MainWindow();

private slots:
    void shownumber ();
    void showpoint();
    void clear();
    void clearall();
    void operatorClicked();
    void switchType();
    void converToSigMag();
    void converToTwosComp();
    void converToFloat16();
    void converToDec();
    void setSigMag();
    void setTwosComp();
    void setFloat16();
    void setDec();

public slots:
    void result(QString);

signals:
    void VtCSigMag(QVector<QString>);
    void VtCTwosComp(QVector<QString>);
    void VtCFloat16(QVector<QString>);
    void VtCDec(QVector<QString>);
    void sendOperand(QString);
    void sendOperator(QChar);
};

#endif // MAINWINDOW_H
