//
// Created by user.v2.0 on 05.04.2021.
//

#ifndef SORTINGS_MAIN_HEADERS_H
#define SORTINGS_MAIN_HEADERS_H

int* shakerSort(int* array , int size , int& iterations);

void countingSort(int* array, int size, int k);

int* pocketSort(int* array_const , int size ,int& iterations);

int* quickSort(int* arr, const size_t size ,int& iterations);

void testingTimeDifficult();

void test(int* ptr_array , size_t size);

bool is_sorted (int *ptr_array , int size);

void fillWorst(int* array , size_t size);

void fillBest(int* array , size_t size);

void fillMiddle(int* array , size_t size);

#endif //SORTINGS_MAIN_HEADERS_H
