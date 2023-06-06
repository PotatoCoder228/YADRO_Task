//
// Created by sasha on 03.06.2023.
//

#include "../include/App.h"
#include "CsvTable.h"

namespace TestApp {

    int App::start() {
        if (!(this->file.is_open())) {
            std::cerr << "Cannot open target file." << std::endl;
            std::cout << "Program shut down..." << std::endl;
            return EXIT_FAILURE;
        }

        TestApp::CsvTable table;
        table.parseCsvTable(file);
        table.calcAllCells();
        table.printAsCsv();
        this->file.close();
        return EXIT_SUCCESS;
    }

    App::App(char *filename) noexcept: file(filename, std::ios_base::in) {

    }
} // TestApp