# Table Formatter


### What does the program do?
The program reads a table from input file (argv[1]) and writes this into stdout in formatted view. 

### Remarks:
1. Input data doesn't contain table name.
2. The first row contains column names.
3. Following rows contain columns data, which are separated by tabulation.

### Data formatting rules:
* Strings are aligned to the left edge.
* Integers are aligned to the right edge.
* Floating point numbers are aligned to the point.
* Single symbols are aligned to the center.
* Columns width depends on containing data.

## Example:

### Input data
```
ManagerId	FirstName	LastName	Email	Password	Active
1	Johnny	Smithe	no@no.com	system	Y
2	Karen	Xythe	no@no.com	system	Y
3	Brett	Heath	no@no.com	system	Y
4	Gabby	Banks	no@no.com	system	Y
5	Faye	Jones	no@no.com	system	Y
6	Joh	Boy	no@no.com	system	Y
```

### Output data
```
+-----------+-----------+----------+-----------+----------+--------+
| ManagerId | FirstName | LastName | Email     | Password | Active |
+-----------+-----------+----------+-----------+----------+--------+
|         1 | Johnny    | Smithe   | no@no.com | system   |   Y    |
|         2 | Karen     | Xythe    | no@no.com | system   |   Y    |
|         3 | Brett     | Heath    | no@no.com | system   |   Y    |
|         4 | Gabby     | Banks    | no@no.com | system   |   Y    |
|         5 | Faye      | Jones    | no@no.com | system   |   Y    |
|         6 | Joh       | Boy      | no@no.com | system   |   Y    |
+-----------+-----------+----------+-----------+----------+--------+
```