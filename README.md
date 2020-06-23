# ft_printf
_Recoded libc printf function_

> ### Please note the school's restrictions & codestyle rules:
> * No `for` loops
> * No `switch` and `case` statements
> * No variabe declaration and assignment on the same line (i.e. no `int sum = 0;`)
> * No multiline or complicated macroses
> * No mare than 5 functions per file


## Features

#### Supports `N$` and `*N$`
`N$`: take parameter N to print its representation
`*N$': take parameter N as representation width or precision

For example we want to print different representations of two numbers, long double 1/7 and long long int 8000.
And we want every representation to be of some fixed width. 

```C
int   width;

width = 16;
ft_printf(" Binary: %2$0*3$llk \n Octal: %2$0*3$llo \n Decimal: %2$0*3$lld \n"
          " Float hexadecimal: %1$0*3$La \n Float exponential: %1$0*3$Le \n Float regular: %1$0*3$",
          1.L/7.L, 8000, width);
```

The result:
```
```

