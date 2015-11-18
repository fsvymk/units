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

    //QString toString(entry s); // entry.h
    //int serialize(entry M, QByteArray* target);
    //entry deserialize(QByteArray* source);

    //user methods:
    void p(QString str);

    //QString s(int str); // entry.h
    //void on_listWidget_itemClicked(QListWidgetItem *item);

private:
    Ui::units *ui;
    QList<unsigned> graphT;
    quint32 lastSend;
};

#endif // UNITS_H
