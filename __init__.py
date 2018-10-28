# Rolling_Shutters
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

LOGGER = getLogger(__name__)

class RollingShuttersSkill(MycroftSkill):
    

    def __init__(self):
        super(RollingShuttersSkill, self).__init__(name="RollingShuttersSkill")
    
        self.Ip_Address = self.settings.get('RS_IpAddress') 
  #      print("Ip address : ",self.Ip_Address)
        
    @intent_handler(IntentBuilder("OpenShuttersIntent").require("OpenShuttersKeyword"))
    def handle_open_shutters_intent(self, message):
        self.speak_dialog("roll.shut.open")
        r = requests.get("http://"+self.Ip_Address+"/?up")

    @intent_handler(IntentBuilder("CloseShuttersIntent").require("CloseShuttersKeyword"))
    def handle_close_shutters_intent(self, message):
        self.speak_dialog("roll.shut.close")
        r = requests.get("http://"+self.Ip_Address+"/?down")
                    
    @intent_handler(IntentBuilder("ShadowShuttersIntent").require("ShadowShuttersKeyword"))
    def handle_shadow_shutters_intent(self, message):
        self.speak_dialog("roll.shut.shadow")
        r = requests.get("http://"+self.Ip_Address+"/?shadow")

    def stop(self):
        pass

def create_skill():
    return RollingShuttersSkill()
