/**
 *
 * Descripcion: Implementation of sorting functions
 *
 * Fichero: sorting.c
 * Autor: Carlos Aguirre
 * Version: 1.0
 * Fecha: 16-09-2019
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "sorting.h"

/***************************************************/
/* Function: InsertSort       */
/***************************************************/
int InsertSort(int* array, int ip, int iu)
{
    int i, j, key;
    int comparisons;
    
    if (array == NULL || ip < 0 || iu < ip) {
        return ERR;
    }
    
    comparisons = 0;
    i = ip + 1;
    while (i <= iu) {
        key = array[i];
        j = i - 1;
        
        /* Mover elementos mayores que la clave una posición hacia adelante*/
        while (j >= ip && array[j] > key) {
            array[j + 1] = array[j];
            j--;
            comparisons++; 
        }
        
        /*Comparación extra cuando elciclo existe*/
        if (j >= ip) {
            comparisons++;
        }
        
        array[j + 1] = key;
        i++;
    }
    
    return comparisons;
}

/***************************************************/
/* Function: BubbleSort       */
/***************************************************/
int BubbleSort(int* array, int ip, int iu)
{
    int i, j, temp;
    int comparisons;
    
    if (array == NULL || ip < 0 || iu < ip) {
        return ERR;
    }
    
    comparisons = 0;
    i = ip;
    while (i < iu) {
        j = ip;
        while (j < iu - (i - ip)) {
            comparisons++;
            if (array[j] > array[j + 1]) {
                temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
            j++;
        }
        i++;
    }
    
    return comparisons;
}


int mergesort (int* tabla, int ip, int iu)
{
    int imedio;
    int total_comp = 0;
    int comp;
    
    if (tabla == NULL || ip < 0 || iu < ip) {
        return ERR;
    }

    /* Caso base */
    if (ip < iu) {
        
        imedio = ip + (iu - ip) / 2; 

        
        comp = mergesort(tabla, ip, imedio);
        if (comp == ERR) return ERR;
        total_comp += comp;

        comp = mergesort(tabla, imedio + 1, iu);
        if (comp == ERR) return ERR;
        total_comp += comp;

        
        comp = merge(tabla, ip, iu, imedio);
        if (comp == ERR) return ERR;
        total_comp += comp;
    }

    return total_comp;
}



int merge(int* tabla, int ip, int iu, int imedio)
{
    int i, j, k;
    int *temp;
    int comp = 0;
    
    if (tabla == NULL || ip < 0 || iu < ip || imedio < ip || imedio >= iu) {
        return ERR;
    }

    /* Crear tabla temporal*/
    temp = (int*)malloc((iu - ip + 1) * sizeof(int));
    if (temp == NULL) {
        return ERR;
    }
    
    i = ip;        
    j = imedio + 1;
    k = 0;         

    /* Combinar: compara y copia a 'temp' */
    while (i <= imedio && j <= iu) {
        comp++; /* O.B.: la comparación de elementos */
        if (tabla[i] <= tabla[j]) {
            temp[k++] = tabla[i++];
        } else {
            temp[k++] = tabla[j++];
        }
    }

    /* Copiar elementos restantes de la primera mitad */
    while (i <= imedio) {
        temp[k++] = tabla[i++];
    }

    /*Copiar elementos restantes de la segunda mitad */
    while (j <= iu) {
        temp[k++] = tabla[j++];
    }

    /* Copiar 'temp' de vuelta a la 'tabla' original */
    for (i = 0; i < (iu - ip + 1); i++) {
        tabla[ip + i] = temp[i];
    }
    
    free(temp);
    
    return comp;
}

/*ej3 */
int median(int *tabla, int ip, int iu, int *pos)
{
    if (tabla == NULL || pos == NULL || ip < 0 || iu < ip) {
        return ERR;
    }
    
    /* El pivote es el primer elemento */
    *pos = ip;
    
    /* Devuelve 0 OBs */
    return 0; 
}

int median_avg(int *tabla, int ip, int iu, int *pos)
{
    if (tabla == NULL || pos == NULL || ip < 0 || iu < ip) {
        return ERR;
    }
    
    /* El pivote es el elemento en la posición media */
    *pos = (ip + iu) / 2;
    
    /* Devuelve 0 OBs */
    return 0;
}

int median_stat(int *tabla, int ip, int iu, int *pos)
{
    int imedio;
    int val_ip, val_iu, val_imedio;
    int comparisons = 0;
    
    if (tabla == NULL || pos == NULL || ip < 0 || iu < ip) {
        return ERR;
    }
    
    imedio = (ip + iu) / 2;
    val_ip = tabla[ip];
    val_iu = tabla[iu];
    val_imedio = tabla[imedio];
    
    /* Comparar los tres valores para encontrar la mediana */
    /* Comparación 1: ip vs iu */
    comparisons++;
    if (val_ip <= val_iu) {
        /* Comparación 2: ip vs imedio */
        comparisons++;
        if (val_imedio <= val_ip) {
            /* ip es la mediana */
            *pos = ip;
        } else {
            /* Comparación 3: imedio vs iu */
            comparisons++;
            if (val_imedio <= val_iu) {
                /* imedio es la mediana */
                *pos = imedio;
            } else {
                /* iu es la mediana */
                *pos = iu;
            }
        }
    } else {
        /* Comparación 2: ip vs imedio */
        comparisons++;
        if (val_imedio <= val_iu) {
            /* iu es la mediana */
            *pos = iu;
        } else {
            /* Comparación 3: imedio vs ip */
            comparisons++;
            if (val_imedio <= val_ip) {
                /* imedio es la mediana */
                *pos = imedio;
            } else {
                /* ip es la mediana */
                *pos = ip;
            }
        }
    }
    
    return comparisons;
}

int partition (int* tabla, int ip, int iu, int *pos)
{
    int piv_index, piv_value, temp;
    int i, j;
    int comparisons = 0;
    int median_obs;

    if (tabla == NULL || pos == NULL || ip < 0 || iu < ip) {
        return ERR;
    }

    /* Llama a la función median para obtener la posición del pivote */
    /* Para usar median_avg o median_stat, cambiar median por la función deseada */
    median_obs = median(tabla, ip, iu, &piv_index);
    if (median_obs == ERR) return ERR;
    
    comparisons += median_obs; /* Suma las OBs de la rutina median/median_avg/median_stat */
    
    /* Mueve el pivote al final para simplificar el bucle */
    piv_value = tabla[piv_index];
    temp = tabla[piv_index];
    tabla[piv_index] = tabla[iu];
    tabla[iu] = temp;
    
    i = ip;
    
    /* Bucle principal: i busca elementos mayores, j itera */
    for (j = ip; j < iu; j++) {
        comparisons++; /* O.B.: la comparación tabla[j] <= piv_value */
        if (tabla[j] <= piv_value) {
            /* Intercambia tabla[i] y tabla[j] */
            temp = tabla[i];
            tabla[i] = tabla[j];
            tabla[j] = temp;
            i++;
        }
    }

    /* Mueve el pivote a su posición final (i) */
    temp = tabla[i];
    tabla[i] = tabla[iu];
    tabla[iu] = temp;
    
    *pos = i; /* Devuelve la posición final del pivote */
    
    return comparisons;
}

int quicksort(int* tabla, int ip, int iu)
{
    int total_comparisons = 0;
    int comparisons;
    int pivote_pos;
    
    if (tabla == NULL || ip < 0 || iu < ip) {
        return ERR;
    }
    
    /* Caso base: si hay al menos dos elementos */
    if (ip < iu) {
        /* Divide (Particionar) */
        comparisons = partition(tabla, ip, iu, &pivote_pos);
        if (comparisons == ERR) return ERR;
        total_comparisons += comparisons;

        /*Lado izquierdo - solo si hay elementos */
        if (ip < pivote_pos) {
            comparisons = quicksort(tabla, ip, pivote_pos - 1);
            if (comparisons == ERR) return ERR;
            total_comparisons += comparisons;
        }
        
        /* Lado derecho - solo si hay elementos */
        if (pivote_pos < iu) {
            comparisons = quicksort(tabla, pivote_pos + 1, iu);
            if (comparisons == ERR) return ERR;
            total_comparisons += comparisons;
        }
    }
    
    return total_comparisons;
}