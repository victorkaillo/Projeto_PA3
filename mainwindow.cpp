#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  socket = new QTcpSocket(this);

  connect(ui->pushButtonPut,
          SIGNAL(clicked(bool)),
          this,
          SLOT(putData()));
}

void MainWindow::tcpConnect(QString str){
  socket->connectToHost(str,1234);
  if(socket->waitForConnected(3000)){
    qDebug() << "Connected";
  }
  else{
    qDebug() << "Disconnected";
  }
}

void MainWindow::timerEvent(QTimerEvent *e){
  putData();
}

void MainWindow::putData()
{
  QDateTime datetime;
  QString str;
  if(socket->state()== QAbstractSocket::ConnectedState){
      datetime = QDateTime::currentDateTime();
      str = "set "+
          datetime.toString(Qt::ISODate)+
          " "+
          QString::number(ui->sliderMin->value() + qrand()%(ui->sliderMax->value()+1))+"\r\n";
      ui->textEdit->insertPlainText(str);
      qDebug() << str;
      qDebug() << socket->write(str.toStdString().c_str()) << " bytes written";
      if(socket->waitForBytesWritten(3000)){
        qDebug() << "wrote";
      }
  }
}
void MainWindow::mataTempo(){
    killTimer(id);
}

void MainWindow::xablau(int tempo)
{
    //temporizador int id = startTimer(1000); killTimer(id)
    id = startTimer(tempo*1000);
}
MainWindow::~MainWindow()
{
  delete socket;
  delete ui;
}

void MainWindow::on_buttonConnect_clicked()
{
    tcpConnect(ui->lineEdit->text());
}

void MainWindow::on_buttonDisconnect_clicked()
{
    //disconnect
    socket->disconnectFromHost();
}

void MainWindow::on_buttonStart_clicked()
{
    xablau(ui->sliderTiming->value());
}

void MainWindow::on_buttonStop_clicked()
{
    mataTempo();
}
