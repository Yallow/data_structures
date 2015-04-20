#include "d_array.h"
#include <assert.h>

DArray *DArray_create(size_t element_size, size_t initial_max)
{
    // allocate some memory for the new array
    DArray *array = malloc(sizeof(DArray));
    check_mem(array);
    // set the size of the array
    array->max = initial_max;
    check(array->max > 0, "You must set and initial_max > 0.");

    // open up some space for the contents of the array
    array->contents = calloc(initial_max, sizeof(void *));
    check_mem(array->contents);

    // what index the array ends at
    array->end = 0;
    array->element_size = element_size;
    array->expand_rate = DEFAULT_EXPAND_RATE;

    return array;

error:
    if(array) free(array);
    return NULL;
}

void DArray_clear(DArray *array)
{
    int i = 0;
    // check that there are items in the array
    if(array->element_size > 0) {
        // run through the array
        for(i = 0; i < array->max; i++) {
            if(array->contents[i] != NULL) {
                // free the content of index i
                free(array->contents[i]);
            }
        }
    }
}

static inline int DArray_resize(DArray *array, size_t newsize)
{
    // change the array->max to the newsize
    array->max = newsize;
    check(array->max > 0, "The newsize must be > 0.");

    // realocate some memory
    void *contents = realloc(array->contents, array->max * sizeof(void *));

    // check contents and assume realloc doesn't harm the original on error
    check_mem(contents);

    array->contents = contents;

    return 0;
error:
    return -1;
}

int DArray_expand(DArray *array)
{
    size_t old_max = array->max;
    check(DArray_resize(array, array->max + array->expand_rate) == 0,
            "Failed to expand array to new size: %d",
            array->max + (int)array->expand_rate);
    memset(array->contents + old_max, 0, array->expand_rate + 1);
    return 0;
    
error:
    return -1;
}

int DArray_contract(DArray *array)
{
    // get a new size 
    // if the end shorter than the expand_rate, use expand_rate so not to
    // cut off the end of the array
    int new_size = array->end < (int)array->expand_rate ? (int)array->expand_rate : array->end;

    return DArray_resize(array, new_size + 1);
}

void DArray_destroy(DArray *array)
{
    // free everything if there is anything there
    if(array) {
        if(array->contents) free(array->contents);
        free(array);
    }
}

void DArray_clear_destroy(DArray *array)
{
    DArray_clear(array);
    DArray_destroy(array);
}

int DArray_push(DArray *array, void *el)
{
    // put a new value at the end of the array
    array->contents[array->end] = el;
    array->end++;

    // make more room in the array if needed
    if(DArray_end(array) >= DArray_max(array)) {
        return DArray_expand(array);
    } else {
        return 0;
    }
}

void *DArray_pop(DArray *array)
{
    check(array->end - 1 > 0, "Attempt to pop from an empty array.");

    // grab the struct at the end of the array
    void *el = DArray_remove(array, array->end -1);
    array->end--;

    // 
    if(DArray_end(array) > (int)array->expand_rate && DArray_end(array) % array->expand_rate) {
        DArray_contract(array);

        return el;

error:
        return NULL;
    }
}

int main(int argc, char *argv[])
{
    // call the functions needed
    // an array to be manipulated
    DArray *test_array;
    test_array = DArray_create(sizeof(int), 20); 
}
