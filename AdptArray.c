#include "AdptArray.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//arr struct
typedef struct AdptArray_{
    PElement* PElement;
    void(*DEL_FUNC)(PElement);
    PElement(*COPY_FUNC)(PElement);
    void(*PRINT_FUNC)(PElement);
    int size;
}*PAdptArray;

//creat new arr
PAdptArray CreateAdptArray(COPY_FUNC fc, DEL_FUNC fd,PRINT_FUNC fp){
    PAdptArray newArr = (PAdptArray)malloc(sizeof(struct AdptArray_));
    if(newArr == NULL)
    {
        printf("faild in malloc!\n");
        return NULL;
    }
    newArr->PElement = NULL;
    newArr->COPY_FUNC = fc;
    newArr->DEL_FUNC = fd;
    newArr->PRINT_FUNC = fp;
    newArr->size = 0;
    // printf("created new arr!\n");
    return newArr;
}

//delete arr
void DeleteAdptArray(PAdptArray arr){
    if(arr != NULL)
    {
        if(arr->size != 0) //free each element of arr with DEL_FUNC
        {
            for(int i=0; i < arr->size; i++)
            {
                if((arr->PElement)[i] != NULL)
                {
                    arr->DEL_FUNC((arr->PElement)[i]);
                }
            }
        }
        free(arr->PElement);
        free(arr); //free all arr
    }
    // printf("deleted arr!\n");
}

//copy element to a place in arr (+free the element that was there before if was)
Result SetAdptArrayAt(PAdptArray arr, int i, PElement elm){
    if(arr == NULL)
    {
        printf("create an arr first\n");
        return FAIL;
    }
    if(arr->size > i) //if i is an index already in arr
    {
        if((arr->PElement)[i] != NULL)
        {
            arr->DEL_FUNC((arr->PElement)[i]); //if there is an element delete with DEL_FUNC
        }
    }
    else{ //we need more space in arr for index i
        PElement* newArr1 = (PElement*)realloc(arr->PElement, (i + 1) * sizeof(PElement));  
        if(newArr1 == NULL)
        {
            printf("faild in realloc!\n");
            DeleteAdptArray(arr);
            return FAIL;
        }
        for (int j = arr->size; j < i; j++) { // Initialize new memory with NULL values
            newArr1[j] = NULL;
        }
        arr->PElement = newArr1;
        arr->size = i+1; //change the size of arr
    }
    if(elm != NULL)
    {
        PElement * new_elm = arr->COPY_FUNC(elm);
        (arr->PElement)[i] = new_elm; //copy of the element by COPY_FUNC in the i place in arr
    }
    // printf("SetAdptArrayAt- SUCCESS!\n");
    return SUCCESS;
}

//get index i and return copy of the element in arr
PElement GetAdptArrayAt(PAdptArray arr, int i){
    if(arr == NULL)
    {
        printf("create an arr first\n");
        return NULL;
    }
    if(arr->size > i)
    {
        if((arr->PElement)[i] != NULL)
        {
            return arr->COPY_FUNC((arr->PElement)[i]); //return copy with COPY_FUNC
        }
    }
    return NULL; //if i not in arr or NULL
}

//return the size of arr or -1 if not initialize
int GetAdptArraySize(PAdptArray arr){
    if(arr == NULL) //if arr not initialize
    {
        return -1;
    }
    return arr->size;
}

// print the elements in arr
void PrintDB(PAdptArray arr){
    for(int i=0; i< arr->size; i++)
    {
        if ((arr->PElement)[i] != NULL)
        {
            PElement elm = (arr->PElement)[i];
            arr->PRINT_FUNC(elm);
        }
        
    }
    // printf("arr printfed!\n");
}