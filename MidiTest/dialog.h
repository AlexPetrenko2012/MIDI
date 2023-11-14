#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QMap>
#include <QList>
#include <QString>


#include  "../CMidi/src/CMidiIn.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();


private:
    Ui::Dialog *ui;
    CMidiIn *midi_in;
    QMap<QString,QString> devises;
    QList<QString> deviseIDs;
    bool fConnected;

private:

    void connectAndStart();
    void disconnectAndStop();



private slots:
    void onBtnConnect_clicked();
    void onCmbxMidiInputs_currentIndexChanged(int Index);

public slots:

void onMidiEvent(quint32 message, quint32 timing);

};
#endif // DIALOG_H
