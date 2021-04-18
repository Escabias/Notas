#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define CHAR_SIZE sizeof(char)
#define CHAR_SIZE_2 sizeof(char*)
#define TRUE 1
#define FALSE 0
#define SUCCESS 0
#define ERROR -1

int numero = 15; // 0x1000 -> 15
char caracter = 'c'; // 0x1004 -> 'c' / 99
char *string = "Hola Patricia";
            //  ^

struct notas {
    char *nombre;
    int nNotas;
    char **notas; // 0x1000 => 0x8000 -> P
};

void escribeNota(char * nota, int tamNota, struct notas *libroNotas) {
    int lastIndex = libroNotas->nNotas;
    libroNotas->nNotas++;
    int tam = tamNota*CHAR_SIZE;
    char *nuevaNota = (char *)malloc(tam);
    strncpy(nuevaNota, nota, tam);
    if (libroNotas->notas == NULL) {
        libroNotas->notas = (char **)malloc(1*CHAR_SIZE_2);
    } else {
        libroNotas->notas = (char **)realloc(libroNotas->notas,libroNotas->nNotas*CHAR_SIZE_2);
    }
    libroNotas->notas[lastIndex] = nuevaNota;
}

char *leeUltimaNota(struct notas *libroNotas) {
    return libroNotas->notas[libroNotas->nNotas-1];
}

void borrarNota(int index, struct notas *libroNotas) {
    int error = FALSE;
    if (0 > index > libroNotas->nNotas -1) {
        error = TRUE;
        printf("Error, no puedes borrar una nota que no existe.\n");
    }
    if (libroNotas->notas != NULL && !error) {
        int nNotas = libroNotas->nNotas;
        char **seQuedan = (char **)malloc((nNotas-1)*CHAR_SIZE_2);
        for(int i = 0; i < nNotas; i++) {
            if (i != index) {
                seQuedan[i] = (char *)malloc(strlen(libroNotas->notas[i])*CHAR_SIZE);
                strcpy(seQuedan[i], libroNotas->notas[i]);
            }
            free(libroNotas->notas[i]);
        }
        free(libroNotas->notas);
        libroNotas->nNotas--;
        if (libroNotas->nNotas == 0) {
            libroNotas->notas = NULL;
            printf("AVISO! Libro de notas %s vacio!\n", libroNotas->nombre);
        } else {
            libroNotas->notas = seQuedan;
        }
        printf("Nota borrada.\n");
    } else {
        printf("No hay ninguna nota que borrar.\n");
    }
}

void showNotas(struct notas *libroNotas) {
    printf("Mostrando todas las notas...\n");
    int k = libroNotas->nNotas;
    int index = 0;
    while (k > 0) {
        char *nota = libroNotas->notas[index];
        index++;
        k--;
        printf("Nota numero %d: %s \n", index, nota);
    }
    printf("No hay mas notas para el libro \"%s\"\n", libroNotas->nombre);
}

int main(int argc, char *argv[]) {
    printf("Iniciando prueba del sistema de notas...\n");
    struct notas miLibroNotas = {"Super notas", 0, NULL};

    //borrarNota(-1, &miLibroNotas);

    char *nota1 = "Mi primera nota";
    int tamNota1 = strlen(nota1);
    escribeNota(nota1, tamNota1, &miLibroNotas);

    char *nota2 = "Mi segunda nota";
    int tamNota2 = strlen(nota2);
    escribeNota(nota2, tamNota2, &miLibroNotas);
    
    showNotas(&miLibroNotas);

    printf("La ultima nota aniadida es \n-> %s\n", leeUltimaNota(&miLibroNotas));

    char *nota3 = "Mi tercera nota";
    int tamNota3 = strlen(nota3);
    escribeNota(nota3, tamNota3, &miLibroNotas);

    showNotas(&miLibroNotas);

    borrarNota(1, &miLibroNotas);

    showNotas(&miLibroNotas);

    exit(SUCCESS);
}