/*
 * Uart Communication
 */

#ifndef Uart_comm_input_h
#define Uart_comm_input_h

#include "Arduino.h"


#define UARTCMD_TYPE_MODE 0x01
#define UARTCMD_TYPE_KEYPRESS 0x02
#define UARTCMD_TYPE_KEYRELEASE 0x03

#define UARTCMD_TYPE_TEXT 0x30

class UartComm {
  public:
    UartComm(HardwareSerial *);
    void sendMessage(uint8_t, uint16_t);
  private:
    HardwareSerial *serial;
};

#endif