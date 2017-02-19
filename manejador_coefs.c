//#include "hc06_driver.h"
#include "manejador_coefs.h"
#include "fir_q31.h"

char pos;

void inicializar_coefs(char * coefs) //funcion de inicializacion coeficientes
{
	int i;
	pos=0;
	for(i = 0; i < 8; ++i)  //inicializa coefs sin atenuacion
	{
	   coefs[i] =  10;	
	};
}

void actualizar_coefs( char * coefs)  //se carga un valor en el filtro
{
/*
	uint8_t receivedByte;
	receivedByte = HC06_ReadByte();

	if ( receivedByte = "flecha derecha") {
	  if ( pos == 7)
		pos = 0;   
	   else  
	   pos++; 
	}

	if ( receivedByte = "flecha izquierda") {
	  if ( pos == 0)
		pos = 7;   
	   else  
	   pos--; 
	}

	if ( receivedByte = "flecha arriba") {
	  if ( pos !=  10)
		coefs[pos]++;   
	}

	if ( receivedByte = "flecha abajo") {
	  if ( pos !=  0)
		coefs[pos]--;   
	}

*/
}
/*
int calcular_respuesta(fir_q31_t * f, char * coefs, char i )	//funcion de filtrado de una señal
{
	int acc;
	acc = (int) coefs[i];
	acc = fir_q31_get(f) * acc;
	acc = (int) acc / 10;
	return acc;
}

*/

