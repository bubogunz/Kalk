#include "QCustomBtn.h"

QCustomBtn::QCustomBtn(const QString & text, QWidget * parent) : QPushButton(parent){
    bool ok;
    int value = text.toInt(&ok);
    if(ok)
        setFixedSize(60,60);
    else
        setFixedSize(60,40);
    setText(text);
    ++value; //this avoids compiler warning
}

QCustomBtn::QCustomBtn(const QString & text, const std::size_t w, const std::size_t h, QWidget * parent) : QPushButton(parent){
    setFixedSize(w, h);
    setText(text);
}
