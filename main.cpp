#include <iostream>
#include <stack>
#include "random"
#include <time.h>

#include "main_headers.h"

int main() {
    testingTimeDifficult();
//    int array[] = {10, 15, 12, 13, 8, 16, 10};
//    int *ptr_array = array;
//    test(ptr_array);
//    srand(time(0));
//    int array1[] = {rand()%1000 , rand()%1000 , rand()%1000 , rand()%1000 , rand()%1000 , rand()%1000 , rand()%1000};
//    int* ptr_array1 = array1;
//    test(ptr_array1);
    return 0;
}

void test(int *ptr_array, size_t size) {
    int iterations;
    std::cout << "initial array_______\n";
    for (int i = 0; i < size; ++i) {
        std::cout << ptr_array[i] << " ";
    }
    std::cout << "\n__shaker sort_______\n";
    int *shaker_sort_array = shakerSort(ptr_array, size , iterations);
    std::cout << "-------result-------\n";
    for (int i = 0; i < size; ++i) {
        std::cout << shaker_sort_array[i] << " ";
    }
    std::cout << "time difficult : iterations - "<< iterations << "\n";
    std::cout << "__pocket sort_______\n";
    int *pocket_sort = pocketSort(ptr_array, size , iterations);
    std::cout << "-------result-------\n";
    for (int i = 0; i < size; ++i) {
        std::cout << pocket_sort[i] << " ";
    }
    std::cout << "time difficult : iterations - "<< iterations << "\n";
    std::cout << "___quick sort_______\n";
    int *quickSortArray = quickSort(ptr_array, size , iterations);
    std::cout << "-------result-------\n";
    for (int i = 0; i < size; ++i) {
        std::cout << quickSortArray[i] << " ";
    }
    std::cout << "time difficult : iterations - "<< iterations << "\n";
}

int *shakerSort(int *array_const, int size , int& iterations) {
    int *array = new int[size];
    iterations = 0;
    for (int i = 0; i < size; ++i) {
        array[i] = array_const[i];
    }
    int left_border = 0, right_border = size - 1, last_swap_index;
    while (right_border > left_border) {
        last_swap_index = 0;
        std::cout << "forward direction\n";
        for (int i = left_border; i < right_border; ++i) {
            if (array[i] > array[i + 1]) {
                std::swap(array[i], array[i + 1]);
                last_swap_index = i;
                for (int j = 0; j < size; ++j) {
                    std::cout << array[j] << " ";
                }
                std::cout << "\n";
            }
            iterations++;
        }
        right_border = last_swap_index;
        std::cout << "reverse direction\n";
        for (int i = right_border; i > left_border; --i) {
            if (array[i] < array[i - 1]) {
                std::swap(array[i], array[i - 1]);
                last_swap_index = i;
                for (int j = 0; j < size; ++j) {
                    std::cout << array[j] << " ";
                }
                std::cout << "\n";
            }
            iterations++;
        }
        left_border = last_swap_index;
    }
    return array;
}

int *pocketSort(int *array_const, int size,int& iterations) {
    int *array = new int[size];
    iterations = 0 ;
    for (int i = 0; i < size; ++i) {
        array[i] = array_const[i];
    }
    int left_border = array[0], right_border = array[0];
    for (int i = 0; i < size; ++i) {
        if (array[i] > right_border)
            right_border = array[i];
        if (array[i] < left_border)
            left_border = array[i];
    }
    int pockets = 4, pocket_size = (right_border - left_border + 1) / pockets;
    int last_expand = 0;
    int *result = new int[size];
    int result_index = 0;
    int *pocket_temp = new int[size];
    std::cout << "pocket size " << pocket_size << "\n";
    for (int i = 0; i < pockets; i++) { //O(pockets)
        int pocket_temp_size = 0;
        if (pockets - 1 == i)
            last_expand = (right_border - left_border + 1) % pockets;
        for (int j = 0; j < size; ++j) { //O(n)
            if (array[j] >= left_border + i * pocket_size &&
                array[j] < left_border + (i + 1) * pocket_size + last_expand) {
                pocket_temp[pocket_temp_size] = array[j];
                pocket_temp_size++;
            }
            iterations++;
        }
        std::cout << i + 1 << " pocket\n";
        int fix;
        pocket_temp = shakerSort(pocket_temp, pocket_temp_size , fix);
        for (int j = 0; j < pocket_temp_size; ++j, result_index++) {//O(diapozone)
            result[result_index] = pocket_temp[j];
            std::cout << result[result_index] << " ";
            iterations++;
        }
        std::cout << "\n";
    }
    //O(pockets*(n+diapozone))
    return result;
}

