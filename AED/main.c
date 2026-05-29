#include "cadastro.h"

#define TAM 50

static void exibirMenu(void) {
    printf("\n------------------------------------\n");
    printf("   SISTEMA DE CADASTRO DE ALUNOS\n");
    printf("------------------------------------\n");
    printf("  1. Cadastrar aluno\n");
    printf("  2. Buscar aluno\n");
    printf("  3. Listar todos\n");
    printf("  4. Atualizar notas\n");
    printf("  5. Dar bonus a aluno\n");
    printf("  6. Remover aluno\n");
    printf("  7. Ordenar por media\n");
    printf("  0. Sair\n");
    printf("------------------------------------\n");
    printf("Opcao: ");
}

int main(void) {
    Aluno turma[TAM];
    int total = 0;
    int opcao;

    inicializar(turma, TAM);

    do {
        exibirMenu();
        if (scanf("%d", &opcao) != 1) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            printf("Opcao invalida.\n");
            continue;
        }
        getchar();

        switch (opcao) {

            case 1: {
                if (total >= TAM) {
                    printf("Cadastro cheio (max %d alunos).\n", TAM);
                    break;
                }
                cadastrar(turma, &total);
                break;
            }

            case 2: {
                int mat;
                printf("Matricula: ");
                scanf("%d", &mat);
                getchar();
                Aluno *a = buscar(turma, total, mat);
                if (a)
                    imprimirBoletim(*a);
                else
                    printf("Aluno nao encontrado.\n");
                break;
            }

            case 3: {
                listarTodos(turma, total);
                break;
            }

            case 4: {
                int mat;
                printf("Matricula: ");
                scanf("%d", &mat);
                getchar();
                atualizar(turma, total, mat);
                break;
            }

            case 5: {
                int mat;
                float bonus;
                printf("Matricula: ");
                scanf("%d", &mat);
                getchar();
                Aluno *a = buscar(turma, total, mat);
                if (!a) {
                    printf("Aluno nao encontrado.\n");
                    break;
                }
                printf("Pontos de bonus: ");
                scanf("%f", &bonus);
                getchar();
                darBonus(a, bonus);
                printf("Bonus aplicado. Nova media: %.2f  Status: %s\n",
                       a->media, a->status);
                break;
            }

            case 6: {
                int mat;
                printf("Matricula: ");
                scanf("%d", &mat);
                getchar();
                remover(turma, &total, mat);
                break;
            }

            case 7: {
                ordenar(turma, total);
                printf("Turma ordenada por media crescente.\n");
                listarTodos(turma, total);
                break;
            }

            case 0: {
                printf("Encerrando. Ate logo!\n");
                break;
            }

            default: {
                printf("Opcao invalida. Tente novamente.\n");
                break;
            }
        }

    } while (opcao != 0);

    return 0;
}
