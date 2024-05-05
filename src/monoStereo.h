#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct tCADEIA {
 unsigned char byte;
 struct tCADEIA *prox;
} tCADEIA;

typedef struct tWAV {
    unsigned int numCanal;
    unsigned int taxaAmostragem;
    unsigned int bitDepth;
    unsigned int tamanhoData;
    tCADEIA *dados;
    struct tWAV *proxWAV;  // Ponteiro para o próximo WAV na lista
} tWAV;

int setMono(tWAV* wav, float *canalMono) {
	if (!wav) {
  		printf("Arquivo WAV inexistente!");
  		return 0;
  	}
	tCADEIA *cab = 0;
	unsigned int qtdAmostras = (wav->tamanhoData/(wav->bitDepth/8))/wav->numCanal;
		
	cab = malloc(sizeof(tCADEIA));
	if (!cab) {
		printf("Deu problema na alocacao dinamica!");
  		return 0;
  	}
  	else {
  		wav->dados = cab;
				
		//variÃ¡veis auxiliares:
		long long amplitudeMax = pow(2, wav->bitDepth - 1) - 1;
		int amostraIntMono = 0;
		int i = 0;
		
		//Reconstruindo para o modelo de amostras inteiras:
		for (i = 0; i < qtdAmostras; i++) {
			amostraIntMono = canalMono[i] * amplitudeMax;
			if (wav->bitDepth == 16) {
				cab->byte = amostraIntMono;
				cab->prox = malloc(sizeof(tCADEIA));
				cab = cab->prox;
				cab->byte = (amostraIntMono >> 8);
				cab->prox = malloc(sizeof(tCADEIA)); 
				cab = cab->prox;
			}
			else if (wav->bitDepth == 24) {
				cab->byte = amostraIntMono;
				cab->prox = malloc(sizeof(tCADEIA));
				cab = cab->prox;
				cab->byte = (amostraIntMono >> 8);
				cab->prox = malloc(sizeof(tCADEIA));
				cab = cab->prox;
				cab->byte = (amostraIntMono >> 16);
				cab->prox = malloc(sizeof(tCADEIA)); 
				cab = cab->prox;
			}
		}
		cab = 0;
		return i;
	}
}	

int setStereo(tWAV* wav, float *canalL, float *canalR) {
	if (!wav) {
  		printf("Arquivo WAV inexistente!");
  		return 0;
  	}
	tCADEIA *cab = 0;
	unsigned int qtdAmostras = (wav->tamanhoData/(wav->bitDepth/8))/wav->numCanal;
		
	cab = malloc(sizeof(tCADEIA));
	if (!cab) {
		printf("Deu problema na alocacao dinamica!");
  		return 0;
  	}
  	else {
  		wav->dados = cab;
				
		//variÃƒÂ¡veis auxiliares:
		long long amplitudeMax = pow(2, wav->bitDepth - 1) - 1;
		int amostraIntL = 0, amostraIntR = 0;
		int i = 0;
		
		//Reconstruindo para o modelo de amostras inteiras:
		for (i = 0; i < qtdAmostras; i++) {
			amostraIntL = canalL[i] * amplitudeMax;
			amostraIntR = canalR[i] * amplitudeMax;
			if (wav->bitDepth == 16) {
				//Canal L:
				cab->byte = amostraIntL;
				cab->prox = malloc(sizeof(tCADEIA));
				cab = cab->prox;
				cab->byte = (amostraIntL >> 8);
				cab->prox = malloc(sizeof(tCADEIA)); 
				cab = cab->prox;
				//Canal R:
				cab->byte = amostraIntR;
				cab->prox = malloc(sizeof(tCADEIA));
				cab = cab->prox;
				cab->byte = (amostraIntR >> 8);
				cab->prox = malloc(sizeof(tCADEIA)); 
				cab = cab->prox;
			}
			else if (wav->bitDepth == 24) {
				//Canal L:
				cab->byte = amostraIntL;
				cab->prox = malloc(sizeof(tCADEIA));
				cab = cab->prox;
				cab->byte = (amostraIntL >> 8);
				cab->prox = malloc(sizeof(tCADEIA));
				cab = cab->prox;
				cab->byte = (amostraIntL >> 16);
				cab->prox = malloc(sizeof(tCADEIA)); 
				cab = cab->prox;
				//Canal R:
				cab->byte = amostraIntR;
				cab->prox = malloc(sizeof(tCADEIA));
				cab = cab->prox;
				cab->byte = (amostraIntR >> 8);
				cab->prox = malloc(sizeof(tCADEIA));
				cab = cab->prox;
				cab->byte = (amostraIntR >> 16);
				cab->prox = malloc(sizeof(tCADEIA)); 
				cab = cab->prox;
			}
		}
		cab = 0;
		return i;
	}
}