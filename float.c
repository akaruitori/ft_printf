/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 23:21:36 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/27 19:45:27 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <float.h>
#include <stdint.h>
#include <stdlib.h>
# include <stdarg.h>



char				*ft_strnew(size_t size);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_strjoin(char const *s1, char const *s2);
size_t				ft_strlen(const char *str);
long long int		ft_abs(long long int n);
void				ft_strdel(char **as);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
void				ft_memdel(void **ap);
void				ft_str_free_array(char ***array);
char				*ft_itoa(int n);
void				ft_bzero(void *s, size_t n);
char				*ft_llint_to_str_base(long long int num, int base);
char				*ft_ullint_to_str_base(unsigned long long int num, int base);

void						del_trailing_point_zeroes(char *s)
{
	int						len;

	len = ft_strlen(s) - 1;
	while (s[len] && s[len] == '0')
	{
		s[len] = '\0';
		len--;
	}
	if (s[len] && s[len] == '.')
		s[len] = '\0';
}

char						*convert_exp_to_str(t_float *fnum, int long_flag)
{
	char					*temp_exp;
	char					*result;
	int						exp_bias;
	int						normal_flag;

	exp_bias = get_exp_bias(long_flag);
	normal_flag = is_normal_float_num(fnum);
	if (fnum->exp)
		temp_exp = ft_itoa(ft_abs(fnum->exp - exp_bias));
	else if (normal_flag)
		temp_exp = ft_strcpy(ft_strnew(2), "0");
	else
		temp_exp = ft_itoa(ft_abs(fnum->exp - exp_bias + 1));
	result = ft_strjoin("p ", temp_exp);
	ft_strdel(&temp_exp);
	if ((fnum->exp >= exp_bias || !fnum->exp) && normal_flag)
		result[1] = '+';
	else
		result[1] = '-';
	return (result);
}

char						*convert_man_to_str(t_float *fnum, int long_flag)
{
	char					*temp_man;
	char					*result;
	int						temp_man_len;
	int						expected_man_len;

	if (fnum->mantissa)
		temp_man = ft_ullint_to_str_base(fnum->mantissa, 16);
	else
		temp_man = ft_strnew(1);
	temp_man_len = ft_strlen(temp_man);
	expected_man_len = (long_flag ? LDBL_MAN_LEN / 4 : DBL_MAN_LEN / 4);
	if ((temp_man_len < expected_man_len) && fnum->mantissa)
	{
		result = ft_strnew(expected_man_len + 1);
		ft_memset(result, '0', expected_man_len);
		ft_strcpy(result + expected_man_len - temp_man_len, temp_man);
		ft_strdel(&temp_man);
	}
	else
		result = temp_man;
	return (result);
}

void						convert_float_parts_to_hexstr(t_float *fnum,
							int long_flag, int precision_flag,
							unsigned char alt_form_flag)
{
	int						i;

	fnum->exp_str = convert_exp_to_str(fnum, long_flag);
	fnum->man_str = convert_man_to_str(fnum, long_flag);
	if (!is_zero(fnum))
		del_trailing_point_zeroes(fnum->man_str);
	fnum->prefix = ft_strnew(7);
	i = 0;
	if (fnum->sign)
		fnum->prefix[i++] = '-';
	ft_strcpy(fnum->prefix + i, "0x");
	i += 2;
	if (long_flag && is_normal_float_num(fnum))
	{
		fnum->prefix[i++] = fnum->man_str[0];
		ft_memmove(fnum->man_str, fnum->man_str + 1, ft_strlen(fnum->man_str));
	}
	else if (is_normal_float_num(fnum) && (!is_zero(fnum)))
		fnum->prefix[i++] = '1';
	else
		fnum->prefix[i++] = '0';
	if (precision_flag || fnum->man_str[0] || alt_form_flag)
		fnum->prefix[i] = '.';
}

