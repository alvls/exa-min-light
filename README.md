# Демонстрационная система по глобальной оптимизации

## Требования
1. Демонстрационная система предназначена для решения задач многомерной глобальной однокритериальной оптимизации.
2. Размерность решаемых задач жестко ограничена. Текущий вариант - до 5 параметров.
3. В первой версии системы рассматриваются задачи только безусловной оптимизации.
4. Метод решения основан на редукции размерности с использованием разверток.
5. Редукция выполняется с использованием одиночной или множественной (вращаемой) развертки.
6. Распараллеливание выполняется по характеристикам.
7. Первая версия ориентирована только на системы с общей памятью и не использует MPI.
8. Работа с матрицей состояния поиска ускоряется за счет использования глобальной очереди характеристик.
9. Матрица состояния поиска хранится в виде АВЛ-дерева.
10. Постановка задачи оптимизации с точки зрения пользователя системы состоит в подключении динамической библиотеки, в которой должна быть реализована оптимизируемая функция.
11. Система рассчитана на поиск глобального минимума оптимизируемой функции. Если требуется поиск максимума, нужно соответствующим образом переформулировать задачу и исправить dll с оптимизируемой функцией.
12. Система представляет собой консольное приложение без графического интерфейса.
13. Система будет поставляться в исходных кодах и будет выложена в Интернет.
14. Ближе к концу разработки будет выбрана лицензия, под которой будет поставляться система (текущее понимание – использовать LGPL).

## Основные классы
1. Процесс - управляющий класс, отвечает за создание всех объектов системы.
2. Метод - класс, содержащий метод решения.
3. Задача - класс инкапсулирует задачу оптимизации.
4. Поисковая информация - класс инкапсулирует МСП и методы ее обработки. МСП в классе хранится в виде АВЛ-дерева.
5. Одиночная развертка.
6. Множественная (вращаемая) развертка.
6. Очередь - хранит интервалы с лучшими характеристиками.

## Этапы и сроки
### Предварительные замечания:
1. Большая часть кода будет взята из ExaMin.
2. Для всего позаимствованного кода будет выполнен рефакторинг с целью удаления не требующейся функциональности. Как результат, большинство этапов будут состоять не в разработке соответствующих классов, а в их модификации.
3. Для всех основных методов всех классов будут разработаны тесты с использованием библиотеки Google Test. Как минимум по два теста на метод - с корректным входом, с некорректным входом.
4. С самого начала работы будет подготовлена инфраструктура для постоянного запуска тестов. Каждый этап будет считаться выполненным только при нулевом числе тестов с состоянием FAILED.
5. Разработка будет вестись на GitHub-е. 
6. Начало работы - 1 октября. Окончание работы - 23 декабря.

### Этап 1. Метод + одиночная развертка
- Подготовка инфраструктуры проекта
- Модификация класса Метод из ExaMin.
- Подключение класса Развертка из ExaMin
- Разработка тестов для классов Развертка, Метод

На этом этапе работа с поисковой информацией будет целиком взята из ExaMin, оптимизируемая функция будет задаваться прямо в коде, без использования dll. Класса Процесс не будет, его функции будут реализованы непосредственно в функции main(). Развертка будет только одиночная.

**_Результаты этапа_**

Подготовлена инфраструктура проекта. Подготовлены тесты для классов Развертка, Метод.

**_Срок - 21 октября_**

### Этап 2. Задача + поисковая информация
- Модификация класса Задача из ExaMin
- Модификация класса Поисковая информация из ExaMin
- Модификация класса Очередь из ExaMin
- Разработка тестов для классов Задача, Поисковая информация, Очередь

На этом этапе указанные выше классы будут модифицированы под требования ТЗ.

**_Результаты этапа_**

Подготовлены тесты для классов Задача, Поисковая информация, Очередь. Система способна искать глобальный минимум функций, заданных непосредственно в коде, используя одиночную развертку.

**_Срок - 11 ноября_**

### Этап 3. Множественная развертка
- Перенос множественной (вращаемой развертки) из ExaMin
- Модификация класса Метод для использования множественной развертки
- Разработка тестов для класса Множественная развертка

**_Результаты этапа_**

Подготовлены тесты для класса Множественная развертка. Система способна искать глобальный минимум функций, заданных непосредственно в коде, используя одиночную илии множественную развертку.

**_Срок - 2 декабря_**

### Этап 4. Процесс и постановка задачи
- Разработка класса Процесс
- Разработка шаблона dll с постановкой задачи (на основе схемы из Global Expert с исключением ненужных деталей)
- Разработка тестов для класса Процесс
- Разработка консольного интерфейса
- Подготовка кода к выкладыванию в Интернет (Readme, лицензия, оформление исходников и т.д.).

**_Результаты этапа_**

Подготовлены тесты для класса Процесс. Система способна искать глобальный минимум функций, заданных в виде dll, используя одиночную или множественную развертку.

**_Срок – 23 декабря_**

