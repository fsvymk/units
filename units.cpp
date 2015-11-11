#include <entry.h>
#include "units.h"
#include "ui_units.h"
#include <QUdpSocket>


units::units(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::units)
{
    ui->setupUi(this);
}

units::~units()
{
    delete ui;
}

void units::p(QString str){
    ui->textEdit->append(str);
}

void units::on_pushButton_clicked()         // ADD
{
    int num = ui->lineEdit->text().toInt();
    ui->lineEdit->setText(ss(num+1));
}

/*
int units::serialize(entry M, QByteArray* target){
    bool result = false;

    // Использование встроеного в Qt класса QDataStream оказалось лучшим решением.
    QDataStream niceTool(target, QIODevice::WriteOnly);

    niceTool << M.t;
    niceTool << M.v;

    niceTool << M.x;
    niceTool << M.y;

    niceTool << M.z;
    niceTool << M.n;

    return result;
}

entry units::deserialize(QByteArray* source){
    entry result;
    QDataStream prettyTool(source, QIODevice::ReadOnly);
    prettyTool >> result.t >> result.v >> result.x >> result.y >> result.z >> result.n;
    return result;
}*/

void units::on_pushButton_2_clicked()       // SEND
{
    QUdpSocket udpSocket;
    QString ip = ui->lineEdit_ip->text();
    quint16 port = ui->lineEdit_port->text().toInt();

    QByteArray message;
    message.append(QByteArray::fromHex("0000000100000001"));
    message.append(QByteArray::fromHex("0001000100010001"));

    int i;
    for(i=0; i<32; i++){

        entry point;
        point.t = i%4;
        point.v = i%2;
        point.n = 100+i;
        point.z = i%4;
        point.x = i/4;
        point.y = 10 - i/4;

        serialize(point, &message); // Understandable by hadgehog
        udpSocket.writeDatagram(message, QHostAddress(ip), port);

    }


}
