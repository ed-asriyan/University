# Лабораторная работа №5
## Обработка разреженных матриц
**Цель работы:** реализация алгоритмов обработки разреженных матриц, сравнение этих алгоритмов со стандартными
алгоритмами обработки матриц.

Разреженная (содержащая много нулей) матрица хранится в форме 3-х объектов:
* вектор `A` содержит значения ненулевых элементов;
* вектор `IA` содержит номера строк для элементов вектора `A`;
* связный список `JA`, в элементе `Nk` которого находится номер компонент в `A` и `IA`, с которых начинается описание
столбца `Nk` матрицы `A`.

1. Смоделировать операцию сложения двух матриц, хранящихся в этой форме, с получением результата в той же форме.
2. Произвести операцию сложения, применяя  стандартный алгоритм работы с матрицами.
3. Сравнить время выполнения операций и объем памяти при использовании этих 2-х алгоритмов при различном проценте
заполнения матриц.