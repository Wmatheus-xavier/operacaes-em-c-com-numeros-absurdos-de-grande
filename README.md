# Operações em C com Números Absurdamente Grandes

Implementação em C puro de aritmética de precisão arbitrária usando strings. O programa lê uma operação e dois números inteiros não-negativos gigantes (representados como strings de dígitos) e imprime o resultado.

## Como usar

```bash
gcc -o prog estruradedados.c
echo "SOMA 123 456" | ./prog
```

**Formato de entrada:**
```
OPERACAO NUMERO_A NUMERO_B
```

**Operações disponíveis:** `SOMA`, `SUBTRACAO`, `MULTIPLICACAO`, `DIVISAO`

> A `DIVISAO` retorna apenas o quociente inteiro.  
> A `SUBTRACAO` retorna resultado negativo (com `-`) quando B > A.

---

## Como foi implementado

Cada operação trabalha diretamente sobre as strings de dígitos, sem converter para tipos numéricos nativos — o que permite lidar com números de qualquer tamanho.

| Função | Estratégia |
|---|---|
| `SOMA` | Soma dígito a dígito da direita para a esquerda com carry |
| `SUBTRACAO` | Compara qual é maior, faz subtração com borrow, adiciona `-` se necessário |
| `MULTIPLICACAO` | Multiplicação clássica O(n×m) com array de dígitos intermediários |
| `DIVISAO` | Long division dígito a dígito — acumula resto, conta quantas vezes o divisor cabe |

---

## 🧪 Casos de Teste Oficiais (UnB / Aprender3)

Abaixo estão os casos de teste rigorosos utilizados no sistema de avaliação para validar a precisão aritmética do código com strings massivas.

### Teste 1: Soma Simples
**Input:**
```
SOMA 123456789123456789123456789 987654321987654321987654321
```
**Saída Esperada:**
```
1111111111111111111111111110
```

---

### Teste 2: Subtração Simples
**Input:**
```
SUBTRACAO 987654321987654321987654321 876543219876543219876543219
```
**Saída Esperada:**
```
111111102111111102111111102
```

---

### Teste 3: Multiplicação
**Input:**
```
MULTIPLICACAO 123456789123456789123456789 987654321987654321987654321
```
**Saída Esperada:**
```
121932631356500531591068431581771069347203169112635269
```

---

### Teste 4: Divisão (Quociente 1)
**Input:**
```
DIVISAO 1111111111111111111111111111111111111112 1111111111111111111111111111111111111111
```
**Saída Esperada:**
```
1
```

---

### Teste 5: Divisão Complexa
**Input:**
```
DIVISAO 58245432345342546549567493453842345243503428595483656353434535 4925592438549358340643694568496294548958243282584390432523
```
**Saída Esperada:**
```
11825
```

---

### Teste 6: Soma de Tamanhos Diferentes
**Input:**
```
SOMA 58245432345342546549567493453842345243503428595483656353434535 49255924385493583406436945684962945489582432825843904325234583425
```
**Saída Esperada:**
```
49314169817838925952986513178416787834825936254439387981588017960
```

---

### Teste 7: Multiplicação Extrema
**Input:**
```
MULTIPLICACAO 58245432345342546549567493453842345243503428595483656353434535 49255924385493583406436945684962945489582432825843904325234583425
```
**Saída Esperada:**
```
2868932611402574658675245944711188715853028455384137057460885657951669207459278434019819381647633516015260003329775558733582375
```

---

### Teste 8: Subtração Resultando em Negativo
**Input:**
```
SUBTRACAO 58245432345342546549567493453842345243503428595483656353434535 49255924385493583406436945684962945489582432825843904327676453353
```
**Saída Esperada:**
```
-49197678953148240859887378191509103144338929397248420671323018818
```

> **Dica sobre o Teste 8:** Repare que a Saída Esperada tem um **sinal de menos (`-`)** no começo. Na implementação de `SUBTRACAO`, é preciso verificar qual string representa o maior valor. Se B > A, o resultado deve imprimir o `-` e fazer `B - A`.
