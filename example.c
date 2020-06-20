#include <limits.h>
#include <float.h>
#include "ft_printf.h"
#include <stdio.h>

int		main()
{
	// ft_printf("%a, %b, %c, %d, %e, %f, %g, %i, %k, %o, %p, %s, %u, %x\n", 1. / 7., 0x123456, 'A', 125, 1. / 7., 1. / 7., 1. / 7., 125, 123456789, 128, &main, "hi!", 125, 128);
	// ft_printf("%14$a, %13$b, %12$c, %11$d, %10$e, %9$f, %8$g, %7$i, %6$k, %5$o, %4$p, %3$s, %2$u, %1$x\n", 128, 125, "hi!", &main, 128, 123456789, 125, 1. / 7., 1. / 7., 1. / 7., 125, 'A', 0x123456, 1. / 7.);
	ft_printf("{green}* List of supported format specifiers: *{eoc}\n");
	ft_printf("\t{red}a{eoc} or {red}A{eoc}:\ta hexadecimal representation of floating point numbers");
	ft_printf("\n\t\t\t1/7: {blue}%a{eoc}\n", 1. / 7.);
	ft_printf("\t\t\t1/3: {blue}%A{eoc}\n", 1. / 3.);
	ft_printf("\t\t\tMax long double number: {blue}%La{eoc}\n", LDBL_MAX);
	ft_printf("\t{red}b{eoc}:\tbinary representation of integers\n");
	ft_printf("\t\t\t25: {blue}%b{eoc}\n", 25);
	ft_printf("\t\t\t-12345: {blue}%b{eoc}\n", -12345);
	ft_printf("\t{red}c{eoc}:\tA single printable character\n");
	ft_printf("\t\t\t{blue}%c{eoc} or {blue}%c{eoc} or {blue}%c{eoc}\n", 65, 38, 126);
	ft_printf("\t{red}d or i{eoc}:\tIntegers\n");
	ft_printf("\t\t\tMax int: {blue}%d{eoc}\n\t\t\tMin long int: {blue}%ld{eoc}\n", INT_MAX, LONG_MIN);
	ft_printf("\t{red}e{eoc} or {red}E{eoc}:\tfloating point number in exponential form\n");
	ft_printf("\t\t\t1/7: {blue}%e{eoc}\n", 1. / 7.);
	ft_printf("\t\t\t1/3: {blue}%E{eoc}\n", 1. / 3.);
	ft_printf("\t\t\tMin long double number: {blue}%Le{eoc}\n", LDBL_MIN);
	ft_printf("\t{red}f{eoc} or {red}F{eoc}:\tfloating point number\n");
	ft_printf("\t\t\t1/7: {blue}%f{eoc}\n", 1. / 7.);
	ft_printf("\t\t\t1/3: {blue}%F{eoc}\n", 1. / 3.);
	ft_printf("\t\t\tMin double number: {blue}%f{eoc}\n", DBL_MIN);
	ft_printf("\t{red}k{eoc}:\tdate and time converted from unix time\n");
	ft_printf("\t\t\t0: {blue}%lk{eoc}\n\t\t\t1234567890: {blue}%lk{eoc}\n", 0, 1234567890);
	ft_printf("\t{red}o{eoc}:\tUnsigned integer in octal system\n");
	ft_printf("\t\t\t25: {blue}%o{eoc}\n\t\t\t-54321: {blue}%o{eoc}\n", 25, -54321);
	ft_printf("\t{red}p{eoc}:\tPointer as an address\n");
	ft_printf("\t\t\tAddress of the main() function in this program: {blue}%p{eoc}\n", &main);
	ft_printf("\t{red}s{eoc}:\tA string\n");
	ft_printf("\t\t\t{blue}%s{eoc}\n", "like this one");
	ft_printf("\t\t\tIf null pointer is given: {blue}%s{eoc}\n", NULL);
	ft_printf("\t{red}u{eoc}:\tUnsigned integer\n");
	ft_printf("\t\t\t-12345 would turn into {blue}%u{eoc}\n", -12345);
	ft_printf("\t\t\tMax unsigned long int: {blue}%lu{eoc}\n", ULONG_MAX);
	ft_printf("\t{red}x{eoc} or {red}X{eoc}:\tUnsigned integer in hexadecimal system\n");
	ft_printf("\t\t\t-12345: {blue}%x{eoc}\n\t\t\t12345: {blue}%X{eoc}\n", -12345, 12345);
	return (0);

}
