# emac_ivad_board_init
Arduino code to initialize eMac IVAD board via i2c.

When starting the eMac, the logic board or mother board initializes the IVAD
board via an i2c interface so that the CRT can be used. This arduino sketch 
sends the commands to the IVAD board in order to initialize it. The logic board
can now be removed and replaced with almost anything that can output a VGA signal. 

These commands were captured with a logic analyzer during the booting process and 
implemented here.

This program sends the init code 5 seconds after being powered and also monitors
pin 3 for button presses.

All code to control external relays was removed.

You can get or add more info at the following wiki page.
https://en.wikibooks.org/w/index.php?title=How_to_modify_an_eMac_to_use_as_an_external_monitor

NOTE: In addition to the data connection outlined in README.txt, after supplying 120v AC to the eMac, 
the ivad board needs 5v applied to pins 4 and 10 of the eMac video connector in order to turn turn it on in preparation for the init sequence to be sent.

I used the 5v pin on the arduino, and when I plug in the arduino, the delay 
in the ardunio sketch is sufficient time for the ivad board to be ready for the init.