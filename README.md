# Rolling_Shutters
**a SKILL for Mycroft**

My home rolling shutters are radio controlled using remotes. 
I use a Wemos D1 mini (ESP8266) in order to simulate one pushing the switches on a remote. 
The Wemos D1 mini is listening for a GET on its port 80. A command is transmitted through text in the URI.
This works fine from desktop using browser or from Android devices (smartphone or tablet) using an APK I wrote thanks to Thunkable.
It was too difficult to resist doing the same with Mycroft !


## Devices
* Raspberry 3 
* Google AIY Voice kit 
* Wemos D1 mini


## Installation:
Refer to : **[Mycroft Skills Manager - msm](https://mycroft.ai/documentation/msm/)**

Before installing check your own device IP address !


## Usage:
* to shut the rolling shutters : close shutters or close window or shutters down
* to open the rolling shutters : open shutters or open windows or lift shutters
* to shut the southern rolling shutters half way on sunny days : shadow shutters or sunny windows shut or southern windows shut


## Author
* Henri Debierre


## Acknowledgments
To those who wrote the Microft.AI documentation : [Developing a new Skill](https://mycroft.ai/documentation/skills/introduction-developing-skills/#structure-of-the-skill-repo)
