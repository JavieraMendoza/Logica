/*
 * FILE: T1.c
 *
 * AUTHOR: Alonso Maripi Vallejos & Javiera Mendoza Garrido
 *
 * LAST REVISED: Santiago de Chile, 16/04/2018
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <limits.h>
#include <string.h>
#include <ctype.h>

void Usage (char *message);

/*
 * Main function.
 */
int main(int argc, char **argv) {

    if(argc < 2)
        Usage(argv[0]);
    else{
        char * logica, *sep;
        char save[10];
        int n ;
        logica=argv[1];
        strcpy(save,logica);
        n=strlen(logica);
        for(int i=0;i<n;i=i+1){
            if(isalpha(save[i]))
                printf(" deberia ir la pila de mierda o k \n");
        
        }
        //esta maloooo, tengo una idea voy a pensarla bien y te comento.
        //sep=strtok(save,"~");
    
        //Insertar Codigo aqui 
    }

}

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