#pragma once
#include "Table.h"
#include "DatValue.h"
#include "Marks.h"
#include <sstream>
#include <string>
#include <sstream>
#include <fstream>
#include <random>
#include <chrono>

class TableTestKit{
private:
    Table& table;
public:
    TableTestKit(Table& table); //через двоеточие присвоить ссылке

    void FillTable();  //Руками талицу заполнить

    void GenBenchmarkTab();  //Benchmark алгоритм проверки. у нас генерация рандом таблицы 
    void ShowTable(); //печать таблицы
    void FindRecord(); //поиск записи
    void DeleteRecord(); //без параметра, т.к. оцениваем среднюю эффективность алгоритма. запуск на 100 рандом записях

    void PrintMetrics(); //печать метрик. Сколько итераций\времени было на поиск/удаление/добавление, были ли ошибки. Запуск из мейна
};