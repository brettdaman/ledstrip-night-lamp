# ledstrip-night-lamp
This night lamp was designed and build as a new year present. The idea came from a fancy globe night lamps with a wake-up function and quickly got out of control. 
The design was done in blender and tinkercad. It is 3d printed with a zortrax m200 printer. For the electronics, it contains a teensy LC, a steel button as a capacitive touch button and an infrared remote.

A video of the light at work:
https://youtu.be/c7YyH6Le0BA

The design and the code are open source so you can build it yourself.

The design:
http://www.thingiverse.com/thing:2078079

In the video, you can see the different functions, out the frame I'm pushing the buttons on the remote.
It has 3 basic functions:
 - one color mode
 - two color mode, the text has a different color
 - special programs (hue color loop, color random, dual color circle, ...)

The capacitive button toggles the light on/ off.

The remote can:
 - turn the light on/off
 - change the modes
 - numbers 1 - 6: single colors modes
 - numbers 7 - 9 dual color modes
 - arrow up/down change color of he outside/inside by looping over the hue spectrum
 - arrow left/right loop over the special programs
 - -/+ buttons are for the light brightness

What you need:
 - a 3d printer with transparent and colored filament
 - a teensy LC
 - a 144leds/m 2811/2812 ledstrip (about 50cm needed)
 - a infrared remote
 - A steel button (for clothes) that fits the left small hole (or modify the size of the hole, drill or tinkercad) 
 - 2 resistors 1k and 470k - 50M Ohm depending on how sensitive the touch needs to be (I used a 10M)
 - power connector + 5v power supply
 - 2 M3 screws (or m4 if your printer cant print the thread)


![alt tag](https://github.com/brettdaman/ledstrip-night-lamp/blob/master/electrics_overview.jpg)

How to build
 - First 3D print the parts from thingiverese (http://www.thingiverse.com/thing:2078079)
 - Glue the name holder to the main body (mine was so tight it didn’t need glue
 - Take the infrared led and bend the wires to the back 90 degree, push the led in the right hole of the main part it should fit tight. Use glue if it comes loose.
 - Push the button through the print and solder two resistors to it, leave the unused leads hanging
 - Program the code to the teensy.
 - Take teensy and connect it with the 5v input coming from the connector from the back, cut the teensy usb power pad in the middle.
 - Take the teensy and guide the 2 leads from the button through the correct pads of the teensy
    * Resistor 10M to Teensy 2
    * Resistor 1k to Teensy 4
 - Push the teensy until it touches the wall with the screw hole and solder the wires at this position, cut the ends
 - Take the loose infrared led leads and solder them
   * IR pin 1 to Teensy 3v
   * IR pin 2 to Teensy Ground
   * IR pin 3 to Teensy 12
 - Wrap the ledstring in the middle around the main component and cut it where the 2 ends meet.
 -Install the ledstring in the name holder
   * Cut a piece of the ledstring to the size of the name holder
   * Solder wires from the ledstring around the model to the ledstring inside the name holder, make sure that the signal ends in the name holder at the first letter.
 - Solder the ledstring power to the power supply connector
 - Solder the data pin from the ledstring to pin 17 at Vin (The one at the short edge of the teensy)
 - In my case the teensy was holding in place by the wires from the IR and the button if yours comes loose use a little tape to secure it.
 - Test the electronics, see if everything is working.
 - Use a dremel to create a 45degree edge inwards on the top transparent part
 - Do the same at the bottom but in the other direction so the two pieces fit perfectly around the main body. (do it in small steps so you don’t need to print it again)
 - Use a little bit of glue to secure the top part, it should already fit pretty good with the lips in the model.
 - Screw the bottom plate to the main plate and make sure the edges fit nicely (worst case use a bit of glue)
 - Great success it should be complete by now
 
 

The adafruit products I used:

1 x Mini Remote Control[ID:389] = $4.95
1 x IR (Infrared) Receiver Sensor (TSOP38238) [ID:157] = $1.95
1 x Adafruit Mini Skinny NeoPixel Digital RGB LED Strip - 144 LED/m (1m WHITE) [ID:2969] = $64.95
1 x Teensy-LC Without Pins[ID:2419] = $13.95


Extra build images:

![alt tag](https://github.com/brettdaman/ledstrip-night-lamp/blob/master/electrics_wiring.jpg)

![alt tag](https://github.com/brettdaman/ledstrip-night-lamp/blob/master/on_off_button_connection.jpg)



