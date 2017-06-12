#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
private:
    int id;
public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

    void tcpConnect(QString str);
public slots:
  void putData();
  void xablau(int tempo);
  void mataTempo();
  void timerEvent(QTimerEvent *e);
private slots:
  void on_buttonConnect_clicked();
  void on_buttonDisconnect_clicked();
  void on_buttonStart_clicked();
  void on_buttonStop_clicked();

private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
};

#endif // MAINWINDOW_H
