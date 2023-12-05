//****************************************
//
// author: Petrenko Alexandr   5.12.2023
//
//*****************************************


#include <QCoreApplication>
#include <QObject>

#include <iostream>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <termios.h>

#include "cmidimessager.h"

using namespace std;

static struct termios oldSettings;
static struct termios newSettings;


void initTermios()
{
    tcgetattr(0,&oldSettings); /* grab old terminal i/o settings */
    newSettings = oldSettings; /* make new settings same as old settings */
    newSettings.c_lflag &= ~ICANON; /* disable buffered i/o */
    newSettings.c_lflag &= ~ECHO; /* disable echo mode */
    tcsetattr(0,TCSANOW,&newSettings); /* use these new terminal i/o settings now */
}


void resetTermios(void)
{
    tcsetattr(0,TCSANOW,&oldSettings);
}


void signit_handler(int)
{
    cout << "\nexit\n";
    qApp->quit();
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    CMidiMessager* cmm = new CMidiMessager;
    initTermios();
    signal(SIGINT,signit_handler);
    cmm->connectAndStart();
    return a.exec();
}
