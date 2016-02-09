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

  void on_slider_beta_sliderMoved(int position);

  void on_slider_beta_sliderReleased();

  void on_slider_ack_delta_sliderMoved(int position);

  void on_slider_ack_delta_sliderReleased();

  void on_slider_low_window_sliderMoved(int position);

  void on_slider_low_window_sliderReleased();

  void on_slider_ssthresh_sliderMoved(int position);

  void on_slider_ssthresh_sliderReleased();

private:
  Ui::MainWindow* ui;
};

#endif // MAINWINDOW_H
