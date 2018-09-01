#ifndef BINMODEL_H
#define BINMODEL_H
#include <QObject>
#include <QVector>
#include "binary/binary.h"
//forward declaration: this avoids preprocessor's cross inclusion
class binController;
/*enum type {signMagnitude, twosComplement, floatingPoint16, decimal};
enum operation {add, subtract, multiply, divide, conjugate, equal, nop};*/

class binModel : public QObject{
  Q_OBJECT
private:
  binary* ans;
  binController* ctrl;

  void updateAns(binary*);
  static binary* checkType(binary*, binary*);

public:
  explicit binModel(binController*, QObject* =nullptr);
  explicit binModel() =default;
  virtual ~binModel() override;

signals:
  void result(binary*);
  void sendDec(QString);
  void ofErr(QString);
  void ufErr(QString);
  void zeroErr(QString);

public slots:
  //void operation(QChar);
  void toSigMag(QVector<QString>);
  void toTwosComp(QVector<QString>);
  void toFloat16(QVector<QString>);
  void toDec(QVector<QString>);
};

#endif // binModel_H
