# STM32F4 character LCD interface demo

This is a small project to interface the stm32f4 with a character LCD.

It is not particularly fancy in any way, but it should get the job done in most 
cases.

I should note that this project uses very very stupid delays to achieve the slow
timing required by the LCD, these delays are a HUGE waste of cycles, and make 
your 168MHz cpu act like a few KHz, I will later work on a version of this 
library using timers, which should be far more efficient, but until that is 
completed this does get the job done.

The work in this project will likely be used in creating a small computer type 
system, using this character LCD code for display.

If you're interested in using the same display that I have used for testing with
this, it can be found [here](http://www.seeedstudio.com/depot/lcd-204-characters-white-back-light-p-350.html), 
it's not the cheapest, but it does look nice and it's easy to find plenty of 
documenation on it from the site.

This project is licensed under the MIT License, please see the LICENSE file for 
more info! :)

# ENJOY!