void						apply_precision_hex(t_float *fnum, int precision)
{
	char					*temp;
	int						man_len;

	man_len = ft_strlen(fnum->man_str);
	if (precision > man_len)
	{
		temp = fnum->man_str;
		fnum->man_str = ft_strnew(precision + 1);
		ft_strcpy(fnum->man_str, temp);
		ft_memset((void *)(fnum->man_str + man_len), '0', precision - man_len);
		ft_strdel(&temp);
	}
	else if (precision < man_len)
		ft_bzero((void *)(fnum->man_str + precision), man_len - precision);
 }



void						round_hex(t_float *fnum, int precision,
										int long_flag)
{
	int						man_len;
	unsigned long long int	man_temp;

	man_len = (long_flag ? LDBL_MAN_LEN / 4 : DBL_MAN_LEN / 4);
	man_temp = fnum->mantissa + 8.0 * ft_float_power(16, man_len - precision - 1);
	if (man_temp < fnum->mantissa)
	{
		fnum->exp += 4;
		fnum->mantissa = man_temp + ft_float_power(16, man_len - 1);
	}
	else if (!is_normal_float_num(fnum))
	{
		if (man_temp > ft_float_power(16, man_len - 1))
			fnum->exp++;
		fnum->mantissa = man_temp;
	}
	else
		fnum->mantissa = man_temp;
}

void						convert_long_double_hex(t_pholder *pholder)
{
	__uint128_t				num_bits;
	t_float					fnum;
	long double				num;
	char					*temp;
	unsigned char			alt_form_flag;

	num = *(long double *)pholder->arg; //
	num_bits = *(__uint128_t *)&num; //

	fnum.sign = (unsigned short)(num_bits >> (79) & 0x1);
	fnum.exp = (short int)((num_bits >> LDBL_MAN_LEN) & LDBL_EXP_MASK);
	fnum.mantissa = (unsigned long long)(num_bits & LDBL_MAN_MASK);
	alt_form_flag = ((pholder->flags && pholder->flags->alt_form) ? 1 : 0);
	if (pholder->precision && (pholder->precision->value >= 0))
	{
		round_hex(&fnum, pholder->precision->value, 1);
		convert_float_parts_to_hexstr(&fnum, 1, 1, alt_form_flag);
		apply_precision_hex(&fnum, pholder->precision->value);
	}
	else
		convert_float_parts_to_hexstr(&fnum, 1, 0, alt_form_flag);
	temp = ft_join_strings(3, fnum.prefix, fnum.man_str, fnum.exp_str);
	pholder->arg_len = ft_strlen(temp);
	pholder->converted_arg = temp;
	memfree_fnum(&fnum);
}

void						convert_double_hex(t_pholder *pholder)
{
	u_int64_t				num_bits;
	t_float					fnum;
	char					*temp;
	unsigned char			alt_form_flag;

	num_bits = *(u_int64_t *)pholder->arg;

	fnum.sign = (unsigned char)(num_bits >> (DBL_EXP_LEN + DBL_MAN_LEN));
	fnum.exp = (short int)((num_bits >> DBL_MAN_LEN) & DBL_EXP_MASK);
	fnum.mantissa = (unsigned long long)(num_bits & DBL_MAN_MASK);
	alt_form_flag = ((pholder->flags && pholder->flags->alt_form) ? 1 : 0);
	if ((pholder->precision && (pholder->precision->value >= 0)))
	{
		round_hex(&fnum, pholder->precision->value, 0);
		convert_float_parts_to_hexstr(&fnum, 0, 1, alt_form_flag);
		apply_precision_hex(&fnum, pholder->precision->value);
	}
	else
		convert_float_parts_to_hexstr(&fnum, 0, 0, alt_form_flag);
	temp = ft_join_strings(3, fnum.prefix, fnum.man_str, fnum.exp_str);
	pholder->arg_len = ft_strlen(temp);
	pholder->converted_arg = temp;
	memfree_fnum(&fnum);
}


