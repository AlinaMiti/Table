#pragma once
#include "Table.h"
#include "DatValue.h"
#include "Marks.h"
#include <sstream>
#include <string>
#include <sstream>
#include <fstream>
#include <random>
#include <vector>
#include <chrono>
#include <iomanip> 
#include <algorithm>
#include <memory>
#include "HashTable.h"

class TableTestKit{
private:
    Table& table;
    std::vector<std::string> _metrics;
    size_t _operationsCount = 0;
    double _totalTime = 0.0;

    int _maxEfficiency = std::numeric_limits<int>::min();
    int _minEfficiency = std::numeric_limits<int>::max();
    int _totalEfficiency = 0;

    struct OperationStats {
        double totalTime = 0;
        double minTime = std::numeric_limits<double>::max();
        double maxTime = 0;
        int totalEfficiency = 0;
        int minEfficiency = std::numeric_limits<int>::max();
        int maxEfficiency = 0;
        size_t count = 0;
        double avgEfficiency() const {
            return (count > 0) ? static_cast<double>(totalEfficiency) / count : 0.0;
        }
    } _findStats, _deleteStats;

    struct GenConfig {
        size_t recordCount = 20000;
        int minMark = 3;
        int maxMark = 5;
        std::string filename = "benchmark_data.txt";
    } _config;

    // Базы имен
const std::vector<std::string> lastNames = {
    "Smith", "Johnson", "Williams", "Jones", "Brown", "Davis", "Miller", "Wilson", "Moore", "Taylor",
    "Anderson", "Thomas", "Jackson", "White", "Harris", "Martin", "Thompson", "Garcia", "Martinez", "Robinson",
    "Clark", "Rodriguez", "Lewis", "Lee", "Walker", "Hall", "Allen", "Young", "Hernandez", "King",
    "Wright", "Lopez", "Hill", "Scott", "Green", "Adams", "Baker"
};

const std::vector<std::string> firstNames = {
    "James", "John", "Robert", "Michael", "William", "David", "Richard", "Charles", "Joseph", "Thomas",
    "Christopher", "Daniel", "Paul", "Mark", "Donald", "George", "Kenneth", "Steven", "Edward", "Brian",
    "Ronald", "Anthony", "Kevin", "Jason", "Jeffrey", "Timothy", "Jose", "Mary", "Patricia", "Linda", "Barbara"
};

const std::vector<std::string> middleNames = {
    "A.", "B.", "C.", "D.", "E.", "F.", "G.", "H.", "I.", "J.", "K.", "L.", "M.", "N.", "O.", "P.", "Q.", "R.", "S.", "T."
};
public:
    TableTestKit(Table& table); //через двоеточие присвоить ссылке

    void TestHashTablePerformance();

    void AddMetric(const std::string& name, const std::string& value) {
        _metrics.push_back(name + ": " + value);
    }    

    void UpdateEfficiencyStats(int efficiency);

    void SetConfig(size_t recordCount, int minMark = 3, int maxMark = 5, 
                  const std::string& filename = "benchmark_data.txt") {
        _config = {recordCount, minMark, maxMark, filename};
    } 

    void FillTable();  //таблица из файла заполнится 

    void GenBenchmarkTab();  //Benchmark алгоритм проверки. у нас генерация рандом таблицы (файл из 20000 записей генерирует)
    void ShowTable(); //печать таблицы
    void FindRecord(); //поиск записи рандомной 1000 раз
    void DeleteRecord(); //без параметра, т.к. оцениваем среднюю эффективность алгоритма. запуск на 100 рандом записях

    void PrintMetrics(); //печать метрик. Сколько итераций\времени было на поиск/удаление/добавление, были ли ошибки. Запуск из мейна
};