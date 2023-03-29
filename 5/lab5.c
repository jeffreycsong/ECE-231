/*
lab5.c - ECE231 Lab 5 Assignment
Ultrasound Range Measurement with Visual Indications

Date        Author          Revision
5/5/2022    Jeffrey Song    Initial Code
*/

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>     // defines strlen() function
#include <stdlib.h>     // defines itoa() function

#include "i2c.h"        // library from github
#include "SSD1306.h"    // library from github
#include "uart.h"       // uart library, uneeded

#define TRIG PB1    // PB1 = pin 15
#define ECHO PB0    // PB0 = pin 14
#define RPC 1.098   // range per clock

void timer0_init(void);


int main(void){
    unsigned char rising_ec, falling_ec, echo_wc;

    float target_range;
    
    DDRB = 1<<TRIG;         // TRIG is the output pin
    PORTB &= ~(1<<TRIG);    // set the TRIG pin low
    OLED_Init();            // initialize the OLED display
    timer0_init();          // initialize timer0

    while(1){
        TCNT0 = 0;          // load counter with 0
        PORTB |= 1<<TRIG;   // put a 10 usec 
        _delay_us(10);      // pulse on the
        PORTB &= ~(1<<TRIG);// TRIG pin

        // wait till ECHO pulse goes high
        while ((PINB & (1<<ECHO)) == 0);
        rising_ec = TCNT0;      // note the time
        // now wait till the ECHO pulse goes low
        while (!(PINB & (1<<ECHO)) == 0);
        falling_ec = TCNT0;

        if (falling_ec > rising_ec){
            // compute target range and send it to the OLED
            echo_wc = falling_ec - rising_ec;
            target_range = echo_wc * RPC;

            // have line 0 be my name
            OLED_GoToLine(0);
            OLED_DisplayString("Jeffrey Song");

            char buffer[10];

            // sends range in cm to OLED
            dtostrf(target_range, 3, 0, buffer);
            OLED_GoToLine(2);
            OLED_DisplayString("Range in cm");
            OLED_GoToLine(3);
            OLED_DisplayString(buffer);
            OLED_DisplayString(" cm");

            // sends range in in to OLED
            dtostrf(target_range/2.54, 3, 0, buffer);
            OLED_GoToLine(5);
            OLED_DisplayString("Range in in");
            OLED_GoToLine(6);
            OLED_DisplayString(buffer);
            OLED_DisplayString(" in");

            _delay_ms(100);

        }

        _delay_ms(500); // delay then go again

    }

}


void timer0_init(){
    TCCR0A = 0; // timer 1 normal mode (count up)
    TCCR0B = 5; // divide clock by 1024
    TCNT0 = 0;  // start the timer at 0
}