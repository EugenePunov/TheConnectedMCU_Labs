/* 
 * File: User Functions
 * Author: Eugene Punov 
 * Brief: main functionality of prgramm
 */

/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/

#ifdef __XC32
#include <xc.h>          /* Defines special function registers, CP0 regs  */
#endif

#include <stdint.h>          /* For uint32_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */
#include "user.h"            /* variables/params used by user.c               */
#include <sys/attribs.h>
#include "UART.h"

/******************************************************************************/
/* User Functions                                                             */

/******************************************************************************/

/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/



/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

/*!
 initialize input output
\param[out] none
\param[in] none
\return none
*/
void init_gpio(void) {
    /* Setup functionality and port direction */
    // LED output
    // Disable analog mode
    ANSELBbits.ANSB13 = 1;
    // LED outputs
    // Disable analog mode if present
    ANSELG &= ~(1 << 15);
    ANSELB &= ~(1 << 11);
    // Set direction to output 
    TRISG &= ~( (1 << 6) | (1 << 15) );
    TRISB &= ~( (1 << 11) );
    TRISD &= ~( (1 << 4) );
    // Turn off LEDs for initialization
    LD1_PORT_BIT = LD2_PORT_BIT = LD3_PORT_BIT = LD4_PORT_BIT = 0;

    // BTN1 and BTN2 inputs
    // Disable analog mode
    ANSELA &= ~(1 << 5);
    // Set directions to input
    TRISA |= (1 << 5);
    TRISA |= (1 << 4);

     
    TRISDCLR = 1<<11;
}
/*!
 begins program
\param[out] none
\param[in] none
\return none
*/
void init_app(void) {
    // Initialize peripherals
    init_gpio();
    uart4_init();
}
/*!
 all functional of programm
\param[out] none
\param[in] none
\return none
*/
void turn_on_off_leds() {
    while(1){
    char c = ' ';        //variable that cintains chars
    c = uart4_getc();   //read one symbol from UART
    uart4_putc(c); // echo back character
    
    switch (c) {        //Choose number of LED
        case '1':
            uart4_puts("\r\nYou choose first led!\r\n");
            c = ' ';     //clear c
            while (' ' == c){    //wait for next entering
                c = uart4_getc();   //read one symbol from UART    
                if ('0' == c){      //if 0 turn off led1
                    LD1_PORT_BIT = 0;
                    uart4_puts("\r\nLED tuned off!\r\n");  //massage for user
                    break;
                } else if ('1' == c) {//if 1 turn on led1
                    LD1_PORT_BIT = 1;
                    uart4_puts("\r\nLED tuned on!\r\n");//massage for user
                    break;
                } else {
                    c = ' ';
                    uart4_puts("\r\nInvalid command!\r\n");//erorr
                }
            }
            break;
        case '2':
            uart4_puts("\r\nYou choose second led!\r\n");
            c = ' ';     //clear c
            while (' ' == c){
                c = uart4_getc();
                if ('0' == c){
                    LD2_PORT_BIT = 0;
                    uart4_puts("\r\nLED tuned off!\r\n");
                    break;
                } else if ('1' == c) {
                    LD2_PORT_BIT = 1;
                    uart4_puts("\r\nLED tuned on!\r\n");
                    break;
                } else {
                    c = ' ';
                    uart4_puts("\r\nInvalid command!\r\n");
                }
            }
            break;
        case '3':
            uart4_puts("\r\nYou choose third led!\r\n");
            c = ' ';     //clear c
            while (' ' == c){
                c = uart4_getc();
                if ('0' == c){
                    LD3_PORT_BIT = 0;
                    uart4_puts("\r\nLED tuned off!\r\n");
                    break;
                } else if ('1' == c) {
                    LD3_PORT_BIT = 1;
                    uart4_puts("\r\nLED tuned on!\r\n");
                    break;
                } else {
                    c = ' ';
                    uart4_puts("\r\nInvalid command!\r\n");
                }
            }
            break;
        case '4':
            uart4_puts("\r\nYou choose fourth led!\r\n");
            c = ' ';     //clear c
            while (' ' == c){
                c = uart4_getc();
                if ('0' == c){
                    LD4_PORT_BIT = 0;
                    uart4_puts("\r\nLED tuned off!\r\n");
                    break;
                } else if ('1' == c) {
                    LD4_PORT_BIT = 1;
                    uart4_puts("\r\nLED tuned on!\r\n");
                    break;
                } else {
                    c = ' ';
                    uart4_puts("\r\nInvalid command!\r\n");
                }
            }
            break;
        default:
            uart4_puts("\r\nInvalid number of LED!\r\n");//erorr
            break;
    }
    }
}

