#include "Controller/binController.h"
#include <QApplication>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  binController* m = new binController();

  return a.exec();
}
