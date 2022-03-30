#include<stdio.h>
#include"matriz.h"

matriz_t Matriz_constroi(unsigned int tamanho[2], double * matriz){
    matriz_t me;
    int i, j;
    
    me.tam[0] = tamanho[0];
    me.tam[1] = tamanho[1];
   
    for(i=0; i<me.tam[0]*me.tam[1]; i++){
        me.mat[i] = matriz[i];
    }
    return me;
}

matriz_t Matriz_resize(matriz_t me, unsigned int tam_novo[2]){
    double * zeros; 
    int i, cont;

    for(i=0; i<tam_novo[0]*tam_novo[1]; i++){
        zeros[i] = 0;
    }

    matriz_t outro = Matriz_constroi(tam_novo, zeros);

    for(i=0, cont=0; i<outro.tam[0]*outro.tam[1]; i++){
        if(i%me.tam[1]==0){
            cont++;
            i+= outro.tam[1] - me.tam[1];
        }
        outro.mat[i] = me.mat[i-(cont*(outro.tam[1]-me.tam[1]))];
    }
    return outro;
}
/* a função cria um vetor maior preenchido com zeros, este vetor é preenchido com os valores antigos
a logica é que se pula o numero de posições correspondente a diferença de tamanho entre as linhas do novo
e do antigo vetor */

 
matriz_t Matriz_ones(unsigned int tamanho[2]){
    matriz_t me;
    int i;
    
    me.tam[0] = tamanho[0];
    me.tam[1] = tamanho[1];
    for(i=0; i<me.tam[0]*me.tam[1]; i++){
        me.mat[i] = 1;
    }
    return me;
}

matriz_t Matriz_identidade(unsigned int tamanho[2]){ // 5x5 10000 01000 00100 00010 00001
    double * zeros; 
    int i, cont;

    for(i=0; i<tamanho[0]*tamanho[1]; i++){
        zeros[i] = 0;
    }

    matriz_t me = Matriz_constroi(tamanho, zeros);

    me.mat[0] = 1;
    for(i=0, cont=1; i<me.tam[0]*me.tam[1]; i++){ // 100 010 001
        if(i%me.tam[1]==0){
            me.mat[i+cont] = 1;
            cont++;
        }
    }
    return me;
}

matriz_t Matriz_soma(matriz_t me, matriz_t outro){
    int i;

    matriz_t result = Matriz_ones(me.tam);

    for(i=0; i<me.tam[0]*me.tam[1]; i++){
        result.mat[i] = me.mat[i] + outro.mat[i];
    }
    return result;
}

matriz_t Matriz_subt(matriz_t me, matriz_t outro){
    int i;

    matriz_t result = Matriz_ones(me.tam);

    for(i=0; i<me.tam[0]*me.tam[1]; i++){
        result.mat[i] = me.mat[i] - outro.mat[i];
    }
    return result;
}

matriz_t Matriz_mult(matriz_t me, double valor){
    int i;

    for(i=0; i<me.tam[0]*me.tam[1]; i++){
        me.mat[i] *= valor;
    }
    return me;
}

matriz_t Matriz_div(matriz_t me, double valor){
    int i;

    for(i=0; i<me.tam[0]*me.tam[1]; i++){
        me.mat[i] /= valor;
    }
    return me;
}
/*
a11 a12 | b11 b12
a21 a22 | b21 b22

a11*b11+a12*b21 a11*b12+a12*b22
a21*b11+a22*b21 a21*b12+a22*b22
*/

//00 = 00a * 01a * 02a + 00b * 10 b * 20b

matriz_t Matriz_dot(matriz_t me, matriz_t outro){
    unsigned int tamanho[2] = {me.tam[0], outro.tam[1]};
    //Gambiarra a gente aceita
    double gambiarra1[me.tam[0]][me.tam[1]];
    double gambiarra2[outro.tam[0]][outro.tam[1]];
    double gambiarra_master[me.tam[0]][outro.tam[1]];
    int i,j,k=0, aux1, aux2;

    for(i=0; i<me.tam[0]; i++){
        for(j=0; j<me.tam[1]; j++){
            gambiarra1[i][j] = me.mat[k];
            k++;
        }
    }
    k=0;
    for(i=0; i<outro.tam[0]; i++){
        for(j=0; j<outro.tam[1]; j++){
            gambiarra2[i][j] = outro.mat[k];
            k++;
        }
    }

    for(i=0; i<me.tam[0]; i++){
        for(j=0; j<outro.tam[1]; j++){
            gambiarra_master[i][j] = 0;

            aux1 = 0;
            for(aux2=0; aux2<outro.tam[0]; aux2++){
                if(aux1<me.tam[1]){
                    gambiarra_master[i][j] += gambiarra1[i][aux1]*gambiarra2[aux2][j];
                    aux1++;
                }
            }
        }
    }

    matriz_t result = Matriz_ones(tamanho);
    k=0;
    for(i=0; i<me.tam[0]; i++){
        for(j=0; j<outro.tam[1]; j++){
            result.mat[k] = gambiarra_master[i][j];
            k++;
        }
    }
}

/*
Código antigo que por coincidencia eu (Daniel) estava fazendo
uma calculadora de matrizes quando comecei a aprender programacao
Não lembro como que funciona exatamente, como diria meu amigo Will: Confia
//Geração da Matriz C
	for(i=0;i<Aimax;i++){
		for(j=0;j<Bjmax;j++){
			C[i][j] = 0;
			
			//Cálculo da multiplicação
			aux1=0;
			for(aux2=0;aux2<Bimax;aux2++){
				while(aux1<Ajmax){
					
					C[i][j] += A[i][aux1]*B[aux2][j];
					aux1++;
					break;
				}
			}
			printf("%f || ",C[i][j]);
		}
		printf("\n");
	}
*/

matriz_t Matriz_transpor(matriz_t me){ // 123 456 321 654

matriz_t outro;
    
    outro.tam[0] = me.tam[1];
    outro.tam[1] = me.tam[0];
    

    for(i=0; i<me.tam[0]*me.tam[1]; i++){
        me.mat[i] = matriz[i];
    }
    return me;

}

matriz_t Matriz_transpor2(matriz_t me){}

matriz_t Matriz_reverse_hor(matriz_t me){} // 321 654 987 

matriz_t Matriz_reverse_vert(matriz_t me){} // 789 456 123

matriz_t Matriz_addl(matriz_t me){ // resize com uma linha a mais do que o me
unsigned int tamanho[2] = {me.tam[0], me.tam[1]+1};
matriz_t me = Matriz_resize(me, tamanho);

return me

} 

matriz_t Matriz_addc(matriz_t me){ // resize com uma coluna a mais

unsigned int tamanho[2] = {me.tam[0]+1, me.tam[1]};
matriz_t me = Matriz_resize(me, tamanho);

return me

} 