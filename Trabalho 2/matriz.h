#ifndef Matriz_H
#define Matriz_H

typedef struct matriz_st matriz_t;
struct matriz_st{
    unsigned int tam[2]; 
    double * mat;      
};

matriz_t Matriz_constroi(unsigned int tamanho[2], double * matriz);

matriz_t Matriz_resize(matriz_t me, unsigned int tam_novo[2]);

matriz_t Matriz_ones(unsigned int tamanho[2]);

matriz_t Matriz_identidade(unsigned int tamanho[2]);

matriz_t Matriz_soma(matriz_t me, matriz_t outro);

matriz_t Matriz_subt(matriz_t me, matriz_t outro);

matriz_t Matriz_mult(matriz_t me, double valor);

matriz_t Matriz_div(matriz_t me, double valor);

matriz_t Matriz_dot(matriz_t me, matriz_t outro);

matriz_t Matriz_transpor(matriz_t me);

matriz_t Matriz_transpor2(matriz_t me);

matriz_t Matriz_reverse_hor(matriz_t me);

matriz_t Matriz_reverse_vert(matriz_t me);

matriz_t Matriz_addl(matriz_t me);

matriz_t Matriz_addc(matriz_t me);

/*
soma
subtração
resize
ones
identidade
multi esc
mult vet
transpor
transpor diagonal 2
trocar linhas / reverse horizontal
trocar colunas / reverse vertical
acrescentar linhas
acresctar colunas
*/

#endif /* Matriz_H */