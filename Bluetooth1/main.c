/*
 * Bluetooth1.c
 *
 * Created: 27.12.2016 13:44:30
 * Author : Kim
 */ 


#define F_CPU 8000000
#define BAUD 9600

#include <avr/io.h>
#include <util/setbaud.h>




int main(void)
{
	char Line[40];
	USART_Init();
	
	
	unsigned char Test = 'c';
	char Test_Array[] = {'T','E','S','T'};
	
    /* Replace with your application code */
    while (1) 
    {
		
		USART_Transmit_Char(Test);
		USART_Transmit_String(Test_Array);
		
		
		USART_Receive_String( Line, sizeof( Line ) );
		
		
    }
	
	
}



void USART_Init() 
{
	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;
	
	UCSRB |= (1<<TXEN)|(1<<RXEN);
	UCSRC |= (1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
	
	
}
	
	
void USART_Transmit_Char( unsigned char data )
{
	/* Wait for empty transmit buffer */
	while ( !( UCSRA & (1<<UDRE)) )
	;
	/* Put data into buffer, sends the data */
	UDR = data;
}
	
void USART_Transmit_String (char s[])
{
	int i =0;
	
	while (s[i] != 0x00)
	{
		USART_Transmit_Char(s[i]);
		i++;
	}
}

unsigned char USART_Receive_Char( void )
{
	/* Wait for data to be received */
	if ( !(UCSRA & (1<<RXC)) )
	;
	/* Get and return received data from buffer */
	return UDR;
}

void USART_Receive_String( char* Buffer, uint8_t MaxLen )
{
	uint8_t NextChar;
	uint8_t StringLen = 0;

	NextChar = USART_Receive_Char();         // Warte auf und empfange das nächste Zeichen

	// Sammle solange Zeichen, bis:
	// * entweder das String Ende Zeichen kam
	// * oder das aufnehmende Array voll ist
	while( NextChar != '\n' && StringLen < MaxLen - 1 ) {
		*Buffer++ = NextChar;
		StringLen++;
		NextChar = USART_Receive_Char();
	}

	// Noch ein '\0' anhängen um einen Standard
	// C-String daraus zu machen
	*Buffer = '\0';
}

