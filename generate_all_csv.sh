#!/bin/bash

# Script para generar automáticamente todos los archivos CSV de esta práctica
# - mergesort_data.csv (MergeSort)
# - quicksort_median.csv (QuickSort con median)
# - quicksort_avg.csv (QuickSort con median_avg)
# - quicksort_stat.csv (QuickSort con median_stat)

echo "=== Generando archivos CSV de la práctica ==="
echo ""

# Parámetros para exercise5 (puedes modificarlos)
NUM_MIN=10
NUM_MAX=100
INCR=10
NUM_PERMS=20

EXERCISE5_FILE="exercise5.c"
SORTING_FILE="sorting.c"
BACKUP_EX5="exercise5.c.backup"
BACKUP_SORT="sorting.c.backup"

# Crear backups
echo "1. Creando backups de los archivos..."
cp "$EXERCISE5_FILE" "$BACKUP_EX5"
cp "$SORTING_FILE" "$BACKUP_SORT"

# Función para generar CSV con MergeSort
generate_mergesort() {
    echo "2. Generando CSV para MergeSort..."
    
    # Cambiar exercise5 para usar mergesort
    sed -i 's/generate_sorting_times(quicksort/generate_sorting_times(mergesort/g' "$EXERCISE5_FILE"
    
    echo "   Compilando..."
    make clean > /dev/null 2>&1
    make exercise5 > /dev/null 2>&1
    
    if [ $? -ne 0 ]; then
        echo "   ERROR: Fallo en la compilación"
        return 1
    fi
    
    echo "   Ejecutando exercise5 y generando mergesort_data.csv..."
    ./exercise5 -num_min $NUM_MIN -num_max $NUM_MAX -incr $INCR -numP $NUM_PERMS -outputFile "mergesort_data.csv"
    
    if [ $? -eq 0 ]; then
        echo "   ✓ mergesort_data.csv generado correctamente"
    else
        echo "   ERROR: Fallo al generar mergesort_data.csv"
        return 1
    fi
    
    # Restaurar exercise5
    cp "$BACKUP_EX5" "$EXERCISE5_FILE"
}

# Función para generar CSV con QuickSort y función de pivote específica
generate_quicksort_pivot() {
    local pivot_func=$1
    local output_file=$2
    local description=$3
    
    echo ""
    echo "3. Generando CSV para QuickSort con $description..."
    
    # Cambiar exercise5 para usar quicksort
    sed -i 's/generate_sorting_times(mergesort/generate_sorting_times(quicksort/g' "$EXERCISE5_FILE"
    
    # Cambiar partition para usar la función de pivote específica
    sed -i "s/median_obs = median(tabla, ip, iu, \&piv_index);/median_obs = $pivot_func(tabla, ip, iu, \&piv_index);/" "$SORTING_FILE"
    
    echo "   Compilando..."
    make clean > /dev/null 2>&1
    make exercise5 > /dev/null 2>&1
    
    if [ $? -ne 0 ]; then
        echo "   ERROR: Fallo en la compilación"
        return 1
    fi
    
    echo "   Ejecutando exercise5 y generando $output_file..."
    ./exercise5 -num_min $NUM_MIN -num_max $NUM_MAX -incr $INCR -numP $NUM_PERMS -outputFile "$output_file"
    
    if [ $? -eq 0 ]; then
        echo "   ✓ $output_file generado correctamente"
    else
        echo "   ERROR: Fallo al generar $output_file"
        return 1
    fi
    
    # Restaurar sorting.c
    cp "$BACKUP_SORT" "$SORTING_FILE"
}

# Generar todos los CSV
generate_mergesort

generate_quicksort_pivot "median" "quicksort_median.csv" "median (primer elemento)"
generate_quicksort_pivot "median_avg" "quicksort_avg.csv" "median_avg (elemento medio)"
generate_quicksort_pivot "median_stat" "quicksort_stat.csv" "median_stat (mediana de tres)"

# Restaurar archivos originales
echo ""
echo "4. Restaurando archivos a su estado original..."
cp "$BACKUP_EX5" "$EXERCISE5_FILE"
cp "$BACKUP_SORT" "$SORTING_FILE"
rm "$BACKUP_EX5" "$BACKUP_SORT"

# Recompilar con la configuración original
echo "5. Recompilando con configuración original..."
make clean > /dev/null 2>&1
make all > /dev/null 2>&1

echo ""
echo "=== Proceso completado ==="
echo ""
echo "Archivos CSV generados:"
echo "  - mergesort_data.csv (MergeSort)"
echo "  - quicksort_median.csv (QuickSort con primer elemento)"
echo "  - quicksort_avg.csv (QuickSort con elemento medio)"
echo "  - quicksort_stat.csv (QuickSort con mediana de tres)"
echo ""
echo "Parámetros usados:"
echo "  Tamaño: $NUM_MIN a $NUM_MAX (incremento: $INCR)"
echo "  Permutaciones: $NUM_PERMS"
echo ""
echo "Para modificar parámetros, edita las variables al inicio del script:"
echo "  NUM_MIN, NUM_MAX, INCR, NUM_PERMS"

