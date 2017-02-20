#include "adc.h"
#include "dac.h"
#include "fir_q31.h"
#include "filtro.h"
#include "manejador_coefs.h"



volatile uint32_t * DWT_CTRL = (uint32_t *)0xE0001000;
volatile uint32_t * DWT_CYCCNT = (uint32_t *)0xE0001004;
volatile uint16_t data;			//define variable global data uso del adc

fir_q31_t filtro1;			// define variable global estructura filtros
fir_q31_t filtro2;
fir_q31_t filtro3;
fir_q31_t filtro4;
fir_q31_t filtro5;			// define variable global estructura filtros
fir_q31_t filtro6;
fir_q31_t filtro7;
fir_q31_t filtro8;

extern int lowpass_taps1[];	//incializa variables externas coeficientes
extern int bandpass_taps2[];
extern int bandpass_taps3[];
extern int bandpass_taps4[];
extern int bandpass_taps5[];	
extern int bandpass_taps6[];
extern int bandpass_taps7[];
extern int bandpass_taps8[];

//fir_q31_t array_filters[8];


int history1[LOWPASS_TAP_NUM1];        //declara vector con coeficientes
int history2[BANDPASS_TAP_NUM2];
int history3[BANDPASS_TAP_NUM3];
int history4[BANDPASS_TAP_NUM4];
int history5[BANDPASS_TAP_NUM5];     
int history6[BANDPASS_TAP_NUM6];
int history7[BANDPASS_TAP_NUM7];
int history8[BANDPASS_TAP_NUM8];


char coefs[8];
extern char pos;


int y[500];

static void initHardware(void)
{
#if defined (__USE_LPCOPEN)
#if !defined(NO_BOARD_LIB)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
    // Set the LED to the state of "Off"
    Board_LED_Set(0, false);
#endif
#endif
   adcInit();
   dacInit();
}

int main(void)
{

	inicializar_coefs(&coefs);
	int i=0, j=0, offset;
	

	fir_q31_init(&filtro1, history1, lowpass_taps1, LOWPASS_TAP_NUM1);   //llamado a funcion de inicio con cada filtro
	fir_q31_init(&filtro2, history2, bandpass_taps2, BANDPASS_TAP_NUM2); // los parametros son un puntero a la estructura de filtro f
	fir_q31_init(&filtro3, history3, bandpass_taps3, BANDPASS_TAP_NUM3);  // una historia con el para el valor leido
	fir_q31_init(&filtro4, history4, bandpass_taps4, BANDPASS_TAP_NUM4);  // el arreglo con los coeficientes
	fir_q31_init(&filtro5, history5, bandpass_taps5, BANDPASS_TAP_NUM5);     // y la cantidad de coeficientes
	fir_q31_init(&filtro6, history6, bandpass_taps6, BANDPASS_TAP_NUM6); 
	fir_q31_init(&filtro7, history7, bandpass_taps7, BANDPASS_TAP_NUM7); 
	fir_q31_init(&filtro8, history8, bandpass_taps8, BANDPASS_TAP_NUM8); 

	offset=400;

	initHardware(); //inicializa adc dac

	*DWT_CTRL |= 1;



	for(j = 0; j < LOWPASS_TAP_NUM1; ++j)  //actualiza coeficientes a 31 bits
	{

 	lowpass_taps1[j] = (int) lowpass_taps1[j] / 2;	
  	bandpass_taps2[j] = (int) bandpass_taps2[j] / 2;
  	bandpass_taps3[j] = (int) bandpass_taps3[j] / 2;
  	bandpass_taps4[j] = (int) bandpass_taps4[j] / 2;
   	bandpass_taps5[j] = (int) bandpass_taps5[j] / 2;
   	bandpass_taps6[j] = (int) bandpass_taps6[j] / 2;
   	bandpass_taps7[j] = (int) bandpass_taps7[j] / 2;
   	bandpass_taps8[j] = (int) bandpass_taps8[j] / 2;
	};




	


	while(1)
	{
		if(adcFlag)
		{
			adcFlag=0;
			*DWT_CYCCNT=0; /* para medir tiempos de ejecucion */
			actualizar_coefs(coefs); 

			
			
			
//			y[i] = calcular_respuesta(&filtro1, coefs,1) +500;   //llamado a la funcion de inicializacion del filtro 
//			y[i] += calcular_respuesta(&filtro2, coefs,2) +500;	
//			y[i] += calcular_respuesta(&filtro3, coefs,3);
//			y[i] += calcular_respuesta(&filtro4, coefs,4);
//			y[i] += calcular_respuesta(&filtro5, coefs,5);
//			y[i] += calcular_respuesta(&filtro6, coefs,6);
//			y[i] += calcular_respuesta(&filtro7, coefs,7);
//			y[i] += calcular_respuesta(&filtro8, coefs,8);


			y[i] = (int) (coefs[0] * fir_q31_get(&filtro1))  / 10;
			y[i] += offset;
			y[i] += (int) (coefs[1] * fir_q31_get(&filtro2))  / 10;
			y[i] += (int) (coefs[2] * fir_q31_get(&filtro3))  / 10;			
			y[i] += (int) (coefs[3] * fir_q31_get(&filtro4))  / 10;	
			y[i] += (int) (coefs[4] * fir_q31_get(&filtro5))  / 10;			
			y[i] += (int) (coefs[5] * fir_q31_get(&filtro6))  / 10;
			y[i] += (int) (coefs[6] * fir_q31_get(&filtro7))  / 10;
			y[i] += (int) (coefs[7] * fir_q31_get(&filtro8))  / 10;

			y[i] = y[i] * 2;

			if(y[i]>0x3FF) y[i] = 0x3FF;   // verifica que el valor no supere el umbral
			else if(y[i]<0) y[i] = 0;

			dacWrite(y[i]);		//escribe resultado en el dac	

			i++;
			if(i==500)
				i=0;
		}
	}
}
