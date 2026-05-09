#ifndef SISTEMA_DE_CADASTRO_ALUNOS_H
#define SISTEMA_DE_CADASTRO_ALUNOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Notas {
    float notaProva1;
    float notaProva2;
    float notaTrabalho;
} Notas;

typedef struct Aluno {
    int   matricula;
    char  nome[100];
    Notas notas;
    float media;
    char  status[20];
} Aluno;

void   inicializar(Aluno *al, int tam);
void   cadastrar(Aluno *al, int *total);
Aluno* buscar(Aluno *al, int total, int mat);
void   calcularMedia(Aluno *al);
void   definirStatus(Aluno *al);
void   darBonus(Aluno *al, float ponto);
void   imprimirBoletim(Aluno a);
void   listarTodos(Aluno *al, int total);
void   ordenar(Aluno *al, int total);
void   remover(Aluno *al, int *total, int mat);
void   atualizar(Aluno *al, int total, int mat);

#endif
