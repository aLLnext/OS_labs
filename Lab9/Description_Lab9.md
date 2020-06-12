# Лабораторная №9

**№1.** *С помощью helgrind (valgrind --tool=helgrind main-race) в программе main-race.c\
проанализировать ошибки в коде, связанные с несинхронизованностью потоков команд,
работающих с общими данными (data race), и попытаться их устранить.*


Ввели данные команды.
```
gcc main-race.c -o main-race -lpthread
valgrind --tool=helgrind ./main-race 
```

Получили отчет, который можем проанализировать.

```
==5989== Possible data race during read of size 4 at 0x10C084 by thread #1
==5989== Locks held: none
==5989==    at 0x109516: main (in /home/sapiest/OS_labs/Lab9/main-race)
==5989== 
==5989== This conflicts with a previous write of size 4 by thread #2
==5989== Locks held: none
==5989==    at 0x1094CE: worker (in /home/sapiest/OS_labs/Lab9/main-race)
==5989==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
==5989==    by 0x489646E: start_thread (in /usr/lib/libpthread-2.31.so)
==5989==    by 0x49AE3D2: clone (in /usr/lib/libc-2.31.so)
==5989==  Address 0x10c084 is 0 bytes inside data symbol "balance"
==5989== 
==5989== ----------------------------------------------------------------
==5989== 
==5989== Possible data race during write of size 4 at 0x10C084 by thread #1
==5989== Locks held: none
==5989==    at 0x10951F: main (in /home/sapiest/OS_labs/Lab9/main-race)
==5989== 
==5989== This conflicts with a previous write of size 4 by thread #2
==5989== Locks held: none
==5989==    at 0x1094CE: worker (in /home/sapiest/OS_labs/Lab9/main-race)
==5989==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
==5989==    by 0x489646E: start_thread (in /usr/lib/libpthread-2.31.so)
==5989==    by 0x49AE3D2: clone (in /usr/lib/libc-2.31.so)
==5989==  Address 0x10c084 is 0 bytes inside data symbol "balance"
==5989== 
==5989== 
==5989== Use --history-level=approx or =none to gain increased speed, at
==5989== the cost of reduced accuracy of conflicting-access information
==5989== For lists of detected and suppressed errors, rerun with: -s
==5989== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
```
Отчет показывает, что у нас есть 2 ошибки, связанные с "гонкой данных",
так как переменная balance используется в 2 потоках одновременно,
а блокировки отсутствуют.

Решение - добавить блокировку.
Заменить 
```balance++```
на 
```
pthread_mutex_t m; //создали мьютекс

Pthread_mutex_lock(&m); //блокировка мьютекса
balance++;
Pthread_mutex_unlock(&m); //разблокировка мьютекса
```  

Проверяем через helgrind:

