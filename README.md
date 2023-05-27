# Demonic solar-powered cats

A (very simple) project to convert solar-powered, cat-shaped garden lamps to omniously blinking cat demons.

![Cats](doc/supernova.png)

It uses ATtiny13 MCU running at 600 kHz (4.8 MHz clock divided by 8 by CKDIV8). I wanted to use a 128 kHz clock, but it was minimally too slow to obtain needed number of PWM levels and avoid flickering.

It runs when there's no light, and stops when the light is present (it also slows down the timer then, to save power). Light detection is done indirectly, by detecting the signal from one of two QX5252F chips (this signal is output by the on-chip boost converter to charge the external inductor, but in this project the inductor has been removed). Detection is done using ADC, because the signal level is too low (around 1 V, depending on the SoC of the batteries) to be reliably detected by the digital I/O.

This circuit works down to 2 V and draws around 260 µA when idle.

Documentation contains schematic in Eagle format and PCB in AutoTrax format.

More about this project can be found on my YouTube channel: https://youtu.be/gxKObwk-78I

<a href="http://www.youtube.com/watch?feature=player_embedded&v=gxKObwk-78I" target="_blank"><img src="http://img.youtube.com/vi/gxKObwk-78I/0.jpg" alt="Video" width="240" height="180" border="10" /></a>
