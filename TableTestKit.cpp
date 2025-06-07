#include "TableTestKit.h"
#include "ListHashTable.h"
#include <set>

TableTestKit::TableTestKit(Table& table): table(table){}

void TableTestKit::UpdateEfficiencyStats(int efficiency){
    if (efficiency > _maxEfficiency) _maxEfficiency = efficiency;
    if (efficiency < _minEfficiency) _minEfficiency = efficiency;
    _totalEfficiency += efficiency;
    _operationsCount++;  
}

void TableTestKit::GenBenchmarkTab(){
    std::ofstream outFile(_config.filename);
    if (!outFile) {
        _metrics.push_back("Error: Cannot create file " + _config.filename);
        return;
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> markDist(2, 5);
    
    // Генератор уникальных ФИО
    std::set<std::string> generatedNames;
    size_t attempts = 0;
    const size_t maxAttempts = 50000; // Защита от бесконечного цикла

    auto generateUniqueName = [&]() -> std::string {
        while (attempts++ < maxAttempts) {
            std::string name = lastNames[gen() % lastNames.size()] + " " +
                             firstNames[gen() % firstNames.size()] + " " +
                             middleNames[gen() % middleNames.size()];
            
            if (generatedNames.insert(name).second) {
                return name;
            }
        }
        throw std::runtime_error("Failed to generate unique names");
    };

    try {
        for (size_t i = 0; i < 20000; ++i) {
            std::string fullName = generateUniqueName();
            outFile << fullName << ","
                   << markDist(gen) << ","
                   << markDist(gen) << ","
                   << markDist(gen) << ","
                   << markDist(gen) << ","
                   << markDist(gen) << "\n";
            
            if (i % 1000 == 0) {
                outFile.flush(); // Периодическая запись на диск
            }
        }
        _metrics.push_back("Generated 20000 unique records");
    } catch (const std::exception& e) {
        _metrics.push_back("Generation error: " + std::string(e.what()));
    }        
}

//
void TableTestKit::FillTable() {
    try {
        std::ifstream inFile(_config.filename);
        if (!inFile) throw std::runtime_error("File open failed");

        std::string line;
        size_t loaded = 0;
        const size_t batchSize = 500;
        bool isHashTable = dynamic_cast<ListHashTable*>(&table) != nullptr;
        
        while (std::getline(inFile, line) && loaded < 20000) {
            try {
                std::string key;
                int marks[5];
                char delim;
                std::stringstream ss(line);

                if (std::getline(ss, key, ',') &&
                    ss >> marks[0] >> delim && delim == ',' &&
                    ss >> marks[1] >> delim && delim == ',' &&
                    ss >> marks[2] >> delim && delim == ',' &&
                    ss >> marks[3] >> delim && delim == ',' &&
                    ss >> marks[4]) {

                    if (table.IsFull()) {
                        _metrics.push_back("Table full at " + std::to_string(loaded));
                        break;
                    }

                    std::unique_ptr<Marks> marksPtr(
                        new Marks(marks[0], marks[1], marks[2], marks[3], marks[4]));
                    
                    // Специальная обработка для ListHashTable
                    if (isHashTable) {
                        try {
                            table.InsRecord(key, marksPtr.release());
                        } catch (const char* e) {
                            // Простая проверка на дубликат без strstr
                            std::string errorMsg(e);
                            if (errorMsg.find("Duplication") != std::string::npos) {
                                continue; // Пропускаем дубликаты
                            }
                            throw;
                        }
                    } else {
                        table.InsRecord(key, marksPtr.release());
                    }
                    loaded++;
                }
            } catch (const char* e) {
                _metrics.push_back("Parse error in line: " + line + " | Error: " + e);
            } catch (...) {
                _metrics.push_back("Unknown error in line: " + line);
            }
        }
        _metrics.push_back("Total loaded: " + std::to_string(loaded));
        
        // Добавляем информацию о коллизиях для хеш-таблицы
        if (isHashTable) {
            ListHashTable* hashTable = static_cast<ListHashTable*>(&table);
            _metrics.push_back("Collisions: " + std::to_string(hashTable->GetCollisionCount()));
            _metrics.push_back("Load factor: " + std::to_string(hashTable->GetLoadFactor()));
        }

    } catch (const std::exception& e) {
        _metrics.push_back("FillTable error: " + std::string(e.what()));
        throw;
    }
}
//
// void TableTestKit::FillTable(){
//     try {
//         std::ifstream inFile(_config.filename);
//         if (!inFile) throw std::runtime_error("File open failed");

//         std::string line;
//         size_t loaded = 0;
//         const size_t batchSize = 500;  // Обрабатываем частями
        
//         while (std::getline(inFile, line) && loaded < 20000) {
//             try {
                
//                 std::string key;
//                 int marks[5];
//                 char delim;
//                 std::stringstream ss(line);

//                 if (std::getline(ss, key, ',') &&
//                     ss >> marks[0] >> delim && delim == ',' &&
//                     ss >> marks[1] >> delim && delim == ',' &&
//                     ss >> marks[2] >> delim && delim == ',' &&
//                     ss >> marks[3] >> delim && delim == ',' &&
//                     ss >> marks[4]) {

//                     if (table.IsFull()) {
//                         _metrics.push_back("Table full at " + std::to_string(loaded));
//                         break;
//                     }

//                     //умный указатель
//                     std::unique_ptr<Marks> marksPtr(
//                         new Marks(marks[0], marks[1], marks[2], marks[3], marks[4]));
                    
//                     table.InsRecord(key, marksPtr.release());
//                     loaded++;
//                     //
//                 if (auto hashTable = dynamic_cast<ListHashTable*>(&table)) {
//                 hashTable->InsRecord(key, marksPtr.release(), true); // Разрешаем дубликаты
//             } else {
//                 table.InsRecord(key, marksPtr.release());
//             }
//             loaded++;
//             //
                    
//                 }
//             } catch (...) {
//                 _metrics.push_back("Parse error in line: " + line);
//             }
//         }
//         _metrics.push_back("Total loaded: " + std::to_string(loaded));
//     } catch (const std::exception& e) {
//         _metrics.push_back("FillTable error: " + std::string(e.what()));
//         throw;
//     }
// }

void TableTestKit::ShowTable() {
    if (table.IsEmpty()) {
        throw "Table is empty";
    }

    const int keyWidth = 25;
    const int mathWidth = 6;
    const int physWidth = 6;
    const int sportWidth = 6;
    const int psychWidth = 6;
    const int histWidth = 6;
    
    std::cout << "+" << std::string(keyWidth + 2, '-') 
              << "+" << std::string(mathWidth + 2, '-')
              << "+" << std::string(physWidth + 2, '-')
              << "+" << std::string(sportWidth + 2, '-')
              << "+" << std::string(psychWidth + 2, '-')
              << "+" << std::string(histWidth + 2, '-') << "+" << std::endl;
    
    std::cout << "| " << std::left << std::setw(keyWidth) << "Student Key" 
              << " | " << std::setw(mathWidth) << "Math"
              << " | " << std::setw(physWidth) << "Phys"
              << " | " << std::setw(sportWidth) << "Sport"
              << " | " << std::setw(psychWidth) << "Psych"
              << " | " << std::setw(histWidth) << "Hist" << " |" << std::endl;
    
    std::cout << "+" << std::string(keyWidth + 2, '-') 
              << "+" << std::string(mathWidth + 2, '-')
              << "+" << std::string(physWidth + 2, '-')
              << "+" << std::string(sportWidth + 2, '-')
              << "+" << std::string(psychWidth + 2, '-')
              << "+" << std::string(histWidth + 2, '-') << "+" << std::endl;
    
    table.Reset();
    while (!table.IsTabEnded()) {
        Key key = table.GetKey();
        Marks* marks = dynamic_cast<Marks*>(table.GetValue());
        
        if (marks) {
            std::cout << "| " << std::left << std::setw(keyWidth) << key
                      << " | " << std::setw(mathWidth) << marks->GetMath()
                      << " | " << std::setw(physWidth) << marks->GetPhysics()
                      << " | " << std::setw(sportWidth) << marks->GetSport()
                      << " | " << std::setw(psychWidth) << marks->GetPsychology()
                      << " | " << std::setw(histWidth) << marks->GetHistory() << " |" << std::endl;
            
            std::cout << "+" << std::string(keyWidth + 2, '-') 
                      << "+" << std::string(mathWidth + 2, '-')
                      << "+" << std::string(physWidth + 2, '-')
                      << "+" << std::string(sportWidth + 2, '-')
                      << "+" << std::string(psychWidth + 2, '-')
                      << "+" << std::string(histWidth + 2, '-') << "+" << std::endl;
        }
        
        table.GoNext();
    }
}
// void TableTestKit::FindRecord() {
//     try {
//         if (table.IsEmpty()) {
//             AddMetric("FindRecord Status", "Skipped (empty table)");
//             return;
//         }

//         // Ограничение для больших таблиц
//         const size_t MAX_TEST_KEYS = 10000;
//         const size_t actualSize = std::min(MAX_TEST_KEYS, table.GetDataCount());
        
//         std::vector<Key> testKeys;
//         testKeys.reserve(actualSize);

//         // Сбор ключей с прогресс-баром
//         table.Reset();
//         size_t collected = 0;
//         while (!table.IsTabEnded() && collected < actualSize) {
//             testKeys.push_back(table.GetKey());
//             table.GoNext();
//             collected++;
            
//             if (collected % 1000 == 0) {
//                 std::cout << "Collected " << collected << "/" << actualSize 
//                           << " keys for testing...\n";
//             }
//         }

//         if (testKeys.empty()) {
//             AddMetric("FindRecord Status", "No valid keys found");
//             return;
//         }

//         OperationStats stats;
//         std::random_device rd;
//         std::mt19937 gen(rd());
//         std::uniform_int_distribution<size_t> dist(0, testKeys.size() - 1);

//         for (size_t i = 0; i < std::min(size_t(1000), testKeys.size()); ++i) {
//             const auto& key = testKeys[dist(gen)];
            
//             auto start = std::chrono::high_resolution_clock::now();
//             table.FindRecord(key);
//             auto end = std::chrono::high_resolution_clock::now();

//             double duration = std::chrono::duration<double, std::milli>(end - start).count();
//             int efficiency = table.GetEfficiency();

//             // Обновление статистики с проверкой переполнения
//             stats.totalTime += duration;
//             stats.minTime = std::min(stats.minTime, duration);
//             stats.maxTime = std::max(stats.maxTime, duration);
//             stats.totalEfficiency += efficiency;
//             stats.minEfficiency = std::min(stats.minEfficiency, efficiency);
//             stats.maxEfficiency = std::max(stats.maxEfficiency, efficiency);
//             stats.count++;
//         }

//         // Добавление метрик
//         AddMetric("01. FindRecord Tests", std::to_string(stats.count));
//         AddMetric("02. FindRecord Avg Time", std::to_string(stats.totalTime/stats.count) + " ms");
//         AddMetric("03. FindRecord Min Time", std::to_string(stats.minTime) + " ms");
//         AddMetric("04. FindRecord Max Time", std::to_string(stats.maxTime) + " ms");
//         AddMetric("05. FindRecord Avg Eff", std::to_string(stats.avgEfficiency()));
//         AddMetric("06. FindRecord Min Eff", std::to_string(stats.minEfficiency));
//         AddMetric("07. FindRecord Max Eff", std::to_string(stats.maxEfficiency));

//     } catch (const std::exception& e) {
//         AddMetric("FindRecord Error", std::string("Exception: ") + e.what());
//     } catch (...) {
//         AddMetric("FindRecord Error", "Unknown exception occurred");
//     }
// }
void TableTestKit::FindRecord(){

    if (table.IsEmpty()) {
        _metrics.push_back("FindRecord: Table is empty");
        return;
    }

    // Собираем все ключи один раз
    std::vector<Key> allKeys;
    table.Reset();
    while (!table.IsTabEnded()) {
        allKeys.push_back(table.GetKey());
        table.GoNext();
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<size_t> dist(0, allKeys.size() - 1);

    _findStats = OperationStats(); // Сброс статистики

    for (int i = 0; i < 1000; i++) {
        Key key = allKeys[dist(gen)];
            
        auto start = std::chrono::high_resolution_clock::now();
        table.FindRecord(key);
        auto end = std::chrono::high_resolution_clock::now();

        double duration = std::chrono::duration<double, std::milli>(end - start).count();
        int efficiency = table.GetEfficiency();

        // Обновляем статистику
        _findStats.totalTime += duration;
        _findStats.minTime = std::min(_findStats.minTime, duration);
        _findStats.maxTime = std::max(_findStats.maxTime, duration);
        _findStats.totalEfficiency += efficiency;
        _findStats.minEfficiency = std::min(_findStats.minEfficiency, efficiency);
        _findStats.maxEfficiency = std::max(_findStats.maxEfficiency, efficiency);
        _findStats.count++;
    }

    _metrics.push_back("FindRecord: Searched " + std::to_string(_findStats.count) + " records");
    _metrics.push_back("FindRecord: Avg time = " + 
                        std::to_string(_findStats.totalTime/_findStats.count) + " ms");
    _metrics.push_back("FindRecord: Min time = " + std::to_string(_findStats.minTime) + " ms");
    _metrics.push_back("FindRecord: Max time = " + std::to_string(_findStats.maxTime) + " ms");
    _metrics.push_back("FindRecord: Avg eff = " + 
                        std::to_string(_findStats.totalEfficiency/_findStats.count) + " ops");
    _metrics.push_back("FindRecord: Min eff = " + 
                        std::to_string(_findStats.minEfficiency) + " ops");    
    _metrics.push_back("FindRecord: Max eff = " + 
                        std::to_string(_findStats.maxEfficiency) + " ops");
};

void TableTestKit::DeleteRecord() {
    if (table.IsEmpty()) {
        _metrics.push_back("DeleteRecord: Table is empty");
        return;
    }

    // Собираем ключи для удаления
    std::vector<Key> allKeys;
    table.Reset();
    while (!table.IsTabEnded()) {
        allKeys.push_back(table.GetKey());
        table.GoNext();
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    _deleteStats = OperationStats(); // Сброс статистики
    size_t deleted = 0;

    for (int i = 0; i < 1000 && !allKeys.empty(); i++) {
        size_t idx = std::uniform_int_distribution<size_t>(0, allKeys.size() - 1)(gen);
        Key key = allKeys[idx];

        auto start = std::chrono::high_resolution_clock::now();
        try {
            table.DelRecord(key);
            allKeys.erase(allKeys.begin() + idx);
            deleted++;

            auto end = std::chrono::high_resolution_clock::now();
            double duration = std::chrono::duration<double, std::milli>(end - start).count();
            int efficiency = table.GetEfficiency();

            // Обновляем статистику
            _deleteStats.totalTime += duration;
            _deleteStats.minTime = std::min(_deleteStats.minTime, duration);
            _deleteStats.maxTime = std::max(_deleteStats.maxTime, duration);
            _deleteStats.totalEfficiency += efficiency;
            _deleteStats.minEfficiency = std::min(_deleteStats.minEfficiency, efficiency);
            _deleteStats.maxEfficiency = std::max(_deleteStats.maxEfficiency, efficiency);
            _deleteStats.count++;
        } catch (...) {
            _metrics.push_back("DeleteRecord: Failed to delete " + key);
        }
    }

    _metrics.push_back("DeleteRecord: Deleted " + std::to_string(deleted) + "/1000 records");
    _metrics.push_back("DeleteRecord: Avg time = " + 
                        std::to_string(_deleteStats.totalTime/_deleteStats.count) + " ms");
    _metrics.push_back("DeleteRecord: Min time = " + std::to_string(_deleteStats.minTime) + " ms");
    _metrics.push_back("DeleteRecord: Max time = " + std::to_string(_deleteStats.maxTime) + " ms");
    _metrics.push_back("DeleteRecord: Avg eff = " + 
                        std::to_string(_deleteStats.totalEfficiency/_deleteStats.count) + " ops");
    _metrics.push_back("DeleteRecord: Min eff = " + std::to_string(_deleteStats.minEfficiency) + " ms");
    _metrics.push_back("DeleteRecord: Max eff = " + std::to_string(_deleteStats.maxEfficiency) + " ms");
}


void TableTestKit::PrintMetrics() {
    const int col1 = 30, col2 = 20;
    const std::string sep(col1 + col2 + 3, '-');

    std::cout << "\nMETRICS\n+" << sep << "+\n"
                << "| " << std::left << std::setw(col1) << "METRIC" 
                << " | " << std::setw(col2) << "VALUE" << " |\n+" 
                << sep << "+\n";

    for (const auto& m : _metrics) {
        size_t colon = m.find(':');
        std::string name = m.substr(0, colon);
        std::string value = (colon != std::string::npos) ? m.substr(colon + 2) : "";
        
        std::cout << "| " << std::left << std::setw(col1) << name 
                    << " | " << std::setw(col2) << value << " |\n";
    }

    std::cout << "+" << sep << "+\n";
}

void TableTestKit::TestHashTablePerformance() {
    //std::cout << "Testing table with size: " << hashTable.GetTabSize() << std::endl;
    if (auto hashTable = dynamic_cast<HashTable*>(&table)) {
        hashTable->ResetCollisions(); // 
        hashTable->ResetEfficiency();
        AddMetric("Table Size", std::to_string(hashTable->GetTabSize()));
    }
    
    // Тестирование вставки
    table.ResetEfficiency();
    FillTable();
    if (auto hashTable = dynamic_cast<HashTable*>(&table)) {
        AddMetric("Insert Collisions", std::to_string(hashTable->GetCollisionCount()));
        AddMetric("Insert Efficiency", std::to_string(hashTable->GetEfficiency()));
    }

    // Тестирование поиска
    table.ResetEfficiency();
    FindRecord();
    if (auto hashTable = dynamic_cast<HashTable*>(&table)) {
        AddMetric("Search Efficiency", std::to_string(hashTable->GetEfficiency() / _findStats.count));
    }
    // AddMetric("Find Efficiency (avg)", std::to_string(_findStats.avgEfficiency()));
    
    // Тестирование удаления
    table.ResetEfficiency();
    DeleteRecord();
    if (auto hashTable = dynamic_cast<HashTable*>(&table)) {
        AddMetric("Delete Efficiency", std::to_string(hashTable->GetEfficiency() / _deleteStats.count));
    }
    //AddMetric("Delete Efficiency (avg)", std::to_string(_deleteStats.avgEfficiency()));
    
    // Специфичные для хеш-таблицы метрики
    if (auto hashTable = dynamic_cast<HashTable*>(&table)) {
        AddMetric("Collisions", std::to_string(hashTable->GetCollisionCount()));
        AddMetric("Load Factor", std::to_string(hashTable->GetLoadFactor()));
    }
}