char						*fractional_part_to_str(long double num,
							int current_order, t_pholder *pholder)
{
	int						num_dig;
	char					*temp;
	int						precision;
	int						i;

	if (pholder->modifier && pholder->modifier->is_big_l)
		num_dig = LDBL_DIG - current_order;
	else
		num_dig = DBL_DIG - current_order;
	if (pholder->precision && pholder->precision->value >= 0)
		precision = pholder->precision->value;
	else
		precision = 6;
	temp = ft_strnew(precision + 2);
	i = 0;
	if (precision > 0 || (pholder->flags && pholder->flags->alt_form))
		temp[i++] = '.';
	while (precision--)
	{
		num *= 10.l;
		temp[i++] = (num_dig > 0 ? ((int)num % 10 + 48) : '0');
		num -= (int)num;
		num_dig--;
	}
	return (temp);
}


void						convert_huge_float_full(long double num,
													t_pholder *pholder)
{
	int						order;
	int						num_dig;
	int						i;
	char					*temp;
	char					*temp_str_fraction;

	order = get_float_order(num);
	num /= ft_float_power(10.l, order - 1);
	temp = (char *)malloc(sizeof(char) * (order + 1));
	temp[order] = '\0';
	if (pholder->modifier && pholder->modifier->is_big_l)
		num_dig = LDBL_DIG;
	else
		num_dig = DBL_DIG;
	i = 0;
	while (order)
	{
		temp[i++] = (num_dig <= 0 ? '0' : ((int)num + 48));
		num = (num - (int)num) * 10.l;
		num_dig--;
		order--;
	}
	temp_str_fraction = fractional_part_to_str(num, ft_strlen(temp), pholder);
	pholder->converted_arg = ft_strjoin(temp, temp_str_fraction);
	ft_strdel(&temp);
	ft_strdel(&temp_str_fraction);
}

void						convert_medium_float_full(long double num,
														t_pholder *pholder)
{
	unsigned long long int	integer;
	char					*temp_str_integer;
	char					*temp_str_fraction;

	integer = (unsigned long long)num;
	num -= integer;
	temp_str_integer = ft_ullint_to_str_base(integer, 10);
	temp_str_fraction = fractional_part_to_str(num,
						ft_strlen(temp_str_integer), pholder);
	pholder->converted_arg = ft_strjoin(temp_str_integer, temp_str_fraction);
	ft_strdel(&temp_str_integer);
	ft_strdel(&temp_str_fraction);
}


void						convert_small_float_full(long double num,
												t_pholder *pholder)
{
	char					*temp;

	temp =  fractional_part_to_str(num, 0, pholder);
	pholder->converted_arg = ft_strjoin("0", temp);
	ft_strdel(&temp);
}

char						*get_sign(long double num)
{
	unsigned char			bits[16];

	ft_memcpy((void *)bits, (void *)&num, 16);
	if (bits[9] & 0x80)
		return ("-");
	else
		return ("");
}

void						convert_float_full(long double num,
												 t_pholder *pholder)
{
	char					*sign;
	char					*temp;
	int						precision;

	sign = get_sign(num); //(num >= 0. ? "\0" : "-");
	num = (num >= 0.l ? num : -num);
	precision = (pholder->precision ? pholder->precision->value : 6);
	if (pholder->precision && pholder->precision->value >= 0)
		precision = pholder->precision->value;
	else
		precision = 6;
	num += calculate_rounding(num, precision);
	if (num > (unsigned long long int)-1)
		convert_huge_float_full(num, pholder);
	else if ((int)num == 0)
		convert_small_float_full(num, pholder);
	else
		convert_medium_float_full(num, pholder);
	if (*sign)
	{
		temp = pholder->converted_arg;
		pholder->converted_arg = ft_strjoin(sign, pholder->converted_arg);
		ft_strdel(&temp);
	}
	if (pholder->arg_type->is_opt_form &&
		(!pholder->flags || (pholder->flags && !pholder->flags->alt_form)))
		del_trailing_point_zeroes(pholder->converted_arg);
}


