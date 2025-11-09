#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAM 5 // capacidade fixa da fila
// Estrutura que representa uma peça

typedef struct {
 char tipo;
 int id;
} Peca;

// Estrutura da fila circular
typedef struct {
    Peca itens[TAM];
    int frente;
    int tras;
    int total;
} Fila;

// --- Funções da Fila ---

// Inicializa a fila vazia
void inicializarFila(Fila *f) {
    f->frente = 0;
    f->tras = 0;
    f->total = 0;
}

// Verifica se a fila está cheia
int filaCheia(Fila *f) {
    return f->total == TAM;
}

// Verifica se a fila está vazia
int filaVazia(Fila *f) {
    return f->total == 0;
}

// Mostra o conteúdo atual da fila
void mostrarFila(Fila *f) {
    printf("\n===== FILA ATUAL =====\n");
    if (filaVazia(f)) {
        printf("Fila vazia.\n");
        return;
    }

    for (int i = 0; i < f->total; i++) {
    int pos = (f->frente + i) % TAM;
    printf("[%d] Tipo: %c | ID: %d\n", i, f->itens[pos].tipo, f->itens[pos].id);
 }

 printf("=======================\n");
}

// Gera uma nova peça com tipo aleatório e ID sequencial
Peca gerarPeca(int id) {
    Peca nova;
    nova.id = id;
    nova.tipo = 'A' + (rand() % 4); // tipos entre A, B, C, D
    return nova;
}

// Insere uma peça no final da fila (enqueue)
void enqueue(Fila *f, Peca p) {
    if (filaCheia(f)) {
         printf("Fila cheia! Não é possível inserir.\n");
        return;
    }
    f->itens[f->tras] = p;
    f->tras = (f->tras + 1) % TAM;
    f->total++;

}

  // Remove uma peça da frente da fila (dequeue)
Peca dequeue(Fila *f) {
    Peca removida = {'?', -1};
    if (filaVazia(f)) {
        printf("Fila vazia! Não é possível remover.\n");
        return removida;
    }

    removida = f->itens[f->frente];
    f->frente = (f->frente + 1) % TAM;
    f->total--;
    return removida;
}

// --- Programa principal ---
int main() {
    Fila fila;
    int opcao;
    int idGerador = 1;
    srand(time(NULL)); // inicializa aleatoriedade

    inicializarFila(&fila);

    // Preenche a fila com 5 peças iniciais
   for (int i = 0; i < TAM; i++) {
   enqueue(&fila, gerarPeca(idGerador++));
   }

   printf("=== SISTEMA DE FILA DE PECAS FUTURAS ===\n");

   do {
      mostrarFila(&fila);
      printf("\nMenu:\n");
      printf("1 - Jogar (remover a peça da frente e adicionar nova no final)\n");
      printf("0 - Sair\n");
      printf("Escolha: ");
      scanf("%d", &opcao);
      
      if (opcao == 1) {
          // Remove da frente e adiciona nova peça no final
          Peca jogada = dequeue(&fila);
          if (jogada.id != -1) {
              printf("\nPeça jogada: Tipo %c | ID %d\n", jogada.tipo, jogada.id);
 Peca nova = gerarPeca(idGerador++);
 enqueue(&fila, nova);
              printf("Nova peça inserida: Tipo %c | ID %d\n", nova.tipo, nova.id);
            }

        }

    }while(opcao!= 0);

     printf("\nPrograma encerrado.\n");
 
     return 0;

}
