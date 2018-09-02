#include "MainWindow.h"
#include "../Controller/binController.h"
#include <QKeyEvent>
#include <QShortcut>

MainWindow::MainWindow(binController* controller, QWidget *parent):
  QMainWindow(parent), ctrl(controller), btns(19),
  rbtns(4), currDataT("dec"){
    setWindowTitle("Kalk");
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    setFixedSize(270,600);
    QShortcut* s = new QShortcut(this);
    s->setKey(Qt::CTRL + Qt::Key_T);

    setFocusPolicy(Qt::StrongFocus);

    dataTypeBox = new QGroupBox("Choose Type", centralWidget);

    prova = new QLabel(centralWidget);
    prova -> setAlignment(Qt::AlignRight);

    winLayout = new QGridLayout(centralWidget);

    for(int i=0; i<10; i++)
        btns[i] = new QCustomBtn(QString::number(i), centralWidget);

    btns[10] = new QCustomBtn(".", centralWidget);
    btns[11] = new QCustomBtn("+", centralWidget);
    btns[12] = new QCustomBtn("-", centralWidget);
    btns[13] = new QCustomBtn("*", centralWidget);
    btns[14] = new QCustomBtn("/", centralWidget);
    btns[15] = new QCustomBtn("=", 125, 40, centralWidget);
    btns[16] = new QCustomBtn("+/-", centralWidget);
    btns[17] = new QCustomBtn("C", centralWidget);
    btns[18] = new QCustomBtn("CA", centralWidget);


    rbtns[0] = new QRadioButton("Sign-Magnitude", centralWidget);
    rbtns[1] = new QRadioButton("Two's Complement", centralWidget);
    rbtns[2] = new QRadioButton("16-bit Floating Point",  centralWidget);
    rbtns[3] = new QRadioButton("Decimal", centralWidget);

    for(int i=0; i<rbtns.size(); ++i)
      rbtns[i]->setCheckable(true);
    rbtns[3] -> setChecked(true);

    display = new QLineEdit("0", centralWidget);
    display -> setReadOnly(true);
    display -> setAlignment(Qt::AlignRight);
    display -> setMaxLength(40);
    display -> setMaximumHeight(40);


    QVBoxLayout *vbox = new QVBoxLayout;
    vbox -> addWidget(rbtns[0]);
    vbox -> addWidget(rbtns[1]);
    vbox -> addWidget(rbtns[2]);
    vbox -> addWidget(rbtns[3]);
    vbox->addStretch(1);
    dataTypeBox->setLayout(vbox);


    winLayout -> addWidget(dataTypeBox, 0, 0, 2, 4);
    winLayout -> addWidget(prova, 2, 0, 1, 4);
    winLayout -> addWidget(display, 3, 0, 1, 4);
    winLayout -> addWidget(btns[17], 4, 0);
    winLayout -> addWidget(btns[18], 4, 1);
    winLayout -> addWidget(btns[16], 4, 2);
    winLayout -> addWidget(btns[11], 4, 3);
    winLayout -> addWidget(btns[1], 5, 0);
    winLayout -> addWidget(btns[2], 5, 1);
    winLayout -> addWidget(btns[3], 5, 2);
    winLayout -> addWidget(btns[12], 5, 3);
    winLayout -> addWidget(btns[4], 6, 0);
    winLayout -> addWidget(btns[5], 6, 1);
    winLayout -> addWidget(btns[6], 6, 2);
    winLayout -> addWidget(btns[13], 6, 3);
    winLayout -> addWidget(btns[7], 7, 0);
    winLayout -> addWidget(btns[8], 7, 1);
    winLayout -> addWidget(btns[9], 7, 2);
    winLayout -> addWidget(btns[14], 7, 3);
    winLayout -> addWidget(btns[10], 8, 0);
    winLayout -> addWidget(btns[0], 8, 1);
    winLayout -> addWidget(btns[15], 8, 2);

    setLayout(winLayout);

    connect(btns[0], SIGNAL(clicked()), this, SLOT(shownumber()));
    connect(btns[1], SIGNAL(clicked()), this, SLOT(shownumber()));
    connect(btns[2], SIGNAL(clicked()), this, SLOT(shownumber()));
    connect(btns[3], SIGNAL(clicked()), this, SLOT(shownumber()));
    connect(btns[4], SIGNAL(clicked()), this, SLOT(shownumber()));
    connect(btns[5], SIGNAL(clicked()), this, SLOT(shownumber()));
    connect(btns[6], SIGNAL(clicked()), this, SLOT(shownumber()));
    connect(btns[7], SIGNAL(clicked()), this, SLOT(shownumber()));
    connect(btns[8], SIGNAL(clicked()), this, SLOT(shownumber()));
    connect(btns[9], SIGNAL(clicked()), this, SLOT(shownumber()));
    connect(btns[10], SIGNAL(clicked()), this, SLOT(showpoint()));
    connect(btns[11], SIGNAL(clicked()), this, SLOT(operatorClicked()));
    connect(btns[12], SIGNAL(clicked()), this, SLOT(operatorClicked()));
    connect(btns[13], SIGNAL(clicked()), this, SLOT(operatorClicked()));
    connect(btns[14], SIGNAL(clicked()), this, SLOT(operatorClicked()));
    connect(btns[15], SIGNAL(clicked()), this, SLOT(operatorClicked()));
    connect(btns[16], SIGNAL(clicked()), this, SLOT(operatorClicked()));
    connect(btns[17], SIGNAL(clicked()), this, SLOT(clear()));
    connect(btns[18], SIGNAL(clicked()), this, SLOT(clearall()));
    connect(s,SIGNAL(activated()),this,SLOT(switchType()));

    connect(rbtns[0], SIGNAL(clicked()), this, SLOT(converToSigMag()));
    connect(rbtns[0], SIGNAL(clicked()), this, SLOT(setSigMag()));
    connect(rbtns[1], SIGNAL(clicked()), this, SLOT(converToTwosComp()));
    connect(rbtns[1], SIGNAL(clicked()), this, SLOT(setTwosComp()));
    connect(rbtns[2], SIGNAL(clicked()), this, SLOT(converToFloat16()));
    connect(rbtns[2], SIGNAL(clicked()), this, SLOT(setFloat16()));
    connect(rbtns[3], SIGNAL(clicked()), this, SLOT(converToDec()));
    connect(rbtns[3], SIGNAL(clicked()), this, SLOT(setDec()));

    connect(this,SIGNAL(VtCSigMag(QVector<QString>)),ctrl,SIGNAL(CtMSigMag(QVector<QString>)));
    connect(this,SIGNAL(VtCTwosComp(QVector<QString>)),ctrl,SIGNAL(CtMTwosComp(QVector<QString>)));
    connect(this,SIGNAL(VtCFloat16(QVector<QString>)),ctrl,SIGNAL(CtMFloat16(QVector<QString>)));
    connect(this,SIGNAL(VtCDec(QVector<QString>)),ctrl,SIGNAL(CtMDec(QVector<QString>)));
}

