
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "heap.h"

#define KEY_NOT_PRESENT -1

heap_t *heap_create(int capacity) {
    heap_t* heap = malloc(sizeof(heap_t));
    heap->size = 0;
    heap->capacity = capacity;
    heap->data = malloc(sizeof(heap_node_t) * capacity);
    if(heap->data == NULL) {
        free(heap);
        return NULL;
    }
    return heap;
}

void heap_free(heap_t *heap) {
    free(heap->data);
    free(heap);
}

unsigned int heap_size(heap_t *heap) { return heap->size; }

unsigned int heap_parent(unsigned int index) {
    return (index - 1) / 2;
}

unsigned int heap_left_child(unsigned int index) { 
    return (index * 2) + 1;
}

unsigned int heap_right_child(unsigned int index) { 
    return (index * 2) + 2;
}

unsigned int heap_level(unsigned int index) { 
    return (int)floor(log2(index + 1)) % 2 == 0;
}

void heap_print(heap_t *heap) {
    for (int ix = 0; ix < heap_size(heap); ix++) {
        printf("%3d - %3d : " HEAP_KEY_FORMAT "\n", heap_level(ix), ix,
               heap->data[ix].key);
    }
    printf("\n");
}

void heap_swap(heap_t *heap, int index1, int index2) {
    heap_node_t temp = heap->data[index1];
    heap->data[index1] = heap->data[index2];
    heap->data[index2] = temp;
}

void heap_bubble_up(heap_t *heap, int index) {
    if(index != 0)
        while(heap->data[index].key < heap->data[heap_parent(index)].key) {
            heap_swap(heap, index, heap_parent(index));
            index = heap_parent(index);
        }
}

void heap_bubble_down(heap_t *heap, int index) {
    int right = heap->data[heap_right_child(index)].key;
    int left = heap->data[heap_left_child(index)].key;
    int smaller = right > left ? right : left;
    while(heap->data[index].key > smaller) {
        heap_swap(heap, index, smaller);
        index = smaller;
        right = heap->data[heap_right_child(smaller)].key;
        left = heap->data[heap_left_child(smaller)].key;
        smaller = right > left ? right : left;
    }
}

void heap_insert(heap_t *heap, heap_key_t key, heap_value_t data) {

    if (heap_size(heap) == heap->capacity) {
        return;
    }

    heap->data[heap_size(heap)].key = key;
    heap->data[heap_size(heap)].value = data;
    heap->size++;

    heap_bubble_up(heap, heap_size(heap) - 1);
}


heap_value_t heap_remove_min(heap_t *heap) {
    if (heap_size(heap) == 0) {
        return (heap_value_t){.as_int = KEY_NOT_PRESENT};
    }

    heap_value_t min = (heap_value_t)heap->data[0].value;

    heap->size--;

    // move last element to the root
    heap->data[0] = heap->data[heap_size(heap) - 1];

    // then bubble it down to its correct position
    heap_bubble_down(heap, 0);

    return min;
}
