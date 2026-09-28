# Suffix Array Accelerator

## Descripción y Propósito
Este proyecto implementa una estructura de datos basada en un **Arreglo de Sufijos (Suffix Array)** acelerado mediante un **Arreglo LCP (Longest Common Prefix)** y una **Tabla Esparsa (Sparse Table / RMQ)**. 

La intención principal del código es optimizar la búsqueda de patrones dentro de cadenas de texto, mejorando el tiempo de búsqueda a **O(m + log n)** (donde *m* es la longitud del patrón y *n* es la longitud del texto). La aceleración se logra precalculando consultas de mínimo rango en intervalos (RMQ) sobre el arreglo LCP, lo cual evita comparaciones redundantes de caracteres durante la búsqueda binaria tradicional.

## Integrantes del Grupo
* Cabello Villon, Emilio Denis
* Zapata Llaxa, Jorge Andres
* Sánchez Mendoza, Diego Joaquín

## Estructura del Proyecto
* `include/`: Contiene el archivo de cabecera con la declaración de la clase (`suffix_array.h`).
* `src/`: Contiene la implementación lógica de los algoritmos (`suffix_array.cpp`).
* `apps/`: Contiene la aplicación principal con los casos de prueba (`app_main.cpp`).

## Requisitos
* Compilador de C++ (con soporte para el estándar C++17)
* CMake (versión 3.10 o superior)

## Cómo compilar y ejecutar

El proyecto utiliza CMake para facilitar su configuración y compilación multiplataforma.

1. **Generar los archivos de compilación:**
   Crea una carpeta de construcción y ejecuta CMake:
   ```bash
   mkdir build
   cd build
   cmake ..
   ```
   *(En Windows, dependiendo de tu compilador, podrías necesitar indicar el generador, por ejemplo: `cmake -G "MinGW Makefiles" ..`)*

2. **Compilar el proyecto:**
   Dentro de la carpeta `build`, ejecuta:
   ```bash
   cmake --build .
   ```

3. **Ejecutar la aplicación:**
   Una vez compilado, puedes correr el ejecutable para ver los casos de prueba:
   * **En Windows:**
     ```bash
     .\app_suffix_array.exe
     ```
   * **En Linux/Mac:**
     ```bash
     ./app_suffix_array
     ```

Al ejecutarse, el programa imprimirá en consola el Arreglo de Sufijos y el Arreglo LCP generados para cadenas de ejemplo, junto con los índices donde se ubicaron las búsquedas de los patrones solicitados.
