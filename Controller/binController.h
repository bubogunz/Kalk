#ifndef BINCONTROLLER_H
#define BINCONTROLLER_H
#include <QObject>
#include "../Model/binModel.h"
#include "../View/MainWindow.h"

//enum dataType {signMagnitude, twosComplement, floatingPoint16, decimal};
//enum operation {add, subtract, multiply, divide, convert, conjugate, nop};

class binController : public QObject{
    Q_OBJECT
private:
  binModel* model;
  MainWindow* view;

public:
  explicit binController(QObject* =nullptr);

signals:
  void CtMSigMag(QVector<QString>);
  void CtMTwosComp(QVector<QString>);
  void CtMFloat16(QVector<QString>);
  void CtMDec(QVector<QString>);
  void sendResult(QString);
  void sendError(QString);

public slots:
  void getStream(QVector<QString>);
  void getResult(binary*);
};

#endif // BINCONTROLLER_H
