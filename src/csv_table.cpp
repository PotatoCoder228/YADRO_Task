//
// Created by sasha on 03.06.2023.
//

#include "../include/csv_table.h"

namespace test_app {

    static void get_format_line(std::fstream &file, std::string &result) {
        result.clear();
        char ch = 0;
        while (ch != '\n') {
            file.get(ch);
            if (file.eof()) {
                break;
            }
            if (ch != ' ' && ch != '\t' && ch != '\n' && ch != '\r') {
                result += ch;
            }
        }
    }

    static std::string format_double(const std::string &str) {
        if (str.find('.') != std::string::npos) return str.substr(0, str.find('.'));
        else return str;
    }

    bool csv_table::parse_from_csv(std::fstream &file) {

        using std::size_t;
        using std::string;
        using std::cout;
        using std::endl;
        using std::stoll;

        string cur_str;
        size_t max_row_sz = 0;
        size_t rows_counter = 0;
        for (size_t i = 0; !file.eof(); i++) {
            get_format_line(file, cur_str);
            if (cur_str.empty()) break;
            if (i == 0) {
                if (cur_str[0] != ',') return false;
                clmns_line_buf = cur_str;
                size_t prev = 1;
                for (size_t j = 0; true; j++) {
                    size_t found_i = cur_str.find(',', prev);
                    if (found_i == string::npos) {
                        string buf = cur_str.substr(prev);
                        if (buf.empty()) return false;
                        columns[buf] = j;
                        max_row_sz++;
                        break;
                    }
                    string buf = cur_str.substr(prev, found_i - prev);
                    columns[buf] = j;
                    max_row_sz++;
                    prev = found_i + 1;
                }
            } else {
                size_t prev = 0;
                for (size_t j = 0; true; j++) {
                    if (j > max_row_sz) {
                        cout << "Count of columns less than count if " << endl;
                        return false;
                    }
                    size_t found_i = cur_str.find(',', prev);
                    if (found_i == string::npos) {
                        string buf = cur_str.substr(prev, found_i - prev);
                        if (table.empty() || buf.empty()) return false;
                        if (buf[0] == '=') {
                            table.back().push_back(buf);
                            struct table_ptr cell{};
                            cell.column = table[i - 1].size() - 1;
                            cell.row = i - 1;
                            calc_queue.push_front(cell);
                        } else {
                            table.back().push_back(buf);
                        }
                        break;
                    }
                    string buf = cur_str.substr(prev, found_i - prev);
                    if (buf.empty()) return false;
                    if (j == 0) {
                        int64_t row_index = stoll(buf);
                        rows[row_index] = rows_counter;
                        std::vector<string> new_vector;
                        table.push_back(new_vector);
                        rows_counter++;
                        rows_names.push_back(row_index);
                    } else {
                        if (buf[0] == '=') {
                            table[i - 1].push_back(buf);
                            struct table_ptr index{};
                            index.column = table[i - 1].size() - 1;
                            index.row = i - 1;
                            calc_queue.push_front(index);
                        } else {
                            table[i - 1].push_back(buf);
                        }
                    }
                    prev = found_i + 1;
                }
            }
        }
        if (!rows.empty() && !columns.empty()) return true;
        else return false;
    }

    void csv_table::print_as_csv() const {
        using std::cout;
        using std::endl;
        cout << clmns_line_buf << endl;
        for (size_t i = 0; i < table.size(); i++) {
            cout << rows_names[i];
            for (const auto &j: table[i]) {
                cout << ",";
                cout << j;
            }
            cout << endl;
        }
    }

    static std::string get_column(const std::string &expression, size_t start) {
        for (size_t i = start; i < expression.size(); i++) {
            if (expression[i] < 'A') {
                return expression.substr(start, i - start);
            }
        }
        return "";
    }

    static std::string get_row(const std::string &expr, size_t start) {
        for (size_t i = start; i < expr.size(); i++) {
            if (expr[i] < '0') {
                return expr.substr(start, i - start);
            }
        }
        return "";
    }

    double csv_table::cell_operation(double arg_1, double arg_2, std::string &op) {
        switch (op[0]) {
            case '+':
                return arg_1 + arg_2;
            case '-':
                return arg_1 - arg_2;
            case '/':
                if (arg_2 == 0) throw std::invalid_argument("Zero division error.");
                return arg_1 / arg_2;
            case '*':
                return arg_1 * arg_2;
        }
        return 0;
    }

