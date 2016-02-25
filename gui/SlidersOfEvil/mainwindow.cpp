#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdio.h>
#include <string>

using namespace std;

/** from http://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c */
std::string exec(const char* cmd) {
  shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
  if (!pipe) {
    return "ERROR";
  }
  char buffer[128];
  string result = "";
  while (!feof(pipe.get())) {
    if (fgets(buffer, 128, pipe.get()) != NULL) {
      result += buffer;
    }
  }
  return result;
}

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {
  ui->setupUi(this);

  //On startup read values and update GUI to match
  updateGUI("/sys/module/tcp_evil/parameters/alpha");
  updateGUI("/sys/module/tcp_evil/parameters/beta");
  updateGUI("/sys/module/tcp_evil/parameters/fast_convergence");
  updateGUI("/sys/module/tcp_evil/parameters/hystart");
  updateGUI("/sys/module/tcp_evil/parameters/hystart_ack_delta");
  updateGUI("/sys/module/tcp_evil/parameters/hystart_detect");
  updateGUI("/sys/module/tcp_evil/parameters/hystart_low_window");
  updateGUI("/sys/module/tcp_evil/parameters/initial_ssthresh");
  updateGUI("/sys/module/tcp_evil/parameters/tcp_friendliness");

  // Location of the TCP Evil Parameters
  watcher.addPath("/sys/module/tcp_evil/parameters/alpha");
  watcher.addPath("/sys/module/tcp_evil/parameters/beta");
  watcher.addPath("/sys/module/tcp_evil/parameters/fast_convergence");
  watcher.addPath("/sys/module/tcp_evil/parameters/hystart");
  watcher.addPath("/sys/module/tcp_evil/parameters/hystart_ack_delta");
  watcher.addPath("/sys/module/tcp_evil/parameters/hystart_detect");
  watcher.addPath("/sys/module/tcp_evil/parameters/hystart_low_window");
  watcher.addPath("/sys/module/tcp_evil/parameters/initial_ssthresh");
  watcher.addPath("/sys/module/tcp_evil/parameters/tcp_friendliness");
  QStringList fileList = watcher.files();
  Q_FOREACH(QString file, fileList)
  qDebug() << "[info] Watching: " << file << "\n";

  QObject::connect(&watcher, SIGNAL(fileChanged(QString)), this,
                   SLOT(updateGUI(QString)));
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_actionExit_triggered() {
  exit(EXIT_SUCCESS);
}

void MainWindow::updateGUI(const QString& str) {
  cout << "[info] Update GUI" << endl;
  string value;
  int i_value;
  if (str.toStdString() == "/sys/module/tcp_evil/parameters/alpha") {
    value = exec("cat /sys/module/tcp_evil/parameters/alpha");
    value.pop_back(); // remove the newline
    i_value = stoi(value);
    ui->alpha_value->setValue(i_value);
  }
  else if (str.toStdString() == "/sys/module/tcp_evil/parameters/beta") {
    value = exec("cat /sys/module/tcp_evil/parameters/beta");
    value.pop_back(); // remove the newline
    i_value = stoi(value);
    ui->beta_value->setValue(i_value);
  }
  else if (str.toStdString() ==
           "/sys/module/tcp_evil/parameters/fast_convergence") {
    value = exec("cat /sys/module/tcp_evil/parameters/fast_convergence");
    value.pop_back(); // remove the newline
    i_value = stoi(value);
    if (i_value == 1) {
      ui->chk_fast_convergence->setChecked(true);
    }
    else {
      ui->chk_fast_convergence->setChecked(false);
    }
  }
  else if (str.toStdString() == "/sys/module/tcp_evil/parameters/hystart") {
    value = exec("cat /sys/module/tcp_evil/parameters/hystart");
    value.pop_back(); // remove the newline
    i_value = stoi(value);
    if (i_value == 1) {
      ui->chk_hystart->setChecked(true);
    }
    else {
      ui->chk_hystart->setChecked(false);
    }
  }
  else if (str.toStdString() ==
           "/sys/module/tcp_evil/parameters/hystart_ack_delta") {
    value = exec("cat /sys/module/tcp_evil/parameters/hystart_ack_delta");
    value.pop_back(); // remove the newline
    i_value = stoi(value);
    ui->hystartackdelta_value->setValue(i_value);
  }
  else if (str.toStdString() ==
           "/sys/module/tcp_evil/parameters/hystart_detect") {
    value = exec("cat /sys/module/tcp_evil/parameters/hystart_detect");
    value.pop_back(); // remove the newline
    i_value = stoi(value);
    switch (i_value) {
    case 1:
      ui->rb_packet_train->setChecked(true);
      break;
    case 2:
      ui->rb_delay->setChecked(true);
      break;
    default:
      ui->rb_both->setChecked(true);
      break;
    }
  }
  else if (str.toStdString() ==
           "/sys/module/tcp_evil/parameters/hystart_low_window") {
    value = exec("cat /sys/module/tcp_evil/parameters/hystart_low_window");
    value.pop_back(); // remove the newline
    i_value = stoi(value);
    ui->low_window_value->setValue(i_value);
  }
  else if (str.toStdString() ==
           "/sys/module/tcp_evil/parameters/initial_ssthresh") {
    value = exec("cat /sys/module/tcp_evil/parameters/initial_ssthresh");
    value.pop_back(); // remove the newline
    i_value = stoi(value);
    ui->ssthresh_value->setValue(i_value);
  }
  else if (str.toStdString() ==
           "/sys/module/tcp_evil/parameters/tcp_friendliness") {
    value = exec("cat /sys/module/tcp_evil/parameters/tcp_friendliness");
    value.pop_back(); // remove the newline
    i_value = stoi(value);
    if (i_value == 1) {
      ui->chk_tcp_friendliness->setChecked(true);
    }
    else {
      ui->chk_tcp_friendliness->setChecked(false);
    }
  }
}

void MainWindow::on_rb_packet_train_clicked() {
  int status;
  status = system("echo -n 1 > /sys/module/tcp_evil/parameters/hystart_detect");
  if (status != 0) {
    cout << "[ERROR] Could not set hystart_detect." << endl;
  }
}

void MainWindow::on_rb_delay_clicked() {
  int status;
  status = system("echo -n 2 > /sys/module/tcp_evil/parameters/hystart_detect");
  if (status != 0) {
    cout << "[ERROR] Could not set hystart_detect." << endl;
  }
}

void MainWindow::on_rb_both_clicked() {
  int status;
  status = system("echo -n 3 > /sys/module/tcp_evil/parameters/hystart_detect");
  if (status != 0) {
    cout << "[ERROR] Could not set hystart_detect." << endl;
  }
}

void MainWindow::on_chk_fast_convergence_toggled(bool checked) {
  int e;
  if (checked) {
    e = system("echo -n 1 > /sys/module/tcp_evil/parameters/fast_convergence");
  }
  else {
    e = system("echo -n 0 > /sys/module/tcp_evil/parameters/fast_convergence");
  }
  if (e != 0) {
    cout << "[ERROR] Could not set fast_convergence." << endl;
  }
}

void MainWindow::on_chk_tcp_friendliness_toggled(bool checked) {
  int e;
  if (checked) {
    e = system("echo -n 1 > /sys/module/tcp_evil/parameters/tcp_friendliness");
  }
  else {
    e = system("echo -n 0 > /sys/module/tcp_evil/parameters/tcp_friendliness");
  }
  if (e != 0) {
    cout << "[ERROR] Could not set tcp_friendliness." << endl;
  }
}

void MainWindow::on_chk_hystart_toggled(bool checked) {
  int e;
  if (checked) {
    e = system("echo -n 1 > /sys/module/tcp_evil/parameters/hystart");
  }
  else {
    e = system("echo -n 0 > /sys/module/tcp_evil/parameters/hystart");
  }
  if (e != 0) {
    cout << "[ERROR] Could not set hystart." << endl;
  }
}

void MainWindow::on_slider_alpha_valueChanged(int value) {
  int status;
  stringstream ss;
  ss << "echo -n " << value <<
    " > /sys/module/tcp_evil/parameters/alpha";
  status = system(ss.str().c_str());
  if (status != 0) {
    cout << "[ERROR] Could not set alpha." << endl;
  }
}

void MainWindow::on_slider_beta_valueChanged(int value) {
  int status;
  stringstream ss;
  ss << "echo -n " << value << " > /sys/module/tcp_evil/parameters/beta";
  status = system(ss.str().c_str());
  if (status != 0) {
    cout << "[ERROR] Could not set beta." << endl;
  }
}

void MainWindow::on_slider_ack_delta_valueChanged(int value) {
  int status;
  stringstream ss;
  ss << "echo -n " << value <<
    " > /sys/module/tcp_evil/parameters/hystart_ack_delta";
  status = system(ss.str().c_str());
  if (status != 0) {
    cout << "[ERROR] Could not set hystart_ack_delta." << endl;
  }
}

void MainWindow::on_slider_low_window_valueChanged(int value) {
  int status;
  stringstream ss;
  ss << "echo -n " << value <<
    " > /sys/module/tcp_evil/parameters/hystart_low_window";
  status = system(ss.str().c_str());
  if (status != 0) {
    cout << "[ERROR] Could not set hystart_low_window." << endl;
  }
}

void MainWindow::on_slider_ssthresh_valueChanged(int value) {
  int status;
  stringstream ss;
  ss << "echo -n " << value <<
    " > /sys/module/tcp_evil/parameters/initial_ssthresh";
  status = system(ss.str().c_str());
  if (status != 0) {
    cout << "[ERROR] Could not set initial_sshtresh." << endl;
  }
}

void MainWindow::on_chk_use_alpha_toggled(bool checked) {
  int e;
  if (checked) {
    e = system("echo -n 1 > /sys/module/tcp_evil/parameters/use_alpha");
  }
  else {
    e = system("echo -n 0 > /sys/module/tcp_evil/parameters/use_alpha");
  }
  if (e != 0) {
    cout << "[ERROR] Could not set use_alpha." << endl;
  }
}

void MainWindow::on_slider_rto_min_valueChanged(int value) {
  int status;
  string route = exec("ip route | head -n1");
  string s = "rto_min";
  string::size_type i = route.find(s);
  if (i != string::npos) {
    route.erase(route.begin() + i, route.end());
  }
  else {
    route.pop_back();
  }
  stringstream ss;
  ss << "ip route change " << route << " rto_min " << value << "ms";

  status = system(ss.str().c_str());
  if (status != 0) {
    cout << ss.str() << endl;
    cout << "[ERROR] Could not set rto_min." << endl;
  }
}

void MainWindow::on_slider_mtu_valueChanged(int value) {
}

void MainWindow::on_slider_initcwnd_valueChanged(int value) {
}

void MainWindow::on_slider_initrwnd_valueChanged(int value) {
}

void MainWindow::on_slider_rtt_valueChanged(int value) {
}

void MainWindow::on_slider_rttvar_valueChanged(int value) {
}

void MainWindow::on_btn_restoreDefaults_clicked() {
  // Set defaults
  int e;
  e = system("echo -n 3 > /sys/module/tcp_evil/parameters/hystart_detect && "
             "echo -n 1 > /sys/module/tcp_evil/parameters/fast_convergence && "
             "echo -n 1 > /sys/module/tcp_evil/parameters/tcp_friendliness && "
             "echo -n 1 > /sys/module/tcp_evil/parameters/hystart && "
             "echo -n 1 > /sys/module/tcp_evil/parameters/hystart && "
             "echo -n 0 > /sys/module/tcp_evil/parameters/initial_ssthresh && "
             "echo -n 16 > /sys/module/tcp_evil/parameters/hystart_low_window && "
             "echo -n 2 > /sys/module/tcp_evil/parameters/hystart_ack_delta && "
             "echo -n 717 > /sys/module/tcp_evil/parameters/beta && "
             "echo -n 1 > /sys/module/tcp_evil/parameters/alpha");
  if (e != 0) {
    cout << "[ERROR] Couldn't set defaults." << endl;
  }
}
