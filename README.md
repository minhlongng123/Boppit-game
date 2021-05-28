# Boppit-game
GPIO of STM32F4 DISCOVERY BOARD learning

Many of you will have played the Boppit game before. It is a simple game that uses a series of
LEDs and lights them in turn. When the centre LED is lit pressing a button is a “hit” and causes the
delay between the LEDs lighting to decrease. It can also generate a winning tone. When the button
is pressed when either LED adjacent to the centre LED is lit this is a good try, and the game waits
until the button is released and then continues. If any other button is pressed this is a “miss” and the
game restarts, and a losing tone can be generated.
