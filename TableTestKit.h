#pragma once
#include "Table.h"

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