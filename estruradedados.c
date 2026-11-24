#include <stdio.h>
#include <string.h>

void inverte_string(char str[]) {
    int len = 0;
    int jl = 0;

    while (str[jl] != '\0') {
        len++;
        jl++;
    }
    for (int i = 0; i < len / 2; i++) {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}

/* Retorna 1 se |a| > |b|, -1 se |a| < |b|, 0 se iguais (compara como inteiros sem sinal) */
int compara_absoluto(char a[], char b[]) {
    int la = 0, lb = 0;
    while (a[la] != '\0') la++;
    while (b[lb] != '\0') lb++;
    if (la != lb) return la > lb ? 1 : -1;
    for (int i = 0; i < la; i++) {
        if (a[i] != b[i]) return a[i] > b[i] ? 1 : -1;
    }
    return 0;
}

void SOMA(char a[], char b[]) {
    char res[100000];
    int len_a = 0, len_b = 0;
    int jp = 0;

    while (a[jp] != '\0') { len_a++; jp++; }
    jp = 0;
    while (b[jp] != '\0') { len_b++; jp++; }

    int i = len_a - 1, j = len_b - 1, k = 0, vai_um = 0;

    while (i >= 0 || j >= 0 || vai_um > 0) {
        int dig_a = (i >= 0) ? a[i] - '0' : 0;
        int dig_b = (j >= 0) ? b[j] - '0' : 0;

        int soma = dig_a + dig_b + vai_um;
        res[k++] = (soma % 10) + '0';
        vai_um = soma / 10;
        i--; j--;
    }
    res[k] = '\0';
    inverte_string(res);
    printf("%s\n", res);
}

/* Subtrai |maior| - |menor|, ambos sem sinal. Assume |maior| >= |menor|. */
void subtrai_absoluto(char maior[], char menor[], char res[]) {
    int lm = 0, ln = 0;
    while (maior[lm] != '\0') lm++;
    while (menor[ln] != '\0') ln++;

    int i = lm - 1, j = ln - 1, k = 0, emprestimo = 0;

    while (i >= 0) {
        int dig_a = maior[i] - '0' - emprestimo;
        int dig_b = (j >= 0) ? menor[j] - '0' : 0;

        emprestimo = 0;
        if (dig_a < dig_b) {
            dig_a += 10;
            emprestimo = 1;
        }
        res[k++] = (dig_a - dig_b) + '0';
        i--; j--;
    }

    /* Remove zeros à esquerda (que ficaram à direita antes de inverter) */
    while (k > 1 && res[k - 1] == '0') k--;
    res[k] = '\0';
    inverte_string(res);
}

void SUBTRACAO(char a[], char b[]) {
    char res[100000];
    int cmp = compara_absoluto(a, b);

    if (cmp == 0) {
        printf("0\n");
        return;
    }

    if (cmp > 0) {
        /* a > b: resultado positivo */
        subtrai_absoluto(a, b, res);
        printf("%s\n", res);
    } else {
        /* b > a: resultado negativo */
        subtrai_absoluto(b, a, res);
        printf("-%s\n", res);
    }
}

void MULTIPLICACAO(char a[], char b[]) {
    int la = 0, lb = 0;
    while (a[la] != '\0') la++;
    while (b[lb] != '\0') lb++;

    /* Resultado pode ter no máximo la + lb dígitos */
    int tam = la + lb;
    int res[200000];
    for (int i = 0; i < tam; i++) res[i] = 0;

    /* Multiplicação clássica dígito a dígito */
    for (int i = la - 1; i >= 0; i--) {
        for (int j = lb - 1; j >= 0; j--) {
            int mul = (a[i] - '0') * (b[j] - '0');
            int pos1 = i + j;
            int pos2 = i + j + 1;
            int soma = mul + res[pos2];

            res[pos2] = soma % 10;
            res[pos1] += soma / 10;
        }
    }

    /* Monta a string do resultado, pulando zeros à esquerda */
    char saida[200000];
    int k = 0;
    int iniciou = 0;
    for (int i = 0; i < tam; i++) {
        if (!iniciou && res[i] == 0) continue;
        iniciou = 1;
        saida[k++] = res[i] + '0';
    }
    if (k == 0) saida[k++] = '0';
    saida[k] = '\0';
    printf("%s\n", saida);
}

/* Compara duas strings de dígitos como inteiros não-negativos.
   Retorna 1 se a > b, -1 se a < b, 0 se iguais. */
int compara_str(char a[], int la, char b[], int lb) {
    if (la != lb) return la > lb ? 1 : -1;
    for (int i = 0; i < la; i++) {
        if (a[i] != b[i]) return a[i] > b[i] ? 1 : -1;
    }
    return 0;
}

/* Subtrai b (tamanho lb) de a (tamanho la) in-place em a[].
   Assume a >= b. Retorna novo comprimento. */
int subtrai_buf(char a[], int la, char b[], int lb) {
    /* alinha pelo lado direito */
    int i = la - 1, j = lb - 1, emprestimo = 0;
    while (i >= 0) {
        int da = a[i] - '0' - emprestimo;
        int db = (j >= 0) ? b[j] - '0' : 0;
        emprestimo = 0;
        if (da < db) { da += 10; emprestimo = 1; }
        a[i] = (da - db) + '0';
        i--; j--;
    }
    /* Remove zeros à esquerda */
    int inicio = 0;
    while (inicio < la - 1 && a[inicio] == '0') inicio++;
    if (inicio > 0) {
        int novo = la - inicio;
        for (int x = 0; x < novo; x++) a[x] = a[inicio + x];
        la = novo;
    }
    a[la] = '\0';
    return la;
}

void DIVISAO(char a[], char b[]) {
    int la = 0, lb = 0;
    while (a[la] != '\0') la++;
    while (b[lb] != '\0') lb++;

    /* Divisão com quociente = 0 se b > a */
    if (compara_str(a, la, b, lb) < 0) {
        printf("0\n");
        return;
    }

    /* Algoritmo de divisão longa (long division) dígito a dígito */
    char quociente[100000];
    int qk = 0;

    char resto[100000];
    int lr = 0;
    resto[0] = '\0';

    for (int i = 0; i < la; i++) {
        /* Acrescenta o próximo dígito ao resto */
        resto[lr++] = a[i];
        resto[lr] = '\0';

        /* Remove zeros à esquerda do resto */
        int inicio = 0;
        while (inicio < lr - 1 && resto[inicio] == '0') inicio++;
        if (inicio > 0) {
            int novo = lr - inicio;
            for (int x = 0; x < novo; x++) resto[x] = resto[inicio + x];
            lr = novo;
            resto[lr] = '\0';
        }

        /* Encontra quantas vezes b cabe no resto atual (0-9) */
        int digit = 0;
        while (compara_str(resto, lr, b, lb) >= 0) {
            lr = subtrai_buf(resto, lr, b, lb);
            digit++;
        }
        quociente[qk++] = digit + '0';
    }

    /* Remove zeros à esquerda do quociente */
    int inicio = 0;
    while (inicio < qk - 1 && quociente[inicio] == '0') inicio++;
    quociente[qk] = '\0';
    printf("%s\n", quociente + inicio);
}

int main() {
    char operacao[100], AI[100000], BI[100000];
    char A[40] = "SOMA", B[40] = "SUBTRACAO", C[40] = "MULTIPLICACAO", D[40] = "DIVISAO";

    if (scanf("%s %s %s", operacao, AI, BI) != 3) return 0;

    int k, combinou;

    k = 0; combinou = 1;
    while (A[k] != '\0' || operacao[k] != '\0') {
        if (operacao[k] != A[k]) { combinou = 0; break; }
        k++;
    }
    if (combinou == 1) { SOMA(AI, BI); return 0; }

    k = 0; combinou = 1;
    while (B[k] != '\0' || operacao[k] != '\0') {
        if (operacao[k] != B[k]) { combinou = 0; break; }
        k++;
    }
    if (combinou == 1) { SUBTRACAO(AI, BI); return 0; }

    k = 0; combinou = 1;
    while (C[k] != '\0' || operacao[k] != '\0') {
        if (operacao[k] != C[k]) { combinou = 0; break; }
        k++;
    }
    if (combinou == 1) { MULTIPLICACAO(AI, BI); return 0; }

    k = 0; combinou = 1;
    while (D[k] != '\0' || operacao[k] != '\0') {
        if (operacao[k] != D[k]) { combinou = 0; break; }
        k++;
    }
    if (combinou == 1) { DIVISAO(AI, BI); return 0; }

    return 0;
}
