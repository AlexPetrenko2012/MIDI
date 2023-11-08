#include "dialog.h"

#include "qdebug.h"
#include <QtGlobal>

#include  "../QMidi/src/QMidiIn.h"
#include  "../QMidi/src/QMidiOut.h"
#include  "../QMidi/src/QMidiFile.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    QMidiOut * midi_out = new QMidiOut();
    QMidiIn * midi_in = new QMidiIn();

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
