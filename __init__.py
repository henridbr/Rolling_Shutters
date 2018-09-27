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
# http://192.168.0.85/
# command : /?up
# command : /?down
# command : /?shadow


# Mycroft libraries
from os.path import dirname

from adapt.intent import IntentBuilder
from mycroft.skills.core import MycroftSkill
from mycroft.util.log import getLogger

import requests


__author__ = 'Henri','@henridbr' # hd@uip

LOGGER = getLogger(__name__)

class RollingShutterSkill(MycroftSkill):

    def __init__(self):
        super(RollingShutterSkill, self).__init__(name="RollingShutterSkill")

    def initialize(self):
	    self.load_data_files(dirname(__file__))

        RollingShutter_command_intent = IntentBuilder("RollingShutterCommandIntent").require("RollingShutterKeyword").require("Action").build()
        self.register_intent(RollingShutter_command_intent, self.handle_RollingShutter_command_intent)

    def handle_RollingShutter_command_intent(self, message):
        action_word = message.data.get("Action")
        LOGGER.info("Command word: " + action_word)
        if action_word == "open":
		    self.speak_dialog("roll.shut.open")   
		    r = requests.get('http://192.168.0.85/?up')
	    elif action_word == "close":
		    self.speak_dialog("roll.shut.close") 
		    r = requests.get('http://192.168.0.85/?down')
	    elif action_word == "shadow":
		    self.speak_dialog("roll.shut.shadow") 
		    r = requests.get('http://192.168.0.85/?shadow')
	    else:
		    self.speak("not sure about that")  	

	def stop(self):
        pass

def create_skill():
    return RollingShutterSkill()
