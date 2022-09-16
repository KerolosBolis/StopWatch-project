/*
 * Mini_Project2.c
 *
 *  Created on: Sep 18, 2021
 *      Author: DELL
 */
#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
unsigned char seconds=0;
unsigned char minutes=0;
unsigned char hours=0;
ISR(INT0_vect){
	seconds=0;
	minutes=0;
	hours=0;
}
ISR(INT1_vect){
	TIMSK&=~(1<<OCIE1A);
}
ISR(INT2_vect){
	TIMSK|=(1<<OCIE1A);
}
ISR(TIMER1_COMPA_vect){
	if(seconds==59){
		seconds=0;
		if(minutes==59){
	        minutes=0;
			if(hours==24){
				hours=0;
			}
			else{
				hours++;
			}
		}
		else{
			minutes++;
		}
	}
	else{
		seconds++;
	}

}
void INT2_Init(void){
	MCUCSR&=~(1<<ISC2);
	DDRB&=~(1<<2);
	PORTB|=(1<<2);
	GICR|=(1<<INT2);
}
void INT1_Init(void){
	MCUCR=(1<<ISC10)|(1<<ISC11);
	DDRD&=~(1<<3);
	GICR|=(1<<INT1);
}
void INT0_Init(void){
	MCUCR=(1<<ISC01);
	DDRD&=~(1<<2);
	PORTD|=(1<<2);
	GICR|=(1<<INT0);
}
void TIMER1_Init(void){
	TCCR1A=(1<<FOC1A);
	TIMSK=(1<<OCIE1A);
	TCNT1=0 ;
	OCR1A=977;
	TCCR1B=(1<<WGM12)|(1<<CS12)|(1<<CS10);;
}
int main(void){
	DDRC|=0x0F;
	PORTC&=0xF0;

	INT0_Init();
	INT1_Init();
	INT2_Init();

	DDRA|=0x3F;
	PORTA|=0x3F;
	TIMER1_Init();
	SREG|=(1<<7);
	//unsigned char num=0;
	while(1){

		PORTA=(1<<0);
		PORTC=seconds%10;
		_delay_ms(3);
		PORTA=(1<<1);
		PORTC=seconds/10;
		_delay_ms(3);
		PORTA=(1<<2);
		PORTC=minutes%10;
		_delay_ms(3);
		PORTA=(1<<3);
		PORTC=minutes/10;
		_delay_ms(3);
		PORTA=(1<<4);
		PORTC=hours%10;
		_delay_ms(3);
		PORTA=(1<<5);
		PORTC=hours/10;
		_delay_ms(3);
	}
}


