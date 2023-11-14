
#include "CMidiIn.h"

CMidiIn::CMidiIn(QObject *parent)
	: QObject(parent),
	fMidiPtrs(nullptr),
    fConnected(false),
    fStarted(false)
{
}

CMidiIn::~CMidiIn()
{
    if (fStarted)
        stop();

	if (fConnected)
		disconnect();
}
