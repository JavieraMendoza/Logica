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
struct Pnode{ //Principal Stack node declaration.
		char element;
		int * matrix;
		struct Pnode *next;
};

struct Anode{ //Auxiliar Stack node declaration.
		char element;
		struct Anode *next;
};
/*
 * End declaration.
 */

struct Pnode*principalTop = NULL;
struct Anode*auxiliarTop = NULL;

/*
 * Usage function.
 */
void Usage(char *message) {//Message that indicates how execute the program.

		printf("\n********* Usage *********\n\n");
		printf(" In Terminal : %s S1 S2 S3 ... Sn \n\n",message);
		printf(" Example: %s '('p \\land q')' \\rightarrow p \n\n",message);
		printf("  - {S1 S2 S3 ... Sn}: A logical expression to evaluate.\n\n");
		printf("  - Logical operators: \\land, \\lor, \\rigtharrow, \\neg  \n\n");
		printf("\n********* Usage *********\n\n");
}

/*
 * isOperator function
 */
int isOperador(char* op){//La funcion busca si el caracter leido es uno de los 4 operadores definidos.
		if(strcmp(op,"land") == 0)
				return 1;
		else{
				if(strcmp(op,"lor") == 0)
						return 1;
				else{
						if(strcmp(op,"neg") == 0)
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

char Transform(char* op){
	if(strcmp(op,"land") == 0)
			return '*';
	else{
			if(strcmp(op,"lor") == 0)
					return '+';
			else{
					if(strcmp(op,"neg") == 0)
							return '-';
					else{
							if(strcmp(op,"rightarrow") == 0)
									return '_';
					}
			}
	}
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

void aux_push(char add){
		struct Anode* aux = malloc(sizeof(struct Anode));
		aux -> element = add;
		aux -> next = auxiliarTop;
		auxiliarTop = aux;
}

void prin_push(char add, int* mtx){
		struct Pnode* aux = malloc(sizeof(struct Pnode));
		aux -> element = add;
		aux -> matrix = mtx;
		aux -> next = principalTop;
		principalTop = aux;
}

void aux_pop(){
		if(auxiliarTop ==NULL)
				printf("ERROR: EMPTY STACK!!!");
		else{
				struct Anode *aux;
				aux = auxiliarTop;
				auxiliarTop = auxiliarTop -> next;
				free(aux);
		}
}

void prin_pop(){
		if(principalTop ==NULL)
				printf("ERROR: EMPTY STACK!!!");
		else{
				struct Pnode *aux;
				aux = principalTop;
				principalTop = principalTop -> next;
				free(aux);
		}
}


///RECORDAR: BORRAR ESTAS FUNCIONES.
void aux_show(){
		struct Anode* aux;
		aux = auxiliarTop;
		while (aux != NULL) {
				printf("PilaAux : %c\n",aux -> element);
				aux = aux -> next;
		}
}

void prin_show(){
		struct Pnode* aux;
		aux = principalTop;
		while (aux != NULL) {
				printf("PilaPrin : %c\n",aux -> element);
				aux = aux -> next;
		}
}
/// FIN RECORDAR.

int eval(int A, int B, char op){

	if(op == '*')//Operacion 'land'
		return A*B;
	else{
		if(op == '+'){//Operacion 'lor'
			int exc = A+B;

			if(exc == 2)
				return exc-1;
			return exc;
		}
		else{
			if(op == '-'){//Operacion 'neg'
				if(A == 0)
					return 1;
				return 0;
			}
			else{//Operacion 'rightarrow' logico.
				if(A == 0)
					A = 1;
				A = 0;

				int exc = A+B;

				if(exc == 2)
					return exc-1;
				return exc;
			}
		}
	}

}

int exist_op(char *op_list, char op, int cont){
	for(int i = 0;i < cont; i++){
		if(op_list[i] == op)
			return 1;
	}
	return 0;
}

void log_operate(int *R, int *A, int*B, char op){

	int n = 0;

	if(op == '-'){
		for(int i = 0;A[i] != 5;i++){
				R[n] = eval(A[i],A[i],op);
				n++;
		}
	}
	else{
		for(int i = 0;A[i] != 5; i++){
					R[n] = eval(A[i],B[i],op);
					n++;
		}
	}
	R[n] = 5;
	prin_push('R',R);
}

int atom_cont(char **A, int C){
	int cont = 0;

	char* atoms = calloc(24,sizeof(char));

	for(int i = 1;i < C;i++){
		if(!isOperador(A[i])){
			for(int j = 0;j < strlen(A[i]);j++){
				if(isParenthesis(A[i][j]) == 0)
					if(!exist_op(atoms,A[i][j],cont)){
						atoms[cont] = A[i][j];
						cont++;
				}
			}
		}
	}
	return cont;
}

/*
 * Main function.
 */
int main(int argc, char **argv) {//RECORDAR QUE SE ASUME QUE LA EXPRESION LOGICA ESTA BIEN ESCRITA (ES CORRECTA).

		if(argc < 2)
				Usage(argv[0]);
		else{
				int opCont = atom_cont(argv,argc);
				int cont = 2;
				int max = (int)pow(2,opCont);
				int *mtx = calloc(max,sizeof(int));

				for(int i = 1;i < argc;i++){
						if(isOperador(argv[i]))//se buscan los operadores primero debido a que estos utilizan todo un elemento en el argumento y ademas son strings.
								//Se guarda el operador en la pila auxiliar
								aux_push(Transform(argv[i]));
						else{
								for(int j = 0;j < strlen(argv[i]);j++){
										if(isParenthesis(argv[i][j]) == 1)//Se busca apertura de parentesis
												//Se procede a guardar el parentesis de apertura en la pila auxiliar.
												aux_push(argv[i][j]);
										else{
												if(isParenthesis(argv[i][j]) == 2){//Se busca cierre de parentesis y se evalua lo que este en la pila principal conforme a la pila auxiliar.
														//NO guarda el parentesis de cierre, sino que ejecuta la funcion para vaciar la pila auxiliar en la pila principal, sin incluir el parentesis de apertura '('.

														char ope;
														int *lado_A;
														int *lado_B;


														while (auxiliarTop -> element != '(') {
															ope = auxiliarTop -> element;
															aux_pop();

															if(ope == '-'){
																lado_B =  principalTop -> matrix;
																prin_pop();

																log_operate(mtx,lado_B,lado_B,ope);

															}
															else{
																lado_B =  principalTop -> matrix;
																prin_pop();
																lado_A =  principalTop -> matrix;
																prin_pop();

																log_operate(mtx,lado_A,lado_B,ope);
															}
														}
														aux_pop();

												}
												else{// En otro caso el elemento es si o si un operando.
														//Se procede a guardar el atomo en la pila principal.
														int n1 = 0;
														int n2 = 0;

														for(int i = 0;i < max;i++){

															if(n1 < max/cont){
																mtx[i] = 0;
																n1++;
															}
															else{
																if(n2 < max/cont){
																	mtx[i] = 1;
																	n2++;
																}
																if(n1 == max/cont && n2 == max/cont){

																	n1 = 0;
																	n2 = 0;
																}
															}
														}
														mtx[max] = 5;
														cont = cont*2;
														/*
														for(int i = 0;mtx[i] != 5;i++)
															printf("%d\n", mtx[i]);

														printf("\n");
														*/
														prin_push(argv[i][j],mtx);
												}
										}
								}
						}
				}
				//Insertar Codigo aqui
				//aux_show();
				//prin_show();

				int* test = principalTop -> matrix;

				for(int i = 0;test[i] != 5;i++)
					printf("%d\n", test[i]);


		}

}
