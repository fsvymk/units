#include <entry.h>
#include "units.h"
#include "ui_units.h"
#include <QUdpSocket>
#include <QDateTime>

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
    graphT.append(num);
    ui->listWidget->addItem(ss(num));
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
    unsigned range = ui->lineEdit_points->text().toInt();
    QDateTime setTime = QDateTime::fromString (QString("2000-01-01T00:00:00"), Qt::ISODate);
    QDateTime current = QDateTime::currentDateTime();
    quint32 msecs = setTime.time().msecsTo(current.time());
    ui->line_timestamp->setText(ss(msecs));
    ui->lineEdit_xfrom->setText(ss(msecs));
    ui->lineEdit_xto->setText(ss(msecs+range));

    QUdpSocket udpSocket;
    QString ip = ui->lineEdit_ip->text();
    quint16 port = ui->lineEdit_port->text().toInt();

    QByteArray message;
    message.append(QByteArray::fromHex("0000000100000001"));
    message.append(QByteArray::fromHex("0001000100010001"));

    int i;
    unsigned t;
    foreach(t, graphT){
        for(i=0; i<range; i++){
            entry point;
            point.t = t;    //i%4;
            point.v = 3;    //i%2;
            point.n = 4;    //100+i;
            point.z = 5;    //i%4;
            point.x = msecs + i;    //i/4;
            point.y = 10 + 1 * i + 2  * (i%2);    //10 - i/4;

            if(ui->radioButton->isChecked()){
                p("sinus");
            }

            if(ui->radioButton_2->isChecked()){
                p("sinus2");
            }

            if(ui->radioButton_3->isChecked()){
                p("fenze");
            }

            if(ui->radioButton_4->isChecked()){
                p("fenze2");
            }

            if(ui->radioButton_random->isChecked()){
                p("random");
            }

            serialize(point, &message); // Understandable by hadgehog
            p(toString(point));
            udpSocket.writeDatagram(message, QHostAddress(ip), port);
        }
    }
}

/*
void units::on_listWidget_itemClicked(QListWidgetItem *item)
{
    QString itemText = item->text();
}*/
