
#include "CMidiOut.h"

#include "CMidiFile.h"

// TODO: error reporting

CMidiOut::CMidiOut()
	: fMidiPtrs(NULL),
	  fConnected(false)
{
}
CMidiOut::~CMidiOut()
{
	if (fConnected)
		disconnect();
}

void CMidiOut::sendEvent(const QMidiEvent& e)
{
	if (e.type() == QMidiEvent::SysEx) {
		sendSysEx(e.data());
		return;
	}

	sendMsg(e.message());
}

void CMidiOut::setInstrument(int voice, int instr)
{
	qint32 msg = 0xC0 + voice;
	msg |= instr << 8;
	sendMsg(msg);
}

void CMidiOut::noteOn(int note, int voice, int velocity)
{
	qint32 msg = 0x90 + voice;
	msg |= note << 8;
	msg |= velocity << 16;
	sendMsg(msg);
}

void CMidiOut::noteOff(int note, int voice, int velocity)
{
	qint32 msg = 0x80 + voice;
	msg |= note << 8;
	msg |= velocity << 16;
	sendMsg(msg);
}

void CMidiOut::pitchWheel(int voice, int value)
{
	qint32 msg = 0xE0 + voice;
	msg |= (value & 0x7F) << 8; // fine adjustment (ignored by many synths)
	msg |= (value / 128) << 16; // coarse adjustment
	sendMsg(msg);
}

void CMidiOut::channelAftertouch(int voice, int value)
{
	qint32 msg = 0xD0 + voice;
	msg |= value << 8;
	sendMsg(msg);
}

void CMidiOut::polyphonicAftertouch(int note, int voice, int value)
{
	qint32 msg = 0xA0 + voice;
	msg |= note << 8;
	msg |= value << 16;
	sendMsg(msg);
}

void CMidiOut::controlChange(int voice, int number, int value)
{
	qint32 msg = 0xB0 + voice;
	msg |= number << 8;
	msg |= value << 16;
	sendMsg(msg);
}

void CMidiOut::stopAll()
{
	for (int i = 0; i < 16; i++)
		stopAll(i);
}

void CMidiOut::stopAll(int voice)
{
	sendMsg((0xB0 | voice) | (0x7B << 8));
}
