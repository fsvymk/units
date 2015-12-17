#include <entry.h>
#include "units.h"
#include "ui_units.h"
#include <QUdpSocket>
#include <QDateTime>
#include <qmath.h>
#include <QTimer>

units::units(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::units)
{
    ui->setupUi(this);
    //lastSend = QDateTime::fromString (QString("1986-06-06T05:00:00"), Qt::ISODate);
    lastSend = QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();
    ui->pushButton->click();

    Server = new QUdpSocket;
    connect(Server, SIGNAL(readyRead()),
                this, SLOT(readUdpDatagrams()));

    quint16 serverPort = ui->lineEdit_serverPort->text().toInt();
    if (Server->bind(serverPort)) { ui->textEdit_incoming->append("Ready.");}
    else {       ui->textEdit_incoming->append("Cann't bind port" + QString::number(serverPort));    }
}

units::~units()
{
    delete ui;
}

void units::readUdpDatagrams()
{
    while (Server->hasPendingDatagrams()) {
        QByteArray datagram;
        //datagram.resize(udpServerSocket.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        Server->readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);
        ui->textEdit_incoming->append(datagram.toHex());
    }
}

void units::p(QString str){
    ui->textEdit->append(str);
}

void units::on_pushButton_clicked()         // ADD
{
    int num = ui->lineEdit->text().toInt();
    ui->lineEdit->setText(ss(num+1));
    graphT.append(num);
    ui->listWidget->addItem(ss(num));
}

void units::on_pushButton_2_clicked()       // SEND
{
    bool oneDatagram = ui->checkBox_oneDatagram->isChecked();
    unsigned steps = ui->lineEdit_points->text().toInt();
    quint32 current=  QDateTime::currentDateTimeUtc().toMSecsSinceEpoch();
    quint32 msecs = current - lastSend;
    unsigned step = msecs/steps;

    if(step==0) {p("warning. current time equals time of last send.");}

    ui->line_timestamp->setText(ss(current));
    ui->lineEdit_xfrom->setText(ss(lastSend));
    ui->lineEdit_xto->setText(ss(msecs));

    QUdpSocket udpSocket;
    QString ip = ui->lineEdit_ip->text();
    quint16 port = ui->lineEdit_port->text().toInt();

    QByteArray allMessages;
    QByteArray message;
    message.append(QByteArray::fromHex("0000000100000001"));
    message.append(QByteArray::fromHex("0001000100010001"));

    int i;
    unsigned t;
    foreach(t, graphT){
        for(i=0; i<msecs; i+=step){
            entry point;
            point.t = t;    //i%4;
            point.v = 3;    //i%2;
            point.n = 4;    //100+i;
            point.z = 5;    //i%4;
            point.x = lastSend + i;    //i/4;
            point.y = 20 + (lastSend+i)%100;   //10 - i/4;

            if(ui->radioButton->isChecked()){
                p("sinus");
                double sy = (lastSend+i)/1000;
                point.y = sy;
            }

            if(ui->radioButton_2->isChecked()){
                p("sinus2");
                double sy = (double)lastSend+i;
                sy /= 1000;
                sy = sin(sy);
                point.y = sy*20;
            }

            if(ui->radioButton_3->isChecked()){
                p("fence");
            }

            if(ui->radioButton_4->isChecked()){
                p("fence2");
            }

            if(ui->radioButton_random->isChecked()){
                p("random");
                point.y = qrand()%500 + 500;
            }

            serialize(point, &message); // Understandable by hadgehog
            p(toString(point));
            if(oneDatagram){
                    allMessages.append(message);
            }else{
                udpSocket.writeDatagram(message, QHostAddress(ip), port);
            }
        }
    }
    if(oneDatagram){udpSocket.writeDatagram(allMessages, QHostAddress(ip), port);}
    lastSend = current;
}


void units::on_checkBox_oneDatagram_clicked()
{

}
