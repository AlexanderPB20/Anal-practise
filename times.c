/**
 *
 * Descripcion: Implementation of time measurement functions
 *
 * Fichero: times.c
 * Autor: Carlos Aguirre Maeso
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include "times.h"
#include "sorting.h"
#include "permutations.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/***************************************************/
/* Function: average_sorting_time Date:            */
/***************************************************/
short average_sorting_time(pfunc_sort metodo, int n_perms, int N, PTIME_AA ptime)
{
    int** permutations;
    int total_ob;
    double total_time;
    clock_t start, end;
    int i, j, k;
    int* current_perm;
    int ob_count;
    
    /* Validar parámetros */
    if (!metodo || n_perms <= 0 || N <= 0 || !ptime) {
        return ERR;
    }
    
    /* Generar permutaciones */
    permutations = generate_permutations(n_perms, N);
    if (!permutations) {
        return ERR;
    }
    
    /* Inicializar variables */
    total_ob = 0;
    total_time = 0.0;
    ptime->min_ob = -1;
    ptime->max_ob = -1;
    ptime->n_elems = n_perms;
    ptime->N = N;
    
    /* Procesar cada permutación */
    i = 0;
    while (i < n_perms) {
        current_perm = (int*)malloc(N * sizeof(int));
        if (!current_perm) {
            /* Liberar memoria y salir */
            for (j = 0; j < n_perms; j++) {
                free(permutations[j]);
            }
            free(permutations);
            return ERR;
        }
        
        /* Copiar permutación */
        k = 0;
        while (k < N) {
            current_perm[k] = permutations[i][k];
            k++;
        } 
        /* Medir tiempo y OB */
        start = clock();
        ob_count = metodo(current_perm, 0, N-1);
        end = clock();
        
        if (ob_count == ERR) {
            free(current_perm);
            for (j = 0; j < n_perms; j++) {
                free(permutations[j]);
            }
            free(permutations);
            return ERR;
        }
        
        total_time += ((double)(end - start)) / CLOCKS_PER_SEC;
        total_ob += ob_count;
        
        /* Actualizar min y max OB */
        if (ptime->min_ob == -1 || ob_count < ptime->min_ob) {
            ptime->min_ob = ob_count;
        }
        if (ob_count > ptime->max_ob) {
            ptime->max_ob = ob_count;
        }
        
        free(current_perm);
        i++;
    }
    /* Calcular promedios */
    ptime->time = total_time / n_perms;
    ptime->average_ob = (double)total_ob / n_perms;
    
    /* Liberar memoria */
    j = 0;
    while (j < n_perms) {
        free(permutations[j]);
        j++;
    }
    free(permutations);
    
    return OK;
}

/***************************************************/
/* Function: generate_sorting_times Date:          */
/***************************************************/
short generate_sorting_times(pfunc_sort method, char* file, 
                                int num_min, int num_max, 
                                int incr, int n_perms)
{
    PTIME_AA times;
    int n_times;
    int current_size;
    int i;
    short result;
    
    /* Validar parámetros */
    if (!method || !file || num_min <= 0 || num_max < num_min || incr <= 0 || n_perms <= 0) {
        return ERR;
    }
    
    n_times = ((num_max - num_min) / incr) + 1;
    times = (PTIME_AA)malloc(n_times * sizeof(TIME_AA));
    if (!times) {
        return ERR;
    }
    
    current_size = num_min;
    i = 0;
    while (i < n_times) {
        if (average_sorting_time(method, n_perms, current_size, &times[i]) == ERR) {
            free(times);
            return ERR;
        }
        current_size += incr;
        i++;
    }
    
    result = save_time_table(file, times, n_times);
    free(times);
    return result;
}

/***************************************************/
/* Function: save_time_table Date:                 */
/***************************************************/
short save_time_table(char* file, PTIME_AA time, int n_times)
{
    FILE* f;
    int i;
    
    if (!file || !time || n_times <= 0) {
        return ERR;
    }
    
    f = fopen(file, "w");
    if (!f) {
        return ERR;
    }
    
    fprintf(f, "Size\tTime\tAvg_OB\tMin_OB\tMax_OB\n");
    i = 0;
    while (i < n_times) {
        fprintf(f, "%d\t%.6f\t%.2f\t%d\t%d\n", 
                time[i].N, time[i].time, time[i].average_ob, 
                time[i].min_ob, time[i].max_ob);
        i++;
    }
    
    fclose(f);
    return OK;
}