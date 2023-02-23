# Part 3: Button Based Delay
The point of this section is to create a program that allows a user to hold down a button and times how long they hold it for. The program then blinks an led at the rate they held it down for.

# Blinking the led
The first part of this program is to just blink an led. The timer uses interrupts and when the timer counts to a predetermined number it resets and blinks the led.

# Getting the user input
The next part of this program is to see when the user is holding the button down. When the user presses a button the program changes the edge transition to catch the release of the button.
Then, the timer is reset and is set to up mode and begins counting again. When the button is released, the timer is stopped and the current time is read for the register. 
With the time read from the register, it is set as the new offset and the led now blinks at that rate.

# Combating timer oveflow
One problem of the timer is that when counting in up mode it will overflow and reset to 0, which if not hndled, will throw off your time.
The way I chose to counter this was to use a /4 clock divider. This will slow down my clock enough that a user can hold down the button for awhile and it won't overflow.