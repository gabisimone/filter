#include "fir_q31.h"

void fir_q31_init(fir_q31_t * f, int * history, const int * kernel, int num_taps) //inicializa la estructura filtro
{
	int i;

	f->num_taps = num_taps;   //carga cantidad de coeficientes
	f->history = history;	  // carga historial
	f->kernel = kernel;	  //carga coeficientes

	for(i = 0; i < f->num_taps; ++i)
		f->history[i] = 0;	//inicializa el historial a 0
	f->last_index = 0;
}

void fir_q31_put(fir_q31_t * f, int input)
{
  f->history[f->last_index++] = input;  //actualiza el historial
  if(f->last_index == f->num_taps)
    f->last_index = 0;			// si llega al limite reinicia el buffer
}

int fir_q31_get(fir_q31_t * f)
{
	long long acc = 0;   	
	int index = f->last_index, i;
	for(i = 0; i < f->num_taps; ++i)  //realiza filtrado en tiempo por sumas sucesivas
	{
		index = index != 0 ? index-1 : f->num_taps-1;  	//actualiza index, si llega a 0 reinicia el buffer
		acc += (long long)f->history[index] * f->kernel[i];  //acumula valor en la salida
	};
	return acc >> 31;
}


