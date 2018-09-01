#ifndef QCUSTOMBTN
#define QCUSTOMBTN


#include <QPushButton>

class QCustomBtn : public QPushButton {

public:
    explicit QCustomBtn(const QString& text, QWidget* parent);
    explicit QCustomBtn(const QString & text, const std::size_t w, const std::size_t h, QWidget * parent);
};


#endif // CUSTOMBTN

