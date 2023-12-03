#ifndef CMIDIMESSAGER_H
#define CMIDIMESSAGER_H


#include <QMap>
#include <QList>
#include <QString>


#include  "../CMidi/src/CMidiIn.h"


class CMidiMessager :  public QObject
{
    Q_OBJECT

public:
    CMidiMessager();
~CMidiMessager();

private:
    CMidiIn *midi_in;
    QMap<QString,QString> devises;
    QList<QString> deviseIDs;
    bool fConnected;

private:

    void connectAndStart();
    void disconnectAndStop();



public slots:

void onMidiEvent(quint32 message, quint32 timing);




};

#endif // CMIDIMESSAGER_H
