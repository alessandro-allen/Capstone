/****************
 PIC16F87XA Source File
 Capstone Fall 2014
 Created by Harrison Donahue 12.1.14
 This source file will contain all the functions necessary for
 handling the inputs and outputs from the Bluetooth module via UART and relaying
 the commands to the respective ports for the IR circuit and X10 bridge
 ******************/

#include <pic16f877.h>
#include <xc.h>
#include <stdlib.h>
#include <fproto.h>


/****************************
 MAIN FUNCTION
 Search for commands from UART and configure UART
 *****************************/
void main(){

    //initialize global variables
    unsigned int typeCMD = 0;      //initialize variable for storing command type
    unsigned int userCMD = 0;      //initialize variable for storing command from Bluetooth

    //Configure PIC
    TRISC = 0xF6;           //set portC to all inputs except unused
    TRISD = 0x00;           //set PortD to all outputs

    //configure osc
    INTCON = 0b11010000;    //configure interrupts
    PIE1 = 0b00110000;      //configure peripheral interrupts for UART

    //Configure TX control register
    TXSTAbits.TX9 = 0;      //8 bit transmission enabled
    TXSTAbits.TXEN = 1;     //Transmit enabled
    TXSTAbits.SYNC = 0;     //Asynchronous mode
    TXSTAbits.BRGH = 0;     //Low speed mode

    //Configure RX control register
    RCSTAbits.SPEN = 1;     //Serial port enabled (RX/TX pins configured)
    RCSTAbits.RX9 = 0;      //8 bit recepetion enabled
    RCSTAbits.CREN = 1;     //Enables continuous receive mode for Asynchronous
    RCSTAbits.FERR = 0;
    RCSTAbits.OERR = 0;

    /***********************
     Configure UART
     function sets the special GPIO pins on the Bluetooth Module
     ***********************/
    configureUART();

    //Loop and look for interrupt to recieve command
    while(1){
        if(RXint){          //check for interrupt flag on RX high
            userCMD = getCMD();
            if(!RCREG)    //RCREG is clear, IR command read
                flashIR(userCMD);
            if(RCREG)     //RCREG is set, X10 command read
                sendX10(userCMD);
        }
    }

}

/****************************
 CONFIGURE UART FUNCTION
 configures special GPIO for Bluetooth Module
 *****************************/
void configureUART(void){
PORTCbits.RC5 = LOW;        //GPIO7 - set Baud rate default 115k
PORTCbits.RC4 = LOW;        //GPIO6 - Default Bluetooth Slave mode
PORTCbits.RC3 = LOW;        //GPIO4 - Factory Reset Disabled
PORTCbits.RC2 = HI;         //GPIO3 - Auto Discovery enabled
exit(0);
}

/***************************
 GET CMD FUNCTION
 gets ASCII command type and user command value from bluetooth module
 ***************************/
int getCMD(void){
    //get CMD type
    int CMD = RCREG;
    TXREG = ACK;//ASCII ACK CMD for Bluetooth
    while(!TXIF);
    return CMD;
}

/***************************
 FLASH IR FUNCTION
 sends user command to IR circuit
 ***************************/
void flashIR(int CMD){
    int i = 0;          //for loop counter
    unsigned char userCMD[8] = CMD; //store userCMD ASCII value in bit string
    for(i=0; i<8; i++){             //send bits to IR circuit
        PORTDbits.RD4 = userCMD[i];
        //delay for required nanoseconds
    }
}

/***************************
 SEND X10 FUNCTION
 sends user command to X10 circuit
 ***************************/
void sendX10(int CMD){
    //TBD
}