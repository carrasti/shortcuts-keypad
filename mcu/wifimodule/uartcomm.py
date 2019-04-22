
import uos
from machine import UART

# a marker to indicate beginning of command
INSTRUCTION = b'\xf1\xe5'

COMMAND_SET_SCREEN = 0x01

class UartComm():
    """
    The main class for communication between the main input
    module and the WiFi module
    """
    def __init__(self):
        self.handlers = {}
        self._uart = UART(0, 115200)
        self._uart.init(115200, bits=8, parity=None, stop=1)

    def begin(self):
        """
        Enables the serial port to receive data, otherwise
        repl will not allow data being read 
        """
        uos.dupterm(None, 1)

    def end(self):
        """
        Re-enable the serial port to be used by REPL
        """
        uos.dupterm(UART(0, 115200), 1)

    def add_handler(self, command, callback):
        self.handlers[command] = callback

    def apply_command(self, display, command, *args):
        if command in self.handlers:
            self.handlers[command](*args)

    def _extract_input_instruction(self, display, data):
        """
        Extracts the command if found and applies it
        """
        command = data[0]
        self.apply_command(display, command, data[1:])

    def check_input(self, display):
        """
        This method is to be called whenever any serial
        data is available, it will try to extract commands
        """
        if not self._uart.any():
            return False
        
        uartdata = self._uart.read()
        display.lcd.fill(0)
        display.lcd.text(uartdata[3:], 0, 0, 1)
        display.lcd.show()
        r = len(uartdata)
        while True:
            position = uartdata.rfind(INSTRUCTION, 0, r)
            if position < 0:
                break
            self._extract_input_instruction(display, uartdata[position+2:r])
            r = position
