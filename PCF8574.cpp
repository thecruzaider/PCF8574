#include "PCF8574.h"
#include "Arduino.h"



//#define DEBUG_PCF8574



/*! ---------------------------------------------------------------------------------------------
 *  @brief  Instantiates a new PCF8574 with the I2C address on a TwoWire interface
 * 
 */
PCF8574::PCF8574(TwoWire &w)
{
  wire = &w;
}

/*! ---------------------------------------------------------------------------------------------
 *  @brief  Setups the I2C interface and hardware for each PCF8574 connected
 *  @param  pAddress Address of the device 
 *  @param  pRegInitMask First IO state you want to set
 */
void  PCF8574::begin(unsigned char pAddress, unsigned char pRegInitMask)
{
#ifdef DEBUG_PCF8574
  Serial.println("Initialization of IO extender PCF8574");
  Serial.print("  address   0x");  Serial.println(pAddress, HEX);
  Serial.print("  reg mask  0x");  Serial.println(pRegInitMask, HEX);
#endif

  wire->begin();

  rmAddress = pAddress;
  rmWriteMask = pRegInitMask;

  PCF8574::writeByte(rmWriteMask);
}

/*! ---------------------------------------------------------------------------------------------
 *  @brief  Write single byte to PCF8574
 *  @param  pData Data byte to write IO state
 */
void PCF8574::writeByte(unsigned char pData)
{
#ifdef DEBUG_PCF8574
  Serial.print("PCF8574 - WriteByte 0x");  Serial.println(pData, HEX);
#endif

  wire->beginTransmission(rmAddress);
  wire->write(pData);
  wire->endTransmission();

  rmWriteMask = pData;
}

/*! ---------------------------------------------------------------------------------------------
 *  @brief  Write single bit to PCF8574
 *  @param  pData Data bit to write to an IO
 */
void PCF8574::writeBit(int pPinNum, bool pState)
{
  if (pState)
    rmWriteMask |= 1 << pPinNum;
  else
    rmWriteMask &= ~(1 << pPinNum);

#ifdef DEBUG_PCF8574
  Serial.print("PCF8574 - WriteBit 0x");  Serial.println(rmWriteMask, HEX);
#endif

  wire->beginTransmission(rmAddress);
  wire->write(rmWriteMask);
  wire->endTransmission();
}

/*! ---------------------------------------------------------------------------------------------
 *  @brief  Read single byte from PCF8574
 *  @return read value from the PCF8574
 */
unsigned char PCF8574::readByte(void)
{
  wire->beginTransmission(rmAddress);
  wire->endTransmission(true);
  wire->requestFrom(rmAddress, 1);

  unsigned char data =  wire->read();

#ifdef DEBUG_PCF8574
  Serial.print("PCF8574 - ReadByte 0x");  Serial.println(data, HEX);
#endif

  return data;
}

/*! ---------------------------------------------------------------------------------------------
 *  @brief  Read single bit from PCF8574
 *  @return Read value from an IO of the PCF8574
 */
bool PCF8574::readBit(int pPinNum)
{
  wire->beginTransmission(rmAddress);
  wire->endTransmission(true);
  wire->requestFrom(rmAddress, 1);

  bool data =  ((wire->read()) >> pNum) & 1;

#ifdef DEBUG_PCF8574
  Serial.print("PCF8574 - ReadBit 0x");  Serial.println(data, HEX);
#endif

  return data;
}
