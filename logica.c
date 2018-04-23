/*
 * FILE: logica.c
 *
 * AUTHOR: Alonso Maripi Vallejos & Javiera Mendoza Garrido
 *
 * LAST REVISED: Santiago de Chile, 21/04/2018
 *
 */
//REVISAR LAS LIBRERIAS, NO CREO QUE LAS USEMOS TODAS.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

/*
 * Struct declaration
 */
struct node{ //Stack node declaration.
		char* element;
		struct node *next;
};
/*
 * End declaration.
 */

struct node*principalTop = NULL;
struct node*auxiliarTop = NULL;

/*
 * Usage function.
 */
void Usage(char *message) {//Message that indicates how execute the program.

		printf("\n********* Usage *********\n\n");
		printf(" In Terminal : %s S1 S2 S3 ... Sn \n\n",message);
		printf(" Example: %s (p \\and q) \\rightarrow p \n\n",message);
		printf("  - {S1 S2 S3 ... Sn}: A logical expression to evaluate.\n\n");
		printf("\n********* Usage *********\n\n");
}

/*
 * isOperator function
 */
int isOperador(char* op){//La funcion busca si el caracter leido es uno de los 4 operadores definidos.
		if(strcmp(op,"and") == 0)
				return 1;
		else{
				if(strcmp(op,"or") == 0)
						return 1;
				else{
						if(strcmp(op,"not") == 0)
								return 1;
						else{
								if(strcmp(op,"rightarrow") == 0)
										return 1;
								else
										return 0;
						}
				}
		}//OJO!!!: Al compilar el compilador remueve automaticamente los backslash de los argumentos.
}

/*
 * isParenthesis function
 */
int isParenthesis(char op){//La funcion busca si el caracter leido es una apertura de parentesis o una clausura de parentesis.
		if(op == '(')
				return 1;
		else{
				if(op == ')')
						return 2;
				else
						return 0;
		}
}

void push(char* add){
		struct node* aux = malloc(sizeof(struct node));
		aux -> element = add;
		aux -> next = auxiliarTop;
		auxiliarTop = aux;
}

void pop(){
		if(auxiliarTop ==NULL)
				printf("ERROR: EMPTY STACK!!!");
		else{
				struct node *aux;
				aux = auxiliarTop;
				auxiliarTop = auxiliarTop -> next;
				free(aux);
		}
}

void show(){
		struct node* aux;
		aux = auxiliarTop;
		while (aux != NULL) {
				printf("value : %s\n",aux -> element);
				aux = aux -> next;
		}
}

/*
 * Main function.
 */
int main(int argc, char **argv) {//RECORDAR QUE SE ASUME QUE LA EXPRESION LOGICA ESTA BIEN ESCRITA (ES CORRECTA).

		if(argc < 2)
				Usage(argv[0]);
		else{
				for(int i = 1;i < argc;i++){
						//printf("%s\n", argv[i]);
						if(isOperador(argv[i])){ //se buscan los operadores primero debido a que estos utilizan todo un elemento en el argumento y ademas son strings.
								//Se guarda el operador en la pila auxiliar
								printf("Operador: %s \n",argv[i] );
						}
						else{
								for(int j = 0;j < strlen(argv[i]);j++){
										if(isParenthesis(argv[i][j]) == 1){//Se busca apertura de parentesis
												//Se procede a guardar el parentesis de apertura en la pila auxiliar.
												printf("%c\n",argv[i][j]);
										}
										else{
												if(isParenthesis(argv[i][j]) == 2){//Se busca cierre de parentesis
														//NO guarda el parentesis de cierre, sino que ejecuta la funcion para vaciar la pila auxiliar en la pila principal, sin incluir el parentesis de apertura '('.
														printf("%c\n",argv[i][j]);
												}
												else{// En otro caso el elemento es si o si un operando.
														//Se procede a guardar el operando en la pila principal.
														printf("Operando: %c\n",argv[i][j]);
												}
										}
								}
						}
				}
			/*
				char * logica, *sep;
				char save[10];
				int n ;
				logica=argv[1];
				strcpy(save,logica);
				n=strlen(logica);
				for(int i=0;i<n;i=i+1){
						if(isalpha(save[i]))//isalpha(...) verifica si una variable es alfabetica, Sirve para mas adelante para determinar los elementos que van para la pila como operadores u operandos.
								printf(" deberia ir la pila de mierda o k \n");
				}
			*/
				//esta maloooo, tengo una idea voy a pensarla bien y te comento.
				//sep=strtok(save,"~");

				//Insertar Codigo aqui
		}

}