void MainWindow::switchType(){
  short int i=0, length = rbtns.size();
  while(i<length && !rbtns[i]->isChecked())
    ++i;
  rbtns[i]->setChecked(false);
  if(i==length-1) i = 0;
  else ++i;
  rbtns[i]->setChecked(true);
  emit rbtns[i]->clicked();
}
void MainWindow::keyPressEvent(QKeyEvent* event){
  int i = event->key();
  switch (i) {
    case 42: //*
      emit btns[13]->clicked();
      break;
    case 43: //+
      emit btns[11]->clicked();
      break;
    case 44: //,
      emit btns[10]->clicked();
      break;
    case 45: //-
      emit btns[12]->clicked();
      break;
    case 46: //.
      emit btns[10]->clicked();
      break;
    case 47:
      emit btns[14]->clicked();
      break;
    case 48: //0
      emit btns[0]->clicked();
      break;
    case 49: //1
      emit btns[1]->clicked();
      break;
    case 50: //2
      emit btns[2]->clicked();
      break;
    case 51: //3
      emit btns[3]->clicked();
      break;
    case 52: //4
      emit btns[4]->clicked();
      break;
    case 53: //5
      emit btns[5]->clicked();
      break;
    case 54: //6
      emit btns[6]->clicked();
      break;
    case 55: //7
      emit btns[7]->clicked();
      break;
    case 56: //8
      emit btns[8]->clicked();
      break;
    case 57: //9
      emit btns[9]->clicked();
      break;
    case 16777216: //escape
      emit btns[18]->clicked();
      break;
    case 16777219: //backspace
      emit btns[17]->clicked();
      break;
    default:
      if(event->key()==Qt::Key_Enter || event->key()==Qt::Key_Return)
	emit btns[15]->clicked();
      else if(event->key()==Qt::Key_Delete)
	emit btns[18]->clicked();
      break;
  }
}
void MainWindow::setSigMag(){
  currDataT = "sigMag";
}
void MainWindow::setTwosComp(){
  currDataT = "twosComp";
}
void MainWindow::setFloat16(){
  currDataT = "float16";
}
void MainWindow::setDec(){
  currDataT = "dec";
}
//Funzione mul la visualizzazione delle cifre digitate
void MainWindow::shownumber(){

    //"value" contiene la cifra corrispondente al tasto cliccato
    QPushButton* clickedBtn = qobject_cast<QPushButton *>(sender());
    int value = clickedBtn->text().toInt();

    //Se display ha valore di default (0), non accoda altri 0 digitati - Evita 0000
    if (display->text() == "0" && value == 0.0)
        return;

    //Se display ha valore di default (0), cancella lo 0 prima di scrivere le cifre digitate - Evita 012345
    if (display->text() == "0" && value != 0.0)
        display->clear();

    //Accoda le cifre digitate a quelle eventualmente presenti
    display->setText(display->text() + QString::number(value));
}

