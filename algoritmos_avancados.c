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

/**
 * @file detective_quest_aventureiro.c
 * @brief Simula a exploração da mansão e a coleta de pistas usando duas árvores:
 * uma Árvore Binária para o mapa e uma Árvore BST para as pistas.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Definição das Estruturas ---

// Estrutura do nó da Árvore de Pistas (BST)
typedef struct PistaNode {
    char pista[100];
    struct PistaNode *esquerda;
    struct PistaNode *direita;
} PistaNode;

// Estrutura do nó da Árvore de Salas (Mapa)
typedef struct Sala {
    char nome[50];
    char pista[100]; // Pista associada ao cômodo (vazia se não houver)
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// --- Funções Auxiliares para o Mapa (Árvore Binária) ---

/**
 * @brief Cria dinamicamente um cômodo com ou sem pista.
 *
 * Aloca memória para uma nova sala, inicializa seus caminhos como NULL
 * e associa o nome e a pista fornecidos.
 * @param nomeSala O nome do cômodo.
 * @param conteudoPista O texto da pista (use "" se não houver pista).
 * @return Um ponteiro para a nova Sala criada.
 */
Sala* criarSala(const char* nomeSala, const char* conteudoPista) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala == NULL) {
        printf("Erro de alocação de memória para Sala!\n");
        exit(EXIT_FAILURE);
    }
    
    strncpy(novaSala->nome, nomeSala, 49);
    novaSala->nome[49] = '\0';
    
    strncpy(novaSala->pista, conteudoPista, 99);
    novaSala->pista[99] = '\0';
    
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

// --- Funções para a Árvore de Pistas (BST) ---

/**
 * @brief Cria dinamicamente um novo nó de pista.
 * @param conteudoPista O texto da pista.
 * @return Um ponteiro para o novo PistaNode.
 */
PistaNode* criarPistaNode(const char* conteudoPista) {
    PistaNode* novoNode = (PistaNode*)malloc(sizeof(PistaNode));
    if (novoNode == NULL) {
        printf("Erro de alocação de memória para PistaNode!\n");
        exit(EXIT_FAILURE);
    }
    strncpy(novoNode->pista, conteudoPista, 99);
    novoNode->pista[99] = '\0';
    novoNode->esquerda = NULL;
    novoNode->direita = NULL;
    return novoNode;
}

/**
 * @brief Insere uma nova pista na Árvore Binária de Busca (BST) de forma recursiva.
 *
 * A inserção é baseada na ordem alfabética (comparação de strings).
 * @param raiz O nó raiz atual da subárvore.
 * @param conteudoPista O texto da pista a ser inserida.
 * @return O ponteiro para o nó raiz atualizado.
 */
PistaNode* inserirPista(PistaNode* raiz, const char* conteudoPista) {
    // Caso base: Árvore vazia ou alcançou a posição de inserção
    if (raiz == NULL) {
        return criarPistaNode(conteudoPista);
    }
    
    // Compara a nova pista com a pista do nó atual
    int comparacao = strcmp(conteudoPista, raiz->pista);
    
    if (comparacao < 0) {
        // Nova pista é alfabeticamente menor: insere na esquerda
        raiz->esquerda = inserirPista(raiz->esquerda, conteudoPista);
    } else if (comparacao > 0) {
        // Nova pista é alfabeticamente maior: insere na direita
        raiz->direita = inserirPista(raiz->direita, conteudoPista);
    }
    // Se comparacao == 0, a pista já existe; não insere duplicata.
    
    return raiz;
}

/**
 * @brief Imprime a Árvore de Pistas em ordem alfabética (Caminhamento In-Order).
 *
 * Utiliza recursividade para visitar: Esquerda -> Raiz -> Direita.
 * @param raiz O nó raiz atual da BST de pistas.
 */
void exibirPistas(PistaNode* raiz) {
    if (raiz != NULL) {
        // 1. Visita a subárvore esquerda
        exibirPistas(raiz->esquerda);
        
        // 2. Imprime a pista do nó atual
        printf("  - %s\n", raiz->pista);
        
        // 3. Visita a subárvore direita
        exibirPistas(raiz->direita);
    }
}

// --- Função Principal de Exploração ---

