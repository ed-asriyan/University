# Лабораторная работа 4
## Условия задачи
Система массового обслуживания состоит из двух обслуживающих аппаратов (ОА1 и ОА2) и двух очередей заявок. Всего в 
системе обращается 100 заявок. Заявки поступают в "хвост" каждой очереди; в ОА они поступают из "головы" очереди по 
одной и обслуживаются по случайному закону за интервалы времени `Т1` и `Т2`, равномерно распределенные от 0 до 6 и от 1 
до 8 единиц времени соответственно. (Все времена – вещественного типа).  Каждая заявка после ОА1 c вероятностью Р=0.7
вновь поступает в "хвост" первой очереди, совершая новый цикл обслуживания, а с вероятностью 1-Р входит во вторую
очередь. В начале процесса все заявки находятся в первой очереди. Смоделировать процесс обслуживания до выхода из 
ОА2 первых 1000 заявок. Выдавать на экран после обслуживания  в ОА2 каждых 100 заявок информацию о текущей и 
средней длине каждой очереди, а в конце процесса - общее время моделирования, время простоя ОА2, количество 
срабатываний ОА1, среднее времени пребывания заявок в очереди.

## ТЗ
### Исходные данные и результаты
**Входные данные:** выбор (да/нет): выводить или нет адреса элементов для очереди, построенной на списке. 

**Результат работы:**  
Для каждого типа ОА:
* количество обработанных заявок;
* время простоя;
* время работы
* средняя длина очереди;
* среднее время обслуживания;

### Описание реализации ОА
Существует два ОА: один основан на очереди на списке, второй - на очереди на массиве. На каждом шаге ОА случайным
образом вычисляет время обработки заявки в указанном диапазоне и обрабатывает одну заявку (переводит ее из входной
очереди в выходную). При добавлении, если очередь пустая, увеличивается время простоя на разность между текущим временем
и временем последней обаботки.

## Описание внутренних структур данных
### RequestUnit

| Тип | Имя | Описание |
|-----|-----|----------|
| int | proc_count | кол-во прохождений через ОА |
| double | queuing_time | время в очереди |
| double | service_time | время обслуживания |

### QueueListNode

| Тип | Имя | Описание |
|-----|-----|----------|
| RequestUnit | value | значение |
| QueueListNode* | prev | предыдущий узел |


### QueueList

| Тип | Имя | Описание |
|-----|-----|----------|
| QueueLisеNode* | head | голова очереди |
| QueueLisеNode* | tail | конец очереди |
| int | size | длина очереди |

### QueueArray

| Тип | Имя | Описание |
|-----|-----|----------|
| RequestUnit* | head | голова очереди |
| RequestUnit* | tail | конец очереди |
| int | size | длина очереди |


### ServiceUnit

| Тип | Имя | Описание |
|-----|-----|----------|
| Queue | requests | очередь заявок |
| double | curr_time | текщее время моделирования |
| double | min_proc_time | минимальное время обработки |
| double | max_proc_time | максимальное время обработки |
| double | sum_proc_time | суммарное время обработки заявок |
| double | sum_queuing_time | суммарное время очереди |
| int | sum_size | сумма длин очереди |
| int | proc_count | количество обработанных заявок |