//Funzione mul la visualizzazione del point
void MainWindow::showpoint(){
    if(!display->text().contains('.'))
        display->setText(display->text() + ".");
}

//Funzione mul la cancellazione dell'ultima cifra digitata
void MainWindow::clear(){
    QString text = display->text();
    text.chop(1);

    if(text.isEmpty())
        text = "0";

    display->setText(text);
}

//Funzione mul la cancellazione di tutto il numero digitato
void MainWindow::clearall(){
    display -> setText("0");
    prova -> clear();
}

void MainWindow::operatorClicked(){
    QPushButton* clickedOp = qobject_cast<QPushButton *>(sender());
    QChar op = clickedOp->text()[0];

    QString input = display->text();
    display->clear();
    prova->setText(prova->text() + input + " " + QString(op) + " ");

}

void MainWindow::result(QString s){
  currStream.clear();
  display->setText(s);
}

void MainWindow::converToSigMag(){
  currStream.push_back(display->text());
  currStream.push_back(currDataT);
  currDataT = "sigMag";
  emit VtCSigMag(currStream);
}

void MainWindow::converToTwosComp(){
  currStream.push_back(display->text());
  currStream.push_back(currDataT);
  currDataT = "twosComp";
  emit VtCTwosComp(currStream);
}

void MainWindow::converToFloat16(){
  currStream.push_back(display->text());
  currStream.push_back(currDataT);
  currDataT = "float16";
  emit VtCFloat16(currStream);
}

void MainWindow::converToDec(){
  currStream.push_back(display->text());
  currStream.push_back(currDataT);
  currDataT = "dec";
  emit VtCDec(currStream);
}

MainWindow::~MainWindow()
{

}

