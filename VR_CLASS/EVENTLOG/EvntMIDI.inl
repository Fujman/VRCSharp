#ifndef __EVNTMIDI_INL
#define __EVNTMIDI_INL
/////////////////////////////////////////////////////////////////////////////
// Class YEventMidi inline implementation
inline YEventMidi::YEventMidi(const void *p, int n/*0*/) : YEvent64(p,n)
  { ASSERT(m_nType==EVN_MIDI_TYPE); }
inline YEventMidi::YEventMidi(YMidiActionInfo info) : YEvent64(EVN_MIDI_TYPE,info.info.dw[0],info.info.dw[1])
  { }
inline YEventMidi::~YEventMidi()
  { }

#endif//__EVNTMIDI_INL
