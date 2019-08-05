/*
 * Uart communication
 */

#include "uart_comm.h"

UartComm::UartComm(HardwareSerial *hs_in) {
  serial = hs_in;
}

void UartComm::sendMessage(uint8_t command, uint16_t value){
  serial->write(0xf1);
  serial->write(0xe5);
  serial->write(command);
  serial->write(value);
}