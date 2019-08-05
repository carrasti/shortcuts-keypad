import sys
from machine import SPI
from machine import Pin
import framebuf
from pcd8544_fb import PCD8544_FB

class LcdDisplay(object):
    """
    A wrapper for the Nokie 5110 LCD screen and utilities
    """
    def __init__(self, dc, bl):
        # hardware spi
        self._hspi = SPI(1, baudrate=20000000, polarity=0, phase=0)

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

    def draw_asset(self, asset_name, x=0, y=0, blit_key=None, show=False):
        """
        It draws and blits a file in the assets directory. Note that this file
        must be generated using the scripts in utils/image2bin.py as it prepares
        a 1 bit monochrome image as a format which can be read and processed
        by this method
        """
        with open('/assets/{}.bin'.format(asset_name), 'rb') as f:
            w = ord(f.read(1))
            h = ord(f.read(1))
            stride = ord(f.read(1))

            blit_args = []
            if blit_key is not None and blit_key in (1,0) :
                blit_args.append(blit_key)

            self.lcd.blit(
                framebuf.FrameBuffer(
                    bytearray(f.read()), w, h, framebuf.MONO_HLSB, stride), 
                x, y, *blit_args)
            if show:
                self.lcd.show()

    def show_connection(self, connected):
        if connected:
            data = [
                0b00000000,
                0b00111100,
                0b01111110,
                0b01111110,
                0b01111110,
                0b01111110,
                0b00111100,
                0b00000000,
            ]
        else:
            data = [
                0b00000000,
                0b01100110,
                0b00111100,
                0b00011000,
                0b00011000,
                0b00111100,
                0b01100110,
                0b00000000,
            ]
        _lcd = self.lcd
        for y in range(0, 8):
            _d = data[y]
            for x in range(0,8):
                self.lcd.pixel(_lcd.width + x - 8, y, (_d >> (7 - x)) & 1)
        # fixme: this is to be called outside
        _lcd.show()