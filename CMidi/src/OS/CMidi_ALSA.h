
#pragma once

#include <QThread>

class CMidiIn;
struct NativeMidiInInstances;

namespace CMidiInternal
{
//! \brief The MidiInReceiveThread class runs the ALSA MIDI input thread.  This
//! is required since the function that reads input from a \c snd_seq_t handle
//! blocks.
class MidiInReceiveThread : public QThread
{
	Q_OBJECT

public:
    MidiInReceiveThread(CMidiIn* CMidiIn, NativeMidiInInstances* fMidiPtrs, QObject* parent = nullptr);

private:
	void run() override;

private:
    CMidiIn* fMidiIn;
	NativeMidiInInstances* fMidiPtrs;
};
};
