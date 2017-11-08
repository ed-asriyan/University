# Лабораторная работа №1 «Алгоритм Левенштейна»
## Постановка задачи
1. Изучить и реализовать следующие версии алгоритма Левенштейна для вычисления минимального редакционного расстояния: 
   * базовый
   * Дамерау-Левенштейна (модифицированный)
   * рекурсивный
2. Провести сравнение реализаций алгоритма.

## Описание алгоритмов
### Базовый
Редакционное расстояние, или расстояние Левенштейна — метрика, позволяющая определить «схожесть» двух строк —
минимальное количество операций вставки одного символа, удаления одного символа и замены одного символа на другой,
необходимых для превращения одной строки в другую.

Модифицированный алгоритма Левенштейна также учитывает возмож- ность перестановки двух соседних символов.
Пусть `S1` и `S2` - две строки над некоторым алфавитом длиной `M` и `N`, тогда минимальное редакционное расстояние
`D(S1, S2) ` можно посчитать по следующей формуле `D(S1, S2) = D(M, N)`;

![equation](https://latex.codecogs.com/gif.latex?D%28i%2Cj%29%3D%5Cbegin%7Bcases%7D0%2Ci%3D0%2Cj%3D0%5C%5Ci%2Cj%3D0%2Ci%3E0%5C%5Cj%2Ci%3D0%2Cj%3E0%5C%5Cmin%5Cbegin%7Bcases%7DD%28i%2Cj-1%29%2B1%5C%5CD%28i-1%2Cj%29%2B1%5C%5CD%28i-1%2Cj-1%29%2Bm%28S_%7B1%7D%5Bi%5D%29%2CS_%7B2%7D%5Bj%5D%29%5Cend%7Bcases%7D%5Cend%7Bcases%7D)

где `m(a, b)` равна нулю, если `a = b` и единице в противном случае; `min{a, b, c}` возвращает наименьший из аргументов.

### Дамерау-Левенштейна (модифицированный)
Расстояние Дамерау— Левенштейна между двумя строками `a` и `b` определяется функцией `d(|a|, |b|)` как:

![equation](https://latex.codecogs.com/gif.latex?d_%7Ba%2Cb%7D%3D%5Cbegin%7Bcases%7Dmax%28i%2Cj%29%2Cmin%28i%2Cj%29%3D0%5C%5Cmin%5Cbegin%7Bcases%7Dd_%7Ba%2Cb%7D%28i-1%2Cj%29%2B1%5C%5Cd_%7Ba%2Cb%7D%28i%2Cj-1%29%2B1%5C%5Cd_%7Ba%2Cb%7D%28i-1%2Cj-1%29%2Ca_%7Bi%7D%5Cneq%20b%7Bj%7D%5C%5Cd_%7Ba%2Cb%7D%28i-2%2Cj-2%29%2B1%5Cend%7Bcases%7D%2Ci%3E1%5Cwedge%20j%3E1%5Cwedge%20a_%7Bi%7D%3Db_%7Bj-1%7D%5Cwedge%20a_%7Bi-1%7D%3Db_%7Bj%7D%5C%5Cmin%5Cbegin%7Bcases%7Dd_%7Ba%2Cb%7D%28i-1%2Cj%29%2B1%5C%5Cd_%7Ba%2Cb%7D%28i%2Cj-1%29%2B1%5C%5Cd%7Ba%2Cb%7D%28i-1%2Cj-1%29%2B1%2Ca_%7Bi%7D%5Cneq%20b_%7Bj%7D%5Cend%7Bcases%7D%5Cend%7Bcases%7D)

## Реализация алгоритмов
### Базовый

```objectivec
int calc_levenshtein_general(const char* src, const char* dst) {
	// distance between str and "" is always len(str)
	const int m = (int) strlen(src);
	const int n = (int) strlen(dst);
	if (!m) return n;
	if (!n) return m;

	// for all i and j, matrix[i,j] will hold the Levenshtein distance between
	// the first i characters of src and the first j characters of dst;
	// note that matrix has (m+1)*(n+1) values
	int** const matrix = (int**) malloc((m + 1) * sizeof(int*));
	for (int i = 0; i <= m; ++i) {
		matrix[i] = (int*) malloc((n + 1) * sizeof(int));
		matrix[i][0] = i;
	}
	for (int i = 0; i <= n; ++i) {
		matrix[0][i] = i;
	}

	for (int i = 1; i <= m; ++i) {
		for (int j = 1; j <= n; ++j) {
			const int cost = src[i - 1] != dst[j - 1];

			const int above = matrix[i - 1][j];
			const int left = matrix[i][j - 1];
			const int diag = matrix[i - 1][j - 1];
			matrix[i][j] = MIN3(above + 1, left + 1, diag + cost);
		}
	}

	const int result = matrix[m][n];
	for (int i = m; i >= 0; --i) {
		free(matrix[i]);
	}
	free(matrix);

	return result;
}
```

### Рекурсивный
```objectivec
int calc_levenshtien_recoursive(const char* src, int src_len, const char* dst, int dst_len) {
	// base case: empty strings
	if (src_len == 0) return dst_len;
	if (dst_len == 0) return src_len;

	const int cost = src[src_len - 1] != dst[dst_len - 1];

	// return minimum of delete char from src, delete char from dst, and delete char from both
	return MIN3(calc_levenshtien_recoursive(src, src_len - 1, dst, dst_len) + 1,
	            calc_levenshtien_recoursive(src, src_len, dst, dst_len - 1) + 1,
	            calc_levenshtien_recoursive(src, src_len - 1, dst, dst_len - 1) + cost);

}
```

### Дамерау-Левенштейна (модифицированный)
```objectivec
int calc_levenshtein_modified(const char* src, const char* dst) {
	const int src_len = (const int) strlen(src);
	const int dst_len = (const int) strlen(dst);

	int** const matrix = (int**) malloc((src_len + 1) * sizeof(int*));

	for (int i = 0; i <= src_len; i++) {
		matrix[i] = (int*) malloc((dst_len + 1) * sizeof(int));
		matrix[i][0] = i;
	}
	for (int j = 0; j <= dst_len; j++) {
		matrix[0][j] = j;
	}
	for (int i = 1; i <= src_len; i++) {
		int* const row = matrix[i];
		int* const row_prev = matrix[i - 1];
		int* const row_prev2 = matrix[i - 2];

		const char src_char_prev = src[i - 1];
		const char src_char_prev2 = src[i - 2];

		const int i_gt_1 = i > 1;

		for (int j = 1; j <= dst_len; j++) {
			const int cost = src_char_prev != dst[j - 1];

			row[j] = MIN3(row_prev[j] + 1, row[j - 1] + 1, row_prev[j - 1] + cost);
			if (i_gt_1 &&
				(j > 1) &&
				(src_char_prev == dst[j - 2]) &&
				(src_char_prev2 == dst[j - 1])
				) {

				row[j] = MIN(
					row[j],
					row_prev2[j - 2] + cost
				);
			}
		}
	}

	const int result = matrix[src_len][dst_len];
	for (int i = src_len; i >= 0; --i) {
		free(matrix[i]);
	}
	free(matrix);

	return result;
}
```

## Примеры работы 
| # | src | dst | Базовый | Модифицированный | Рекурсивный | 
|---|-----|-----|---------|------------------|-------------| 
| 1 | abc | abs | 1 | 1 | 1 | 
| 2 | abc | bc  | 1 | 1 | 1 | 
| 3 | abc | abc | 0 | 0 | 0 | 
| 4 | aaab | aaac | 1 | 1 | 1 | 
| 5 | aaba | aaab | 2 | 1 | 2 | 
| 6 | abc | ab | 1 | 1 | 1 | 
| 7 | qqqq | q | 3 | 3 | 3 | 
| 8 | qwerty | ytrewq | 6 | 5 | 6 | 
 
## Сравнение 
В ходе выполнения лабораторной работы было проведено сравнение реализованных алгоритмов по времени выполнения с разными 
длинами строк. 
 
| Length | Distance | Recoursive | General | Modified | 
|--------|----------|------------| --------|----------| 
|      5 |        5 |     324.16 |    2.00 |     1.77 | 
|      6 |        6 |    3657.80 |    1.45 |     1.44 | 
|      7 |        7 |   49678.84 |    1.62 |     1.56 | 
|      8 |        8 |  626232.87 |    2.96 |     2.78 | 
 
## Вывод 
В ходе лабораторной работы были изучены и написаны три алгоритма Левенштейна (базовый, рекурсивный и модифицированный). 
Также была проведена временная оценка всех трёх алгоритмов, результаты представлены.
