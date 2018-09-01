#include "binModel.h"
#include "../Controller/binController.h"
#include "binary/integer.h"
#include "binary/floatP.h"
#include "binary/twosComp.h"
#include "binary/float16.h"
#include "binary/sigMag.h"
#include "binary/opEx.h"
#include <typeinfo>
#include <QDebug>

binModel::binModel(binController* cont, QObject* parent):
    QObject(parent), ans(nullptr){
  ctrl = cont;
  connect(this,SIGNAL(ofErr(QString)),ctrl,SIGNAL(sendError(QString)));
  connect(this,SIGNAL(ufErr(QString)),ctrl,SIGNAL(sendError(QString)));
  connect(this,SIGNAL(zeroErr(QString)),ctrl,SIGNAL(sendError(QString)));
  connect(this,SIGNAL(result(binary*)),ctrl,SLOT(getResult(binary*)));
  connect(this,SIGNAL(sendDec(QString)),ctrl,SIGNAL(sendResult(QString)));
}
binary* binModel::checkType(binary* op1, binary* op2){
  QString s = typeid(*op2).name();
  binary* p = nullptr;
  if(s!=typeid(*op1).name()){
    p = dynamic_cast<sigMag*>(op2);
    if(p){
      twosComp* p1 = dynamic_cast<twosComp*>(op1);
      if(p1) return new sigMag(p1->toVal());
      float16* p2 = dynamic_cast<float16*>(op1);
      if(p2) return new sigMag(p2->toVal());
    }
    p = dynamic_cast<twosComp*>(op2);
    if(p){
      sigMag* p1 = dynamic_cast<sigMag*>(op1);
      if(p1) return new twosComp(p1->toVal());
      float16* p2 = dynamic_cast<float16*>(op1);
      if(p2) return new twosComp(p2->toVal());
    }
    p = dynamic_cast<float16*>(op2);
    if(p){
      twosComp* p1 = dynamic_cast<twosComp*>(op1);
      if(p1) return new float16(p1->toVal());
      sigMag* p2 = dynamic_cast<sigMag*>(op1);
      if(p2) return new float16(p2->toVal());
    }
  }
  return nullptr; //this avoids compiler warning
}
void binModel::updateAns(binary* p){
  if(ans) delete ans;
  ans = p;
}
void binModel::toSigMag(QVector<QString> stream){
  QString operand = stream[0];
  QString type = stream[1];
  binary* p;
  if(type=="dec")
    p = new sigMag(operand.toInt());
  else if(type=="twosComp"){
    twosComp x(operand);
    p = new sigMag(x.toVal());
  }
  else if(type=="float16"){
    float16 x(operand);
    p = new sigMag(x.toVal());
  }
  updateAns(p);
  emit result(p);
}
void binModel::toTwosComp(QVector<QString> stream){
  QString operand = stream[0];
  QString type = stream[1];
  binary* p;
  if(type=="dec")
    p = new twosComp(operand.toInt());
  else if(type=="sigMag"){
    sigMag x(operand);
    p = new twosComp(x.toVal());
  }
  else if(type=="float16"){
    float16 x(operand);
    p = new twosComp(x.toVal());
  }
  updateAns(p);
  emit result(p);
}
void binModel::toFloat16(QVector<QString> stream){
  QString operand = stream[0];
  QString type = stream[1];
  binary* p;
  if(type=="dec")
    p = new float16(operand.toDouble());
  else if(type=="sigMag"){
    sigMag x(operand);
    p = new float16(x.toVal());
  }
  else if(type=="twosComp"){
    twosComp x(operand);
    p = new float16(x.toVal());
  }
  updateAns(p);
  emit result(p);
}
void binModel::toDec(QVector<QString> stream){
  QString operand = stream[0];
  QString type = stream[1];
  QString s;
  if(type=="sigMag"){
    sigMag x(operand);
    s = QString::number(x.toVal());
  }
  else if(type=="twosComp"){
    twosComp x(operand);
    s = QString::number(x.toVal());
  }
  else if(type=="float16"){
    float16 x(operand);
    s = QString::number(x.toVal());
  }
  emit sendDec(s);
}
binModel::~binModel(){
  updateAns(nullptr);
}