void countingSort(int *array_const, int size, int k) {
    int *array = new int[size];
    for (int i = 0; i < size; ++i) {
        array[i] = array_const[i];
    }
    int *c[k + 1];
    for (int i = 0; i < k + 1; ++i) {
        c[i] = 0;
    }
    for (int i = 0; i < size; ++i) {
        *c[array[i]]++;
    }
    int b = 0;
    for (int i = 0; i < k + 1; ++i) {
        for (int *j = 0; j < c[i]; ++j) {
            std::cout << "found out " << i << "\n";
            array[b++] = i;
        }
    }
    std::cout << "-------result-------\n";
    for (int i = 0; i < size; ++i) {
        std::cout << array[i] << " ";
    }
    std::cout << "\n";
}

int *quickSort(int *array, const size_t size , int& iterations) {
    int *arr = new int[size];
    iterations = 0;
    for (int i = 0; i < size; ++i) {
        arr[i] = array[i];
    }
    std::stack<int> stack;
    int pivotPos, pivotNum, minP, maxP, pastMinP, pastMaxP;
    pastMinP = 0;
    pastMaxP = size - 1;
    stack.push(pastMinP);
    stack.push(pastMaxP);
    while (!stack.empty()) {
        maxP = stack.top();
        stack.pop();
        minP = stack.top();
        stack.pop();
        pastMinP = minP;
        pastMaxP = maxP;
        pivotPos = (maxP + minP) / 2;
        pivotNum = arr[pivotPos];
        while (minP < maxP) {
            if (arr[minP] >= pivotNum) {
                if (arr[maxP] <= pivotNum) {
                    if (arr[maxP] <= arr[minP]) {
                        if (minP == pivotPos) {
                            pivotPos = maxP;
                            std::swap(arr[maxP], arr[minP]);
                            minP++;
                        } else {
                            if (maxP == pivotPos) {
                                pivotPos = minP;
                                std::swap(arr[maxP], arr[minP]);
                                maxP--;
                            } else {
                                std::swap(arr[maxP], arr[minP]);
                                minP++;
                                maxP--;
                            }
                        }
                    }
                } else {
                    maxP--;
                }
            } else {
                minP++;
            }
            iterations++;
        }
        if (pastMaxP - pastMinP >= 2) {

            stack.push(pastMinP);
            stack.push(pivotPos - 1);
            stack.push(pivotPos + 1);
            stack.push(pastMaxP);
        }
        for (int i = 0; i < size; ++i) {
            std::cout << arr[i] << " ";
        }
        std::cout << "\n";
        //std::cout << pastMinP << " "<< pastMaxP << " "<< pivotNum << "\n";
    }
    return arr;
}

bool is_sorted(int *ptr_array, int size) {
    for (int i = 1; i < size; ++i) {
        if (ptr_array[i - 1] > ptr_array[i])
            return false;
    }
    return true;
}

void testingTimeDifficult() {
    int *array = new int[10];
    fillBest(array, 10);
    test(array, 10);
    fillMiddle(array, 10);
    test(array, 10);
    fillWorst(array, 10);
    test(array, 10);
}

void fillWorst(int *array, size_t size) {
    for (int i = 0; i < size; i++) {
        array[i] = size - i;
    }
}

void fillBest(int *array, size_t size) {
    for (int i = 0; i < size; i++) {
        array[i] = i;
    }
}

void fillMiddle(int *array, size_t size) {
    for (int i = 0; i < size; i++) {
        if (i < size / 2) {
            array[i] = i;
        } else {
            array[i] = -i;
        }
    }
}