```
==6292== Use --history-level=approx or =none to gain increased speed, at
==6292== the cost of reduced accuracy of conflicting-access information
==6292== For lists of detected and suppressed errors, rerun with: -s
==6292== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
Видим, что ошибок нет.
         
**№2.** *В программе main-deadlock.c имеется ошибка, называемая мёртвая блокировка
(deadlock, ситуация, при которой один поток (поток A), ждет ресурса,
удерживаемого другим потоком (потоком B),
и при этом удерживает ресурс, который нужен потоку B.
Поскольку потоки A и B блокированы в ожидании ресурсов, 
удерживаемых другим потоком, выполнения не происходит).
Использовать helgrind и проинтерпретировать отчет.*

Вводим команды:

```
gcc main-deadlock.c -o main-deadlock -lpthread
valgrind --tool=helgrind ./main-deadlock
```

Получим отчет:

```
==6473== 
==6473== Thread #3: lock order "0x10C0A0 before 0x10C0E0" violated
==6473== 
==6473== Observed (incorrect) order is: acquisition of lock at 0x10C0E0
==6473==    at 0x483DC3F: mutex_lock_WRK (hg_intercepts.c:909)
==6473==    by 0x1092C6: Pthread_mutex_lock (in /home/sapiest/OS_labs/Lab9/main-deadlock)
==6473==    by 0x1094F5: worker (in /home/sapiest/OS_labs/Lab9/main-deadlock)
==6473==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
==6473==    by 0x489646E: start_thread (in /usr/lib/libpthread-2.31.so)
==6473==    by 0x49AE3D2: clone (in /usr/lib/libc-2.31.so)
==6473== 
==6473==  followed by a later acquisition of lock at 0x10C0A0
==6473==    at 0x483DC3F: mutex_lock_WRK (hg_intercepts.c:909)
==6473==    by 0x1092C6: Pthread_mutex_lock (in /home/sapiest/OS_labs/Lab9/main-deadlock)
==6473==    by 0x109501: worker (in /home/sapiest/OS_labs/Lab9/main-deadlock)
==6473==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
==6473==    by 0x489646E: start_thread (in /usr/lib/libpthread-2.31.so)
==6473==    by 0x49AE3D2: clone (in /usr/lib/libc-2.31.so)
==6473== 
==6473== Required order was established by acquisition of lock at 0x10C0A0
==6473==    at 0x483DC3F: mutex_lock_WRK (hg_intercepts.c:909)
==6473==    by 0x1092C6: Pthread_mutex_lock (in /home/sapiest/OS_labs/Lab9/main-deadlock)
==6473==    by 0x1094DB: worker (in /home/sapiest/OS_labs/Lab9/main-deadlock)
==6473==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
==6473==    by 0x489646E: start_thread (in /usr/lib/libpthread-2.31.so)
==6473==    by 0x49AE3D2: clone (in /usr/lib/libc-2.31.so)
==6473== 
==6473==  followed by a later acquisition of lock at 0x10C0E0
==6473==    at 0x483DC3F: mutex_lock_WRK (hg_intercepts.c:909)
==6473==    by 0x1092C6: Pthread_mutex_lock (in /home/sapiest/OS_labs/Lab9/main-deadlock)
==6473==    by 0x1094E7: worker (in /home/sapiest/OS_labs/Lab9/main-deadlock)
==6473==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
==6473==    by 0x489646E: start_thread (in /usr/lib/libpthread-2.31.so)
==6473==    by 0x49AE3D2: clone (in /usr/lib/libc-2.31.so)
==6473== 
==6473==  Lock at 0x10C0A0 was first observed
==6473==    at 0x483DC3F: mutex_lock_WRK (hg_intercepts.c:909)
==6473==    by 0x1092C6: Pthread_mutex_lock (in /home/sapiest/OS_labs/Lab9/main-deadlock)
==6473==    by 0x1094DB: worker (in /home/sapiest/OS_labs/Lab9/main-deadlock)
==6473==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
==6473==    by 0x489646E: start_thread (in /usr/lib/libpthread-2.31.so)
==6473==    by 0x49AE3D2: clone (in /usr/lib/libc-2.31.so)
==6473==  Address 0x10c0a0 is 0 bytes inside data symbol "m1"
==6473== 
==6473==  Lock at 0x10C0E0 was first observed
==6473==    at 0x483DC3F: mutex_lock_WRK (hg_intercepts.c:909)
==6473==    by 0x1092C6: Pthread_mutex_lock (in /home/sapiest/OS_labs/Lab9/main-deadlock)
==6473==    by 0x1094E7: worker (in /home/sapiest/OS_labs/Lab9/main-deadlock)
==6473==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
==6473==    by 0x489646E: start_thread (in /usr/lib/libpthread-2.31.so)
==6473==    by 0x49AE3D2: clone (in /usr/lib/libc-2.31.so)
==6473==  Address 0x10c0e0 is 0 bytes inside data symbol "m2"
==6473== 
==6473== 
==6473== 
==6473== Use --history-level=approx or =none to gain increased speed, at
==6473== the cost of reduced accuracy of conflicting-access information
==6473== For lists of detected and suppressed errors, rerun with: -s
==6473== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 7 from 7)
```

Проанализировав отчет, мы можем сделать вывод, что мы неправильно используем мьютексы.

**№3.** *Также использовать helgrind для main-deadlock-global.c
и проанализировать отчет, сравнить с предыдущим.*

Вводим команды:

```
gcc main-deadlock-global.c -o main-deadlock -lpthread
valgrind --tool=helgrind ./main-deadlock-global
```

Получим отчет:

```
==6906== Thread #3: lock order "0x10C0E0 before 0x10C120" violated
==6906== 
==6906== Observed (incorrect) order is: acquisition of lock at 0x10C120
==6906==    at 0x483DC3F: mutex_lock_WRK (hg_intercepts.c:909)
==6906==    by 0x1092C6: Pthread_mutex_lock (in /home/sapiest/OS_labs/Lab9/main-deadlock-global)
==6906==    by 0x109501: worker (in /home/sapiest/OS_labs/Lab9/main-deadlock-global)
==6906==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
==6906==    by 0x489646E: start_thread (in /usr/lib/libpthread-2.31.so)
==6906==    by 0x49AE3D2: clone (in /usr/lib/libc-2.31.so)
==6906== 
==6906==  followed by a later acquisition of lock at 0x10C0E0
==6906==    at 0x483DC3F: mutex_lock_WRK (hg_intercepts.c:909)
==6906==    by 0x1092C6: Pthread_mutex_lock (in /home/sapiest/OS_labs/Lab9/main-deadlock-global)
==6906==    by 0x10950D: worker (in /home/sapiest/OS_labs/Lab9/main-deadlock-global)
==6906==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
==6906==    by 0x489646E: start_thread (in /usr/lib/libpthread-2.31.so)
==6906==    by 0x49AE3D2: clone (in /usr/lib/libc-2.31.so)
==6906== 
==6906== Required order was established by acquisition of lock at 0x10C0E0
==6906==    at 0x483DC3F: mutex_lock_WRK (hg_intercepts.c:909)
==6906==    by 0x1092C6: Pthread_mutex_lock (in /home/sapiest/OS_labs/Lab9/main-deadlock-global)
==6906==    by 0x1094E7: worker (in /home/sapiest/OS_labs/Lab9/main-deadlock-global)
==6906==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
==6906==    by 0x489646E: start_thread (in /usr/lib/libpthread-2.31.so)
==6906==    by 0x49AE3D2: clone (in /usr/lib/libc-2.31.so)
==6906== 
==6906==  followed by a later acquisition of lock at 0x10C120
==6906==    at 0x483DC3F: mutex_lock_WRK (hg_intercepts.c:909)
==6906==    by 0x1092C6: Pthread_mutex_lock (in /home/sapiest/OS_labs/Lab9/main-deadlock-global)
==6906==    by 0x1094F3: worker (in /home/sapiest/OS_labs/Lab9/main-deadlock-global)
==6906==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
==6906==    by 0x489646E: start_thread (in /usr/lib/libpthread-2.31.so)
==6906==    by 0x49AE3D2: clone (in /usr/lib/libc-2.31.so)
==6906== 
==6906==  Lock at 0x10C0E0 was first observed
==6906==    at 0x483DC3F: mutex_lock_WRK (hg_intercepts.c:909)
==6906==    by 0x1092C6: Pthread_mutex_lock (in /home/sapiest/OS_labs/Lab9/main-deadlock-global)
==6906==    by 0x1094E7: worker (in /home/sapiest/OS_labs/Lab9/main-deadlock-global)
==6906==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
==6906==    by 0x489646E: start_thread (in /usr/lib/libpthread-2.31.so)
==6906==    by 0x49AE3D2: clone (in /usr/lib/libc-2.31.so)
==6906==  Address 0x10c0e0 is 0 bytes inside data symbol "m1"
==6906== 
==6906==  Lock at 0x10C120 was first observed
==6906==    at 0x483DC3F: mutex_lock_WRK (hg_intercepts.c:909)
==6906==    by 0x1092C6: Pthread_mutex_lock (in /home/sapiest/OS_labs/Lab9/main-deadlock-global)
==6906==    by 0x1094F3: worker (in /home/sapiest/OS_labs/Lab9/main-deadlock-global)
==6906==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
==6906==    by 0x489646E: start_thread (in /usr/lib/libpthread-2.31.so)
==6906==    by 0x49AE3D2: clone (in /usr/lib/libc-2.31.so)
==6906==  Address 0x10c120 is 0 bytes inside data symbol "m2"
==6906== 
==6906== 
==6906== 
==6906== Use --history-level=approx or =none to gain increased speed, at
==6906== the cost of reduced accuracy of conflicting-access information
==6906== For lists of detected and suppressed errors, rerun with: -s
==6906== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 7 from 7)
```

По отчету helgrind можно понять об аналогичной ошибке как в 3 задании, 
тогда как она отсутствует, так как дополнительный мьютекс не допускает такую ситуацию.
 
**№4.** *В программе main-signal.c переменная (done)\
используется для того, чтобы обозначить состояние,\
когда дочерний процесс закончил работу и родительский может продолжить.\
Проанализировать эффективность и результат работы helgrind\
на этой программе.*

Вводим команды:

```
gcc main-signal.c -o main-signal -lpthread
valgrind --tool=helgrind ./main-signal 
```

Получаем отчет:

```
this should print first
==7184== ---Thread-Announcement------------------------------------------
==7184== 
==7184== Thread #1 is the program's root thread
==7184== 
==7184== ---Thread-Announcement------------------------------------------
==7184== 
==7184== Thread #2 was created
==7184==    at 0x49AE3C2: clone (in /usr/lib/libc-2.31.so)
==7184==    by 0x489532B: create_thread (in /usr/lib/libpthread-2.31.so)
==7184==    by 0x4896C9B: pthread_create@@GLIBC_2.2.5 (in /usr/lib/libpthread-2.31.so)
==7184==    by 0x4840677: pthread_create_WRK (hg_intercepts.c:427)
==7184==    by 0x109453: Pthread_create (in /home/sapiest/OS_labs/Lab9/main-signal)
==7184==    by 0x109530: main (in /home/sapiest/OS_labs/Lab9/main-signal)
==7184== 
==7184== ----------------------------------------------------------------
==7184== 
==7184== Possible data race during read of size 4 at 0x10C08C by thread #1
==7184== Locks held: none
==7184==    at 0x109532: main (in /home/sapiest/OS_labs/Lab9/main-signal)
==7184== 
==7184== This conflicts with a previous write of size 4 by thread #2
==7184== Locks held: none
==7184==    at 0x1094E5: worker (in /home/sapiest/OS_labs/Lab9/main-signal)
==7184==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
==7184==    by 0x489646E: start_thread (in /usr/lib/libpthread-2.31.so)
==7184==    by 0x49AE3D2: clone (in /usr/lib/libc-2.31.so)
==7184==  Address 0x10c08c is 0 bytes inside data symbol "done"
==7184== 
==7184== ----------------------------------------------------------------
==7184== 
==7184== Possible data race during write of size 1 at 0x52791A5 by thread #1
==7184== Locks held: none
==7184==    at 0x4846526: mempcpy (vg_replace_strmem.c:1537)
==7184==    by 0x4930871: _IO_file_xsputn@@GLIBC_2.2.5 (in /usr/lib/libc-2.31.so)
==7184==    by 0x4926237: puts (in /usr/lib/libc-2.31.so)
==7184==    by 0x109547: main (in /home/sapiest/OS_labs/Lab9/main-signal)
==7184==  Address 0x52791a5 is 21 bytes inside a block of size 1,024 alloc'd
==7184==    at 0x483A7CF: malloc (vg_replace_malloc.c:309)
==7184==    by 0x4923BC3: _IO_file_doallocate (in /usr/lib/libc-2.31.so)
==7184==    by 0x49325FF: _IO_doallocbuf (in /usr/lib/libc-2.31.so)
==7184==    by 0x49317E7: _IO_file_overflow@@GLIBC_2.2.5 (in /usr/lib/libc-2.31.so)
==7184==    by 0x49308F5: _IO_file_xsputn@@GLIBC_2.2.5 (in /usr/lib/libc-2.31.so)
==7184==    by 0x4926237: puts (in /usr/lib/libc-2.31.so)
==7184==    by 0x1094E4: worker (in /home/sapiest/OS_labs/Lab9/main-signal)
==7184==    by 0x4840876: mythread_wrapper (hg_intercepts.c:389)
==7184==    by 0x489646E: start_thread (in /usr/lib/libpthread-2.31.so)
==7184==    by 0x49AE3D2: clone (in /usr/lib/libc-2.31.so)
==7184==  Block was alloc'd by thread #2
==7184== 
this should print last
==7184== 
==7184== Use --history-level=approx or =none to gain increased speed, at
==7184== the cost of reduced accuracy of conflicting-access information
==7184== For lists of detected and suppressed errors, rerun with: -s
==7184== ERROR SUMMARY: 23 errors from 2 contexts (suppressed: 40 from 40)
```

Проанализировав отчет, можно понять, что helgrind сообщает о возможной "гонке данных".
(использование printf() и переменной done сразу в 2 потоках).
Данный способ ожидания потока не является эффективным, как как мы тратим 
ресурсы на ожидающем потоке. Наиболее оптимальным решением было бы использовать мьютексы.

**№5.** *Теперь рассмотреть main-signal-cv.c,\
которая использует условную переменную (condition variable).\
Сравнить с предыдущей. Проанализировать main-signal-cv с использованием helgrind.*

Введем команды

```
gcc main-signal-cv.c -o main-signal-cv -lpthread
valgrind --tool=helgrind ./main-signal-cv
```

Получим отчет

```
==7847== 
==7847== Use --history-level=approx or =none to gain increased speed, at
==7847== the cost of reduced accuracy of conflicting-access information
==7847== For lists of detected and suppressed errors, rerun with: -s
==7847== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 7 from 7)
```

Отчет показывает, что ошибок нет.
Данный подход более оптимален, так как используются condition variable.         
         
