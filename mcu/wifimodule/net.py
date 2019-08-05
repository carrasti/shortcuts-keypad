import network
import ujson
import utime


class NetControl(object):
    """
    Some helper for controlling network
    """
    def __init__(self):
        self._interface = network.WLAN(network.STA_IF)
        self._connect_callbacks = []
        self._disconnect_callbacks = []
        self._last_is_connected = False

    def _get_registered_networks(self):
        """
        Read from configuration file the networks for which
        a password is provided, it is returned as tuple list
        of string, 
        """
        with open('config_wifi.json', 'rb') as f:
            return [
                (ssid.encode('ascii'), password) 
                for ssid, password in ujson.loads(f.read())
            ]

    def add_connect_callback(self, callback):
        self._connect_callbacks.append(callback)
    
    def add_disconnect_callback(self, callback):
        self._disconnect_callbacks.append(callback)

    def get_registered_available_nets(self):
        """
        Returns a list of networks and passwords based on
        registered SSIDs and available networks after scan
        """
        self._interface.active(True)
        registered_nets = self._get_registered_networks()
        available_nets = self._interface.scan()
        available_nets = {net[0]: net for net in available_nets if net[0] in dict(registered_nets)}
        
        # return the networks in preference order
        return [
            registered_net 
            for registered_net in registered_nets 
            if registered_net[0] in available_nets
        ]

    def _is_fully_connected(self):
        return self._interface.isconnected() and \
            self._interface.status() == network.STAT_GOT_IP

    def check_connection(self):
        """
        Checks connection status and runs callbacks for it
        """
        # on connection
        if not self._last_is_connected and self._is_fully_connected():
            any(fn(self) for fn in self._connect_callbacks)
            self._last_is_connected = True
        # on disconnection
        elif self._last_is_connected and not self._interface.isconnected():
            any(fn(self) for fn in self._disconnect_callbacks)
            self._last_is_connected = False

    def connect(self, ssid, password, timeout=10):
        if not self._interface.active():
            self._interface.active(True)

        # check if already connected to the current network
        if self._interface.isconnected() and \
            self._interface.config('essid').encode('ascii') == ssid:
            self.check_connection()
            return True

        # attempt to connect for given timeout
        timeout = utime.ticks_add(utime.ticks_ms(), timeout * 1000)
        self._interface.connect(ssid, password)
        while not self._is_fully_connected() and utime.ticks_ms() < timeout:
            utime.sleep(0.5)

        completed = self._is_fully_connected()
        if not completed:
            # stop retrying to connect
            self._interface.disconnect()
        
        # update connection
        self.check_connection()
        
        return completed
