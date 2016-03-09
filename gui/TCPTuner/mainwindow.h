#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QFileSystemWatcher>
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

  void update_graph();

  void on_chk_fast_convergence_toggled(bool checked);

  void on_chk_tcp_friendliness_toggled(bool checked);

  void on_slider_beta_valueChanged(int value);

  void on_slider_alpha_valueChanged(int value);

  void on_slider_rto_min_valueChanged(int value);

  void on_slider_initcwnd_valueChanged(int value);

  void on_btn_restoreDefaults_clicked();

  void updateGUI(const QString& str);

  void on_actionAbout_TCPvil_triggered();

private:
  Ui::MainWindow* ui;
  QFileSystemWatcher watcher;
};

#endif // MAINWINDOW_H
