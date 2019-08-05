# -*- coding: UTF-8 -*-
"""
This is the main program loop for the WiFi and display module
"""
import sys
import uos
import time
import urandom
from display import LcdDisplay
from uartcomm import UartComm, COMMAND_SET_SCREEN
from net import NetControl
import urequests
import ujson

# initialise the network class
nc = NetControl()

# initialise UART communication class
uartcomm = UartComm()

# initialise the display
LCD_PIN_DC = 15  # Data
LCD_PIN_BL = 16  # Backlight
display = LcdDisplay(LCD_PIN_DC, LCD_PIN_BL)

# register callbacks
def command_set_screen_callback(data):
    display.lcd.text(data, 0, 0, 1)
    display.lcd.show()

uartcomm.add_handler(0x01, command_set_screen_callback)

# Display splash screen and wait 5 seconds, in this time should
# be possible to log in to REPL and stop the program for reflashing,
# after that the UART used for REPL will be used for communication
display.backlight_on()

display.draw_asset('splash_screen', show=True)

time.sleep(10)
display.backlight_off()

time.sleep(1)
# clear the display
display.clear()

# hijack the uart from REPL
uartcomm.begin()

"""
display.show_connection(False)
nc.add_connect_callback(lambda net_control: display.show_connection(True))
nc.add_disconnect_callback(lambda net_control: display.show_connection(False))
nets = nc.get_registered_available_nets()
if nets:
    connected = nc.connect(*nets[0])

print("connection")
response = urequests.get('http://stib.monkeynirvana.com/?format=json&client=stib&stop_id=8211', headers={
    'Authorization': 'Bearer 8pJYM4YKq3VXJNHddJRiWAciUHBsmHfP'
})

print(response.status_code)

if (response.status_code == 200):
    display.lcd.fill(0)
    display.lcd.text(response.json()['country'], 0, 0, 1)
    display.lcd.show()
"""

#sys.exit(0)
#uartcomm.end()
# the application loop:
#while True:

display.backlight_on()
for x in range(0,50):
    # check for UART input
    try:
        uartcomm.check_input(display)
    except:
        pass
    #command = b'\x01' + x
    #uartcomm._extract_input_instruction(command)
    time.sleep(0.2)
uartcomm.end()
display.backlight_off()

#display.lcd.fill(0)
#display.lcd.text("DONE", 0, 0, 1)
#display.lcd.show()

