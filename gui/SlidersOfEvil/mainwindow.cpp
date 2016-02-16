#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>

using namespace std;

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {
  ui->setupUi(this);
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_actionExit_triggered() {
  exit(EXIT_SUCCESS);
}

void MainWindow::on_rb_packet_train_clicked() {
  system("echo -n 1 > /sys/module/tcp_evil/parameters/hystart_detect");
  cout << "Hystart Detect set to Packet Train" << endl;
}

void MainWindow::on_rb_delay_clicked() {
  system("echo -n 2 > /sys/module/tcp_evil/parameters/hystart_detect");
  cout << "Hystart Detect set to Delay" << endl;
}

void MainWindow::on_rb_both_clicked() {
  system("echo -n 3 > /sys/module/tcp_evil/parameters/hystart_detect");
  cout << "Hystart Detect set to both Delay and Packet Train" << endl;
}

void MainWindow::on_chk_fast_convergence_toggled(bool checked) {
  if (checked) {
    system("echo -n 1 > /sys/module/tcp_evil/parameters/fast_convergence");
  }
  else {
    system("echo -n 0 > /sys/module/tcp_evil/parameters/fast_convergence");
  }
  // system(
  //   "(echo -n Fast Convergence: ) && (cat /sys/module/tcp_evil/parameters/fast_convergence)");
}

void MainWindow::on_chk_tcp_friendliness_toggled(bool checked) {
  if (checked) {
    system("echo -n 1 > /sys/module/tcp_evil/parameters/tcp_friendliness");
  }
  else {
    system("echo -n 0 > /sys/module/tcp_evil/parameters/tcp_friendliness");
  }
  // system(
  //   "(echo -n tcp_friendliness: ) && (cat /sys/module/tcp_evil/parameters/tcp_friendliness)");
}

void MainWindow::on_chk_hystart_toggled(bool checked) {
  if (checked) {
    system("echo -n 1 > /sys/module/tcp_evil/parameters/hystart");
  }
  else {
    system("echo -n 0 > /sys/module/tcp_evil/parameters/hystart");
  }
  // system(
  //   "(echo -n hystart: ) && (cat /sys/module/tcp_evil/parameters/hystart)");
}

void MainWindow::on_slider_beta_sliderMoved(int position) {
  stringstream ss;
  ss << "echo -n " << position << " > /sys/module/tcp_evil/parameters/beta";
  system(ss.str().c_str());
}

void MainWindow::on_slider_beta_sliderReleased() {
  // system(
  //   "(echo -n beta: ) && (cat /sys/module/tcp_evil/parameters/beta)");
}

void MainWindow::on_slider_ack_delta_sliderMoved(int position) {
  stringstream ss;
  ss << "echo -n " << position <<
    " > /sys/module/tcp_evil/parameters/hystart_ack_delta";
  system(ss.str().c_str());
}

void MainWindow::on_slider_ack_delta_sliderReleased() {
  // system(
  //   "(echo -n hystart_ack_delta: ) && (cat /sys/module/tcp_evil/parameters/hystart_ack_delta)");
}

void MainWindow::on_slider_low_window_sliderMoved(int position) {
  stringstream ss;
  ss << "echo -n " << position <<
    " > /sys/module/tcp_evil/parameters/hystart_low_window";
  system(ss.str().c_str());
}

void MainWindow::on_slider_low_window_sliderReleased() {
  // system(
  //   "(echo -n hystart_low_window: ) && (cat /sys/module/tcp_evil/parameters/hystart_low_window)");
}

void MainWindow::on_slider_ssthresh_sliderMoved(int position) {
  stringstream ss;
  ss << "echo -n " << position <<
    " > /sys/module/tcp_evil/parameters/initial_ssthresh";
  system(ss.str().c_str());
}

void MainWindow::on_slider_ssthresh_sliderReleased() {
  // system(
  //   "(echo -n initial_ssthresh: ) && (cat /sys/module/tcp_evil/parameters/initial_ssthresh)");
}
