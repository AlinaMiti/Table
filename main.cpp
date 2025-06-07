#include <iostream>
#include <random>
#include <sstream>
#include <forward_list>
#include "Table.h"
#include "Marks.h"
#include <fstream>
#include <string>
#include "TableTestKit.h"
#include "ArrayTable.h"
#include "DatValue.h"
#include "ScanTable.h"
#include "SortTable.h"
#include "ListHashTable.h"

// void Merge(int* array, int left, int mid, int right);
// void MergeSort( int* array, int left, int right){
//     if(left < right){
//         int mid = (right - left)/2 + left;
//         MergeSort(array, left, mid);
//         MergeSort(array, mid + 1, right);

//         Merge(array, left, mid, right);
//     }
    
// }

// void Merge(int* array, int left, int mid, int right){
//     size_t s1 = mid - left + 1;
//     size_t s2 = right - mid;

//     int* left_array = new int[s1];
//     int* right_array = new int[s2];

//     for (size_t i = 0; i < s1; i++){
//         left_array[i] = array[i + left];
//     }
//     for (size_t i = 0; i < s2; i++){
//         right_array[i] = array[i + mid + 1];
//     }

//     size_t i = 0, j = 0, k = left;
//     while(i < s1 && j < s2){
//         if(left_array[i] <= right_array[j]){
//             array[k] = left_array[i];
//             i++;
//         }
//         else{
//             array[k] = right_array[j];
//             j++;
//         }
//         k++;
//     }

//     while(i < s1){
//         array[k] = left_array[i];
//         i++;
//         k++;
//     }
//     while(i < s2){
//         array[k] = right_array[j];
//         j++;
//         k++;
//     }
//     delete [] left_array;
//     delete [] right_array;

    
// }


int main(){
    
    // Marks* marks = new Marks(5, 4, 5, 3, 5);
    // std::cout << "Marks: " << *marks << std::endl; 
    // delete marks;
    

 
      //  
        // ScanTable table(3);
        
        // table.InsRecord("student1", new Marks(5, 4, 3, 5, 4));
        // table.InsRecord("student2", new Marks(3, 3, 4, 4, 5));
        
        // PDatValue val = table.FindRecord("student1");
        // if(val) {
        //     std::cout << "Found student1: " << *val << std::endl;
        // }
        
        // table.DelRecord("student1");
        // std::cout << table.GetDataCount() << std::endl;
    // 



    // ScanTable scanTable(5000);
    // TableTestKit tester(scanTable);
    // tester.GenBenchmarkTab(); 
    // tester.FillTable();       
    // tester.FindRecord();      
    // tester.DeleteRecord();    
    // tester.PrintMetrics();

  //
  //СОРТИРОВКА
  // ScanTable sourceTable(10000);
  // TableTestKit tester(sourceTable);
  // tester.GenBenchmarkTab();
  // tester.FillTable();

  // SortTable sortedTable = sourceTable;
  // sortedTable.SetSortMethod(Merge);

  // // Замер эффективности сортировки
  // int sortEfficiency = sortedTable.GetEfficiency(); // Получаем результат
  // //
  // TableTestKit sortedTester(sortedTable);
  // sortedTester.FindRecord(); // Тест поиска
  // sortedTester.DeleteRecord(); // Тест удаления
  // sortedTester.AddMetric("Sorting Algorithm", sortedTable.GetSortMethodName());
  // sortedTester.AddMetric("Sort Efficiency", std::to_string(sortEfficiency));
  // sortedTester.PrintMetrics();
  //
  //

  //
  //
  try {
  ListHashTable hashTable(20000);
  TableTestKit tester(hashTable);
  tester.SetConfig(20000, 2, 5, "hash_benchmark.txt");
  tester.GenBenchmarkTab();
  tester.FillTable();
  std::cout << "Records loaded: " << hashTable.GetDataCount() << std::endl;
    std::cout << "Collisions: " << hashTable.GetCollisionCount() << std::endl;
    std::cout << "Load factor: " << hashTable.GetLoadFactor() << std::endl;
  
  //tester.TestHashTablePerformance();
  tester.FindRecord();
  tester.DeleteRecord();
  
  tester.PrintMetrics();
  
            
  } catch (const std::exception& e) {
    std::cerr << "Error: " << e.what() << std::endl;
}
  return 0;
}