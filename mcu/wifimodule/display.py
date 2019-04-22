from machine import SPI
from machine import Pin

from pcd8544_fb import PCD8544_FB

class LcdDisplay(object):
    """
    A wrapper for the Nokie 5110 LCD screen and utilities
    """
    def __init__(self, dc, bl):
        # hardware spi
        self._hspi = SPI(1, baudrate=80000000, polarity=0, phase=0)

        # a reference to the LCD framebuffer
        self.lcd = PCD8544_FB(
            self._hspi, Pin(dc))
        # a reference to the backlight
        self.backlight = Pin(bl, Pin.OUT, value=1)

    def backlight_toggle(self):
        self.backlight.value(not self.backlight.value())

    def backlight_value(self, turn_on):
        self.backlight.value(0 if turn_on else 1)

    def backlight_on(self):
        self.backlight_value(True)

    def backlight_off(self):
        self.backlight_value(False)

    def turn_on(self):
        self.lcd.power_on()

    def turn_off(self):
        self.lcd.power_off()
        self.backlight_off()
    
    def clear(self, color=0):
        self.lcd.fill(color)
        self.lcd.show()