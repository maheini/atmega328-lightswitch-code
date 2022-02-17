#define F_CPU 1000000
#include<util/delay.h>
#include<avr/io.h>

int main(void)
{
  # setting up 
	DDRC |= (1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4);
	
  # set pin PC5 as input
  DDRC &= ~(1<<5);
  
  # set pullup resistor for pin PC5
	PORTC |= (1<<5);
  
  # set initial position
	int8_t position=1;
  
  #start switch
	while(1)
	{
    # if pin PC5 isn't pressed wait
		if (!(PINC & (1<<5)))
		{
      # check current switch position
			switch(position)
			{
				case 1: PORTC |= (1<<0);
				break;
				case 2: PORTC |= ((1<<1) | (1<<2));
				break;
				case 3: PORTC |= ((1<<3) | (1<<4));
				break;
				case 4: PORTC &= ~((1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4));
				position=0; # reset position
				break;
				default: break;
			}
      # debounce button
			loop_until_bit_is_set(PINC, PC5);
			_delay_ms(230);
			
      # increase position
      position++;
		}
	}
}
