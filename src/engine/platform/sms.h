/**
 * Furnace Tracker - multi-system chiptune tracker
 * Copyright (C) 2021-2022 tildearrow and contributors
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef _SMS_H
#define _SMS_H

#include "../dispatch.h"
#include "../macroInt.h"
#include "sound/sn76496.h"
extern "C" {
  #include "../../../extern/Nuked-PSG/ympsg.h"
}
#include <queue>

class DivPlatformSMS: public DivDispatch {
  struct Channel {
    int freq, baseFreq, pitch, pitch2, note, actualNote, ins;
    bool active, insChanged, freqChanged, keyOn, keyOff, inPorta;
    signed char vol, outVol;
    DivMacroInt std;
    void macroInit(DivInstrument* which) {
      std.init(which);
      pitch2=0;
    }
    Channel():
      freq(0),
      baseFreq(0),
      pitch(0),
      pitch2(0),
      note(0),
      actualNote(0),
      ins(-1),
      active(false),
      insChanged(true),
      freqChanged(false),
      keyOn(false),
      keyOff(false),
      inPorta(false),
      vol(15),
      outVol(15) {}
  };
  Channel chan[4];
  DivDispatchOscBuffer* oscBuf[4];
  bool isMuted[4];
  unsigned char lastPan;
  unsigned char oldValue; 
  unsigned char snNoiseMode;
  int divider=16;
  double toneDivider=64.0;
  double noiseDivider=64.0;
  bool updateSNMode;
  bool resetPhase;
  bool isRealSN;
  bool stereo;
  bool nuked;
  sn76496_base_device* sn;
  ympsg_t sn_nuked;
  struct QueuedWrite {
    unsigned short addr;
    unsigned char val;
    bool addrOrVal;
    QueuedWrite(unsigned short a, unsigned char v): addr(a), val(v), addrOrVal(false) {}
  };
  std::queue<QueuedWrite> writes;
  friend void putDispatchChan(void*,int,int);

  void acquire_nuked(short* bufL, short* bufR, size_t start, size_t len);
  void acquire_mame(short* bufL, short* bufR, size_t start, size_t len);
  public:
    void acquire(short* bufL, short* bufR, size_t start, size_t len);
    int dispatch(DivCommand c);
    void* getChanState(int chan);
    DivMacroInt* getChanMacroInt(int ch);
    DivDispatchOscBuffer* getOscBuffer(int chan);
    void reset();
    void forceIns();
    void tick(bool sysTick=true);
    void muteChannel(int ch, bool mute);
    bool isStereo();
    bool keyOffAffectsArp(int ch);
    bool keyOffAffectsPorta(int ch);
    int getPortaFloor(int ch);
    void setFlags(unsigned int flags);
    void notifyInsDeletion(void* ins);
    void poke(unsigned int addr, unsigned short val);
    void poke(std::vector<DivRegWrite>& wlist);
    const char** getRegisterSheet();
    const char* getEffectName(unsigned char effect);
    void setNuked(bool value);
    int init(DivEngine* parent, int channels, int sugRate, unsigned int flags);
    void quit();
    ~DivPlatformSMS();
};

#endif