int					get_float_exp(long double num)
{
	int				result;

	result = 0;
	while ((long long int)num >= 10)
	{
		num /= 10.l;
		result++;
	}
	while (num != 0.l && (long long int)num == 0)
	{
		num *= 10.l;
		result--;
	}
	return (result);
}

void				convert_float_exp(long double num, t_pholder *pholder)
{
	int				exp;
	char			*exp_str;
	char			*sign;
	char			*temp;
	int				i;

	sign = (num >= 0. ? "\0" : "-");
	num = (num >= 0. ? num : -num);
	exp = get_float_exp(num);
	num /= ft_float_power(10.l, exp);
	convert_float_full(num, pholder);
	temp = ft_itoa(ft_abs(exp));
	exp_str = ft_strnew(4 + ft_strlen(temp));
	ft_strcpy(exp_str, "e");
	i = 1;
	exp_str[i++] = (exp >= 0 ? '+' : '-');
	if (ft_abs(exp) < 10)
		exp_str[i++] = '0';
	ft_strcpy(exp_str + i, temp);
	ft_strdel(&temp);
	temp = pholder->converted_arg;
	pholder->converted_arg = ft_join_strings(3, sign, temp, exp_str);
	ft_strdel(&exp_str);
	ft_strdel(&temp);
}

void				convert_float_opt(long double num, t_pholder *pholder)
{
	int				precision;
	int				exp;

	if (pholder->precision)
	{
		if (pholder->precision->value >= 0)
			precision = pholder->precision->value;
		else
			precision = 1;
	}
	else
	{
		pholder->precision = initialize_precision();
		pholder->precision->value = 6;
		precision = 6;
	}
	exp = get_float_exp(num >= 0.l ? num : -num);
	if (precision > exp && exp >= -4)
	{
		pholder->precision->value -= (1 + exp);
		convert_float_full(num, pholder);
	}
	else
	{
		pholder->precision->value--;
		convert_float_exp(num, pholder);

	}
}

void				ft_capitalize(char *s)
{
	while (*s)
	{
		if (ft_isalpha(*s))
			*s = ft_toupper(*s);
		s++;
	}
}

void				apply_width_left_align(t_pholder *pholder, int len)
{
	int				fill_len;
	char			*temp;

	fill_len = pholder->width->value - len;
	temp = pholder->converted_arg;
	pholder->converted_arg = ft_strnew(pholder->width->value + 1);
	ft_memset(pholder->converted_arg, ' ', pholder->width->value);
	ft_strncpy(pholder->converted_arg, temp, len);
	ft_strdel(&temp);
}

void				apply_width(t_pholder *pholder, int len)
{
	int				fil_len;
	char			*temp;

	fil_len = pholder->width->value - len;
	temp = pholder->converted_arg;
	pholder->converted_arg = ft_strnew(fil_len + len + 1);
	ft_memset(pholder->converted_arg, ' ', fil_len);
	ft_strcpy(pholder->converted_arg + fil_len, temp);
	ft_strdel(&temp);
}

void				apply_plus(char **s)
{
	char			*temp;

	temp = *s;
	if (ft_strchr(HEX_DIGITS, *temp) || ft_strequ(temp, "inf") ||
		ft_strequ(temp, "nan"))
	{
		*s = ft_strjoin("+", temp);
		ft_strdel(&temp);
	}
}

void				apply_space(char **s)
{
	char			*temp;

	temp = *s;
	if (ft_strchr(HEX_DIGITS, *temp) || ft_strequ(temp, "inf") ||
		ft_strequ(temp, "nan"))
	{
		if (*temp != '-')
		{
			*s = ft_strjoin(" ", temp);
			ft_strdel(&temp);
		}
	}
}

void				insert_commas(char **s, int start_pos, int sep_num, int len)
{
	char			*dest;
	char			*src;
	char			*temp;

	src = *s;
	temp = *s;
	*s = ft_strnew(len + sep_num + 1);
	ft_strncpy(*s, src, start_pos);
    src += start_pos;
	dest = *s + start_pos;
	while (sep_num--)
	{
		*dest++ = ',';
		ft_strncpy(dest, src, 3);
		dest += 3;
		src += 3;
	}
	ft_strcpy(dest, src);
	ft_strdel(&temp);
}

