#include "binController.h"

binController::binController(QObject *parent): QObject(parent){
  model = new binModel(this);
  view = new MainWindow(this);
  view->show();

  connect(this,SIGNAL(CtMSigMag(QVector<QString>)),model,SLOT(toSigMag(QVector<QString>)));
  connect(this,SIGNAL(CtMTwosComp(QVector<QString>)),model,SLOT(toTwosComp(QVector<QString>)));
  connect(this,SIGNAL(CtMFloat16(QVector<QString>)),model,SLOT(toFloat16(QVector<QString>)));
  connect(this,SIGNAL(CtMDec(QVector<QString>)),model,SLOT(toDec(QVector<QString>)));
  connect(this,SIGNAL(sendResult(QString)),view,SLOT(result(QString)));
}
void binController::getStream(QVector<QString> stream){

}
void binController::getResult(binary* res){
  QString s = *res;
  emit sendResult(s);
}
