
#include "CMidiIn.h"

CMidiIn::CMidiIn(QObject *parent)
	: QObject(parent),
	fMidiPtrs(nullptr),
	fConnected(false)
{
}

CMidiIn::~CMidiIn()
{
	if (fConnected)
		disconnect();
}
