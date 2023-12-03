//****************************************
//
// author: Petrenko Alexandr   2.12.2023
//
//*****************************************



#include "cmidimessager.h"

#include "qdebug.h"
#include <iostream>
#include  <sstream>

#include <QtGlobal>


#include  "../CMidi/src/CMidiOut.h"
#include  "../CMidi/src/CMidiFile.h"



CMidiMessager::CMidiMessager()
{


    CMidiOut * midi_out = new CMidiOut(); // TODO перенести в класс.
    midi_in = new CMidiIn();

    QObject::connect ( midi_in,SIGNAL(midiEvent(quint32,quint32)), this, SLOT(onMidiEvent(quint32,quint32)));

    devises = midi_out->devices();

    QMapIterator<QString, QString> it(devises);
    while (it.hasNext()) {
        it.next();
        qDebug() << it.key() << ": " << it.value() << Qt::endl;
        deviseIDs.append(it.key());
      }


}


CMidiMessager::~CMidiMessager()
{

}


void CMidiMessager::connectAndStart()
{
    if(fConnected)
        return;


    for (int i=0; i < deviseIDs.count();i++)
    {

    QString deviseID = deviseIDs.at(i); //(ui->cmbxMidiInputs->currentIndex());

    if (!midi_in->connect(deviseID))
    {
        qDebug() << "Can't connect to " << deviseID;
        return;
    }
    qDebug() << "Connected  to " << deviseID;

    }

    midi_in->start();
//    ui->btnConnect->setChecked(true);
//    ui->btnConnect->setText("Disconect");
//    fConnected = true;
}

void CMidiMessager::disconnectAndStop()
{
    if(!fConnected)
        return;


    midi_in->stop();
    midi_in->disconnect();

//    ui->btnConnect->setChecked(false);
//    ui->btnConnect->setText("Connect");
    fConnected = false;

//    QString deviseID = deviseIDs.at(ui->cmbxMidiInputs->currentIndex());


   // qDebug() << "Disonnected from" << deviseID;
}




void CMidiMessager::onMidiEvent(quint32 message, quint32 timing)
{

    QMidiEvent event;
    event.setMessage(message);


    std::stringstream  ss;

    ss <<  event.type() << "  " << event.note() << "  " << event.velocity() << "\n";

    // ui->textEdit->append(QString().fromStdString(ss.str()));

    qDebug() << "received event:" << event.type()
             << "note:" << event.note()
             << "velocity:" << event.velocity();

}