void				apply_apost(char **s, int len)
{
	int				sep_num;
	char			*temp;
	char			*start;

	sep_num = 0;
	temp = *s;
	while (*temp && !ft_strchr(HEX_DIGITS, *temp))
		temp++;
	if (*temp)
	{
		start = temp;
		while (*temp && ft_strchr(HEX_DIGITS, *temp))
			temp++;
		sep_num = (temp - start - 1) / 3;
		start += (temp - start - 1) % 3 + 1;
		insert_commas(s, start - *s, sep_num, len);
	}
}

void				apply_zeroes(t_pholder *pholder)
{
	char			*temp;

	temp = pholder->converted_arg;
	while (*temp == ' ')
	{
		*temp = '0';
		temp++;
	}
	if ((*temp == '+' || *temp == '-') && temp != pholder->converted_arg)
	{
		if (*temp == '+')
			*pholder->converted_arg = '+';
		else
			*pholder->converted_arg = '-';
		*temp = '0';
	}
	else if (pholder->flags->space && (*pholder->converted_arg != '-'))
		*pholder->converted_arg = ' ';
}

void				apply_str_modifiers_float(t_pholder *pholder,
											long double num)
{
	int				len;
	unsigned char	inf_flag;
	unsigned char	nan_flag;

	inf_flag = ft_is_inf(num);
	nan_flag = ft_is_nan(num);
	len = ft_strlen(pholder->converted_arg);
	if (pholder->flags && !nan_flag)
	{
		if (pholder->flags->apost)
			apply_apost(&pholder->converted_arg, len);
		if (pholder->flags->plus)
			apply_plus(&(pholder->converted_arg));
		else if (pholder->flags->space)
			apply_space(&pholder->converted_arg);
	}
	len = ft_strlen(pholder->converted_arg);
	if (pholder->width && (pholder->width->value > len))
	{
		if (pholder->flags && pholder->flags->left_align)
			apply_width_left_align(pholder, len);
		else
			apply_width(pholder, len);
		if (pholder->flags && pholder->flags->zeroes && !inf_flag && !nan_flag)
			apply_zeroes(pholder);
	}
}

void				convert_nan(t_pholder *pholder, long double num)
{
	unsigned char	bits[8];

	ft_memcpy((void *)bits, (void *)&num, 8);
	if (bits[0] & 0x80)
		pholder->converted_arg = ft_strcpy(ft_strnew(4), "-nan");
	else
		pholder->converted_arg = ft_strcpy(ft_strnew(5), "nan");
	
}

void		convert_inf(t_pholder *pholder, long double num)
{
	if (num > 0)
		pholder->converted_arg = ft_strcpy(ft_strnew(4), "inf");
	else
		pholder->converted_arg = ft_strcpy(ft_strnew(5), "-inf");
}

void		convert_float(t_pholder *pholder)
{
	long double		num;

	num = get_long_double_num(pholder);
	if (ft_is_inf(num))
		convert_inf(pholder, num);
	else if (ft_is_nan(num))
		convert_nan(pholder, num);
	else if (pholder->arg_type->is_hex)
	{
		if (pholder->modifier && pholder->modifier->is_big_l)
			convert_long_double_hex(pholder);
		else
			convert_double_hex(pholder);
	}
	else if (pholder->arg_type->is_full_form)
		convert_float_full(num, pholder);
	else if (pholder->arg_type->is_exp_form)
		convert_float_exp(num, pholder);
	else if (pholder->arg_type->is_opt_form)
		convert_float_opt(num, pholder);
	apply_str_modifiers_float(pholder, num);
	if (pholder->is_uppercase)
		ft_capitalize(pholder->converted_arg);
	pholder->arg_len = ft_strlen(pholder->converted_arg);
}
