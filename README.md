# Rolling_Shutters
**for Mycroft**

My home rolling shutters are activated by radio signal. I use a Wemos mini D1 (ESP8266) in order to simulate one pushing the switch on the remote. The Wemos mini D1 is listening for a GET on its port 80. A command is transmitted through the URI.
This works fine from desktop using browser or from Android devices (smartphone or tablet) using an APK I wrote thanks to Thunkable.
It was too difficult to resist doing the same with Mycroft !


## Installation:
Refer to : **[Mycroft Skills Manager - msm](https://mycroft.ai/documentation/msm/)**

## Usage:
* `shut the rolling shutters`
* `open the rolling shutters`
* `shut the southern rolling shutters half way on sunny days`
