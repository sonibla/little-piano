# Little Piano
A simple DIY syhthetizer made with Arduino, Raspberry and paper !

## Installation

### Prerequisites

 - Arduino MEGA
 - Raspberry Pi (running a Linux environment with Python 3)
 - USB type B to type A cable (to connect the Arduino and the Raspberry via serial)
 - 10X LEDs 
 - 10X 220Ω resistors
 - 14X 1MΩ resistors
 - Some cables to connects LEDs to the Arduino
 - A speaker with jack input
 - Aluminium sheets (to create the keyboard)

### On the Raspberry:

Download sound files and [synthe.py](codes/synthe.py), place sound files in a *WAV* directory.

Don't forget to plug a speaker to the Raspberry.

After plugging the Arduino on a USB port, open a terminal and type 

    python3 synthe.py

to start playing piano.

### On the Arduino:

Upload [synthe.ino](codes/synthe.ino) on your Arduino. You'll need the Arduino IDE or similar, check [Arduino official site](https://www.arduino.cc/) for more info.

## Usage

Simply touch aluminium parts to play sound, use octave changer buttons to play lower or higher.
You may change sensitivity configuration in [synthe.ino](codes/synthe.ino) if necessary.

## Authors

* [**Alban Benmouffek**](https://github.com/sonibla)
* **Baptiste Domingo**
* **Hugo Graveline**

## License
This project is licensed under the [MIT License](https://tldrlegal.com/license/mit-license) - see the [LICENSE](LICENSE) file for details
