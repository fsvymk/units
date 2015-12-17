#ifndef UNITS_H
#define UNITS_H

#include <QMainWindow>
#include <QUdpSocket>
#include <entry.h>


namespace Ui {
class units;
}

class units : public QMainWindow
{
    Q_OBJECT

public:
    explicit units(QWidget *parent = 0);
    ~units();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void p(QString str);
    void readUdpDatagrams();
    void on_checkBox_oneDatagram_clicked();

private:
    Ui::units *ui;
    QList<unsigned> graphT;
    quint32 lastSend;
    QUdpSocket *Server;
};

#endif // UNITS_H
