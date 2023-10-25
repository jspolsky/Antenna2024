Future Turtles 2024 Public LED Display
====

For the Future Turtles 44' LED mast this year, I'm hoping to improve the array of short, 6' tall "whips" that accompany it.

* I want to have 24 whips instead of 12 whips
* They will be about 3' apart instead of 6', so the patterns will be more interesting
* I plan to improve the cabling substantially, allowing the whips to be daisy-chained instead of each having a cable connecting it all the way back to the controller.

To make the daisy chaining work, each whip will have it's own mini control box sitting at its feet.

* The mini control box will have a Teensy 4.0 to receive commands from the main controller and display things on the LEDs.
* Power will be daisy-chained too. To minimize voltage drop, the power will be transmitted at 24 volts. Each control box will have a tiny 24 volt -> 12 volt DC transformer to power the LEDs and an even smaller 12 volt -> 5 volt buck converter to power it's MCU.
* The data will be sent from the controller over a single RS-485 bus which can be daisy-chained from one mini control box to the next.

Right now I am working on the code in **Whips** which runs on a Teensy 4.1 in the main control box, and on all the Teensy 4.0s in the mini control boxes.

In the main control box it runs in "DOM" mode (#define DOM) and sends commands to the mini control boxes. The mini control boxes run in "SUB" mode (#define SUB) where they receive these commands and are responsible for the LED display of a single whip.