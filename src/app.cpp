//
// Created by sasha on 03.06.2023.
//

#include "../include/app.h"
#include "../include/csv_table.h"

namespace test_app {

    int app::start(const char *filename) {
        using std::invalid_argument;
        using std::out_of_range;
        using std::cout;
        using std::endl;

        std::shared_ptr<std::wfstream> file_ptr(new std::wfstream(filename, std::ios::in), [](std::wfstream *f) {
            if (f->is_open()) {
                f->close();
            }
            delete f;
        });

        (*file_ptr).imbue(std::locale(std::locale(""), new std::codecvt_utf8<wchar_t>));

        if (!(file_ptr->is_open())) {
            cout << "Cannot open target file." << endl;
            cout << "Program shut down..." << endl;
            return EXIT_FAILURE;
        }

        try {
            csv_table table;
            bool stat = table.parse_from_csv(*file_ptr);
            if (stat) stat = table.calc_cells();
            if (stat) table.print_as_csv();
            else cout << "The table not found" << endl;
        } catch (invalid_argument &e) {
            cout << e.what() << endl;
            cout << "Cannot parse csv-table. Something cell contains a invalid value." << endl;
        } catch (out_of_range &e) {
            cout << e.what() << endl;
            cout << "Cannot parse csv-table. Something row-number contains a value that is out of range!"
                 << endl;
        }
        return EXIT_SUCCESS;
    }
} // TestApp