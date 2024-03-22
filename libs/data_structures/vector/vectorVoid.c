#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "vectorVoid.h"

vectorVoid createVectorV(size_t capacity, size_t baseTypeSize) {
    void *data = malloc( capacity * baseTypeSize);
    if (data == NULL) {
        fprintf(stderr, "bad alloc");
        exit(1);
    }

    return (vectorVoid ) { data, 0, capacity, baseTypeSize };
}

void reserveV(vectorVoid *v, size_t newCapacity) {
    void *data = (int*) realloc(v->data, newCapacity * v->baseTypeSize);
    if (data == NULL) {
        v->data = NULL;
        fprintf(stderr, "bad alloc");
        exit(1);
    }

    v->data = data;
    v->capacity = newCapacity;

    if (v->size > v->capacity) {
        v->size = newCapacity;
    }
}

void shrinkToFitV(vectorVoid *v) {
    v->capacity = v->size;
}

void clearV(vectorVoid *v) {
    v->size = 0;
}

void deleteVectorV(vectorVoid *v) {
    free(v->data);
    v->data = NULL;
    v->size = 0;
    v->capacity = 0;
}

bool isEmptyV(vectorVoid *v) {
    return v->size == 0;
}

bool isFullV(vectorVoid *v) {
    return v->size >= v->capacity;
}

void getVectorValueV(vectorVoid *v, size_t index, void *destination) {
    if (index >= v->size) {
        fprintf(stderr, "element not exists");
        exit(1);
    }

    char *source = (char *) v->data + index * v->baseTypeSize;
    memcpy(destination, source, v->baseTypeSize);
}

void setVectorValueV(vectorVoid *v, size_t index, void *source) {
    if (index >= v->size) {
        fprintf(stderr, "element not exists");
        exit(1);
    }

    void *destination = (void *) v->data + index * v->baseTypeSize;
    memcpy(destination, source, v->baseTypeSize);
}

void popBackV(vectorVoid *v) {
    if (v->size == 0) {
        fprintf(stderr, "vector is empty");
        exit(1);
    }
    v->size--;
}

void pushBackV(vectorVoid *v, void *source) {
    if (v->size >= v->capacity) {
        size_t curr_size = v->size == 0 ? 1 : v->size * 2;
        reserveV(v, curr_size);
    }
    void *dest = (void *) v->data + v->size * v->baseTypeSize;
    memcpy(dest, source, v->baseTypeSize);
    v->size++;
}