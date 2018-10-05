# Copyright 2016 Mycroft AI, Inc.
#
# This file is part of Mycroft Core.
#
# Mycroft Core is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# Mycroft Core is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Mycroft Core.  If not, see <http://www.gnu.org/licenses/>.

# SWK_rolling_shutters
# Mycroft <-> Wemos mini
# ESP8266_IP_address : http://RS_IpAddress/
# command : /?up
# command : /?down
# command : /?shadow


# Mycroft libraries

from adapt.intent import IntentBuilder
from mycroft.skills.core import MycroftSkill
from mycroft.util.log import getLogger
from mycroft import intent_handler

import requests


__author__ = 'henridbr' # hd@uip

Ip_Address = RS_IpAddress
print("RS_IpAddress : "+RS_IpAddress)
print("Ip_Address : "+Ip_Address)

LOGGER = getLogger(__name__)

class RollingShuttersSkill(MycroftSkill):

    def __init__(self):
        super(RollingShuttersSkill, self).__init__(name="RollingShuttersSkill")
        
    @intent_handler(IntentBuilder("OpenShuttersIntent").require("OpenShuttersKeyword"))
    def handle_open_shutters_intent(self, message):
        self.speak_dialog("roll.shut.open")
        r = requests.get('http://Ip_Address/?up')

    @intent_handler(IntentBuilder("CloseShuttersIntent").require("CloseShuttersKeyword"))
    def handle_close_shutters_intent(self, message):
        self.speak_dialog("roll.shut.close")
        r = requests.get('http://Ip_Address/?down')
                    
    @intent_handler(IntentBuilder("ShadowShuttersIntent").require("ShadowShuttersKeyword"))
    def handle_shadow_shutters_intent(self, message):
        self.speak_dialog("roll.shut.shadow")
        r = requests.get('http://Ip_Address/?shadow')

    def stop(self):
        pass

def create_skill():
    return RollingShuttersSkill()
