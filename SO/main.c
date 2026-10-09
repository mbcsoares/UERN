#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_LEITORES   5
#define NUM_ESCRITORES 5
#define ITERACOES      5   /* cada thread acessa o recurso 5 vezes */

int leitores = 0;    /* contador de leitores ativos                */
int escritores = 0;  /* contador de escritores ativos/esperando    */
int recurso = 0;     /* recurso compartilhado                      */

sem_t mutex;   /* protege os contadores leitores e escritores   */
sem_t db;      /* acesso exclusivo ao recurso compartilhado     */
sem_t turno;   /* garante alternância entre blocos de L e E - se um escritor está na fila, novos leitores esperam; e vice-versa    */

/*
Regras da alternância:
- Um leitor só pode tentar entrar se não houver escritor ativo ou esperando.
- Um escritor só pode entrar se não houver leitor ativo nem escritor ativo.
- Ao entrar, o processo marca sua presença; ao sair, marca sua ausência.
- O semáforo "turno" funciona como um "portão" que dá prioridade a quem chegou primeiro no ciclo atual.
*/

/* ---------------------------------------------------------------- */
/* LEITOR                                                           */
/* ---------------------------------------------------------------- */
void *leitor(void *arg)
{
    int id = *(int *)arg;

    for (int i = 0; i < ITERACOES; i++)
    {
        /* ---- ENTRADA ---- */
        
        sem_wait(&turno);   /* pega o portão do turno atual           */
        sem_wait(&mutex);
        
        if (escritores > 0)
        {
            /* há escritor ativo/esperando: leitor espera o próximo ciclo */
            sem_post(&mutex);
            sem_post(&turno); //libera o portão
            
            usleep(1000);
            
            i--;            /* re-tenta a mesma iteração              */
            continue;
        }
        
        leitores++;
        
        if (leitores == 1)
        {
            sem_wait(&db);  /* primeiro leitor reserva o recurso      */
        }
        
        sem_post(&mutex);
        sem_post(&turno);   /* libera o portão para outros leitores   */

        /* ---- LEITURA ---- */
        printf("[Leitor %d] lendo = %d (leitores ativos: %d)\n",
               id, recurso, leitores);
        sleep(1);

        /* ---- SAÍDA ---- */
        sem_wait(&mutex);
        leitores--;
        if (leitores == 0)
            sem_post(&db);  /* último leitor libera o recurso         */
        sem_post(&mutex);

        sleep(1);           /* processa o que foi lido                */
    }

    printf("[Leitor %d] terminou.\n", id);
    return NULL;
}

/* ---------------------------------------------------------------- */
/* ESCRITOR                                                         */
/* ---------------------------------------------------------------- */
void *escritor(void *arg)
{
    int id = *(int *)arg;

    for (int i = 0; i < ITERACOES; i++)
    {
        sleep(1);           /* processa antes de escrever             */

        /* ---- ENTRADA ---- */
        sem_wait(&turno);
        sem_wait(&mutex);
        
        if (leitores > 0 || escritores > 0)
        {
            /* há leitor ativo ou outro escritor: espera próximo ciclo */
            
            sem_post(&mutex);
            sem_post(&turno);
            
            usleep(1000);
            
            i--;
            continue;
        }
        
        escritores++;
        
        sem_wait(&db);      /* escritor reserva o recurso exclusivo   */
        sem_post(&mutex);
        sem_post(&turno);

        /* ---- ESCRITA ---- */
        recurso++;
        printf("[Escritor %d] escrevendo = %d\n", id, recurso);
        sleep(2);

        /* ---- SAÍDA ---- */
        sem_wait(&mutex);
        escritores--;
        sem_post(&db);      /* libera o recurso                       */
        sem_post(&mutex);

        sleep(1);
    }

    printf("[Escritor %d] terminou.\n", id);
    
    return NULL;
}

/* ---------------------------------------------------------------- */
/* MAIN                                                             */
/* ---------------------------------------------------------------- */
int main(void)
{
    pthread_t th_leitores[NUM_LEITORES];
    pthread_t th_escritores[NUM_ESCRITORES];
    int ids_l[NUM_LEITORES], ids_e[NUM_ESCRITORES];

    sem_init(&mutex, 0, 1);
    sem_init(&db,    0, 1);
    sem_init(&turno, 0, 1);

    for (int i = 0; i < NUM_LEITORES; i++)
    {
        ids_l[i] = i + 1;
        pthread_create(&th_leitores[i], NULL, leitor, &ids_l[i]);
    }

    for (int i = 0; i < NUM_ESCRITORES; i++)
    {
        ids_e[i] = i + 1;
        pthread_create(&th_escritores[i], NULL, escritor, &ids_e[i]);
    }

    for (int i = 0; i < NUM_LEITORES; i++)
        pthread_join(th_leitores[i], NULL);
        
    for (int i = 0; i < NUM_ESCRITORES; i++)
        pthread_join(th_escritores[i], NULL);

    printf("=== Fim. Recurso final = %d ===\n", recurso);

    sem_destroy(&mutex);
    sem_destroy(&db);
    sem_destroy(&turno);

    return 0;
}