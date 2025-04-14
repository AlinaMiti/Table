#include <iostream>
#include <random>
#include <sstream>
#include <forward_list>

void Merge(int* array, int left, int mid, int right);
void MergeSort( int* array, int left, int right){
    if(left < right){
        int mid = (right - left)/2 + left;
        MergeSort(array, left, mid);
        MergeSort(array, mid + 1, right);

        Merge(array, left, mid, right);
    }
    
}

void Merge(int* array, int left, int mid, int right){
    size_t s1 = mid - left + 1;
    size_t s2 = right - mid;

    int* left_array = new int[s1];
    int* right_array = new int[s2];

    for (size_t i = 0; i < s1; i++){
        left_array[i] = array[i + left];
    }
    for (size_t i = 0; i < s2; i++){
        right_array[i] = array[i + mid + 1];
    }

    size_t i = 0, j = 0, k = left;
    while(i < s1 && j < s2){
        if(left_array[i] <= right_array[j]){
            array[k] = left_array[i];
            i++;
        }
        else{
            array[k] = right_array[j];
            j++;
        }
        k++;
    }

    while(i < s1){
        array[k] = left_array[i];
        i++;
        k++;
    }
    while(i < s2){
        array[k] = right_array[j];
        j++;
        k++;
    }
    delete [] left_array;
    delete [] right_array;

    
}


int main(){

    int arr[9] = {2, 3, 66, 5, 3, 4, 1, 6665, 5};
    MergeSort(arr, 0, 8);
    for (size_t i = 0 ; i < 9; i++){
        std::cout << arr[i];
    }

    // srand(time(nullptr));
    // int* array = new int[10];
    // for(int i = 0; i < 10; i++){
    //     array[i] = rand() % 100000;
    // }
    
    return 0;
}