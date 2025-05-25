#include "TableTestKit.h"

TableTestKit::TableTestKit(Table& table): table(table){}

void TableTestKit::FillTable(){
    std::string filename;
    std::cout << "File name?: ";
    std::cin >> filename;

    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cerr << "No open file '" << filename << "'" << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inputFile, line)) {
        std::stringstream ss(line);
        std::string key;
        int math, physics, sport, psychology, history;
        char delimiter; // Для хранения разделителей

        if (std::getline(ss, key, ',') &&
            ss >> math >> delimiter && delimiter == ',' &&
            ss >> physics >> delimiter && delimiter == ',' &&
            ss >> sport >> delimiter && delimiter == ',' &&
            ss >> psychology >> delimiter && delimiter == ',' &&
            ss >> history) {

            PDatValue datValue = new Marks(math, physics, sport, psychology, history);
            table.InsRecord(key, datValue);
        } else {
            std::cerr << "Format noy: '" << line << "'" << std::endl;
        }
    }

    inputFile.close();
    std::cout << filename << "'" << std::endl;
}

void TableTestKit::GenBenchmarkTab(){};

void TableTestKit::ShowTable(){
    std::cout << "Table Content:" << std::endl;
    if (table.IsEmpty()) {
        std::cout << "Table is empty." << std::endl;
        return;
    }

    table.Reset();
    while (!table.IsTabEnded()) {
        Key key = table.GetKey();
        PDatValue value = table.GetValue();
        std::cout << "Key: " << key << ", Value: " << *value << std::endl;  // Assuming << operator is overloaded
        table.GoNext();
    }
};

void TableTestKit::FindRecord(){};

void TableTestKit::DeleteRecord(){};

void TableTestKit::PrintMetrics(){};