# Лабораторная №6

> 1 тест проверяет вычисление контрольной суммы с использованием конкретного метода вычисления на маленьком объеме данных - 3 байта\
2 тест проверяет выичсление контрольной суммы с использованием конкретного метода вычисления на среднем объеме данных - 2.2 KB\
3 тест проверяет вычисление контрольной суммы с использованием конкретного метода вычисления на большом объеме данных - 2.8 MB


**№1.** *Разработать программу (check-xor.c), 
которая вычисляет с использованием XOR и выводит контрольную сумму для входных файлов. 
Использовать 8-битный символ без знака (1 байт) под эту сумму.\
Продемонстрировать работу на тестах (тест=входные данные, 
для которых правильный результат известен заранее, 
т.е. данные и ожидаемый результат), подготовленных систематически.*

Код: [check-xor.c](https://github.com/sapiest/OS_labs/blob/master/Lab6/task1_check-xor.c)

**№2.** *Разработать аналогичную программу (check-fletcher.c),
 которая вычисляет и выводит контрольную сумму Флетчера ( the Fletcher checksum) для входных файлов.\
 Продемонстрировать работу на тестах (тест=входные данные, 
 для которых правильный результат известен заранее, 
 т.е. данные и ожидаемый результат), подготовленных систематически.*
 
 Код: [check-fletcher.c](https://github.com/sapiest/OS_labs/blob/master/Lab6/task2_check-fletcher.c)
 
 **№3.** *Разработать аналогичную программу (crc.c), 
 которая вычисляет и выводит 16-битный циклический избыточный код (the 16-bit CRC).\
 Продемонстрировать работу на тестах (тест=входные данные, 
 для которых правильный результат известен заранее, т.е. данные и ожидаемый результат), подготовленных систематически. 
 Продемонстрировать работу на тестах (тест=входные данные, для которых правильный результат известен заранее, 
 т.е. данные и ожидаемый результат), подготовленных систематически.*
 
 Код: [crc.c](https://github.com/sapiest/OS_labs/blob/master/Lab6/task3_crc.c)
 
 **№4.** * Сравнить время работы (gettimeofday) программ из 1, 2 и 3 на входных файлах различных размеров.
 Какая предпочтительнее с точки зрения времени и качества проверки? 
 Продемонстрировать работу на тестах (тест=входные данные, для которых правильный результат известен заранее, 
 т.е. данные и ожидаемый результат), подготовленных систематически.*
 
 ```
Тесты XOR
Тест №1 (3 байта) 0.000005 с
Тест №2 (2.2 КБайта) 0.000009 с
Тест №3 (2.8 МБайта) 0.010680 с

Тесты Fletcher
Тест №1 (3 байта) 0.000004 с
Тест №2 (2.2 КБайта) 0.000019 с
Тест №3 (2.8 МБайта) 0.022685 с

Тесты Crc-16
Тест №1 (3 байта) 0.000003 с
Тест №2 (2.2 КБайта) 0.000022 с
Тест №3 (2.8 МБайта) 0.014007с

```

Делаем вывод, что CRC-16 наиболее оптимальный. По времени ненамного проигрывает XOR,\
при этом выигрывая в надежности (т.к. алгоритм шифрования сложнее)

**№5.** *Разработать программу (create-csum.c), которая вычисляет однобайтовые контрольные суммы для каждого 
4KB блока входного файла и сохраняет их в контрольном файле,\
а также программу (check-csum.c), которая читает файл, также вычисляет однобайтовые контрольные суммы для каждого 
4KB блока и сравнивает их с заранее вычисленными значениями из контрольного файла.\
Если обнаруживаются расхождения,то выводятся соответствующие сообщения. \
Продемонстрировать работу на тестах (тест=входные данные, для которых правильный результат известен заранее, т.е. данные и ожидаемый результат),
 подготовленных систематически.* 

Код: [create-csum.c](https://github.com/sapiest/OS_labs/blob/master/Lab6/task5_create-csum.c)\
Код: [check-csum.c](https://github.com/sapiest/OS_labs/blob/master/Lab6/task5_check-csum.c)

Вычислили с помощью CRC-8 контрольную сумму для блоков, размером в 4 кб и сохранили в файле.\
Испльзуя CRC-8 вычислили контрольную сумму и сравниили с полученной и предыдущего пункта.
