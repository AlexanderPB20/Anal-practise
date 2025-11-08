/**
 *
 * Descripcion: Implementation of function that generate permutations
 *
 * File: permutations.c
 * Autor: Carlos Aguirre
 * Version: 1.1
 * Fecha: 21-09-2019
 *
 */

#include "permutations.h"
#include <stdlib.h>

/***************************************************/
/* Function: random_num Date:                      */
/***************************************************/
int random_num(int inf, int sup)
{
    int range;
    
    if (inf > sup) {
        return ERR;
    }
    
    range = sup - inf + 1;
    return inf + (rand() % range);
}

/***************************************************/
/* Function: generate_perm Date:                   */
/***************************************************/
int* generate_perm(int N)
{
    int* perm;
    int i, j;
    int temp;
    
    if (N <= 0) {
        return NULL;
    }
    
    perm = (int*)malloc(N * sizeof(int));
    if (!perm) {
        return NULL;
    }
    
    /* Inicializar permutación */
    for (i = 0; i < N; i++) {
        perm[i] = i + 1;
    }
    for (i = 0; i < N - 1; i++) {
        j = random_num(i, N - 1);
        
        /* Intercambiar elementos */
        temp = perm[i];
        perm[i] = perm[j];
        perm[j] = temp;
    }
    
    return perm;
}

/***************************************************/
/* Function: generate_permutations Date:           */
/***************************************************/
int** generate_permutations(int n_perms, int N)
{
    int** perms;
    int i, j;
    
    if (n_perms <= 0 || N <= 0) {
        return NULL;
    }
    
    perms = (int**)malloc(n_perms * sizeof(int*));
    if (!perms) {
        return NULL;
    }
    
    i = 0;
    while (i < n_perms) {
        perms[i] = generate_perm(N);
        
        if (!perms[i]) {
            /* Liberar memoria en caso de error */
            for (j = 0; j < i; j++) {
                free(perms[j]);
            }
            free(perms);
            return NULL;
        }
        i++;
    }
    
    return perms;
}