## Тесты
### Без вывода адресов
```
SU2 processed 0 requests
 Current SU1 queue length: 1000
 Current SU2 queue length: 0
 Average SU1 queue length: 1000
 Average SU2 queue length: -nan

SU2 processed 100 requests
 Current SU1 queue length: 1000
 Current SU2 queue length: 0
 Average SU1 queue length: 999.471
 Average SU2 queue length: 1.49

SU2 processed 200 requests
 Current SU1 queue length: 1000
 Current SU2 queue length: 0
 Average SU1 queue length: 999.574
 Average SU2 queue length: 1.405

SU2 processed 300 requests
 Current SU1 queue length: 1000
 Current SU2 queue length: 0
 Average SU1 queue length: 999.459
 Average SU2 queue length: 1.54667

SU2 processed 400 requests
 Current SU1 queue length: 997
 Current SU2 queue length: 3
 Average SU1 queue length: 999.503
 Average SU2 queue length: 1.515

SU2 processed 500 requests
 Current SU1 queue length: 1000
 Current SU2 queue length: 0
 Average SU1 queue length: 999.51
 Average SU2 queue length: 1.5

SU2 processed 600 requests
 Current SU1 queue length: 1000
 Current SU2 queue length: 0
 Average SU1 queue length: 999.485
 Average SU2 queue length: 1.51167

SU2 processed 700 requests
 Current SU1 queue length: 1000
 Current SU2 queue length: 0
 Average SU1 queue length: 999.492
 Average SU2 queue length: 1.50143

SU2 processed 800 requests
 Current SU1 queue length: 1000
 Current SU2 queue length: 0
 Average SU1 queue length: 999.479
 Average SU2 queue length: 1.51

SU2 processed 900 requests
 Current SU1 queue length: 1000
 Current SU2 queue length: 0
 Average SU1 queue length: 999.505
 Average SU2 queue length: 1.48111

SU2 processed 1000 requests
 Current SU1 queue length: 1000
 Current SU2 queue length: 0
 Average SU1 queue length: 999.509
 Average SU2 queue length: 1.48


--- Service units modeling summary ---
SU1 is ServiceUnit<QueueArray>
SU2 is ServiceUnit<QueueList>

SU1 processed 3177 requests
SU2 processed 1000 requests

SU1 average queue length: 999.509
SU2 average queue length: 1.48

SU1 average service time: 2.98768
SU2 average service time: 4.41677

SU1 average queueing time: 2518.51
SU2 average queueing time: 2.02055

SU1 idle time: 0
SU2 idle time: 5082.26
Simulation time: 9499.04

SU1 CPU time: 215131 (enqueue: 3837, dequeue: 211294)
SU2 CPU time: 26366 (enqueue: 847, dequeue: 25519)
Overal CPU time: 323296

--- Memory measurement tests summary (1000 elements) ---
 QueueArray: 11000
 QueueList:  16056
```

### С выводом адресов
```
SU2 processed 0 requests
 Current SU1 queue length: 1000
 Current SU2 queue length: 0
 Average SU1 queue length: 1000
 Average SU2 queue length: -nan

Addresses of SU2 elements: 0x61e568 0x61e5c8 0x61e508 0x61e4a8 
SU2 processed 100 requests
 Current SU1 queue length: 996
 Current SU2 queue length: 4
 Average SU1 queue length: 998.649
 Average SU2 queue length: 2.41

SU2 processed 200 requests
 Current SU1 queue length: 1000
 Current SU2 queue length: 0
 Average SU1 queue length: 999.151
 Average SU2 queue length: 1.88

SU2 processed 300 requests
 Current SU1 queue length: 1000
 Current SU2 queue length: 0
 Average SU1 queue length: 999.33
 Average SU2 queue length: 1.69667

SU2 processed 400 requests
 Current SU1 queue length: 1000
 Current SU2 queue length: 0
 Average SU1 queue length: 999.441
 Average SU2 queue length: 1.5775

Addresses of SU2 elements: 0x61e508 0x61e568 
SU2 processed 500 requests
 Current SU1 queue length: 998
 Current SU2 queue length: 2
 Average SU1 queue length: 999.47
 Average SU2 queue length: 1.554

Addresses of SU2 elements: 0x61e4a8 0x61e508 0x61e5c8 
SU2 processed 600 requests
 Current SU1 queue length: 997
 Current SU2 queue length: 3
 Average SU1 queue length: 999.454
 Average SU2 queue length: 1.59

SU2 processed 700 requests
 Current SU1 queue length: 1000
 Current SU2 queue length: 0
 Average SU1 queue length: 999.447
 Average SU2 queue length: 1.6

SU2 processed 800 requests
 Current SU1 queue length: 1000
 Current SU2 queue length: 0
 Average SU1 queue length: 999.457
 Average SU2 queue length: 1.58625

SU2 processed 900 requests
 Current SU1 queue length: 1000
 Current SU2 queue length: 0
 Average SU1 queue length: 999.45
 Average SU2 queue length: 1.59333

SU2 processed 1000 requests
 Current SU1 queue length: 1000
 Current SU2 queue length: 0
 Average SU1 queue length: 999.457
 Average SU2 queue length: 1.575


--- Service units modeling summary ---
SU1 is ServiceUnit<QueueArray>
SU2 is ServiceUnit<QueueList>

SU1 processed 3378 requests
SU2 processed 1000 requests

SU1 average queue length: 999.457
SU2 average queue length: 1.575

SU1 average service time: 3.02054
SU2 average service time: 4.58792

SU1 average queueing time: 2564.63
SU2 average queueing time: 2.64528

SU1 idle time: 0
SU2 idle time: 5617.3
Simulation time: 10205.2

SU1 CPU time: 202799 (enqueue: 2926, dequeue: 199873)
SU2 CPU time: 23825 (enqueue: 716, dequeue: 23109)
Overal CPU time: 305122

--- Memory measurement tests summary (1000 elements) ---
 QueueArray: 11000
 QueueList:  16056
```

