#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <memory>

using namespace std;

/** from http://stackoverflow.com/questions/478898/how-to-execute-a-command-and-get-output-of-command-within-c */
std::string exec(const char* cmd) {
    shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) return "ERROR";
    char buffer[128];
    string result = "";
    while (!feof(pipe.get())) {
        if (fgets(buffer, 128, pipe.get()) != NULL)
            result += buffer;
    }
    return result;
}

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
  int status;
  status = system("echo -n 1 > /sys/module/tcp_evil/parameters/hystart_detect");
  if (status != 0) {
    cout << "[ERROR] Could not set hystart_detect." << endl;
  }
  cout << "Hystart Detect set to Packet Train" << endl;
}

void MainWindow::on_rb_delay_clicked() {
  int status;
  status = system("echo -n 2 > /sys/module/tcp_evil/parameters/hystart_detect");
  if (status != 0) {
    cout << "[ERROR] Could not set hystart_detect." << endl;
  }
  cout << "Hystart Detect set to Delay" << endl;
}

void MainWindow::on_rb_both_clicked() {
  int status;
  status = system("echo -n 3 > /sys/module/tcp_evil/parameters/hystart_detect");
  if (status != 0) {
    cout << "[ERROR] Could not set hystart_detect." << endl;
  }
  cout << "Hystart Detect set to both Delay and Packet Train" << endl;
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
    route.erase(route.begin()+i, route.end());
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

void MainWindow::on_btn_restoreDefaults_clicked()
{
    // Set defaults
    int e;
    e = system("echo -n 3 > /sys/module/tcp_evil/parameters/hystart_detect");
    if (e != 0) {
      cout << "[ERROR] Couldn't set defaults." << endl;
    }
    e = system("echo -n 1 > /sys/module/tcp_evil/parameters/fast_convergence");
    if (e != 0) {
      cout << "[ERROR] Couldn't set defaults." << endl;
    }
    e = system("echo -n 1 > /sys/module/tcp_evil/parameters/tcp_friendliness");
    if (e != 0) {
      cout << "[ERROR] Couldn't set defaults." << endl;
    }
    e = system("echo -n 1 > /sys/module/tcp_evil/parameters/hystart");
    if (e != 0) {
      cout << "[ERROR] Couldn't set defaults." << endl;
    }
    e = system("echo -n 0 > /sys/module/tcp_evil/parameters/initial_ssthresh");
    if (e != 0) {
      cout << "[ERROR] Couldn't set defaults." << endl;
    }
    e = system("echo -n 16 > /sys/module/tcp_evil/parameters/hystart_low_window");
    if (e != 0) {
      cout << "[ERROR] Couldn't set defaults." << endl;
    }
    e = system("echo -n 2 > /sys/module/tcp_evil/parameters/hystart_ack_delta");
    if (e != 0) {
      cout << "[ERROR] Couldn't set defaults." << endl;
    }
    e = system("echo -n 717 > /sys/module/tcp_evil/parameters/beta");
    if (e != 0) {
      cout << "[ERROR] Couldn't set defaults." << endl;
    }
}
