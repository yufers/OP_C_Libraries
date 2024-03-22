#include <stdio.h>
#include <malloc.h>

#include "ordered_array_set.h"

static void ordered_array_set_shrinkToFit(ordered_array_set *a) {
    if (a->size != a->capacity) {
        a->data = (int *) realloc(a->data, sizeof(int) * a->size);
        a->capacity = a->size;
    }
}

// возвращает пустое множество, в которое можно вставить capacity элементов
ordered_array_set ordered_array_set_create(size_t capacity) {
    return (ordered_array_set) {
            malloc(sizeof(int) * capacity), 0, capacity};
}

// возвращает множество, состоящее из элементов массива a размера size
ordered_array_set ordered_array_set_create_from_array(const int *a, size_t size) {
    ordered_array_set set = ordered_array_set_create(size);

    for (size_t i = 0; i < size; i++) {
        ordered_array_set_insert(&set, a[i]);
    }
    ordered_array_set_shrinkToFit(&set);

    return set;
}

// возвращает значение позицию элемента в множестве,
// если значение value имеется в множестве set,
// иначе - n
size_t ordered_array_set_in(ordered_array_set *set, int value) {
    size_t res = binarySearch_(set->data, set->size, value);

    if (res == SIZE_MAX) {
        return set->size;
    }

    return res;
}

// возвращает значение ’истина’, если элементы множеств set1 и set2 равны
// иначе - ’ложь’
bool ordered_array_set_isEqual(ordered_array_set set1, ordered_array_set set2) {
    if (set1.size != set2.size) {
        return false;
    }

    int res = memcmp(set1.data, set2.data, sizeof(int) * set1.size);

    return res == 0;
}

// возвращает значение ’истина’, если subset является подмножеством set
// иначе - ’ложь’
bool ordered_array_set_isSubset(ordered_array_set subset, ordered_array_set set) {
    if (subset.size < set.size) {
        return false;
    }
    size_t f_num_min_idx = ordered_array_set_in(&set, subset.data[0]);
    size_t f_num_max_idx = ordered_array_set_in(&set, subset.data[subset.size-1]);

    if ((f_num_min_idx == subset.size) || (f_num_max_idx == subset.size)) {
        return false;
    }

    int counter = 0;
    for (size_t i = f_num_min_idx; i <= f_num_max_idx; i++) {
        for (int j = 0; j < subset.size; j++) {
            if (set.data[i] == subset.data[j]) {
                counter++;
            }
        }
    }

    return counter == subset.size;
}

// возбуждает исключение, если в множество по адресу set
// нельзя вставить элемент
void ordered_array_set_isAbleAppend(ordered_array_set *set) {
    assert(set->size < set->capacity);
}

// добавляет элемент value в множество set
void ordered_array_set_insert(ordered_array_set *set, int value) {
    if (set->size == set->capacity) {
        set->data = (int *) realloc(set->data, sizeof(int) * (set->size + 1));
        set->capacity++;
    }

    size_t insert_idx = set->size;
    for (size_t i = 0; i < set->size; i++) {
        if (set->data[i] > value) {
            insert_idx = i;
            break;
        }
    }

    if (set->size != 0) {
        for (size_t i = insert_idx; i < set->size; i++) {
            set->data[i + 1] = set->data[i];
        }
    }
    set->data[insert_idx] = value;
    set->size++;
}

// удаляет элемент value из множества set
void ordered_array_set_deleteElement(ordered_array_set *set, int value) {
    size_t i = ordered_array_set_in(set, value);

    if (i == set->size) {
        return;
    }

    deleteByPosSaveOrder_(set->data, &set->size, i);

    ordered_array_set_shrinkToFit(set);
}

// возвращает объединение множеств set1 и set2
ordered_array_set ordered_array_set_union(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set united_set = ordered_array_set_create_from_array(set1.data, set1.size);

    for (size_t i = 0; i < set2.size; i++) {
        if (ordered_array_set_in(&united_set, set2.data[i]) == united_set.size) {
            ordered_array_set_insert(&united_set, set2.data[i]);
        }
    }

    return united_set;
}

// возвращает пересечение множеств set1 и set2
ordered_array_set ordered_array_set_intersection(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set new_arr = ordered_array_set_create(set1.capacity + set2.capacity);
    for (int i = 0; i < set1.size; i++) {
        for (int j = 0; j < set2.size; j++) {
            if (set1.data[i] == set2.data[j]) {
                ordered_array_set_insert(&new_arr, set2.data[j]);
            }
        }
    }
    ordered_array_set_shrinkToFit(&new_arr);

    return new_arr;
}

// возвращает разность множеств set1 и set2
ordered_array_set ordered_array_set_difference(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set new_arr = ordered_array_set_create(set1.capacity + set2.capacity);
    for (int i = 0; i < set1.size; i++) {
        bool found = false;
        for (int j = 0; j < set2.size; j++) {
            if (set1.data[i] == set2.data[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            ordered_array_set_insert(&new_arr, set1.data[i]);
        }
    }

    ordered_array_set_shrinkToFit(&new_arr);
    return new_arr;
}

// возвращает симметрическую разность множеств set1 и set2
ordered_array_set ordered_array_set_symmetricDifference(ordered_array_set set1, ordered_array_set set2) {
    ordered_array_set new_arr = ordered_array_set_create(set1.capacity + set2.capacity);
    for (int i = 0; i < set1.size; i++) {
        bool found = false;
        for (int j = 0; j < set2.size; j++) {
            if (set1.data[i] == set2.data[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            ordered_array_set_insert(&new_arr, set1.data[i]);
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
            ordered_array_set_insert(&new_arr, set2.data[i]);
        }
    }

    ordered_array_set_shrinkToFit(&new_arr);
    return new_arr;
}

// возвращает дополнение до универсума universumSet множества set
ordered_array_set ordered_array_set_complement(ordered_array_set set, ordered_array_set universumSet) {
    ordered_array_set new_arr = ordered_array_set_create(set.capacity + universumSet.capacity);
    for (int i = 0; i < universumSet.size; i++) {
        bool found = false;
        for (int j = 0; j < set.size; j++) {
            if (universumSet.data[i] == set.data[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            ordered_array_set_insert(&new_arr, universumSet.data[i]);
        }
    }

    return new_arr;
}

// вывод множества set
void ordered_array_set_print(ordered_array_set set) {
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
void ordered_array_set_delete(ordered_array_set set) {
    set.size = 0;
    ordered_array_set_shrinkToFit(&set);
}