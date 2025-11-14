/**
 * @file detective_quest.c
 * @brief Simula a exploração de uma mansão (mapa em árvore binária) para o jogo Detective Quest.
 *
 * Implementa uma árvore binária de salas e permite a navegação interativa do jogador
 * até que um cômodo sem saída (nó-folha) seja alcançado.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definição da estrutura do nó da árvore (Sala/Cômodo)
typedef struct Sala {
    char nome[50];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

/**
 * @brief Cria, de forma dinâmica, uma sala com nome.
 *
 * Aloca memória para uma nova sala e inicializa seus campos.
 * * @param nomeSala O nome do cômodo a ser criado.
 * @return Um ponteiro para a nova sala criada.
 */
Sala* criarSala(const char* nomeSala) {
    // Alocação dinâmica de memória para a nova sala
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    
    // Verifica se a alocação foi bem-sucedida
    if (novaSala == NULL) {
        printf("Erro de alocação de memória!\n");
        exit(EXIT_FAILURE);
    }
    
    // Inicializa o nome da sala, copiando a string fornecida
    strncpy(novaSala->nome, nomeSala, 49);
    novaSala->nome[49] = '\0'; // Garante terminação da string
    
    // Inicializa os ponteiros dos caminhos (filhos) como NULL
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

/**
 * @brief Permite a navegação do jogador pela árvore.
 *
 * O jogador pode escolher 'e' para esquerda, 'd' para direita, ou 's' para sair.
 * A exploração termina ao alcançar um nó-folha.
 * * @param hall O ponteiro para a sala inicial (Hall de entrada).
 */
void explorarSalas(Sala* hall) {
    Sala* salaAtual = hall;
    char escolha;
    
    printf("\n--- Explorando a Mansão: Detective Quest ---\n");
    
    while (salaAtual != NULL) {
        printf("\nVocê está em: **%s**\n", salaAtual->nome);
        
        // Verifica se é um nó-folha (sala sem caminhos)
        if (salaAtual->esquerda == NULL && salaAtual->direita == NULL) {
            printf("\nEsta é uma sala sem caminhos adicionais. A exploração termina aqui.\n");
            break;
        }
        
        // Exibe opções de caminhos disponíveis
        printf("Escolha o próximo caminho:\n");
        if (salaAtual->esquerda != NULL) {
            printf("  [e] Esquerda (Ir para %s)\n", salaAtual->esquerda->nome);
        }
        if (salaAtual->direita != NULL) {
            printf("  [d] Direita (Ir para %s)\n", salaAtual->direita->nome);
        }
        printf("  [s] Sair da Mansão\n");
        printf("Sua escolha: ");
        
        // Captura a escolha do jogador
        scanf(" %c", &escolha);
        
        if (escolha == 's' || escolha == 'S') {
            printf("\nExploração encerrada. Você saiu da mansão.\n");
            break;
        } 
        else if (escolha == 'e' || escolha == 'E') {
            if (salaAtual->esquerda != NULL) {
                salaAtual = salaAtual->esquerda;
            } else {
                printf("Caminho não disponível. Tente novamente.\n");
            }
        } 
        else if (escolha == 'd' || escolha == 'D') {
            if (salaAtual->direita != NULL) {
                salaAtual = salaAtual->direita;
            } else {
                printf("Caminho não disponível. Tente novamente.\n");
            }
        } 
        else {
            printf("Opção inválida. Use 'e', 'd' ou 's'.\n");
        }
    }
}

/**
 * @brief Libera a memória alocada para toda a árvore.
 * * Função recursiva para evitar vazamento de memória.
 * * @param raiz O ponteiro para a raiz da subárvore a ser liberada.
 */
void liberarMapa(Sala* raiz) {
    if (raiz != NULL) {
        liberarMapa(raiz->esquerda);
        liberarMapa(raiz->direita);
        free(raiz);
    }
}

/**
 * @brief Monta o mapa inicial e dá início à exploração.
 * * @return 0 se o programa for executado com sucesso.
 */
int main() {
    // ------------------------------------------------------------------
    // 1. Montagem manual da Árvore Binária (Mapa da Mansão)
    // ------------------------------------------------------------------
    
    // Nível 0 (Raiz)
    Sala* hall = criarSala("Hall de Entrada");
    
    // Nível 1
    hall->esquerda = criarSala("Sala de Estar");
    hall->direita = criarSala("Cozinha");
    
    // Nível 2 - Esquerda
    hall->esquerda->esquerda = criarSala("Biblioteca"); // Nó folha
    hall->esquerda->direita = criarSala("Sala de Jantar");
    
    // Nível 2 - Direita
    hall->direita->esquerda = criarSala("Despensa"); // Nó folha
    hall->direita->direita = criarSala("Jardim de Inverno");
    
    // Nível 3 - Sub-árvore Sala de Jantar
    hall->esquerda->direita->esquerda = criarSala("Dispensa de Louças"); // Nó folha
    hall->esquerda->direita->direita = criarSala("Corredor Oeste");
    
    // Nível 3 - Sub-árvore Jardim de Inverno
    hall->direita->direita->esquerda = criarSala("Varanda"); // Nó folha
    hall->direita->direita->direita = criarSala("Escritório"); // Nó folha

    // Nível 4 - Sub-árvore Corredor Oeste
    hall->esquerda->direita->direita->esquerda = criarSala("Quarto Principal"); // Nó folha
    hall->esquerda->direita->direita->direita = criarSala("Banheiro"); // Nó folha

    // ------------------------------------------------------------------
    // 2. Início da Exploração
    // ------------------------------------------------------------------
    explorarSalas(hall);
    
    // ------------------------------------------------------------------
    // 3. Limpeza de Memória
    // ------------------------------------------------------------------
    liberarMapa(hall);
    
    return 0;
}

