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

    quint32 timestamp();
    void p(QString str);
    void readUdpDatagrams();
    void on_checkBox_oneDatagram_clicked();

    void on_lineEdit_serverPort_selectionChanged();

    void on_horizontalSlider_4_rangeChanged(int min, int max);

    void on_horizontalSlider_4_actionTriggered(int action);

    void on_horizontalSlider_4_sliderMoved(int position);

    void on_horizontalSlider_4_valueChanged(int value);

    void on_horizontalSlider_3_valueChanged(int value);

private:
    Ui::units *ui;
    QList<unsigned> graphT;
    quint32 lastSend;
    QUdpSocket *Server;

    quint16     serverPort;
    quint32     randPointer;
};

#endif // UNITS_H
