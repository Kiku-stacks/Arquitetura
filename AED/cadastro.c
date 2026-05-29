#include "cadastro.h"

void inicializar(Aluno *al, int tam) {
    int i;
    for (i = 0; i < tam; i++) {
        al[i].matricula          = 0;
        al[i].nome[0]            = '\0';
        al[i].notas.notaProva1   = 0.0f;
        al[i].notas.notaProva2   = 0.0f;
        al[i].notas.notaTrabalho = 0.0f;
        al[i].media              = 0.0f;
        strcpy(al[i].status, "");
    }
}

void cadastrar(Aluno *al, int *total) {
    Aluno *a = &al[*total];

    printf("\n--- Cadastro de Aluno ---\n");
    printf("Matricula: ");
    scanf("%d", &a->matricula);
    getchar();

    printf("Nome: ");
    fgets(a->nome, sizeof(a->nome), stdin);
    a->nome[strcspn(a->nome, "\n")] = '\0';

    printf("Nota Prova 1 (0-10): ");
    scanf("%f", &a->notas.notaProva1);

    printf("Nota Prova 2 (0-10): ");
    scanf("%f", &a->notas.notaProva2);

    printf("Nota Trabalho (0-10): ");
    scanf("%f", &a->notas.notaTrabalho);

    calcularMedia(a);
    definirStatus(a);

    (*total)++;
    printf("Aluno cadastrado com sucesso!\n");
}

Aluno* buscar(Aluno *al, int total, int mat) {
    int i;
    for (i = 0; i < total; i++) {
        if (al[i].matricula == mat)
            return &al[i];
    }
    return NULL;
}

void calcularMedia(Aluno *al) {
    al->media = (al->notas.notaProva1   * 0.4f)
              + (al->notas.notaProva2   * 0.4f)
              + (al->notas.notaTrabalho * 0.2f);
}

void definirStatus(Aluno *al) {
    if (al->media >= 7.0f)
        strcpy(al->status, "Aprovado");
    else if (al->media >= 5.0f)
        strcpy(al->status, "Recuperacao");
    else
        strcpy(al->status, "Reprovado");
}

void darBonus(Aluno *al, float ponto) {
    al->media += ponto;
    if (al->media > 10.0f)
        al->media = 10.0f;
    definirStatus(al);
}

void imprimirBoletim(Aluno a) {
    printf("\n--- BOLETIM ---\n");
    printf("Matricula : %d\n",   a.matricula);
    printf("Nome      : %s\n",   a.nome);
    printf("Prova 1   : %.2f\n", a.notas.notaProva1);
    printf("Prova 2   : %.2f\n", a.notas.notaProva2);
    printf("Trabalho  : %.2f\n", a.notas.notaTrabalho);
    printf("Media     : %.2f\n", a.media);
    printf("Status    : %s\n",   a.status);
    printf("---------------\n");
}

void listarTodos(Aluno *al, int total) {
    int i;
    if (total == 0) {
        printf("\nNenhum aluno cadastrado.\n");
        return;
    }
    for (i = 0; i < total; i++)
        imprimirBoletim(al[i]);
}

void ordenar(Aluno *al, int total) {
    int i, j, minIdx;
    Aluno tmp;
    for (i = 0; i < total - 1; i++) {
        minIdx = i;
        for (j = i + 1; j < total; j++) {
            if (al[j].media < al[minIdx].media)
                minIdx = j;
        }
        if (minIdx != i) {
            tmp        = al[i];
            al[i]      = al[minIdx];
            al[minIdx] = tmp;
        }
    }
}

void remover(Aluno *al, int *total, int mat) {
    int i, idx = -1;
    for (i = 0; i < *total; i++) {
        if (al[i].matricula == mat) {
            idx = i;
            break;
        }
    }
    if (idx == -1) {
        printf("Aluno com matricula %d nao encontrado.\n", mat);
        return;
    }
    for (i = idx; i < *total - 1; i++)
        al[i] = al[i + 1];
    (*total)--;
    printf("Aluno removido com sucesso.\n");
}

void atualizar(Aluno *al, int total, int mat) {
    Aluno *a = buscar(al, total, mat);
    if (!a) {
        printf("Aluno com matricula %d nao encontrado.\n", mat);
        return;
    }
    printf("\n--- Atualizacao de Notas (matricula %d) ---\n", mat);
    printf("Nova Nota Prova 1 (0-10): ");
    scanf("%f", &a->notas.notaProva1);

    printf("Nova Nota Prova 2 (0-10): ");
    scanf("%f", &a->notas.notaProva2);

    printf("Nova Nota Trabalho (0-10): ");
    scanf("%f", &a->notas.notaTrabalho);

    calcularMedia(a);
    definirStatus(a);
    printf("Notas atualizadas com sucesso!\n");
}
