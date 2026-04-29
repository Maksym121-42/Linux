# Варіант 11
## Тема роботи
Реалізувати помилку через неправильний `sizeof` (використання `sizeof(ptr)` замість `sizeof(*ptr))`, яка проявляється лише при зміні архітектури.

## Суть помилки
У програмі виділення пам’яті виконано через `sizeof(a)` (розмір вказівника), а потрібно `sizeof(*a)` (розмір елемента масиву). Через це обсяг виділеної пам’яті може бути неправильним.

## Результати запуску
64-біт режим:
```
gcc Lab5_var11.c -o Lab5_var11
./Lab5_var11
1005                    
```
32-біт режим:
```
gcc -m32 Lab5_var11.c -o Lab5_var11
./Lab5_var11

Fatal glibc error: malloc.c:2599 (sysmalloc): assertion failed: (old_top == initial_top (av) && old_size == 0) || ((unsigned long) (old_size) >= MINSIZE && prev_inuse (old_top) && ((unsigned long) old_end & (pagesize - 1)) == 0)
Aborted (core dumped)
```
