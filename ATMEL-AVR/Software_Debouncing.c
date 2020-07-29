/*SWITCH - Software Debouncing!
Debouncing is an effect where the trigger interrupt or simply a switch toggle bounces back.
This usually happens when microcontroller considers one click as more than one.
Due to this, a kind of interference occurs which makes multiple attenuated toggling just with one being physically done.

Here is a novel method to prevent this effect with confidence level technique. 
PORTC is chosen here with
PINC0 --> LED1,
PINC1 --> SWITCH,
PINC2 --> LED2.
*/

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main(void)
{       
	DDRC |= 1 << PINC0; 
	PORTC ^=1 << PINC0;
	DDRC |= 1<< PINC2;
	DDRC &= ~(1 <<PINC1);
	PORTC |= 1<< PINC1;

	int pressed = 0;
	int pressed_confidence_level = 0;
	int released_confidence_level = 0;

	while (1)
	{
		if (bit_is_clear(PINC,1))
		{
			pressed_confidence_level ++;
			if(pressed_confidence_level >500) // pressed_confidence_level > "500" is subjected to change based on trial and errors.
			{
				if (pressed==0)
				{
					PORTC ^= 1 << PINC0;
					PORTC ^= 1 << PINC2;
					pressed = 1;
				}
				pressed_confidence_level = 0;
			}
		}
		else
		{
			released_confidence_level ++;
			if (released_confidence_level >500)
			{
				pressed = 0;
				released_confidence_level = 0;
			}
		}
	}
}
