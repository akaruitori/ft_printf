#include <limits.h>

#include "ft_printf.h"

int		main()
{
	// ft_printf("{green}%a,{eoc} %b, %c, %d, %e, %f, %g, %i, %k, %o, %p, %s, %u, %x\n", 1. / 7., 0x123456, 'A', 125, 1. / 7., 1. / 7., 1. / 7., 125, 123456789, 128, &main, "hi!", 125, 128);
	// ft_printf("%14$a, %13$b, %12$c, %11$d, %10$e, %9$f, %8$g, %7$i, %6$k, %5$o, %4$p, %3$s, %2$u, %1$x\n", 128, 125, "hi!", &main, 128, 123456789, 125, 1. / 7., 1. / 7., 1. / 7., 125, 'A', 0x123456, 1. / 7.);
	ft_printf("{green}* List of supported format specifiers: *{eoc}\n");
	ft_printf("\t{red}a and A{eoc}: a hexadecimal representation of floating point numbers");
	ft_printf("\n\t\t1/7: {blue}%a{eoc}\n", 1. / 7.);
	ft_printf("\t\t1/3: {blue}%A{eoc}\n", 1. / 3.);
	ft_printf("\t\tMax long double number: {blue}%La{eoc}\n", LDBL_MAX);
	ft_printf("\t{red}b{eoc}: binary representation of integers\n");
	ft_printf("\t\t25: {blue}%032b{eoc}\n", 25);
	ft_printf("\t\t-12345: {blue}%b{eoc}\n", -12345);
	ft_printf("\t{red}c{eoc}: A single printable character\n");
	ft_printf("\t\t{red}%c{eoc} or {red}%c{eoc} or {red}%c{eoc}\n", 65, 38, 126);
	ft_printf("\t{red}d{eoc}: integers");
	return (0);

}
