#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTimer>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  socket = new QTcpSocket(this);
  timer = new QTimer(this);
  //tcpConnect();
  connect(ui->btnConnect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(tcpConnect()));

  connect(ui->btnDisconnect,
          SIGNAL(clicked(bool)),
          this,
          SLOT(tcpDisconnect()));

  connect(ui->btnStart,
          SIGNAL(clicked(bool)),
          this,
          SLOT(startReception()));

  connect(ui->btnStop,
          SIGNAL(clicked(bool)),
          this,
          SLOT(stopReception()));

  connect(ui->btnUpdate,
          SIGNAL(clicked(bool)),
          this,
          SLOT(updateList()));

  connect(ui->listHost,
          SIGNAL(itemClicked(QListWidgetItem*)),
          this,
          SLOT(onHostSelected(QListWidgetItem*)));
  connect(timer,
          SIGNAL(timeout()),
          this,
          SLOT(getData()));

  ui->btnConnect->setEnabled(true);
  ui->btnDisconnect->setEnabled(false);
  ui->btnStart->setEnabled(false);
  ui->btnStop->setEnabled(false);
  ui->btnUpdate->setEnabled(false);
  ui->timingSlider->setEnabled(false);

}


void MainWindow::tcpConnect(){
  QString str;
  QStringList list;

  if(!(ui->edtIP->text() == "")){
      socket->connectToHost(ui->edtIP->text().trimmed(),1234);
      if(socket->waitForConnected(3000)){
        ui->btnConnect->setEnabled(false);
        ui->btnDisconnect->setEnabled(true);
        ui->btnUpdate->setEnabled(true);
        qDebug() << "Connected";
        //str = "<font color=\"green\">Connected to "+ ui->edtIP->text().trimmed() +"</font>";
        //showMessage(str);


        //GET HOSTS LIST
        qDebug() << "Listing...";
        socket->write("list\r\n");
        socket->waitForBytesWritten();
        socket->waitForReadyRead();
        qDebug() << socket->bytesAvailable();
        ui->listHost->clear();
        while(socket->bytesAvailable()){
          str = socket->readLine().replace("\n","").replace("\r","");
          list = str.split(" ");
          ui->listHost->addItems(list);
          for(int i=0; i<list.size(); i++){
              qDebug() << list.at(i) ;
              //ui->listHost->addItems();
          }
        }


      }
      else{
          ui->btnConnect->setEnabled(true);
          ui->btnDisconnect->setEnabled(false);
          qDebug() << "Disconnected";
          //str = "<font color=\"blue\">Unable to reach host "+ ui->edtIP->text().trimmed() +"</font>";
          //showMessage(str);
          QMessageBox::warning(this,tr("Error"), tr("Unable to Connect to Host"));
      }
  }else{
    QMessageBox::warning(this,tr("Error"), tr("O campo Ip nao pode ser vazio!"));
  }
}

void MainWindow::updateList(){

    QString str;
    QStringList list;

    if(socket->state() == QAbstractSocket::ConnectedState){
      if(socket->isOpen()){
          //GET HOSTS LIST
          qDebug() << "Listing...";
          socket->write("list\r\n");
          socket->waitForBytesWritten();
          socket->waitForReadyRead();
          qDebug() << socket->bytesAvailable();
          ui->listHost->clear();
          while(socket->bytesAvailable()){
            str = socket->readLine().replace("\n","").replace("\r","");
            list = str.split(" ");
            ui->listHost->addItems(list);
            for(int i=0; i<list.size(); i++){
                qDebug() << list.at(i) ;
                //ui->listHost->addItems();
            }
          }

          ui->btnStart->setEnabled(false);
          ui->btnStop->setEnabled(false);
          ui->timingSlider->setEnabled(false);
          ui->listHost->setEnabled(true);
      }
    }
}

void MainWindow::tcpDisconnect(){

    if(socket->state()== QAbstractSocket::ConnectedState){
        socket->disconnectFromHost();
        ui->btnConnect->setEnabled(true);
        ui->btnDisconnect->setEnabled(false);
        ui->btnStart->setEnabled(false);
        ui->btnStop->setEnabled(false);
        ui->btnUpdate->setEnabled(false);
        ui->timingSlider->setEnabled(false);
        ui->listHost->clear();
        qDebug() << "Disconnected";
        //str = "<font color=\"red\">Disconnected from "+ ui->edtIP->text().trimmed() +"</font>";
        //showMessage(str);
    }
}

void MainWindow::showMessage(QString msg){
    //ui->textBrowser->append(msg);
}

void MainWindow::startReception(){

    ui->btnStart->setEnabled(false);
    ui->btnStop->setEnabled(true);
    ui->timingSlider->setEnabled(false);
    ui->listHost->setEnabled(false);
    ui->btnUpdate->setEnabled(false);

    QString ip = ui->listHost->currentItem()->text();
    qDebug() << "Get Data From "+ ui->listHost->currentItem()->text();

    int sec = ui->timingSlider->value();
    timer->start(sec*1000);

}

void MainWindow::stopReception(){
    timer->stop();
    ui->btnStart->setEnabled(true);
    ui->btnStop->setEnabled(false);
    ui->timingSlider->setEnabled(true);
    ui->listHost->setEnabled(true);
    ui->btnUpdate->setEnabled(true);
}

void MainWindow::onHostSelected(QListWidgetItem *item){
    qDebug() << "Selected " + item->text();
    ui->btnStart->setEnabled(true);
    ui->timingSlider->setEnabled(true);

}


void MainWindow::getData(){
    QString str;
    QStringList list;

    if(socket->state() == QAbstractSocket::ConnectedState){
      if(socket->isOpen()){
        qDebug() << "reading...";
        QString data = "get "+ui->listHost->currentItem()->text()+" 30\r\n";
        socket->write(data.toStdString().c_str());
        socket->waitForBytesWritten();
        socket->waitForReadyRead();
        qDebug() << socket->bytesAvailable();
        while(socket->bytesAvailable()){
          str = socket->readLine().replace("\n","").replace("\r","");
          list = str.split(" ");
          QString x = list.at(0);
          QString y = list.at(1);
          ui->widget->setOriginX(0);
          ui->widget->setOriginY(0);
          int j =0;
          for(int i=0; i<list.size();i+=2){
              bool ok;
              j = j+1;
              str = list.at(i);
              QString x = list.at(i);
              QString y = list.at(i+1);
              qDebug()<<list.at(i) +" "+ list.at(i+1);

              ui->widget->plot(i, y.toInt());

          }
        }
      }
    }
}


MainWindow::~MainWindow()
{
  delete socket;
  delete ui;
  delete timer;
}