/**
 * @brief Controla a navegação do jogador entre salas e coleta de pistas.
 *
 * Permite a escolha entre 'e' (esquerda), 'd' (direita) ou 's' (sair).
 * Coleta automaticamente pistas ao entrar em novos cômodos.
 * @param hall O ponteiro para a sala inicial.
 * @param pistasColetadas O ponteiro para a raiz da BST de pistas.
 * @return O ponteiro atualizado da BST de pistas.
 */
PistaNode* explorarSalasComPistas(Sala* hall, PistaNode* pistasColetadas) {
    Sala* salaAtual = hall;
    char escolha;
    
    printf("\n--- Explorando a Mansão em Busca de Pistas ---\n");
    
    while (salaAtual != NULL) {
        printf("\nVocê está em: **%s**\n", salaAtual->nome);
        
        // Coleta de Pista
        if (strlen(salaAtual->pista) > 0) {
            printf("✅ Pista Encontrada: \"%s\"\n", salaAtual->pista);
            pistasColetadas = inserirPista(pistasColetadas, salaAtual->pista);
            
            // "Limpa" a pista da sala para evitar coleta duplicada na próxima visita
            salaAtual->pista[0] = '\0'; 
        } else {
            printf("  (Nenhuma pista nova neste cômodo.)\n");
        }
        
        // ------------------------------------
        // Menu de Opções
        // ------------------------------------
        printf("\nEscolha o próximo caminho:\n");
        if (salaAtual->esquerda != NULL) {
            printf("  [e] Esquerda (Para %s)\n", salaAtual->esquerda->nome);
        }
        if (salaAtual->direita != NULL) {
            printf("  [d] Direita (Para %s)\n", salaAtual->direita->nome);
        }
        printf("  [s] Sair e Analisar Pistas\n");
        printf("Sua escolha: ");
        
        scanf(" %c", &escolha);
        
        // ------------------------------------
        // Navegação
        // ------------------------------------
        if (escolha == 's' || escolha == 'S') {
            break; // Sai da exploração
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
    
    return pistasColetadas;
}

/**
 * @brief Libera a memória alocada para o mapa (Árvore de Salas).
 */
void liberarMapa(Sala* raiz) {
    if (raiz != NULL) {
        liberarMapa(raiz->esquerda);
        liberarMapa(raiz->direita);
        free(raiz);
    }
}

/**
 * @brief Libera a memória alocada para a BST de pistas.
 */
void liberarPistas(PistaNode* raiz) {
    if (raiz != NULL) {
        liberarPistas(raiz->esquerda);
        liberarPistas(raiz->direita);
        free(raiz);
    }
}


/**
 * @brief Monta o mapa inicial, cria a BST de pistas, inicia a exploração e exibe os resultados.
 */
int main() {
    // ------------------------------------------------------------------
    // 1. Montagem manual do Mapa da Mansão (Árvore Binária)
    // ------------------------------------------------------------------
    
    // Nível 0 (Raiz)
    Sala* hall = criarSala("Hall de Entrada", "A porta de entrada está arrombada.");
    
    // Nível 1
    hall->esquerda = criarSala("Sala de Estar", "Um bilhete rasgado está na mesa.");
    hall->direita = criarSala("Cozinha", "A faca do chef sumiu.");
    
    // Nível 2 - Esquerda
    hall->esquerda->esquerda = criarSala("Biblioteca", "Um livro de história foi removido.");
    hall->esquerda->direita = criarSala("Sala de Jantar", ""); // Sem pista
    
    // Nível 2 - Direita
    hall->direita->esquerda = criarSala("Despensa", "Há pegadas de barro na despensa.");
    hall->direita->direita = criarSala("Jardim de Inverno", "As plantas estão reviradas.");
    
    // Nível 3 - Sub-árvore Sala de Jantar
    hall->esquerda->direita->esquerda = criarSala("Dispensa de Louças", ""); // Sem pista
    hall->esquerda->direita->direita = criarSala("Corredor Oeste", "Um relógio de bolso quebrado.");
    
    // Nível 3 - Sub-árvore Jardim de Inverno
    hall->direita->direita->esquerda = criarSala("Varanda", "O cinzeiro estava cheio."); // Nó folha
    hall->direita->direita->direita = criarSala("Escritório", "Um rascunho de testamento."); // Nó folha

    // Nível 4 - Sub-árvore Corredor Oeste
    hall->esquerda->direita->direita->esquerda = criarSala("Quarto Principal", "O cofre foi aberto com força."); // Nó folha
    hall->esquerda->direita->direita->direita = criarSala("Banheiro", ""); // Nó folha
    
    // ------------------------------------------------------------------
    // 2. Início da Exploração e Coleta de Pistas
    // ------------------------------------------------------------------
    PistaNode* pistasColetadas = NULL;
    pistasColetadas = explorarSalasComPistas(hall, pistasColetadas);
    
    // ------------------------------------------------------------------
    // 3. Exibição dos Resultados (Pistas em Ordem Alfabética)
    // ------------------------------------------------------------------
    printf("\n============================================\n");
    printf("🔎 ANÁLISE FINAL: PISTAS COLETADAS (Ordem Alfabética)\n");
    printf("============================================\n");
    
    if (pistasColetadas == NULL) {
        printf("Nenhuma pista foi coletada durante a exploração.\n");
    } else {
        exibirPistas(pistasColetadas);
    }

    // ------------------------------------------------------------------
    // 4. Limpeza de Memória
    // ------------------------------------------------------------------
    liberarMapa(hall);
    liberarPistas(pistasColetadas);
    
    return 0;
}

/**
 * @file detective_quest_mestre.c
 * @brief Sistema completo de exploração da mansão, coleta de pistas (BST) e
 * associação a suspeitos (Tabela Hash) para a fase de julgamento final.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // Para tolower

// --- Constantes para a Tabela Hash ---
#define TAMANHO_HASH 10

// --- 1. Estruturas para o Mapa (Árvore Binária) ---

typedef struct Sala {
    char nome[50];
    char pista[100]; // Pista do cômodo
    char suspeito_alvo[50]; // Suspeito incriminado pela pista
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// --- 2. Estruturas para a Árvore de Pistas (BST) ---

typedef struct PistaNode {
    char pista[100];
    struct PistaNode *esquerda;
    struct PistaNode *direita;
} PistaNode;

// --- 3. Estruturas para a Tabela Hash (Suspeitos) ---

typedef struct HashEntry {
    char pista[100]; // Chave
    char suspeito[50]; // Valor
    struct HashEntry *proximo; // Encadeamento
} HashEntry;

typedef struct SuspeitoHash {
    HashEntry *tabela[TAMANHO_HASH];
} SuspeitoHash;

// --- Implementação do Mapa (Árvore Binária) ---

/**
 * @brief Cria dinamicamente um cômodo para o mapa.
 * @param nomeSala O nome do cômodo.
 * @param conteudoPista O texto da pista associada.
 * @param alvo O nome do suspeito incriminado pela pista.
 * @return Um ponteiro para a nova Sala criada.
 */
Sala* criarSala(const char* nomeSala, const char* conteudoPista, const char* alvo) {
    Sala* novaSala = (Sala*)malloc(sizeof(Sala));
    if (novaSala == NULL) {
        printf("Erro de alocação de memória para Sala!\n");
        exit(EXIT_FAILURE);
    }
    
    strncpy(novaSala->nome, nomeSala, 49);
    strncpy(novaSala->pista, conteudoPista, 99);
    strncpy(novaSala->suspeito_alvo, alvo, 49);
    
    novaSala->nome[49] = novaSala->pista[99] = novaSala->suspeito_alvo[49] = '\0';
    novaSala->esquerda = NULL;
    novaSala->direita = NULL;
    
    return novaSala;
}

// --- Implementação da Tabela Hash ---

/**
 * @brief Calcula o índice hash a partir de uma chave (pista).
 * @param chave A string da pista.
 * @return O índice na tabela hash.
 */
int calcularHash(const char *chave) {
    unsigned long hash = 5381;
    int c;
    while ((c = *chave++)) {
        hash = ((hash << 5) + hash) + tolower(c); // hash * 33 + c
    }
    return hash % TAMANHO_HASH;
}

/**
 * @brief Inicializa a Tabela Hash.
 * @param sh O ponteiro para a Tabela Hash.
 */
void inicializarHash(SuspeitoHash *sh) {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        sh->tabela[i] = NULL;
    }
}

/**
 * @brief Insere a associação pista/suspeito na tabela hash.
 *
 * Utiliza encadeamento para resolver colisões.
 * @param sh O ponteiro para a Tabela Hash.
 * @param pista A string da pista (chave).
 * @param suspeito O nome do suspeito (valor).
 */
void inserirNaHash(SuspeitoHash *sh, const char *pista, const char *suspeito) {
    int indice = calcularHash(pista);

    HashEntry *novoEntry = (HashEntry*)malloc(sizeof(HashEntry));
    if (novoEntry == NULL) {
        printf("Erro de alocação de memória para HashEntry!\n");
        return;
    }

    strncpy(novoEntry->pista, pista, 99);
    strncpy(novoEntry->suspeito, suspeito, 49);
    novoEntry->pista[99] = novoEntry->suspeito[49] = '\0';

    // Inserção no início da lista encadeada no índice
    novoEntry->proximo = sh->tabela[indice];
    sh->tabela[indice] = novoEntry;
}

/**
 * @brief Consulta o suspeito correspondente a uma pista.
 * @param sh O ponteiro para a Tabela Hash.
 * @param pista A string da pista (chave).
 * @return O nome do suspeito ou NULL se a pista não for encontrada.
 */
char* encontrarSuspeito(SuspeitoHash *sh, const char *pista) {
    int indice = calcularHash(pista);
    HashEntry *current = sh->tabela[indice];

    while (current != NULL) {
        if (strcmp(current->pista, pista) == 0) {
            return current->suspeito;
        }
        current = current->proximo;
    }
    return NULL;
}

// --- Implementação da BST de Pistas ---

/**
 * @brief Cria dinamicamente um novo nó de pista.
 * @param conteudoPista O texto da pista.
 * @return Um ponteiro para o novo PistaNode.
 */
PistaNode* criarPistaNode(const char* conteudoPista) {
    PistaNode* novoNode = (PistaNode*)malloc(sizeof(PistaNode));
    if (novoNode == NULL) {
        printf("Erro de alocação de memória para PistaNode!\n");
        exit(EXIT_FAILURE);
    }
    strncpy(novoNode->pista, conteudoPista, 99);
    novoNode->pista[99] = '\0';
    novoNode->esquerda = NULL;
    novoNode->direita = NULL;
    return novoNode;
}

/**
 * @brief Insere a pista coletada na Árvore Binária de Busca (BST) de forma recursiva.
 * @param raiz O nó raiz atual da subárvore.
 * @param conteudoPista O texto da pista a ser inserida.
 * @return O ponteiro para o nó raiz atualizado.
 */
PistaNode* inserirPista(PistaNode* raiz, const char* conteudoPista) {
    if (raiz == NULL) {
        return criarPistaNode(conteudoPista);
    }
    
    int comparacao = strcmp(conteudoPista, raiz->pista);
    
    if (comparacao < 0) {
        raiz->esquerda = inserirPista(raiz->esquerda, conteudoPista);
    } else if (comparacao > 0) {
        raiz->direita = inserirPista(raiz->direita, conteudoPista);
    }
    
    return raiz;
}

/**
 * @brief Exibe as pistas coletadas em ordem alfabética (Caminhamento In-Order).
 * @param raiz O nó raiz atual da BST de pistas.
 */
void exibirPistas(PistaNode* raiz) {
    if (raiz != NULL) {
        exibirPistas(raiz->esquerda);
        printf("  - %s\n", raiz->pista);
        exibirPistas(raiz->direita);
    }
}

// --- Função Principal de Exploração e Julgamento ---

/**
 * @brief Navega pela árvore e ativa o sistema de pistas.
 *
 * Controla a navegação do jogador, coleta pistas e as adiciona à BST.
 * @param hall O ponteiro para a sala inicial.
 * @param pistasColetadas O ponteiro para a raiz da BST de pistas.
 * @param hashSuspeitos O ponteiro para a Tabela Hash de suspeitos.
 * @return O ponteiro atualizado da BST de pistas.
 */
PistaNode* explorarSalas(Sala* hall, PistaNode* pistasColetadas, SuspeitoHash *hashSuspeitos) {
    Sala* salaAtual = hall;
    char escolha;
    
    printf("\n--- EXPLORAÇÃO DA MANSÃO: NÍVEL MESTRE ---\n");
    
    while (salaAtual != NULL) {
        printf("\nVocê está em: **%s**\n", salaAtual->nome);
        
        // Coleta de Pista
        if (strlen(salaAtual->pista) > 0) {
            printf("✅ Pista Encontrada: \"%s\"\n", salaAtual->pista);
            
            // 1. Adiciona a pista à BST para ordenação
            pistasColetadas = inserirPista(pistasColetadas, salaAtual->pista);
            
            // 2. Adiciona a associação Pista -> Suspeito na Hash
            inserirNaHash(hashSuspeitos, salaAtual->pista, salaAtual->suspeito_alvo);
            
            printf("   * Pista associada ao suspeito: %s\n", salaAtual->suspeito_alvo);
            
            // "Limpa" a pista da sala para evitar coleta duplicada
            salaAtual->pista[0] = '\0'; 
        } else {
            printf("  (Nenhuma pista nova neste cômodo.)\n");
        }
        
        // Menu de Opções
        printf("\nCaminhos disponíveis:\n");
        if (salaAtual->esquerda != NULL) {
            printf("  [e] Esquerda (Para %s)\n", salaAtual->esquerda->nome);
        }
        if (salaAtual->direita != NULL) {
            printf("  [d] Direita (Para %s)\n", salaAtual->direita->nome);
        }
        printf("  [s] SAIR e ACUSAR o Culpado\n");
        printf("Sua escolha: ");
        
        scanf(" %c", &escolha);
        
        // Navegação
        if (escolha == 's' || escolha == 'S') {
            break; 
        } 
        else if (escolha == 'e' || escolha == 'E') {
            if (salaAtual->esquerda != NULL) {
                salaAtual = salaAtual->esquerda;
            } else {
                printf("Caminho não disponível ou cômodo inalcançável. Tente outra direção.\n");
            }
        } 
        else if (escolha == 'd' || escolha == 'D') {
            if (salaAtual->direita != NULL) {
                salaAtual = salaAtual->direita;
            } else {
                printf("Caminho não disponível ou cômodo inalcançável. Tente outra direção.\n");
            }
        } 
        else {
            printf("Opção inválida. Use 'e', 'd' ou 's'.\n");
        }
    }
    
    return pistasColetadas;
}

/**
 * @brief Conta as pistas que apontam para o suspeito acusado.
 *
 * Função recursiva que percorre a BST de pistas, consulta a Tabela Hash para
 * cada pista e conta quantas incriminam o suspeito acusado.
 * @param raiz O nó raiz atual da BST de pistas.
 * @param sh O ponteiro para a Tabela Hash.
 * @param acusado O nome do suspeito acusado.
 * @return O número total de pistas que apontam para o acusado.
 */
int contarPistasParaSuspeito(PistaNode* raiz, SuspeitoHash *sh, const char *acusado) {
    if (raiz == NULL) {
        return 0;
    }

    int contagem = 0;
    char *suspeitoDaPista;

    // 1. Visita o nó atual e consulta a hash
    suspeitoDaPista = encontrarSuspeito(sh, raiz->pista);
    if (suspeitoDaPista != NULL && strcmp(suspeitoDaPista, acusado) == 0) {
        contagem = 1; // Pista encontrada para o acusado
    }
    
    // 2. Visita recursivamente as subárvores
    contagem += contarPistasParaSuspeito(raiz->esquerda, sh, acusado);
    contagem += contarPistasParaSuspeito(raiz->direita, sh, acusado);

    return contagem;
}


/**
 * @brief Conduz à fase de julgamento final.
 *
 * Solicita a acusação do jogador e avalia a contagem de pistas.
 * @param pistasColetadas A raiz da BST de pistas.
 * @param hashSuspeitos O ponteiro para a Tabela Hash.
 */
void verificarSuspeitoFinal(PistaNode* pistasColetadas, SuspeitoHash *hashSuspeitos) {
    char acusado[50];
    int pistas_minimas = 2;

    printf("\n============================================\n");
    printf("🕵️‍♂️ FASE DE JULGAMENTO FINAL\n");
    printf("============================================\n");
    
    if (pistasColetadas == NULL) {
        printf("Você não coletou nenhuma pista! A acusação não pode ser feita.\n");
        return;
    }

    // Listar pistas para ajudar o jogador
    printf("\nPistas Coletadas (em ordem alfabética):\n");
    exibirPistas(pistasColetadas);

    // Solicitar acusação
    printf("\nCom base nas evidências, quem você acusa? ");
    scanf(" %49[^\n]", acusado);
    
    // Contar pistas incriminatórias
    int contagem = contarPistasParaSuspeito(pistasColetadas, hashSuspeitos, acusado);

    // Avaliação
    printf("\n--- Avaliação das Evidências ---\n");
    printf("Acusado: %s\n", acusado);
    printf("Pistas incriminatórias encontradas: %d\n", contagem);

    if (contagem >= pistas_minimas) {
        printf("✅ Acusação de %s é **SUSTENTADA** por %d pistas! O mistério foi resolvido.\n", acusado, contagem);
    } else {
        printf("❌ Acusação de %s é **FRACA**. Você precisa de pelo menos %d pistas.\n", acusado, pistas_minimas);
        printf("   O verdadeiro culpado pode ter escapado!\n");
    }
}

// --- Funções de Limpeza de Memória ---

void liberarMapa(Sala* raiz) {
    if (raiz != NULL) {
        liberarMapa(raiz->esquerda);
        liberarMapa(raiz->direita);
        free(raiz);
    }
}

void liberarPistas(PistaNode* raiz) {
    if (raiz != NULL) {
        liberarPistas(raiz->esquerda);
        liberarPistas(raiz->direita);
        free(raiz);
    }
}

void liberarHash(SuspeitoHash *sh) {
    for (int i = 0; i < TAMANHO_HASH; i++) {
        HashEntry *current = sh->tabela[i];
        while (current != NULL) {
            HashEntry *temp = current;
            current = current->proximo;
            free(temp);
        }
    }
}

// --- Main ---

int main() {
    // ------------------------------------------------------------------
    // 1. Montagem manual do Mapa da Mansão (Árvore Binária)
    //    Formato: criarSala("Nome", "Pista", "Suspeito")
    // ------------------------------------------------------------------
    
    // Suspeitos: D. Branca, Coronel Mostarda, Prof. Plum
    
    Sala* hall = criarSala("Hall de Entrada", "A porta estava aberta.", "Coronel Mostarda");
    
    // Nível 1
    hall->esquerda = criarSala("Sala de Estar", "Um colete ensanguentado.", "D. Branca");
    hall->direita = criarSala("Cozinha", "Um pote de veneno vazio.", "Prof. Plum");
    
    // Nível 2 - Esquerda
    hall->esquerda->esquerda = criarSala("Biblioteca", "Um recado escrito 'A Sra. em perigo'.", "D. Branca"); 
    hall->esquerda->direita = criarSala("Sala de Jantar", "Uma taça de vinho intacta.", ""); // Sem pista
    
    // Nível 2 - Direita
    hall->direita->esquerda = criarSala("Despensa", "Uma chave de fenda suja.", "Coronel Mostarda");
    hall->direita->direita = criarSala("Jardim de Inverno", "Um diário com as iniciais 'C. M.'.", "Coronel Mostarda");
    
    // ------------------------------------------------------------------
    // 2. Inicialização das Estruturas Dinâmicas
    // ------------------------------------------------------------------
    PistaNode* pistasColetadas = NULL;
    SuspeitoHash hashSuspeitos;
    inicializarHash(&hashSuspeitos);

    // ------------------------------------------------------------------
    // 3. Início da Exploração e Coleta de Pistas
    // ------------------------------------------------------------------
    pistasColetadas = explorarSalas(hall, pistasColetadas, &hashSuspeitos);
    
    // ------------------------------------------------------------------
    // 4. Julgamento Final
    // ------------------------------------------------------------------
    verificarSuspeitoFinal(pistasColetadas, &hashSuspeitos);
    
    // ------------------------------------------------------------------
    // 5. Limpeza de Memória
    // ------------------------------------------------------------------
    liberarMapa(hall);
    liberarPistas(pistasColetadas);
    liberarHash(&hashSuspeitos);
    
    return 0;
}