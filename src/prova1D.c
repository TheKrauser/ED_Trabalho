#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "monoStereo.h"


// Estrutura para representar a lista de WAVs
typedef struct ListaWAV {
    tWAV *inicio;
    tWAV *fim;
} ListaWAV;

// Função para adicionar um novo WAV à lista
void adicionarWAV(ListaWAV *lista, tWAV *novoWAV) {
    if (lista->inicio == NULL) {
        lista->inicio = novoWAV;
        lista->fim = novoWAV;
    } else {
        lista->fim->proxWAV = novoWAV;
        lista->fim = novoWAV;
    }
    novoWAV->proxWAV = NULL;
}

// Função para liberar a memória ocupada pela lista de WAVs
void liberarListaWAV(ListaWAV *lista) {
    tWAV *atual = lista->inicio;
    while (atual != NULL) {
        tWAV *proximo = atual->proxWAV;
        free(atual->dados);  // Libera os dados do WAV
        free(atual);         // Libera o próprio WAV
        atual = proximo;
    }
    lista->inicio = NULL;
    lista->fim = NULL;
}

// Função principal para testar
int main() {
    // Criando uma lista de WAVs vazia
    ListaWAV lista;
    lista.inicio = NULL;
    lista.fim = NULL;

    // Criando e adicionando alguns WAVs à lista
    for (int i = 0; i < 3; i++) {
        
        tWAV *novoWAV = malloc(sizeof(tWAV));
        if (!novoWAV) {
            fprintf(stderr, "Erro ao alocar memória para o novo WAV.\n");
            liberarListaWAV(&lista);  // Libera a lista antes de sair
            return 1;  // Sinaliza um erro

        }

        // Preenchendo novoWAV com dados fictícios
        novoWAV->numCanal = 2;
        novoWAV->taxaAmostragem = 44100;
        novoWAV->bitDepth = 16;
        novoWAV->tamanhoData = 176400;
        novoWAV->dados = 88200;  
        novoWAV->proxWAV = NULL;

         novoWAV->dados = malloc(novoWAV->tamanhoData * sizeof(tCADEIA));
        if (!novoWAV->dados) {
            fprintf(stderr, "Erro ao alocar memória para os dados do WAV.\n");
            free(novoWAV);
            liberarListaWAV(&lista);
            return 1;
        }

        // Preenchendo os dados de áudio sintéticos (exemplo: tom de 440Hz)
        double frequencia = 440.0;
        for (int j = 0; j < novoWAV->tamanhoData; j++) {
            double tempo = j / (double)novoWAV->taxaAmostragem;
            double amplitude = 0.5 * sin(2.0 * M_PI * frequencia * tempo);
            short amostra = (short)(amplitude * 32767.0);
            novoWAV->dados[j].byte = amostra & 0xFF;
            novoWAV->dados[j].prox = NULL;
        }

        // Adiciona o novo WAV à lista
        adicionarWAV(&lista, novoWAV);

        printf("\n\nArquivo WAV adicionado com sucesso!\n\n");
        
        // Criando dados de entrada fictícios para testar setMono e setStereo
         CanalMono canalMono;  // Exemplo: mono com 44100 amostras
        float canalL[44100], canalR[44100];  // Exemplo: stereo com 44100 amostras para cada canal

        

        // Chamando setMono para preencher os dados de um canal mono no WAV
        int amostrasMono = setMono(novoWAV, &canalMono);
        if (amostrasMono > 0) {
            printf("Canal mono configurado com sucesso: %d amostras\n", amostrasMono);
        } else {
            printf("Erro ao configurar canal mono.\n");
        }

        // Chamando setStereo para preencher os dados de dois canais stereo no WAV
        int amostrasStereo = setStereo(novoWAV, canalL, canalR);
        if (amostrasStereo > 0) {
            printf("Canais stereo configurados com sucesso: %d amostras\n", amostrasStereo);
        } else {
            printf("Erro ao configurar canais stereo.\n");
        }
        
        
    }

    // Liberando a memória ocupada pela lista antes de sair
    liberarListaWAV(&lista);

    return 0;
}
