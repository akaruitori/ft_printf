# ft_printf
_Recoded libc printf function_  
  

> ### Please note the school's restrictions & codestyle rules (so the code won't seem that wierd):
> * No `for` loops
> * No `switch` and `case` statements
> * No variabe declaration and assignment on the same line (i.e. no `int sum = 0;`)
> * No multiline or complicated macroses
> * No mare than 5 functions per file
___

## Usage:
```bash
git clone ft_printf && cd ft_printf && make
```
This command will compile a libftprintf.a lib.
Do
```bash
make example
```
to see examples below in action.
  
  
## Features:

### _Supports `N$` and `*N$`_
`N$`: take parameter N to print its representation  
`*N$`: take parameter N as width or precision
  
For example we want to print different representations of two numbers, long double 1/7 and unsigned int 8000.
And we want every representation to be of some fixed width (which is useful for printing tables or just pretty-printing of some data). 

```C
int   width;

width = 32;
ft_printf(
          "\tBinary:\t\t\t|%2$*3$b|\n"
          "\tOctal:\t\t\t|%2$*3$o|\n"
          "\tDecimal:\t\t|%2$*3$u|\n"
          "\tHexadecimal:\t\t|%2$*3$x|\n"
          "\tFloat hexadecimal:\t|%1$*3$La|\n"
          "\tFloat exponential:\t|%1$*3$Le| \n"
          "\tFloat regular:\t\t|%1$*3$Lf|\n",
          1.L/7.L, (unsigned int)8000, width
          );
```

The result:
```
        Binary:                 |                   1111101000000|
        Octal:                  |                           17500|
        Decimal:                |                            8000|
        Hexadecimal:            |                            1f40|
        Float hexadecimal:      |          0x9.249249249249249p-6|
        Float exponential:      |                    1.428571e-01| 
        Float regular:          |                        0.142857|
```

___  
### Supprts printing in color
  
```C
ft_printf("\t{red}Printing{eoc} {green}in color{eoc} {blue}is fun!{eoc}\n");
```
Output would be like this:


![ft_printf can print colors](https://s399sas.storage.yandex.net/rdisk/1db162bb31ad4b183db0a4ba6eb546b79ce2c2904cafe75c515de598923ad5b4/5ef2c36d/Hbz9wW-jLxs82N0pxBbacSWmBYIPRstBSfHGGiUKb_IOIFVA9iHgHyMr0ZVrj2BDbEW_GdjxsrqdkOe82_ykyA==?uid=31364244&filename=ft_printf_colors.png&disposition=inline&hash=&limit=0&content_type=image%2Fpng&tknv=v2&owner_uid=31364244&etag=7b8da2a45c1f77a80ec4135202eaa6a3&fsize=2547&media_type=image&hid=cfb8bac3f252a3d4d2912c03f56e8304&rtoken=58QssgZTAffA&force_default=yes&ycrid=na-1651c39f6d4b380bf9cf9df5364840d6-downloader17e&ts=5a8cbc666b300&s=12ae0270d751dfe4a42e1db267b55af05ffe03d56157599888f03b8404621aa9&pb=U2FsdGVkX1_KHjtHI59Ie2l4OoegYg4tZG95nN3Iv3PsaP5nOf65bgm63GWh6ZIzfKAWIDTRehhZUnnlkc69Tc_kJLa2wx9nco-t7_BR8DE)

___
  
### Converts time from an int (interpreting it as unix time)

Time may be printed in three modes (assuming that given parameter is `1234567890`):
* short, just time: `%hk` => `23:31:30`
* regular, date and time: `%k` => `13.02.2009 23:31:30`
* full, weekday, date and time: `%lk` => `fri, 13.02.2009 23:31:30`
  
