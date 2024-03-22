#include <malloc.h>
#include <stdbool.h>
#include <assert.h>
#include <stdio.h>

#include "bitset.h"

// возвращает пустое множество c универсумом 0, 1,..., maxValue
bitset bitset_create(unsigned maxValue) {
    assert(maxValue < sizeof(uint32_t) * 8);
    return (bitset) {0, maxValue};
}

// возвращает значение ’истина’, если значение value имеется в множестве set
// иначе - ’ложь’
bool bitset_in(bitset set, unsigned int value) {
    bool res = (1 << value) & set.values;
    return res;
}

// возвращает значение ’истина’, если множества set1 и set2 равны
// иначе - ’ложь’
bool bitset_isEqual(bitset set1, bitset set2) {
    bool res = (set1.values == set2.values);
    return res;
}

// возвращает значение ’истина’ если множество subset
// является подмножеством множества set, иначе - ’ложь’.
bool bitset_isSubset(bitset subset, bitset set) {
    bool res = ((set.values & subset.values) == subset.values) && (subset.values != set.values);
    return res;
}

// добавляет элемент value в множество set
void bitset_insert(bitset *set, unsigned int value) {
    set->values = set->values | (1 << value);
}

// удаляет элемент value из множества set
void bitset_deleteElement(bitset *set, unsigned int value) {
    set->values = set->values & ~(1 << value);
}

// возвращает объединение множеств set1 и set2
bitset bitset_union(bitset set1, bitset set2) {
    bitset set_union = bitset_create(max(set1.maxValue, set2.maxValue));
    set_union.values = set1.values | set2.values;

    return set_union;
}

// возвращает пересечение множеств set1 и set2
bitset bitset_intersection(bitset set1, bitset set2) {
    bitset set_union = bitset_create(max(set1.maxValue, set2.maxValue));
    set_union.values = set1.values & set2.values;

    return set_union;
}

// возвращает разность множеств set1 и set2
bitset bitset_difference(bitset set1, bitset set2) {
    bitset set_difference = bitset_create(max(set1.maxValue, set2.maxValue));
    set_difference.values = set1.values & ~set2.values;

    return set_difference;
}

// возвращает симметрическую разность множеств set1 и set2
bitset bitset_symmetricDifference(bitset set1, bitset set2) {
    bitset set_symmetricDifference = bitset_create(max(set1.maxValue, set2.maxValue));
    set_symmetricDifference .values = set1.values ^ set2.values;

    return set_symmetricDifference;
}

// возвращает дополнение до универсума множества set
bitset bitset_complement(bitset set) {
    bitset set_complement = bitset_create(set.maxValue);
    set_complement.values = ~set.values;

    return set_complement;
}

// вывод множества set
void bitset_print(bitset set) {
    printf("{");
    int isEmpty = 1;
    for (int i = 0; i <= set.maxValue; i++) {
        if (bitset_in(set, i)) {
            printf("%d, ", i);
            isEmpty = 0;
        }
    }
    if (isEmpty)
        printf("}\n");
    else
        printf("\b\b}\n");
}



