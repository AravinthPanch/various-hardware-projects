#include<reg51.h>           // special function register declarations
                            // for the intended 8051 derivative
#define LED P2            // Defining LED pin

void Delay(void);           // Function prototype declaration

void main (void)
{
    while(1)                // infinite loop
    {
        LED=0x00;            // LED ON
        Delay();
        LED=0xff;            // LED OFF
        Delay();
    }
}

void Delay(void)
{
    int j;
    int i;
    for(i=0;i<10;i++);
    for(j=0;j<10000;j++);
}
