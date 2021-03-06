#ifndef PCF8574_H
#define PCF8574_H

#include "Arduino.h"
#include "Wire.h"



class PCF8574
{
  public:

  PCF8574(TwoWire &w);

  int begin(unsigned char pAddress, unsigned char pRegInitMask);

  int writeByte(unsigned char pData);
  int writeBit(int pPinNum, bool pState);

  unsigned char readByte(void);
  bool readBit(int pPinNum);

  private:

  TwoWire *wire;

  unsigned char rmAddress;    // Addresses of used I/O extender
  unsigned char rmWriteMask;  // Mask if you want to write just a bit
};

#endif
