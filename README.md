# Тестовое задание для стажировки в YADRO

## Компиляция, линковка и запуск программы

Клонирование репозитория в текущую директорию:

***$git clone https://github.com/PotatoCoder228/YADRO_Task***

Для компиляции используем ***CMake***, в директории с проектом прописываем:

***$cmake ./***

***CMake*** подготовит **Makefile** и цели в нём, поэтому достаточно будет написать название
утилиты:

***$make***

## Тестирование

Для тестирования программы я подготовил 9 .csv-файлов в папке tests:

* 0-3 тесты тестируют поведение парсера при некорректных файлах, чтобы программа не падала;
* 4-5 тесты тестируют обращение по несуществующим строкам/столбцам;
* 6 тест - тестирование вычисления "зависимостей", вложенных в друг друга формул + проверка переполнения;
* 7 тест - тестирование вычисления вложенных формул, но с другим типом выражения
* 8 тест - тестирование вычисления вложенных формул, формул вида "=1+1", "=A1+B1", а также
  тестирование форматирования ввода из файла на предмет лишних пробельных символов;
* 9 тест - простой тест на выявление циклических формул;