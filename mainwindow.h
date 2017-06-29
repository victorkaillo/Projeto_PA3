#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QDebug>
#include <QListWidgetItem>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

public slots:
  void getData();
  void tcpConnect();
  void tcpDisconnect();
  void showMessage(QString msg);
  void startReception();
  void stopReception();
  void updateList();
  void onHostSelected(QListWidgetItem* item);
private:
  Ui::MainWindow *ui;
  QTcpSocket *socket;
  QTimer *timer;
};

#endif // MAINWINDOW_H
