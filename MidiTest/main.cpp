#include "dialog.h"

#include <QApplication>
#include <QMap>

#include  "../CMidi/src/CMidiIn.h"
#include  "../CMidi/src/CMidiOut.h"








int main(int argc, char *argv[])
{
    QApplication a(argc, argv);



    Dialog w;
    w.show();
    return a.exec();
}
