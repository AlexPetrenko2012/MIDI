//****************************************
//
// author: Petrenko Alexandr   12.10.2023
//
//*****************************************




#include "dialog.h"
#include "ui_dialog.h"

#include "qdebug.h"
#include <QtGlobal>

#include <iostream>

#include  <sstream>

#include  "../CMidi/src/CMidiOut.h"
#include  "../CMidi/src/CMidiFile.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent),ui(new Ui::Dialog),fConnected(false)
{
    ui->setupUi(this);

    QObject::connect (ui->btnConnect,SIGNAL(clicked()), this, SLOT(onBtnConnect_clicked()));
    QObject::connect (ui->cmbxMidiInputs,SIGNAL(currentIndexChanged(int)), this, SLOT(onCmbxMidiInputs_currentIndexChanged(int)));


    CMidiOut * midi_out = new CMidiOut(); // TODO перенести в класс.
    midi_in = new CMidiIn();

    QObject::connect ( midi_in,SIGNAL(midiEvent(quint32,quint32)), this, SLOT(onMidiEvent(quint32,quint32)));

    devises = midi_out->devices();

    QMapIterator<QString, QString> it(devises);
    while (it.hasNext()) {
        it.next();
        qDebug() << it.key() << ": " << it.value() << Qt::endl;
        deviseIDs.append(it.key());
        ui->cmbxMidiInputs->addItem(QString("%1 %2").arg(it.value()).arg(it.key()));
    }



}

Dialog::~Dialog()
{
}


void Dialog::connectAndStart()
{
    if(fConnected)
        return;

    QString deviseID = deviseIDs.at(ui->cmbxMidiInputs->currentIndex());

    if (!midi_in->connect(deviseID))
    {
        qDebug() << "Can't connect to " << deviseID;
        return;
    }
    qDebug() << "Connected  to " << deviseID;

    midi_in->start();
    ui->btnConnect->setChecked(true);
    ui->btnConnect->setText("Disconect");
    fConnected = true;
}

void Dialog::disconnectAndStop()
{
    if(!fConnected)
        return;


    midi_in->stop();
    midi_in->disconnect();

    ui->btnConnect->setChecked(false);
    ui->btnConnect->setText("Connect");
    fConnected = false;

    QString deviseID = deviseIDs.at(ui->cmbxMidiInputs->currentIndex());


    qDebug() << "Disonnected from" << deviseID;
}




void Dialog::onMidiEvent(quint32 message, quint32 timing)
{

    QMidiEvent event;
    event.setMessage(message);


    std::stringstream  ss;

    ss <<  event.type() << "  " << event.note() << "  " << event.velocity() << "\n";

    ui->textEdit->append(QString().fromStdString(ss.str()));

    qDebug() << "received event:" << event.type()
             << "note:" << event.note()
             << "velocity:" << event.velocity();

}

void Dialog :: onBtnConnect_clicked()

{
    if (!ui->btnConnect->isChecked())
        disconnectAndStop();
    else
    {
        connectAndStart();
        ui->btnConnect->setEnabled(false); // todo
        ui->cmbxMidiInputs->setEnabled(false); // todo

    }
}

void Dialog::onCmbxMidiInputs_currentIndexChanged(int Index)
{
    return;

    if (Index==-1)
        return;

    if (ui->btnConnect->isChecked())
        disconnectAndStop();

}

