//
// Created by sasha on 03.06.2023.
//

#include "CsvTable.h"

namespace TestApp {

    bool CsvTable::parseCsvTable(std::fstream &file) {

        std::string curStr;
        size_t maxRowSize = 0;
        size_t rowsCounter = 0;
        for (size_t i = 0; !file.eof(); i++) {
            getline(file, curStr);
            //std::cout<< curStr <<std::endl;
            if(i == 0){
                hack = curStr;
                size_t prev = 1;
                size_t founded_i;
                std::string buf;
                for(size_t j = 0; true; j++){//TODO
                    founded_i = curStr.find(',', prev);
                    if(founded_i == std::string::npos){
                        buf = curStr.substr(prev);
                        //std::cout<< buf <<std::endl;
                        columns[buf] = j - 1;
                        maxRowSize++;
                        break;
                    }
                    buf = curStr.substr(prev, founded_i-prev);
                    //std::cout<< buf <<std::endl;
                    columns[buf] = j - 1;
                    maxRowSize++;
                    prev = founded_i+1;
                }
            }
            else{
                //std::cout<<curStr<<std::endl;
                size_t prev = 0;
                size_t founded_i;
                std::string buf;
                for(size_t j = 0; true; j++){//TODO
                    if(j>maxRowSize){
                        std::cout <<"Размер одной из строк больше количества столбцов"<<std::endl;
                        return false;
                    }
                    founded_i = curStr.find(',', prev);
                    if(founded_i == std::string::npos) {
                        buf = curStr.substr(prev, founded_i-prev);
                        //std::cout<< buf <<std::endl;
                        if (buf[0] == '=') {
                            table[i-1][rowsCounter] = buf;
                            calcCells.push_back(std::make_shared<std::string>(table[j-1][rowsCounter]));
                        } else {
                            table[i-1][rowsCounter] = buf;
                        }
                        break;
                    }
                    buf = curStr.substr(prev, founded_i-prev);
                    //std::cout<<buf<<std::endl;
                    if(j == 0){
                        int64_t rowNum = std::stoi(buf);
                        rows[rowNum] = rowsCounter;
                        std::vector<std::string> new_vector;
                        table.push_back(new_vector);
                        rowsCounter++;
                        rowsNames.push_back(rowNum);
                    }
                    else{
                        if (buf[0] == '=') {
                            table[i-1].push_back(buf);
                            calcCells.push_back(std::make_shared<std::string>(table[j-1][rowsCounter]));
                        } else {
                            table[i-1].push_back(buf);
                        }
                    }
                    prev = founded_i+1;
                }
                rowsCounter++;
            }
        }
        return true;
    }

    /*
    bool CsvTable::parseCsvTable(std::fstream &file) {

        std::string curStr;
        bool isColumnName = true;
        size_t maxRowSize = 0;
        size_t rowsCounter = 0;
        size_t columnCounter = 0;
        for (size_t i = 0; !file.eof(); i++) {
            getline(file, curStr, ',');
            if (i == 0) {
                continue;
            } else {
                if (curStr[0] == '\n') {
                    isColumnName = false;
                    curStr[0] = ' ';
                    int64_t rowNum = std::stoi(curStr);
                    rows[rowNum] = rowsCounter;
                    rowsCounter++;
                    columnCounter = 0;
                    continue;
                }
                if (isColumnName) {
                    columns[curStr] = i - 1;
                    maxRowSize++;
                    hack+=','+curStr;
                    continue;
                }
                columnCounter++;
                if (columnCounter > maxRowSize) {
                    std::cout << "Длина одного из столбцов выходит за предел." << std::endl;
                    return false;
                }
                if (curStr[0] == '=') {
                    table[columnCounter][rowsCounter] = curStr;
                    calcCells.push_back(std::make_shared<std::string>(table[columnCounter][rowsCounter]));
                } else {
                    table[columnCounter][rowsCounter] = curStr;
                }
            }
        }
        return true;
    }
    */

    void CsvTable::printAsCsv() {
        std::cout<<hack<<std::endl;
        for(size_t i = 0; i<table.size(); i++){
            std::cout<<rowsNames[i];
            for(const auto & j : table[i]){
                std::cout<<",";
                std::cout<<j;
            }
            std::cout<<std::endl;
        }
    }
} // TestApp