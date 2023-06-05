//
// Created by sasha on 03.06.2023.
//

#ifndef YADRO_TASK_APP_H
#define YADRO_TASK_APP_H

#include "allheaders.h"

namespace TestApp {

    class App {
    public:
        explicit App(char *filename) noexcept;

        ~App() = default;

        int start();

    private:
        std::fstream file;
    };

} // TestApp

#endif //YADRO_TASK_APP_H
