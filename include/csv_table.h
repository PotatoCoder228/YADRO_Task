//
// Created by sasha on 03.06.2023.
//

#ifndef YADRO_TASK_CSV_TABLE_H
#define YADRO_TASK_CSV_TABLE_H

#include "all_headers.h"

namespace test_app {

    class csv_table {
    public:
        bool parse_from_csv(std::fstream &file);

        void print_as_csv() const;

        bool calc_cells();

    private:
        struct table_ptr {
        public:
            std::size_t column;
            std::size_t row;
        };

        double calc(const std::string &expr);

        static double cell_operation(double arg_1, double arg_2, std::string &op);

        void moveChain();

        std::vector<std::vector<std::string>> table;
        std::map<std::string, std::size_t> columns;
        std::map<std::size_t, std::size_t> rows;
        std::vector<std::size_t> rows_names;
        std::deque<table_ptr> calc_queue;
        std::string clmns_line_buf;
        std::size_t calc_depth;
        const std::size_t MAX_DEPTH = 2000;
    };

} // TestApp

#endif //YADRO_TASK_CSV_TABLE_H
