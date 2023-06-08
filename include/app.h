//
// Created by sasha on 03.06.2023.
//

#ifndef YADRO_TASK_APP_H
#define YADRO_TASK_APP_H

#include "all_headers.h"

namespace test_app {

    class app {
    public:
        explicit app(char *filename) noexcept;

        ~app() = default;

        int start();

    private:
        std::wfstream file;
    };

} // TestApp

#endif //YADRO_TASK_APP_H
