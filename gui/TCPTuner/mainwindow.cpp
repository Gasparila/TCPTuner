#include "mainwindow.h"
#include "tcp_grapher.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>
#include <QMutex>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdio.h>
#include <string>

// change to false to eliminate print statements
#define DEBUG true

using namespace std;

/** from http://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c */
static string exec(const char* cmd) {
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

static vector<string> &split(const string &s, char delim,
                             vector<string> &elems) {
  stringstream ss(s);
  string item;
  while (getline(ss, item, delim)) {
    elems.push_back(item);
  }
  return elems;
}

static vector<string> split(const string &s, char delim) {
  vector<string> elems;
  split(s, delim, elems);
  return elems;
}

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {
  ui->setupUi(this);

  //On startup read values and update GUI to match
  updateGUI("/sys/module/tcp_tuner/parameters/alpha");
  updateGUI("/sys/module/tcp_tuner/parameters/beta");
  updateGUI("/sys/module/tcp_tuner/parameters/fast_convergence");
  updateGUI("/sys/module/tcp_tuner/parameters/tcp_friendliness");

  // Location of the TCP Evil Parameters
  watcher.addPath("/sys/module/tcp_tuner/parameters/alpha");
  watcher.addPath("/sys/module/tcp_tuner/parameters/beta");
  watcher.addPath("/sys/module/tcp_tuner/parameters/fast_convergence");
  watcher.addPath("/sys/module/tcp_tuner/parameters/tcp_friendliness");

  QObject::connect(&watcher, SIGNAL(fileChanged(QString)), this,
                   SLOT(updateGUI(QString)));
  update_graph();
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::on_actionExit_triggered() {
  exit(EXIT_SUCCESS);
}

void MainWindow::updateGUI(const QString& str) {
  string value;
  int i_value;
  if (str.toStdString() == "/sys/module/tcp_tuner/parameters/alpha") {
    value = exec("cat /sys/module/tcp_tuner/parameters/alpha");
    value.pop_back(); // remove the newline
    i_value = stoi(value);
    ui->alpha_value->setValue(i_value);
  }
  else if (str.toStdString() == "/sys/module/tcp_tuner/parameters/beta") {
    value = exec("cat /sys/module/tcp_tuner/parameters/beta");
    value.pop_back(); // remove the newline
    i_value = stoi(value);
    ui->beta_value->setValue(i_value);
  }
  else if (str.toStdString() ==
           "/sys/module/tcp_tuner/parameters/fast_convergence") {
    value = exec("cat /sys/module/tcp_tuner/parameters/fast_convergence");
    value.pop_back(); // remove the newline
    i_value = stoi(value);
    if (i_value == 1) {
      ui->chk_fast_convergence->setChecked(true);
    }
    else {
      ui->chk_fast_convergence->setChecked(false);
    }
  }
  else if (str.toStdString() ==
           "/sys/module/tcp_tuner/parameters/tcp_friendliness") {
    value = exec("cat /sys/module/tcp_tuner/parameters/tcp_friendliness");
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

void MainWindow::update_graph() {
  static QMutex mutex;
  if (!mutex.tryLock()) {
    return;
  }
  // generate some data:
  QVector<double> x(40), y(40);   // initialize with entries 0..100
  tcp_grapher g(1000, 0.4, ui->alpha_value->value(), ui->beta_value->value());
  for (int i = 0; i < 40; ++i) {
    x[i] = i;
    y[i] = g.get_next();
  }
  // create graph and assign data to it:
  ui->tcp_graph->addGraph();
  ui->tcp_graph->graph(0)->setData(x, y);
  // give the axes some labels:
  ui->tcp_graph->xAxis->setLabel("time (rtt)");
  ui->tcp_graph->xAxis->setTicks(false);
  ui->tcp_graph->yAxis->setLabel("cwnd");
  ui->tcp_graph->yAxis->setTicks(false);
  // set axes ranges, so we see all data:
  ui->tcp_graph->xAxis->setRange(0, x.size());
  ui->tcp_graph->yAxis->setRange(0, g.get_max_window());
  ui->tcp_graph->replot();
  mutex.unlock();
}

void MainWindow::on_chk_fast_convergence_toggled(bool checked) {
  int e;
  if (checked) {
    e = system("echo -n 1 > /sys/module/tcp_tuner/parameters/fast_convergence");
  }
  else {
    e = system("echo -n 0 > /sys/module/tcp_tuner/parameters/fast_convergence");
  }
  if (DEBUG && e != 0) {
    cout << "[ERROR] Could not set fast_convergence." << endl;
  }
}

void MainWindow::on_chk_tcp_friendliness_toggled(bool checked) {
  int e;
  if (checked) {
    e = system("echo -n 1 > /sys/module/tcp_tuner/parameters/tcp_friendliness");
  }
  else {
    e = system("echo -n 0 > /sys/module/tcp_tuner/parameters/tcp_friendliness");
  }
  if (DEBUG && e != 0) {
    cout << "[ERROR] Could not set tcp_friendliness." << endl;
  }
}

void MainWindow::on_slider_alpha_valueChanged(int value) {
  int status;
  stringstream ss;
  ss << "echo -n " << value <<
    " > /sys/module/tcp_tuner/parameters/alpha";
  status = system(ss.str().c_str());
  if (DEBUG && status != 0) {
    cout << "[ERROR] Could not set alpha." << endl;
  }
  update_graph();
}

void MainWindow::on_slider_beta_valueChanged(int value) {
  int status;
  stringstream ss;
  ss << "echo -n " << value << " > /sys/module/tcp_tuner/parameters/beta";
  status = system(ss.str().c_str());
  if (DEBUG && status != 0) {
    cout << "[ERROR] Could not set beta." << endl;
  }
  update_graph();
}

void MainWindow::on_slider_rto_min_valueChanged(int value) {
  int status;
  vector<string> routes = split(exec("ip route"),'\n');

  for (string & route : routes) {
    string::size_type lock_pos = route.find(" lock");
    if (lock_pos != string::npos) {
      route.erase(lock_pos, 5);
    }
    string s = "rto_min";
    string::size_type start = route.find(s);
    if (start != string::npos) {
      //end is first space after rto_min <-- include space
      string::size_type end = route.find(" ", start + 8);
      route.erase(start, end);
    }
    stringstream ss;
    ss << "ip route change " << route;
    if (value != 0) {
      ss << " rto_min " << value << "ms";
    }

    status = system(ss.str().c_str());
    if (DEBUG && status != 0) {
      cout << ss.str() << endl;
      cout << "[ERROR] Could not set rto_min." << endl;
    }
  }
}

void MainWindow::on_slider_initcwnd_valueChanged(int value) {
  int status;
  vector<string> routes = split(exec("ip route"),'\n');

  for (string & route : routes) {
    string::size_type lock_pos = route.find(" lock");
    if (lock_pos != string::npos) {
      route.erase(lock_pos, 5);
    }
    string s = "initcwnd";
    string::size_type start = route.find(s);
    if (start != string::npos) {
      //end is first space after initcwnd <-- include space
      string::size_type end = route.find(" ", start + 9);
      route.erase(start, end);
    }
    stringstream ss;
    ss << "ip route change " << route;
    if (value != 0) {
      ss << " initcwnd " << value;
    }

    status = system(ss.str().c_str());
    if (DEBUG && status != 0) {
      cout << ss.str() << endl;
      cout << "[ERROR] Could not set initcwnd." << endl;
    }
  }
}

void MainWindow::on_btn_restoreDefaults_clicked() {
  // Set defaults
  int e;
  e = system("echo -n 1 > /sys/module/tcp_tuner/parameters/fast_convergence && "
             "echo -n 1 > /sys/module/tcp_tuner/parameters/tcp_friendliness && "
             "echo -n 717 > /sys/module/tcp_tuner/parameters/beta && "
             "echo -n 512 > /sys/module/tcp_tuner/parameters/alpha");
  if (DEBUG && e != 0) {
    cout << "[ERROR] Couldn't set defaults." << endl;
  }
  ui->slider_rto_min->setValue(0);
  ui->slider_initcwnd->setValue(0);
}

void MainWindow::on_actionAbout_TCPvil_triggered() {
  QMessageBox msgBox;
  msgBox.setText("TCPTuner: Congestion Control Your Way");
  msgBox.setInformativeText("Version: 0.1.0");
  msgBox.exec();
}
