#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdlib>
#include <iostream>
#include <stdio.h>

using namespace std;

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_checkBox_toggled(bool checked) {
  if (checked) {
    system("echo -n 1 > /sys/module/tcp_evil/parameters/tcp_friendliness");
  }
  else {
    system("echo -n 0 > /sys/module/tcp_evil/parameters/tcp_friendliness");
  }
  system("cat /sys/module/tcp_evil/parameters/tcp_friendliness");
}

void MainWindow::on_actionExit_triggered() {
  exit(EXIT_SUCCESS);
}
