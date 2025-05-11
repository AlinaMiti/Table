#include "TableTestKit.h"

TableTestKit::TableTestKit(Table& table): table(table){}

void TableTestKit::FillTable(){
    std::cout << "Enter key-value pairs, type 'end' to finish:" << std::endl;
    Key key;
    PDatValue value;
    while(true){
        std::cout << "Enter key (or 'end'): ";
        std::cin >> key;
            if (key == "end") break;
        std::cout << "Enter value: ";
        //std::cin >> &value;
    }
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