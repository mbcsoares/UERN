# README.md

# Problema Leitores-Escritores com Semáforos

## 📋 Descrição

Este projeto implementa uma solução para o clássico **Problema dos Leitores-Escritores** utilizando **semáforos POSIX** em C com a biblioteca `pthreads`. O programa simula múltiplas threads leitoras e escritoras acessando concorrentemente um recurso compartilhado, garantindo as condições de sincronização necessárias.

---

## 🎓 Informações Acadêmicas

| Campo | Informação |
|-------|------------|
| **Disciplina** | Sistemas Operacionais |
| **Docentes** | Profa. Glaucia Medeiros e Profa. Artemísia |
| **Discentes** | Manoel de Medeiros, Micael Bruno, Rafael Manna |

---

## 🎯 Objetivo do Problema

O problema dos leitores-escritores modela uma situação onde:

- **Múltiplos leitores** podem acessar o recurso **simultaneamente** (leitura concorrente é segura).
- **Escritores** precisam de **acesso exclusivo** ao recurso (nenhum outro leitor ou escritor pode estar ativo durante a escrita).
- É necessário **evitar inanição** (starvation) e garantir **exclusão mútua** entre escritores.

---

## ⚙️ Parâmetros de Configuração

| Constante | Valor | Descrição |
|-----------|-------|-----------|
| `NUM_LEITORES` | 5 | Número de threads leitoras |
| `NUM_ESCRITORES` | 5 | Número de threads escritoras |
| `ITERACOES` | 5 | Número de acessos ao recurso por thread |

---

## 🧩 Variáveis Compartilhadas

```c
int leitores = 0;    // Contador de leitores ativos
int escritores = 0;  // Contador de escritores ativos/esperando
int recurso = 0;     // Recurso compartilhado (incrementado pelos escritores)
```

---

## 🔐 Semáforos Utilizados

| Semáforo | Função |
|----------|--------|
| `mutex` | Protege os contadores `leitores` e `escritores` |
| `db` | Garante acesso exclusivo ao recurso compartilhado |
| `turno` | Funciona como "portão" para alternância entre leitores e escritores, evitando inanição |

---

## 🔄 Regras de Alternância

O semáforo `turno` implementa um mecanismo de **prioridade justa**:

1. **Leitor** só entra se **não houver escritor ativo ou esperando**.
2. **Escritor** só entra se **não houver leitor ativo nem escritor ativo**.
3. Ao entrar, a thread **marca sua presença**; ao sair, **marca sua ausência**.
4. O semáforo `turno` funciona como um **portão** que dá prioridade a quem chegou primeiro no ciclo atual.

> 💡 Essa abordagem evita que leitores monopolizem o recurso indefinidamente, garantindo que escritores também tenham chance de executar.

---

## 🧵 Funcionamento das Threads

### Leitor (`leitor()`)

```
┌─────────────────────────────────────────┐
│ 1. Pega o portão (turno)                │
│ 2. Pega o mutex                         │
│ 3. Se há escritor ativo/esperando:      │
│    → Libera mutex e turno               │
│    → Aguarda e retenta                  │
│ 4. Incrementa contador de leitores      │
│ 5. Se for o primeiro leitor:            │
│    → Pega o semáforo db (exclusivo)     │
│ 6. Libera mutex e turno                 │
│ 7. Executa a LEITURA (sleep 1s)         │
│ 8. Decrementa contador de leitores      │
│ 9. Se for o último leitor:              │
│    → Libera o semáforo db               │
│ 10. Processa o que foi lido (sleep 1s)  │
└─────────────────────────────────────────┘
```

### Escritor (`escritor()`)

```
┌─────────────────────────────────────────┐
│ 1. Processa antes de escrever (sleep 1s)│
│ 2. Pega o portão (turno)                │
│ 3. Pega o mutex                         │
│ 4. Se há leitor ativo ou outro escritor:│
│    → Libera mutex e turno               │
│    → Aguarda e retenta                  │
│ 5. Incrementa contador de escritores    │
│ 6. Pega o semáforo db (exclusivo)       │
│ 7. Libera mutex e turno                 │
│ 8. Executa a ESCRITA (sleep 2s)         │
│    → Incrementa o recurso               │
│ 9. Decrementa contador de escritores    │
│ 10. Libera o semáforo db                │
│ 11. Processa após escrita (sleep 1s)    │
└─────────────────────────────────────────┘
```

---

## 🛠️ Compilação e Execução

### Compilar

```bash
gcc main.c -o leitores_escritores -lpthread
```

### Executar

```bash
./leitores_escritores
```

### Exemplo de Saída

```
[Leitor 1] lendo = 0 (leitores ativos: 1)
[Leitor 2] lendo = 0 (leitores ativos: 2)
[Leitor 3] lendo = 0 (leitores ativos: 3)
[Escritor 1] escrevendo = 1
[Escritor 2] escrevendo = 2
[Leitor 4] lendo = 2 (leitores ativos: 1)
...
=== Fim. Recurso final = 5 ===
```

> ⚠️ A saída exata varia conforme o escalonamento das threads pelo sistema operacional.

---

## ✅ Propriedades Garantidas

| Propriedade | Descrição |
|-------------|-----------|
| **Exclusão Mútua** | Escritores têm acesso exclusivo ao recurso |
| **Concorrência de Leitura** | Vários leitores podem ler simultaneamente |
| **Ausência de Deadlock** | Ordem consistente de aquisição de semáforos |
| **Justiça (alternância)** | Leitores e escritores se alternam, evitando inanição |
| **Consistência do Recurso** | O contador `recurso` é sempre atualizado corretamente |

---

## ⚠️ Limitações e Observações

1. **Busy-waiting parcial**: As threads usam `usleep(1000)` e `i--` para retentar, o que não é ideal em termos de eficiência.
2. **Alternância rígida**: O mecanismo pode ser menos eficiente que soluções com filas de espera, mas garante justiça.
3. **Solução não-bloqueante ideal**: Existem implementações mais elegantes usando `pthread_cond` ou semáforos adicionais, mas esta é didática e funcional.
4. **Contador `escritores`**: Inclui escritores ativos **e** esperando, o que ajuda a dar prioridade a escritores na fila.

---

## 📚 Conceitos Abordados

- Programação concorrente com **threads POSIX**
- **Semáforos** como mecanismo de sincronização
- **Exclusão mútua** e **condições de corrida**
- **Inanição (starvation)** e **justiça (fairness)**
- Problema clássico de **Leitores-Escritores**

---

## 👨‍💻 Autores

- Manoel de Medeiros
- Micael Bruno
- Rafael Manna

**Disciplina:** Sistemas Operacionais
**Docentes:** Profa. Glaucia Medeiros e Profa. Artemísia

---

## 📄 Licença

Este código é de domínio público para fins educacionais.
