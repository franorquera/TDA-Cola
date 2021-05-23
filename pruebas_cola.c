#include "cola.h"
#include "testing.h"
#include "stdlib.h"

void destruir_cola(void *cola) {
    cola_destruir(cola, NULL);
}

void duplicar(void *dato) {
    *(int*) dato *= 2;
}

static void prueba_cola_vacia(void) {
    cola_t *cola = cola_crear();
    print_test("La cola se puede crear", cola);
    print_test("La cola esta vacia", cola_esta_vacia(cola));
    print_test("No hay un primer elemento", cola_ver_primero(cola) == NULL);
    print_test("No puedo desencolar elementos", cola_desencolar(cola) == NULL);
    cola_destruir(cola, NULL);
    cola_t *cola2 = cola_crear();
    cola_destruir(cola2, NULL);
}

static void prueba_cola_vaciada(void) {
    cola_t *cola = cola_crear();
    int elem = 1, elem2 = 2;
    print_test("La cola se puede crear", cola);
    print_test("La cola esta vacia", cola_esta_vacia(cola));
    print_test("No hay un primer elemento", cola_ver_primero(cola) == NULL);
    print_test("No puedo desencolar elementos", cola_desencolar(cola) == NULL);
    print_test("Encolo un elemento", cola_encolar(cola, &elem));
    print_test("La cola no esta vacia", cola_esta_vacia(cola) == false);
    print_test("Puedo ver el primer elemento", cola_ver_primero(cola) == &elem);
    print_test("Encolo un segundo elemento", cola_encolar(cola, &elem2));
    print_test("Puedo desencolar el primer elemento", cola_desencolar(cola) == &elem);
    print_test("Puedo desencolar el nuevo primer elemento", cola_desencolar(cola) == &elem2);
    print_test("La cola quedo vacia", cola_esta_vacia(cola));
    print_test("No hay primer elemento", cola_ver_primero(cola) == NULL);
    print_test("No puedo desencolar elementos", cola_desencolar(cola) == NULL);
    cola_destruir(cola, NULL);
}

static void prueba_cola_elementos(void) {
    cola_t *cola = cola_crear();
    print_test("La cola se puede crear", cola);
    int elem = 1, elem2 = 2;
    print_test("La cola esta vacia", cola_esta_vacia(cola));
    print_test("No hay primer elemento", cola_ver_primero(cola) == NULL);
    print_test("Encolo un elemento", cola_encolar(cola, &elem));
    print_test("La cola no esta vacia", cola_esta_vacia(cola) == false);
    print_test("Puedo ver el primer elemento", cola_ver_primero(cola) == &elem);
    print_test("Encolo un segundo elemento", cola_encolar(cola, &elem2));
    print_test("Puedo desencolar el primer elemento", cola_desencolar(cola) == &elem);
    print_test("Puedo ver el nuevo primer elemento", cola_ver_primero(cola) == &elem2);
    print_test("Puedo desencolar el nuevo primer elemento", cola_desencolar(cola) == &elem2);
    print_test("No puedo desencolar mas elementos", cola_desencolar(cola) == NULL);
    print_test("La cola esta vacia", cola_esta_vacia(cola));
    print_test("No hay primer elemento", cola_ver_primero(cola) == NULL);
    cola_destruir(cola, NULL);
}

static void prueba_cola_null(void) {
    cola_t *cola = cola_crear();
    print_test("La cola se puede crear", cola);
    int *elem = NULL, *elem4 = NULL, elem3 = 3;
    char *elem2 = "Segundo elemento";
    print_test("La cola esta vacia", cola_esta_vacia(cola));
    print_test("No hay primer elemento", cola_ver_primero(cola) == NULL);
    print_test("Encolo el elemento NULL", cola_encolar(cola, &elem));
    print_test("La cola no esta vacia", cola_esta_vacia(cola) == false);
    print_test("Puedo ver el primer elemento el cual es NULL", cola_ver_primero(cola) == &elem);
    print_test("Encolo un segundo elemento", cola_encolar(cola, &elem2));
    print_test("Encolo un tercer elemento", cola_encolar(cola, &elem3));
    print_test("Encolo un cuarto elemento NULL", cola_encolar(cola, &elem4));
    print_test("El primer elemento no cambio", cola_ver_primero(cola) == &elem);
    print_test("Puedo desencolar el primer elemento NULL", cola_desencolar(cola) == &elem);
    print_test("La cola no esta vacia", cola_esta_vacia(cola) == false);
    print_test("Puedo desencolar el segundo elemento", cola_desencolar(cola) == &elem2);
    print_test("Puedo desencolar el tercer elemento", cola_desencolar(cola) == &elem3);
    print_test("Puedo ver el primer elemento el cual es NULL", cola_ver_primero(cola) == &elem4);
    print_test("La cola no esta vacia", cola_esta_vacia(cola) == false);
    print_test("Puedo desencolar el cuarto elemento NULL", cola_desencolar(cola) == &elem4);
    cola_destruir(cola, NULL);
}

