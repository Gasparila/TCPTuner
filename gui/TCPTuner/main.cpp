#include "mainwindow.h"
#include <QApplication>
#include <stdio.h>
#include <unistd.h>


int main(int argc, char* argv[]) {
 if (getuid()) {
   printf("%s", "You must run this program as root!\n");
   exit(EXIT_SUCCESS);
 }

  QApplication a(argc, argv);
  MainWindow w;
  w.show();

  return a.exec();
}
