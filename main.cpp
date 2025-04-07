#include <iostream>
#include <random>
#include <sstream>

int main(){
    srand(time(nullptr));
    int* array = new int[10];
    for(int i = 0; i < 10; i++){
        array[i] = rand() % 100000;
    }
    
    return 0;
}