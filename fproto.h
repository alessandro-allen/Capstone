/* 
 * File:   fproto.h
 * Author: harrisondonahue
 * Contains function prototypes and variable definitions
 * Created on 11.30.14
 */

#ifndef FPROTO_H
#define	FPROTO_H

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* FPROTO_H */

//macros
#define IR PORTDbits.RD7
#define HI 1;
#define LOW 0;
#define TXint PIR1bits.TXIF //interrupt flag bit for TX
#define RXint PIR1bits.RCIF //interrupt flag bit for RX
#define TX PORTCbits.RC6    //TX bit
#define RX PORTCbits.RC7    //RX bit

//function prototypes
void configureUART(void);
int getCMD(void);
void flashIR(int);
void sendX10(int);


