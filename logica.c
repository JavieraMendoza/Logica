/*
 * FILE: logica.c
 *
 * AUTHOR: Alonso Maripi Vallejos & Javiera Mendoza Garrido
 *
 * LAST REVISED: Santiago de Chile, 07/05/2018
 *
 */
//REVISAR LAS LIBRERIAS, NO CREO QUE LAS USEMOS TODAS.
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

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
 * END Struct declaration.
 */

/*
 * Struct global declaration.
 */
struct Pnode*principalTop = NULL;
struct Pnode*ListopTop = NULL;
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

/*
 * Transform function
 */
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

/*
 * Stacks/Dynamic Array functions
 */
void aux_push(char add){//Agrega un elemento a la pila auxiliar.
	struct Anode* aux = malloc(sizeof(struct Anode));
	aux -> element = add;
	aux -> next = auxiliarTop;
	auxiliarTop = aux;
}

void prin_push(char add, int* mtx){//Agrega un elemento a la pila principal.
	struct Pnode* aux = malloc(sizeof(struct Pnode));
	aux -> element = add;
	aux -> matrix = mtx;
	aux -> next = principalTop;
	principalTop = aux;
}

void list_push(char add, int* mtx){//Agrega un elemento a la lista enlazada de atomos.
	struct Pnode* aux = malloc(sizeof(struct Pnode));
	aux -> element = add;
	aux -> matrix = mtx;
	aux -> next = ListopTop;
	ListopTop = aux;
}

void aux_pop(){//Saca y borra el primer elemento de la pila auxiliar.
	struct Anode *aux;
	aux = auxiliarTop;
	auxiliarTop = auxiliarTop -> next;
	free(aux);
}

void prin_pop(){//Saca y borra el primer elemento de la pila principal.
	struct Pnode *aux;
	aux = principalTop;
	principalTop = principalTop -> next;
	free(aux);
}

void list_pop(){//Saca y borra el primer elemento de la lista enlazada.
	struct Pnode *aux;
	aux = ListopTop;
	ListopTop = ListopTop -> next;
	free(aux);
}
/*
 * END Stacks/Dynamic Array functions
 */

int eval(int A, int B, char op){//Evalua dos valores de atomos(A y B) conforme a un operador logico(OP).

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
				else
					A = 0;

				int exc = A+B;

				if(exc == 2)
					return exc-1;
				return exc;
			}
		}
	}

}

int exist_op(char op){//Verifica si un atomo(op) existe en la lista enlazada.
	struct Pnode* aux;
	aux = ListopTop;
	while (aux != NULL) {
		if(aux -> element == op)
			return 1;
		aux = aux -> next;
	}
	return 0;
}

void log_operate(int *R, int *A, int*B, char op,int max){//Realiza la negacion del atomo(A) u opera los atomos(A y B) bajo un operador logico(op)

	if(op == '-'){
		for(int i = 0;i < max;i++)
			R[i] = eval(A[i],A[i],op);
	}
	else{
		for(int i = 0;i < max; i++)
			R[i] = eval(A[i],B[i],op);
	}
	prin_push('R',R);
}

int atom_cont(char **A, int C){//Cuenta los atomos distintos existentes en la expresion logica(A = argv).
	int cont = 0;
	int n = 0;
	char* atoms = calloc(24,sizeof(char));

	for(int i = 1;i < C;i++){

		if(!isOperador(A[i])){
			for(int j = 0;j < strlen(A[i]);j++){
				n = 0;
				if(isParenthesis(A[i][j]) == 0){

					for(int x = 0;x < cont;x++){
						if(atoms[x] == A[i][j])
							n = -1;
					}
					if(n != -1){
						atoms[cont] = A[i][j];
						cont++;
					}
				}
			}
		}
	}
	return cont;
}

/*
 * Main function.
 */
int main(int argc, char **argv) {

	if(argc < 2)
		Usage(argv[0]);
	else{
		int opCont = atom_cont(argv,argc);
		int cont = 2;
		int max = (int)pow(2,opCont);
		int *mtx;

		for(int i = 1;i < argc;i++){
			if(isOperador(argv[i])){//se buscan los operadores primero debido a que estos utilizan todo un elemento en el argumento y ademas son strings.
			//Se guarda el operador en la pila auxiliar
				aux_push(Transform(argv[i]));
			}
			else{
				for(int j = 0;j < strlen(argv[i]);j++){
					if(isParenthesis(argv[i][j]) == 1){//Se busca apertura de parentesis
						//Se procede a guardar el parentesis de apertura en la pila auxiliar.
						aux_push(argv[i][j]);
					}
					else{
						if(isParenthesis(argv[i][j]) == 2){//Se busca cierre de parentesis y se evalua lo que este en la pila principal conforme a la pila auxiliar.
							//NO guarda el parentesis de cierre, sino que ejecuta la funcion para vaciar la pila auxiliar en la pila principal, sin incluir el parentesis de apertura '('.
							char ope;
							int *lado_A;
							int *lado_B;

							while (auxiliarTop -> element != '(') {//Las operaciones se ejecutaran hasta que el elemento que se extraiga de la pila auxiliar sea un '('.
								if(auxiliarTop -> element == '-'){//En caso de que se detecte un operador de negacion
									mtx = calloc(max,sizeof(int));

									ope = auxiliarTop -> element;
									aux_pop();

									lado_B =  principalTop -> matrix;
									prin_pop();

									log_operate(mtx,lado_B,lado_B,ope,max);

								}
								else{//En cualquier otro caso(y, o e implica).
									mtx = calloc(max,sizeof(int));

									ope = auxiliarTop -> element;
									aux_pop();

									lado_B =  principalTop -> matrix;
									prin_pop();

									lado_A =  principalTop -> matrix;
									prin_pop();

									log_operate(mtx,lado_A,lado_B,ope,max);
								}
							}
							aux_pop();

						}
						else{// En otro caso el elemento es si o si un operando.
							//Se procede a guardar el atomo en la pila principal.
							int n1 = 0;
							int n2 = 0;

							if(!exist_op(argv[i][j])){//En caso de que el atomo encontrado en la expresion no se haya procesado antes.
								mtx = calloc(max,sizeof(int));

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
							cont = cont*2;

							list_push(argv[i][j],mtx);//El atomo se guarda en la lista enlazada.
							prin_push(argv[i][j],mtx);//EL atomo se agrega a la pila principal.
						}
						else{//En caso de que el atomo encontrado ya se haya procesado previamente.
							struct Pnode*aux;
							aux = ListopTop;
							while (aux != NULL) {//Se busca el atomo en la lista enlazada.
								if(aux -> element == argv[i][j])
									prin_push(argv[i][j],aux -> matrix);//Se agrega el atomo a la pila principal.
								aux = aux -> next;
							}
						}
					}
				}
			}
		}
	}
	int* test = principalTop -> matrix;//Se extrae el resultado, siendo el ultimo elemento de la pila.
	prin_pop();

	int sum = 0;

	for(int i = 0;i < max;i++)//Se suman los 1's o 0's que tengan los valores del resultado.
		sum = sum + test[i];

		if(sum == max)// si la suma da el largo de la lista -> solo habian 1 en el resultado, es TAUTOLOGIA.
			printf("\nTAUTOLOGIA\n\n");
		else{
			if(sum == 0)// si la suma da 0 -> solo habian 0 en el resultado, es CONTRADICCION.
				printf("\nCONTRADICCION\n\n");
			else
				printf("\nCONTINGENCIA\n\n");//En otro caso, es si o si CONTINGENCIA.
		}

		while(ListopTop != NULL)//Se vacia la lista enlazada.
			list_pop();
	}
}
