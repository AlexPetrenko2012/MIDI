#include "dialog.h"

#include "qdebug.h"
#include <QtGlobal>

#include  "../CMidi/src/CMidiIn.h"
#include  "../CMidi/src/CMidiOut.h"
#include  "../CMidi/src/CMidiFile.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    CMidiOut * midi_out = new CMidiOut();
    CMidiIn * midi_in = new CMidiIn();

    QMap<QString,QString> devs = midi_out->devices();

    QObject::connect ( midi_in,SIGNAL(midiEvent(quint32,quint32)), this, SLOT(onMidiEvent(quint32,quint32)));



 //   devs.contains()


    QString deviseID = "24:0";

bool r;

r =  midi_in->connect(deviseID);

midi_in->start();



int y =5;


}

Dialog::~Dialog()
{
}

void Dialog::onMidiEvent(quint32 message, quint32 timing)
{

        QMidiEvent event;
        event.setMessage(message);

        qDebug() << "received event" << event.type()
                 << "note:" << event.note()
                 << "velocity:" << event.velocity();

}
