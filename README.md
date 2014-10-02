ESP8266-LED-Server
==================
To set up, you need to adjust three variables.

in the Arduino sketch:
The SSID of your WiFi.
The password of your WiFi.

In website.py:
The ip address of your esp8266.

to start, wire up the LED and the esp8266 (3.3V power and logic, use level shifters if using 5v Arduino) and then upload the sketch.

To start the computer side you will run website.py.  You will need to have both python, and [Tornado](http://www.tornadoweb.org/en/stable/) installed for the python to run.

either run website.py from the IDE or on the command line: python website.py

To change the color of the LEDs open a browser and go to http://localhost or the IP address of the computer running the web server.