static void prueba_cola_destruccion(void) {
    cola_t *cola = cola_crear();
    cola_t *cola2 = cola_crear();
    print_test("La cola se puede crear", cola);
    print_test("Puedo crear una segunda cola", cola2);
    print_test("La cola esta vacia", cola_esta_vacia(cola));
    print_test("La segunda cola esta vacia", cola_esta_vacia(cola2));
    print_test("No hay primer elemento", cola_ver_primero(cola) == NULL);
    print_test("Encolo una cola2 a mi cola", cola_encolar(cola, cola2));
    print_test("La cola no esta vacia", cola_esta_vacia(cola) == false);
    cola_destruir(cola, destruir_cola);
    cola_t *cola3 = cola_crear();
    int nums[2] = {1,2};
    print_test("La cola se puede crear", cola3);
    print_test("La cola esta vacia", cola_esta_vacia(cola3));
    print_test("Encolo un elemento", cola_encolar(cola3, &nums[0]));
    print_test("Encolo otro elemento", cola_encolar(cola3, &nums[1]));
    cola_destruir(cola3, NULL);
}

static void prueba_cola_destruir_vectores() {
    cola_t *cola2 = cola_crear();
    int* num1 = malloc(sizeof(int));
    int* num2 = malloc(sizeof(int));
    print_test("Puedo crear una cola", cola2);
    print_test("La cola esta vacia", cola_esta_vacia(cola2));
    print_test("Encolo un elemento", cola_encolar(cola2, num1));
    print_test("Encolo un elemento", cola_encolar(cola2, num2));
    cola_destruir(cola2, free);
}

static void prueba_cola_destruccion_2(void) {
    cola_t *cola = cola_crear();
    print_test("La cola se puede crear", cola);
    cola_destruir(cola, NULL);
    cola_t *cola2 = cola_crear();
    int nums[3] = {1,2,3};
    int nums_dobles[3] = {2,4,6};
    print_test("Encolo un elemento", cola_encolar(cola2, &nums[0]));
    print_test("La cola no esta vacia", cola_esta_vacia(cola2) == false);
    print_test("Encolo un segundo elemento", cola_encolar(cola2, &nums[1]));
    print_test("Encolo un tercer elemento", cola_encolar(cola2, &nums[2]));
    cola_destruir(cola2, duplicar);
    for (int i = 2; i >= 0; i--) {
        print_test("Los numeros se duplican", nums[i] == nums_dobles[i]);
    }
}

static void prueba_cola_destruccion_vacia() {
    cola_t *cola = cola_crear();
    print_test("La cola se puede crear", cola);
    cola_destruir(cola, free);
}

static void prueba_cola_volumen(void) {
    cola_t *cola = cola_crear();
    print_test("La cola se puede crear", cola);
    print_test("La cola esta vacia", cola_esta_vacia(cola));
    int elems[1000] = {0};
    bool encolado = true, desencolado = true;
    for (int i = 0; i < 1000; i++) {
        elems[i] = i;
    }
    for (int i = 0; i < 1000; i++) {
        if (encolado) {
            encolado = cola_encolar(cola, &elems[i]);
        }
    }
    print_test("Puedo ver el primer elemento", cola_ver_primero(cola) == &elems[0]);
    print_test("La cola no esta vacia", cola_esta_vacia(cola) == false);
    for (int i = 0; i < 1000; i++) {
        if (desencolado) {
            void *elem = cola_desencolar(cola);
            if (elem != &elems[i]) desencolado = false;
        }
    }
    print_test("La cola esta vacia", cola_esta_vacia(cola));
    print_test("No hay primer elemento", cola_ver_primero(cola) == NULL);
    print_test("No puedo desencolar mas elementos", cola_desencolar(cola) == NULL);
    cola_destruir(cola, NULL);
}

void pruebas_cola_estudiante() {
    prueba_cola_vacia();
    prueba_cola_vaciada();
    prueba_cola_elementos();
    prueba_cola_null();
    prueba_cola_destruccion();
    prueba_cola_destruir_vectores();
    prueba_cola_destruccion_2();
    prueba_cola_destruccion_vacia();
    prueba_cola_volumen();
}

#ifndef CORRECTOR

int main(void) {
    pruebas_cola_estudiante();
    return failure_count() > 0;
}

#endif