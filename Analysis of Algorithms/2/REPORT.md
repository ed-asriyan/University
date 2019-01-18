# По лабораторная работа №2 «Умножение матриц»
## Стандартный алгоритм умножения матриц
Код функции:
```objectivec
template<class T>
Matrix <T> multiplyClassic(const Matrix <T>& a, const Matrix <T>& b) {
    Matrix<T> result = _internal::throwIfInvalidSizeAndCreateResult<T>(a.height, a.width, b.height, b.width);

    // F: (2 + m*(2 + F{})
    for (int i = 0; i < result.height; i++) {
        // F: (2 + n*(2 + F{})
        for (int j = 0; j < result.width; j++) {
            // F: 3
            result.data[i][j] = 0;

            for (int k = 0; k < b.height; k++) {
                // F: 8
                result.data[i][j] += a.data[i][k] * b.data[k][j];
            }
        }
    }

    return result;
}
```

Пусть матрица A имеет размерность m x n, а матрица B – n x q. В этом случае оценка трудоемкости алгоритма:

![equation](https://latex.codecogs.com/gif.latex?2%2Bm%282%2B2%2Bn%282%2B3%2B2%2Bq%282%2B8%29%29%29%3D2%2Bm%284%2Bn%287%2B10q%29%3D10mnq%2B7mq%2B4m%2B2)

## Алгоритм Винограда
Код функции:
```objectivec
template<class T>
Matrix <T> multiplyGrape(const Matrix <T>& a, const Matrix <T>& b) {
    Matrix<T> result = _internal::throwIfInvalidSizeAndCreateResult<T>(a.height, a.width, b.height, b.width);

    size_t a_height = a.height;
    size_t a_width = a.width;
    size_t b_width = b.width;

    T* mul_h = new T[a_height];
    T* mul_w = new T[b_width];

    // F: 2 + m(2 + F{})
    for (int i = 0; i < a_height; i++) {
        // F: 1
        mul_h[i] = 0;
        // F: 3 + n/2(3 + F{})
        for (int j = 0; j < a_width / 2; j++) {
            // F: 12
            //   1  1      1  1            1   2   1            1    3
            mul_h[i] = mul_h[i] + a.data[i][2 * j] * a.data[i][2 * j + 1];
        }

    }

    // F: 2 + q(2 + F{})
    for (int i = 0; i < b_width; i++) {
        // F: 1
        mul_w[i] = 0;
        // F: 3 + n/2(3 + F{})
        for (int j = 0; j < a_width / 2; j++) {
            // F: 12
            //   1  1      1  1             2   1  1              3    1
            mul_w[i] = mul_w[i] + b.data[2 * j][i] * b.data[2 * j + 1][i];
        }
    }

    // F: 2 + m(2 + F{})
    for (int i = 0; i < a_height; i++) {
        // F: 2 + q(2 + F{})
        for (int j = 0; j < b_width; j++) {
            // F: 7
            result.data[i][j] = -mul_h[i] - mul_w[j];
            // F: 3 + n/2(3 + F{})
            for (int k = 0; k < a_width / 2; k++) {
                // F: 21
                //         1  1  1            1  1  1             1   2   1              3    1   1             1    3    1             2   1
                result.data[i][j] = result.data[i][j] + (a.data[i][k * 2] + b.data[k * 2 + 1][j])
                    * (a.data[i][2 * k + 1] + b.data[2 * k][j]);
            }
        }
    }

    // F: 1
    if (a_width % 2) {
        // F: 2 + m(2 + F{})
        for (int i = 0; i < a_height; i++) {
            // F: 2 + q(2 + F{})
            for (int j = 0; j < b_width; j++) {
                // F: 13
                //         1  1  1            1  1  1            1   2   1             2   1
                result.data[i][j] = result.data[i][j] + a.data[i][a_width - 1] * b.data[a_width - 1][j];
            }
        }
    }

    delete[] mul_w;
    delete[] mul_h;

    return result;
}
```

«Слабым местом» алгоритма Винограда является необходимость выделения и освобождения дополнительной памяти под массивы
строковых и столбцовых коэффициентов. Кроме того, в случае нечетного количества столбцов в первой (строк во второй)
матрице, алгоритм должен выполнять дополнительные действия во вложенных циклах.

Оценка трудоемкости каждого блока алгоритмов:

![equation](https://latex.codecogs.com/gif.latex?F1%3D2%2Bm%5Cleft%282%2B1%2B3%2B%5Cfrac%7Bn%7D%7B2%7D%5Cleft%283%2B12%5Cright%29%5Cright%29%3D2%2B6m%2B%5Cleft%28%5Cfrac%7B15mn%7D%7B2%7D%5Cright%29)

![equation](https://latex.codecogs.com/gif.latex?F2%3D2%2Bq%5Cleft%282%2B1%2B3%2B%5Cfrac%7Bn%7D%7B2%7D%5Cleft%283%2B12%5Cright%29%5Cright%29%3D2%2B6q%2B%5Cfrac%7B15nq%7D%7B2%7D)

![equation](https://latex.codecogs.com/gif.latex?F3%3D2%2Bm%5Cleft%282%2B2%2Bq%5Cleft%282%2B7%2B3%2B%5Cfrac%7Bn%7D%7B2%7D%5Cleft%283%2B21%5Cright%29%5Cright%29%5Cright%29%2B1%3D3%2B4m%2B12mq%2Bmnq)

![equation](https://latex.codecogs.com/gif.latex?F4%3D2%2Bm%5Cleft%282%2B2%2B1%5Cleft%282%2B13%5Cright%5Cright%29%3D2%2B4m%2B15mq)

Таким образом, результирующая трудоемкость алгоритма равна
* в лучшем случае: ![equation](https://latex.codecogs.com/gif.latex?F_%7Bw%7D%3DF1%2BF2%2BF3%3D12mnq%2B12mq%2B7.5mn%2B7.5nq%2B10m%2B6q%2B7)
* в худшем случае: ![equation](https://latex.codecogs.com/gif.latex?F_%7Bb%7D%3DF_%7Bw%7D%2BF4%3D12mnq%2B27mq%2B7.5mn%2B7.5nq%2B14m%2B6q%2B9)

## Оптимизированный алгоритм Винограда
Алгоритм Винограда можно улучшить с помощью следующих добавлений:
1. Заменить `a = a + x` на `a += x` везде где это возможно;
2. В циклах `for (int i = 0; i < n / 2; i++)` заменить на `for (int i = 0; i < n; i += 2)` (избавимся от долгой операции
деления);
3. При заполнении массивов коэффициентов `h`, `v` записывать в них н `+=`, а `-=`, чтобы в основном цикле можно было
записать `c[i][j] += h[i]+v[j]` вместо `+= -h[i] – h[j]`;
4. Внести проверку `n % 2` внутрь основного цикла, чтобы не нужно было проходить через два дополнительных `for`;
5. После этого вычислить `n % 2` только один раз, в зависимости от этого установить флаг, и проводить в цикле проверку
`if (flag) `вместо `if (n % 2)`.

В результате получим оптимизированный алгоритм:
```objectivec
template<class T>
Matrix <T> multiplyGrapeOpt(const Matrix <T>& a, const Matrix <T>& b) {
    Matrix<T> result = _internal::throwIfInvalidSizeAndCreateResult<T>(a.height, a.width, b.height, b.width);

    const size_t a_height = a.height;
    const size_t a_width = a.width;
    const size_t b_width = b.width;

    T* const mul_h = new T[a_height];
    T* const mul_w = new T[b_width];

    // F: 2 + m(2 + F{})
    for (int i = 0; i < a_height; i++) {
        // F: 1
        mul_h[i] = 0;

        // F: 2 + n/2(2 + F{})
        for (int j = 1; j < a_width; j += 2) {
            // F: 8
            //   1   1            1   2   1            1  1
            mul_h[i] -= a.data[i][j - 1] * a.data[i][j];
        }
    }

    // F: 2 + m(2 + F{})
    for (int i = 0; i < b_width; i++) {
        // F: 1
        mul_w[i] = 0;
        // F: 2 + n/2(2 + F{})
        for (int j = 1; j < a_width; j += 2) {
            // F: 8
            //   1   1             2   1  1            1  1
            mul_w[i] -= b.data[j - 1][i] * b.data[j][i];
        }

    }

    // F: 3
    const bool isOdd = static_cast<bool>(a_width % 2);

    // F: 2 + m(2 + F{})
    for (int i = 0; i < a_height; i++) {
        // F: 2 + q(2 + F{})
        for (int j = 0; j < b_width; j++) {
            // F: 6
            result.data[i][j] += mul_h[i] + mul_w[j];

            // n/2		// F: 2 + n/2(2 + F{})
            for (int k = 1; k < a_width; k += 2) {
                // F: 16
                //         1  1  1              1   2   1            1  1   1             1  1  1             2   1
                result.data[i][j] += (a.data[i][k - 1] + b.data[k][j]) * (a.data[i][k] + b.data[k - 1][j]);
            }

            // F_if: 10
            if (isOdd) {
                //         1  1   1            1   2   1             2   1
                result.data[i][j] += a.data[i][a_width - 1] * b.data[a_width - 1][j];
            }
        }
    }

    delete[] mul_w;
    delete[] mul_h;

    return result;
}
```

## Оценка трудоемкости:
![equation](https://latex.codecogs.com/gif.latex?F1%3D2%2Bm%5Cleft%282%2B1%2B2%2B%5Cfrac%7Bn%7D%7B2%7D%5Cleft%282%2B8%5Cright%29%5Cright%29%3D2%2B5m%2B5mn)

![equation](https://latex.codecogs.com/gif.latex?F2%3D2%2Bq%5Cleft%282%2B1%2B2%2B%5Cfrac%7Bn%7D%7B2%7D%5Cleft%282%2B8%5Cright%29%5Cright%29%3D2%2B5m%2B5mq)

![equation](https://latex.codecogs.com/gif.latex?F3%3D3%2B2%2Bm%5Cleft%282%2B2%2Bq%5Cleft%282%2B6%2B2%2B%5Cfrac%7Bn%7D%7B2%7D%5Cleft%282%2B%5Cbegin%7Bbmatrix%7D16%5C%5C2%5Cend%7Bbmatrix%7D%5Cright%29%5Cright%29%5Cright%29%3D5%2B4m%2B10mq%2B%5Cbegin%7Bbmatrix%7D9%5C%5C14%5Cend%7Bbmatrix%7Dmnq%0D%0A)

Таким образом, результирующая трудоемкость оптимизированного алгоритма равна
* в лучшем случае: ![equation](https://latex.codecogs.com/gif.latex?F_%7Bb%7D%3D9mnq%2B10mq%2B5mn%2Bnq%2B9m%2B5q%2B9)
* в худшем случае: ![equation](https://latex.codecogs.com/gif.latex?F_%7Bw%7D%3D14mnq%2B10mq%2B5mn%2Bnq%2B9m%2B5q%2B9)

В неоптимизированном алгоритме
* в лучшем случае: ![equation](https://latex.codecogs.com/gif.latex?F_%7Bb%7D%3D12mnq%2B12mq%2B7.5nq%2B7.5nq%2B10m%2B6q%2B7)
* в худшем случае: ![equation](https://latex.codecogs.com/gif.latex?F_%7Bw%7D%3D12mnq%2B27mq%2B7.5nq%2B7.5nq%2B10m%2B6q%2B9)

Разница в эффективности между оптимизированным и обычным алгоритмом составляет
* в лучшем случае: ![equation](https://latex.codecogs.com/gif.latex?3mnq%2B2mq%2B2.5mn%2B2.5nq%2B1m%2B1q%2B2)
* в худшем случае: ![equation](https://latex.codecogs.com/gif.latex?-2mnq%2B17mq%2B2.5mn%2B2.5nq%2B5m%2B1q)

Трудоемкость стандартного алгоритма равна ![equation](https://latex.codecogs.com/gif.latex?10mnq%2B7mq%2B4m%2B2).

Оптимизированный АВ (в худшем случае), также как и неоптимизированный АВ, оказываются более трудоёмкими, чем стандартный
алгоритм, при сравнении по мажоранте (`mnq`). Тем не менее, оба АВ должны работать быстрее за счет того, что в них
производится гораздо меньшее число умножений.
