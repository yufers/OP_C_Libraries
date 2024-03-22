#include <stdio.h>
#include <malloc.h>

#include "unordered_array_set.h"

static void unordered_array_set_shrinkToFit(unordered_array_set *a) {
    if (a->size != a->capacity) {
        a->data = (int *) realloc(a->data, sizeof(int) * a->size);
        a->capacity = a->size;
    }
}

// возвращает пустое множество для capacity элементов
unordered_array_set unordered_array_set_create(size_t capacity) {
    return (unordered_array_set) {
            malloc(sizeof(int) * capacity), 0, capacity};
}

// возвращает множество, состоящее из элементов массива a размера size
unordered_array_set unordered_array_set_create_from_array(const int *a, size_t size) {
    unordered_array_set set = unordered_array_set_create(size);

    for (size_t i = 0; i < size; i++) {
        unordered_array_set_insert(&set, a[i]);
    }
    unordered_array_set_shrinkToFit(&set);

    return set;
}

// возвращает позицию элемента в множестве,
// если значение value имеется в множестве set, иначе - n
size_t unordered_array_set_in(unordered_array_set set, int value) {
    return linearSearch_(set.data, set.size, value);
}

// возвращает позицию элемента в множестве,
// если значение value имеется в множестве set, иначе - n
size_t unordered_array_set_isSubset(unordered_array_set subset, unordered_array_set set) {
    for (int i = 0; i < set.size; i++) {
        int counter = 0;
        for (int j = 0; j < subset.size; j++) {
            if (set.data[i+j] == subset.data[j]) {
                counter++;
                if (counter == subset.size) {
                    return i;
                }
            } else {
                counter = 0;
            }
        }
    }
    return set.size;
}

// возвращает значение ’истина’, если элементы множеств set1 и set2 равны
// иначе - ’ложь’
bool unordered_array_set_isEqual(unordered_array_set set1, unordered_array_set set2) {
    if (set1.size != set2.size) {
        return false;
    }
    for (int i = 0; i < set1.size; i++) {
        if (set1.data[i] != set2.data[i]) {
            return false;
        }
    }

    return true;
}

// возбуждает исключение, если в множество по адресу set
// нельзя вставить элемент
void unordered_array_set_isAbleAppend(unordered_array_set *set) {
    assert(set->size < set->capacity);
}

// добавляет элемент value в множество set
void unordered_array_set_insert(unordered_array_set *set, int value) {
    if (set->size == set->capacity) {
        set->data = (int *) realloc(set->data, sizeof(int) * (set->size + 1));
        set->capacity++;
    }

    append_(set->data, &set->size, value);
}

// удаляет элемент value из множества set
void unordered_array_set_deleteElement(unordered_array_set *set, int value) {
    size_t i = unordered_array_set_in(*set, value);

    if (i == set->size) {
        return;
    }

    deleteByPosSaveOrder_(set->data, &set->size, i);

    unordered_array_set_shrinkToFit(set);
}

// возвращает объединение множеств set1 и set2.
unordered_array_set unordered_array_set_union(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set united_set = unordered_array_set_create_from_array(set1.data, set1.size);

    for (size_t i = 0; i < set2.size; i++) {
        if (unordered_array_set_in(united_set, set2.data[i]) == united_set.size) {
            unordered_array_set_insert(&united_set, set2.data[i]);
        }
    }

    return united_set;
}

// возвращает пересечение множеств set1 и set2
unordered_array_set unordered_array_set_intersection(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set new_arr = unordered_array_set_create(set1.capacity + set2.capacity);
    for (int i = 0; i < set1.size; i++) {
        for (int j = 0; j < set2.size; j++) {
            if (set1.data[i] == set2.data[j]) {
                unordered_array_set_insert(&new_arr, set2.data[j]);
            }
        }
    }
    unordered_array_set_shrinkToFit(&new_arr);

    return new_arr;
}

// возвращает разность множеств set1 и set2
unordered_array_set unordered_array_set_difference(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set new_arr = unordered_array_set_create(set1.capacity + set2.capacity);
    for (int i = 0; i < set1.size; i++) {
        bool found = false;
        for (int j = 0; j < set2.size; j++) {
            if (set1.data[i] == set2.data[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            unordered_array_set_insert(&new_arr, set1.data[i]);
        }
    }

    unordered_array_set_shrinkToFit(&new_arr);
    return new_arr;
}

// возвращает дополнение до универсума множества set2
unordered_array_set unordered_array_set_complement(unordered_array_set set, unordered_array_set universumSet) {
    unordered_array_set new_arr = unordered_array_set_create(set.capacity + universumSet.capacity);
    for (int i = 0; i < universumSet.size; i++) {
        bool found = false;
        for (int j = 0; j < set.size; j++) {
            if (universumSet.data[i] == set.data[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            unordered_array_set_insert(&new_arr, universumSet.data[i]);
        }
    }

    return new_arr;
}

// возвращает симметрическую разность множеств set1 и set2
unordered_array_set unordered_array_set_symmetricDifference(unordered_array_set set1, unordered_array_set set2) {
    unordered_array_set new_arr = unordered_array_set_create(set1.capacity + set2.capacity);
    for (int i = 0; i < set1.size; i++) {
        bool found = false;
        for (int j = 0; j < set2.size; j++) {
            if (set1.data[i] == set2.data[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            unordered_array_set_insert(&new_arr, set1.data[i]);
        }
    }

    for (int i = 0; i < set2.size; i++) {
        bool found = false;
        for (int j = 0; j < set1.size; j++) {
            if (set2.data[i] == set1.data[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            unordered_array_set_insert(&new_arr, set2.data[i]);
        }
    }

    unordered_array_set_shrinkToFit(&new_arr);
    return new_arr;
}

// вывод множества set
void unordered_array_set_print(unordered_array_set set) {
    printf("{");
    int isEmpty = 1;
    for (int i = 0; i <= set.size; i++) {
        printf("%d, ", set.data[i]);
        isEmpty = 0;
    }
    if (isEmpty) {
        printf("}\n");
    } else
        printf("\b\b}\n");
}

// освобождает память, занимаемую множеством set
void unordered_array_set_delete(unordered_array_set set) {
    set.size = 0;
    unordered_array_set_shrinkToFit(&set);
}
