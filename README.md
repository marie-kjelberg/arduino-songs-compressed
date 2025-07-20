# arduino-songs-compressed
Arduino memory is wayyyy to small for most songs, so I made this.
![the new mona lisa](<the new mona lisa.png>)

## How to use:
This project is based on the great work done by Robson Couto & Co. in the [arduino songs](https://github.com/robsoncouto/arduino-songs) repo. Simply copy and paste one of their melodies and the song tempo into the ``input.txt`` and build the program using the makefile. Then you can run the file. Then an ``output.ino`` file should appear with your full file. Simply upload it to your arduino and you should be good to go! (NOTE: I changed the buzzers power line to the ``A0`` pin, but this can be changed in the code).

This program should approxiamtly half the used space for storing the song itself. I also made it use the flash memory instead of using it in the SRAM. This should allow you to do multiple things with your arduino at the same time (such as displaying an OLED image).

## Quirks (if some unexplainable bug happens, see here first): 
- when the program removes block comments such as ``/* ... */``, it allows parsing of expressions such as ``NO/* ... */TE_A4`` into ``NOTE_A4``. This works, but I don't really see a use for it. Having said that, it will probably create some bug down the road. I don't know whether I should fix it. 
- the program supports sharps, but not flats. You can add this if you want, but I have yet to bother. If you need a flat, use the sharp version of that note. 
- the program has slight precision issues. The difference is usally only ±1Hz due to rounding ¯\_(ツ)_/¯

## Would be nice to have: 
- reprogram this to simply take the original file as input and turn out the compressed file. 
- maybe turn this into a command line tool~ 