    static void parse_action(const std::string &expr, std::string &column_1,
                             std::string &column_2, std::string &row_1,
                             std::string &row_2, std::string &op) {
        size_t offset = 1;
        column_1 = get_column(expr, offset);
        offset += column_1.size();
        row_1 = get_row(expr, offset);
        offset += row_1.size();
        op = expr[offset];
        offset++;
        column_2 = get_column(expr, offset);
        offset += column_2.size();
        row_2 = expr.substr(offset);
    }

    double csv_table::calc(const std::string &expr) {
        using std::string;
        using std::cout;
        using std::endl;
        using std::size_t;
        using std::stoll;
        using std::invalid_argument;

        calc_depth++;
        if (expr[0] != '=') {
            calc_depth--;
            return std::stod(expr);
        }
        string column_1, column_2, row_1, row_2, op;
        parse_action(expr, column_1, column_2, row_1, row_2, op);
        auto col_iter_1 = columns.find(column_1);
        auto col_iter_2 = columns.find(column_2);
        int64_t buf_1 = stoll(row_1);
        int64_t buf_2 = stoll(row_2);
        auto row_iter_1 = rows.find(buf_1);
        auto row_iter_2 = rows.find(buf_2);
        if (!op.empty()) {
            double arg_1;
            double arg_2;

            if (col_iter_1 == columns.end()) {
                if (!column_1.empty()) throw invalid_argument("Invalid column name");
                arg_1 = buf_1;
            } else {
                size_t col_index_1 = col_iter_1->second;
                size_t row_index_2 = row_iter_1->second;
                if (calc_depth > MAX_DEPTH) {
                    struct table_ptr cell{};
                    cell.column = col_index_1;
                    cell.row = row_index_2;
                    calc_queue.push_front(cell);
                    return 0;
                }
                if (row_iter_1 == rows.end()) {
                    throw invalid_argument("Incorrect cell index");
                }
                arg_1 = calc(table[row_index_2][col_index_1]);
                if (calc_depth > MAX_DEPTH) return 0;
                table[row_index_2][col_index_1] = format_double(std::to_string(arg_1));
            }


            if (col_iter_2 == columns.end()) {
                if (!column_2.empty()) throw invalid_argument("Invalid column name");
                arg_2 = buf_2;
            } else {
                size_t col_index_1 = col_iter_2->second;
                size_t row_index_2 = row_iter_2->second;
                if (row_iter_2 == rows.end()) {
                    throw invalid_argument("Incorrect cell index");
                }
                arg_2 = calc(table[row_index_2][col_index_1]);
                if (calc_depth > MAX_DEPTH) return 0;
                table[row_index_2][col_index_1] = format_double(std::to_string(arg_2));
            }
            double result = cell_operation(arg_1, arg_2, op);
            calc_depth--;
            return result;
        } else {
            cout << "Incorrect formula in the cell: " << expr << endl;
            calc_depth--;
            return 0;
        }
    }

    void csv_table::moveChain() {
        struct table_ptr buf1 = calc_queue.front();
        calc_queue.pop_front();
        struct table_ptr buf2 = calc_queue.front();
        calc_queue.pop_front();
        calc_queue.push_front(buf1);
        calc_queue.push_back(buf2);
    }

    bool csv_table::calc_cells() {
        using std::string;
        using std::cout;
        using std::endl;
        using std::invalid_argument;
        using std::out_of_range;

        std::size_t queue_length = calc_queue.size();
        while (!calc_queue.empty()) {
            calc_depth = 0;
            struct table_ptr cell = calc_queue.front();
            string expr = table[cell.row][cell.column];
            try {
                if (expr[0] == '=') {
                    double value = calc(expr);
                    if (calc_depth > MAX_DEPTH) {
                        moveChain();
                        queue_length--;
                        if (queue_length == 0) {
                            throw invalid_argument("Recursive call chain detected!\nFormula:" + expr);
                        }
                        continue;
                    }
                    table[cell.row][cell.column] = format_double(std::to_string(value));
                }
            } catch (invalid_argument &e) {
                cout << e.what() << endl;
                cout << "The calculation error, something cell contains incorrect formula/number" << endl;
                return false;
            } catch (out_of_range &e) {
                cout << "The calculation error, something cell contains a value that is out of range!"
                     << endl;
                return false;
            }
            calc_queue.pop_front();
        }
        return true;
    }
} // TestApp