## Сравнение реализаций

| Реализация | Кол-во тиков | Кол-во памяти (1000 элементов) |
|------------|--------------|---------------|
| Массив | 207668 | 11000 |
| Список | 26615 | 16056 |

## Вывод
Очередь, основання на списке, работает намного быстрее (в ~8 раз), чем та, что основана на массиве. Это и следовало
ожидать, так как во в первом случае добавление и удаление работает всегда за `O(1)`, а во втором за `O(1)` в лучшем и за
`O(n)` в худшем случае (хотя амортизированное время - `O(1)`).

## Контрольные вопросы
1. **Что такое очередь?** Очередь – это последовательный список переменной длины, включение элементов в который идет с
одной стороны (с «хвоста»), а исключение – с другой стороны (с «головы»). Принцип работы очереди: первым пришел – первым
вышел, т. е. First In – First Out (FIFO).
2. **Каким образом, и какой объем памяти выделяется под хранение очереди при различной ее реализации?** При
моделировании простейшей линейной очереди на основе одномерного массива выделяется последовательная область памяти из
`m` мест по `L` байт, где `L` – размер поля данных для одного элемента размещаемого типа. В каждый текущий момент
времени выделенная память может быть вся свободна, занята частично или занята полностью. При реализации очереди на
основе односвязного линейного списка, каждый элемент которого содержит информационное поле и поле с указателем «вперед»
(на следующий элемент). В этом случае в статической памяти можно либо хранить адрес начала и конца очереди, либо – адрес
начала очереди и количество элементов. Исходное состояние очереди: `P[out] = P[in]` - пустой указатель, `K = 0`.
3. **Каким образом освобождается память при удалении элемента из очереди при ее различной реализации?** В очереди
исключается элемент, находящийся по адресу (индексу) `P[out]`, а указатель `P[out]`, как и в случае добавления,
перемещается к следующему элементу. Исключается элемент, находящийся по адресу `P[out]`. Указатель `P[out]` при этом
переместится на предыдущий элемент.
4. **Что происходит с элементами очереди при ее просмотре?** Элементы исключаются из очереди.
5. **Каким образом эффективнее реализовывать очередь. От чего это зависит?** При реализации очереди в виде массива все
операции выполняются в среднем в 1,5 раза быстрее. Каждый элемент очереди-списка занимает в памяти 40 байт. Буфер под
150 элементов очереди-массива занимает в памяти 4848  байт (~32 байта на элемент). Очередь-массив в 1,25 раза
эффективнее по памяти (не считая необходимости заранее выделять ограниченный буфер).
