#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
  class MainWindow;
}

class MainWindow: public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget* parent = 0);
  ~MainWindow();

private slots:
  void on_actionExit_triggered();

  void on_rb_packet_train_clicked();

  void on_chk_fast_convergence_toggled(bool checked);

  void on_chk_tcp_friendliness_toggled(bool checked);

  void on_rb_delay_clicked();

  void on_rb_both_clicked();

  void on_chk_hystart_toggled(bool checked);

  void on_slider_beta_valueChanged(int value);

  void on_slider_alpha_valueChanged(int value);

  void on_slider_ack_delta_valueChanged(int value);

  void on_slider_low_window_valueChanged(int value);

  void on_slider_ssthresh_valueChanged(int value);

  void on_chk_use_alpha_toggled(bool checked);

  void on_slider_rto_min_valueChanged(int value);

  void on_slider_mtu_valueChanged(int value);

  void on_slider_initcwnd_valueChanged(int value);

  void on_slider_initrwnd_valueChanged(int value);

  void on_slider_rtt_valueChanged(int value);

  void on_slider_rttvar_valueChanged(int value);

private:
  Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
