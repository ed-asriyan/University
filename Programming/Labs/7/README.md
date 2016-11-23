# Лабораторная работа №7
## Задание
1. Изучить упрощенную лексику языка C.
2. Составить регулярные выражения для каждой категории лексем.
3. Составить программу лексического анализа в соответствии с изложенной методикой.
4. Программа должна:
  * Читать файл исходного текста программы на языке C.
  *  Игнорировать директивы компилятора.
  * Игнорировать комментарии.
  * Выделять лексемы и направлять их в выходной поток в формате XML. Узел XML-документа должен
включать:
    * Категорию лексемы.
    * Посимвольное изображение лексемы.
    * Номер строки исходного файла.
    * Стартовую позицию первого символа лексемы от начала текущей строки.
    * Позицию последнего символа лексемы или длину лексемы.

## УПРОЩЕННАЯ ЛЕКСИКА ЯЗЫКА C (ISO/IEC 9899:1999 (E))
### Lexical elements
* **Syntax**
  * token:
    * keyword
    * identifier
    * constant
    * string-literal
    * punctuator

### Keywords
* **Syntax**
  * auto
  * break
  * case
  * char
  * const
  * continue
  * default
  * do
  * double
  * else
  * enum
  * extern
  * float
  * for
  * goto
  * if
  * inline
  * int
  * long
  * register
  * restrict
  * return
  * short
  * signed
  * sizeof
  * static
  * struct
  * switch
  * typedef
  * union
  * unsigned
  * void
  * volatile
  * while
  * _Bool
  * _Complex
  * _Imaginary

### Identifiers
* **Syntax**
  * identifier:
    * nondigit
    * identifier digit
    * identifier nondigit:
  * *nondigit*: one of `a` `b` `c` `d` `e` `f` `g` `h` `i` `j` `k` `l` `m` `n` `o` `p` `q` `r` `s` `t` `u` `v` `w` `x` `y`
`z` `A` `B` `C` `D` `E` `F` `G` `H` `I` `J` `K` `L` `M` `N` `O` `P` `Q` `R` `S` `T` `U` `V` `W` `X` `Y` `Z`
  * *digit*: one of `0` `1` `2` `3` `4` `5` `6` `7` `8` `9`

### Constants
* Syntax
  * constant:
    * integer-constant
    * floating-constant
    * enumeration-constant
    * character-constant
    
### Integer constants
* Syntax
  * integer-constant:
    * decimal-constant
    * octal-constant
    * hexadecimal-constant
  * decimal-constant:
    * nonzero-digit
    * decimal-constant digit
  * octal-constant:
    * `0`
    * octal-constant octal-digit
  * hexadecimal-constant:
    * hexadecimal-prefix hexadecimal-digit
    * hexadecimal-constant hexadecimal-digit
  * hexadecimal-prefix: one of
    * `0x` `0X`
  * nonzero-digit: one of
    * `1` `2` `3` `4` `5` `6` `7` `8` `9`
  * octal-digit: one of
    * `0` `1` `2` `3` `4` `5` `6` `7`
  * hexadecimal-digit: one of
    * `0` `1` `2` `3` `4` `5` `6` `7` `8` `9`
    * `a` `b` `c` `d` `e` `f`
    * `A` `B` `C` `D` `E` `F`
    
### Floating constants
* Syntax
  * floating-constant:
    * fractional-constant exponent-part opt
    * digit-sequence exponent-part
  * fractional-constant:
    * digit-sequence opt `.` digit-sequence
    * digit-sequence `.`
  * exponent-part:
    * `e` sign opt digit-sequence
    * `E` sign opt digit-sequence
  * sign: one of
    * `+` `-`
  * digit-sequence:
    * digit
    * digit-sequence digit
    
### Character constants
* Syntax
  * character-constant:
    * 'c-char-sequence '
  * c-char-sequence:
    * c-char
    * c-char-sequence c-char
  * c-char:
    * any member of the source character set except the single-quote ', backslash \, or
  * new-line character
    * escape-sequence
  * escape-sequence:
    * one of `\'` `\"` `\?` `\\` `\a` `\b` `\f` `\n` `\r` `\t` `\v`
    
### String literals
* Syntax
  * string-literal:
    * "s-char-sequence opt "
  * s-char-sequence:
    * s-char
    * s-char-sequence s-char
  * s-char:
    * any member of the source character set except the double-quote ", backslash \, or
  * new-line character
    * escape-sequence
    
### Punctuators
* Syntax
  * punctuator:
    * one of `[` `]` `(` `)` `{` `}` `.` `->` `++` `--` `&` `*` `+` `-` `~` `!` `/` `%` `<<` `>>` `<` `>` `<=` `>=` `==`
`!=` `^` `|` `&&` `||` `?` `:` `;` `...` `=` `*=` `/=` `%=` `+=` `-=` `<<=` `>>=` `&=` `^=` `|=` `,` `#` `##`
