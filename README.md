# Weather Blooming Flower
Sketch for [this 3D printed flower](https://www.prusaprinters.org/prints/134028-blooming-flower-remix) that adds 2 features:
- The color of the bloom leds change depending on the oudoor temp in your location
- The petals will open at sunrise, and close at sunset (also based off your location)

## Requirements:
1) Your latitude and longitude (use a service like https://www.maps.ie/coordinates.html)
2) An API Key (free) from api.openweather.org
3) A wireless network to which you know the SSID and password

See the commented section in the .ino file to add your values

## Dependencies
Designed for an `ESP8266` board, specifically `NodeMCU 1.0 (ESP-12E Module)`.

Additional libraries needed (All can be installed to the Arduino IDE through the Library Manager):
- [Adafruit NeoPixel](https://www.arduino.cc/reference/en/libraries/adafruit-neopixel/)
- [Arduino_JSON](https://www.arduino.cc/reference/en/libraries/arduino_json/)
- [NTPClient](https://www.arduino.cc/reference/en/libraries/ntpclient/)
- [Servo](https://www.arduino.cc/reference/en/libraries/servo/)
