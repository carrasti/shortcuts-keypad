# WiFi and screen controller module

This is the code for the WiFi and screen controller module. It is written in MicroPython.

The hardware used for this is:
 * A (cheap) [esp8266 (ESP12 NodeMCU) development board](https://www.az-delivery.de/collections/bestseller/products/d1-mini?ls=en). An standalone ESP12 can be used as well saving some space.
 * A [Nokia 5110 LCD display](https://www.az-delivery.de/products/lcd-display-84x48-pixel?ls=en) (PCD8544) with a resolution of 84x48 pixels connected to SPI bus.


This board communicates via UART to the input module. The input module is an Arduino-like board which receives inputs and acts as a virtual keyboard for the device it is connected to. The input module will send commands to the WiFi module requesting performing operations requiring WiFi or informing of the
state the board is in. In some cases there will be some configuration which needs to be duplicate in each board (or passed around on initialisation). 

The design choices of this set up are:
 * leveraging the simplicity of MicroPython for managing web content and some data structures.
 * taking advantage of the relative large size of the NodeMCU flash to store some media (like bitmaps) and configuration 


## Software requirements

At the time of writing the version of MicroPython used is 1.10

The program requires the following libraries:
 * Micropython PCD8544 LCD Framebuffer controller https://github.com/mcauser/micropython-pcd8544/blob/master/pcd8544_fb.py
