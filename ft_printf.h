/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtimeon <dtimeon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 20:54:14 by dtimeon           #+#    #+#             */
/*   Updated: 2019/08/28 17:41:20 by dtimeon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft.h"
# include <stdarg.h>
# include <float.h>
# include <stdint.h>

# define SPECIFIERS "%diouxXbaAfFeEgGcspk"
# define NOT_SUPPORTED_SPECIFIERS "DCS"
# define LENGTH_MODIFIERS "hlL"
# define FLAGS "0-+ #'"
# define NUM_ARG 1
# define WIDTH_VALUE 2
# define PRECISION_VALUE 3
# define HEX_DIGITS "0123456789abcdef"
# define DBL_EXP_LEN 11
# define LDBL_EXP_LEN 16
# define DBL_MAN_LEN 52
# define LDBL_MAN_LEN 64
# define DBL_EXP_MASK 0x7ff
# define DBL_MAN_MASK 0xfffffffffffff
# define LDBL_EXP_MASK 0x7fff
# define LDBL_MAN_MASK 0xffffffffffffffff
# define DBL_EXP_BIAS 1023
# define LDBL_EXP_BIAS 16386
# define SECONDS_IN_A_DAY (24 * 60 * 60)
# define SECONDS_IN_A_YEAR 31556926
# define COLOURS_NUM 3

typedef struct				s_flags
{
	unsigned int			space;
	unsigned int			plus;
	unsigned int			left_align;
	unsigned int			apost;
	unsigned int			alt_form;
	unsigned int			zeroes;
}							t_flags;

typedef struct				s_width
{
	int						value;
	unsigned int			is_from_arg;
	int						arg_pos;
	void					*arg;
}							t_width;

typedef struct				s_precision
{
	int						value;
	unsigned int			is_from_arg;
	int						arg_pos;
	void					*arg;
}							t_precision;

typedef struct				s_modifier
{
	unsigned int			is_big_l;
	unsigned int			is_l;
	unsigned int			is_ll;
	unsigned int			is_h;
	unsigned int			is_hh;
}							t_modifier;

typedef	struct				s_arg_type
{
	unsigned int			is_binary;
	unsigned int			is_octal;
	unsigned int			is_hex;
	unsigned int			is_signed_int;
	unsigned int			is_unsigned_int;
	unsigned int			is_float;
	unsigned int			is_full_form;
	unsigned int			is_exp_form;
	unsigned int			is_opt_form;
	unsigned int			is_char;
	unsigned int			is_char_str;
	unsigned int			is_pointer;
	unsigned int			is_time;
}							t_arg_type;

typedef struct				s_pholder
{
	unsigned int			is_from_num_arg;
	int						arg_pos;
	void					*arg;
	char					*converted_arg;
	unsigned int			arg_len;
	unsigned int			pholder_len;
	t_arg_type				*arg_type;
	t_flags					*flags;
	t_width					*width;
	t_precision				*precision;
	t_modifier				*modifier;
	unsigned int			is_uppercase;
	unsigned int			is_procent;
	unsigned char			ignore_precision; //
}							t_pholder;

typedef struct				s_arg_use
{
	int						purpose;
	char					*type;
	t_pholder				*pholder;
	struct s_arg_use		*same_pos_next;
}							t_arg_use;

typedef struct				s_float
{
	unsigned short int		sign;
	short int				exp;
	unsigned long long int	mantissa;
	char					*prefix;
	char					*exp_str;
	char					*man_str;

}							t_float;

typedef struct				s_time
{
	int						epoch_time;
	short int				year;
	unsigned char			month;
	unsigned char			day;
	char					*wday;
	unsigned char			hour;
	unsigned char			minute;
	unsigned char			second;
}							t_time;

typedef struct				s_colour
{
	char					*name;
	int						tag_len;
	void					(*write_function)(void);
}							t_colour;

/*
** modifier_checkers
*/
int							is_specifier(char c);
int							is_flag(char c);
int							is_length_modifier(char c);

/*
** validation
*/
int							is_valid_pholder(char *s);
int							is_correct_property_order(char **s, int n_arg_flag);
int							is_correct_length_modifier(char **s);
int							is_correct_modifiers_order(char *s);
int							check_for_lh_modifiers(t_modifier *mod, char *s);

/*
** procent_checkers
*/
int							is_valid_procent_pholder(char *s, int pholder_len);
int							is_procent_pholder(char	*start);

/*
** num_arg_checkers
*/
int							is_correct_num_arg_order(char **s);
int							is_num_arg_in_this_pholder(char *format);
int							is_numbered_arg_used(const char *format);
unsigned int				has_numbered_args(char *pholder_start);

/*
** pholder_managment
*/
int							count_pholders(const char *format);
char						*find_next_pholder(char **format);
int							parse_a_pholder(char *start, t_pholder **pholder,
											int num_args_flag, int pholder_num);

/*
** exit
*/
void						malloc_error_exit();
void						*ft_malloc_or_exit(size_t size);

/*
** modifiers_initializers
*/
t_arg_type					*initialize_arg_type();
t_flags						*initialize_flags();
t_width						*initialize_width();
t_precision					*initialize_precision();
t_modifier					*initialize_modifier();

/*
** parsing_modifiers
*/
void						add_flags(t_pholder **pholder, char **str);
int							add_field_width(t_pholder **pholder, char **str,
											int numbered_args_flag);
int							add_precision(t_pholder **pholder, char **str,
											int numbered_args_flag);
void						add_length_modifier(t_pholder **ph, char **str);
int							parse(const char *format, t_pholder **pholders);

/*
** filling_pholder_struct
*/
void						add_arg_position(t_pholder **pholder, char **temp);
void						add_specifier(t_pholder **pholder, char **str);
int							add_procent(t_pholder **pholder);

/*
** num_args_validation
*/
int							check_and_count_dub_args(t_pholder **pholders,
													int expected_args_num);

/*
** arg_uses_creation
*/
t_arg_use					**save_arg_uses(t_pholder **pholders, int arg_num);

/*
** arg_uses_management
*/
void						save_args_for_all_pholders(t_arg_use *arg_use);
void						**save_args(va_list ap, t_pholder **p, int a_num);

/*
** adding_types_to_arg_uses
*/
char						*get_sint_type(t_modifier *modifier);
char						*get_uint_type(t_modifier *modifier);
char						*get_type(t_pholder *pholder);

/*
** reading_va_list_properties
*/
void						read_width_value_from_arg(t_pholder *p, va_list ap);
void						read_precision_value_from_arg(t_pholder *pholder,
															va_list ap);

/*
** reading_va_list_args
*/
void						read_args(va_list ap, t_arg_use **arg_uses);

/*
** converting_args_to_string
*/
int							convert_args_to_strings(t_pholder **pholders);

/*
** creating_output_line
*/
int							count_pholders_len(t_pholder **pholders);
int							handle_formatted_input(va_list ap, const char *fmt,
													int ps_num, char **line);

/*
** freeing_memory
*/
void						free_arg_uses(t_arg_use **arg_uses);
void						free_args(void **args);
void						free_pholders(t_pholder **pholders, int ps_num);

/*
** colours_switchers
*/
void						switch_to_green(void);
void						switch_to_red(void);
void						switch_to_blue(void);
void						switch_to_default(void);

/*
** colours_managemrnt
*/
int							any_colours_used(char *line, int line_len);
void						print_with_colours(char	*line, int line_len);

/*
** ft_printf
*/
void						print_line(char *line, int line_len);
int							ft_printf(const char *format, ...);

/*
** converters_numbers_char
*/
void						convert_char(t_pholder *pholder);
void						convert_float(t_pholder *pholder);
void						convert_int(t_pholder *pholder);

/*
** uinteger
*/
short int					determine_base(t_pholder *pholder);
void						convert_uint(t_pholder *pholder);

/*
** converters_pointers_time_procent
*/
void						convert_procent(t_pholder *pholder);
void						convert_string(t_pholder *pholder);
void						convert_pointer(t_pholder *pholder);

/*
** float_additional_move_to_libft_01
*/
char						*ft_join_str_array(char **array);
char						*ft_join_strings(int str_num, ...);
long double					ft_float_power(long double n, int power);

/*
** float_additional_move_to_libft_02
*/
int							ft_is_inf(long double num);
int							ft_is_nan(long double num);
void						ft_capitalize(char *s);

/*
** float_fnum_checkers_and_free
*/
int							is_zero(t_float *fnum);
int							is_normal_float_num(t_float *fnum);
void						memfree_fnum(t_float *fnum);

/*
** float_misc_calculations
*/
long double					calculate_rounding(long double num, int precision);
short int					get_exp_bias(int long_flag);
int							get_float_order(long double num);
long double					get_long_double_num(t_pholder *pholder);
int							get_float_exp(long double num);

/*
** float_convert_parts
*/
void						del_trailing_point_zeroes(char *s);
void						convert_float_parts_to_hexstr(t_float *f,
							int l_flag, int p_flag, unsigned char alt_form_f);

/*
** float_hex_convert_rounding
*/
void						convert_long_double_hex(t_pholder *pholder);
void						convert_double_hex(t_pholder *pholder);

/*
** float_convert_for_diff_exp
*/
char						*fractional_part_to_str(long double num,
										int current_order, t_pholder *pholder);
void						convert_huge_float_full(long double num,
													t_pholder *pholder);
void						convert_medium_float_full(long double num,
													t_pholder *pholder);
void						convert_small_float_full(long double num,
													t_pholder *pholder);

/*
** float_convert_f_e_g
*/
void						convert_float_full(long double n, t_pholder *p);
void						convert_float_exp(long double n, t_pholder *p);
void						convert_float_opt(long double n, t_pholder *p);

/*
** float_flags
*/
void						apply_plus(char **s);
void						apply_space(char **s);
void						insert_commas(char **s, int st, int s_num, int len);
void						apply_apost(char **s, int len);

/*
** float_modifiers
*/
void						apply_zeroes(t_pholder *pholder);
void						apply_width_left_align(t_pholder *p, int len);
void						apply_width(t_pholder *pholder, int len);
void						apply_str_modifiers_float(t_pholder *pholder,
													long double num);

/*
** uint_modifiers
*/
char						*get_alt_form_prefix(int base);
void						apply_alt_form_uint(char **s, int base);
void						apply_zeroes_uint(t_pholder *p, int width, int len);
void						apply_flags_uint(t_pholder *pholder, int base);
void						apply_str_modifiers_uint(t_pholder *p, int base);

/*
** integer
*/
void						apply_leading_zeroes_int(t_pholder *pholder,
													int width, int len);
void						convert_int(t_pholder *pholder);

/*
** time_calculations
*/
void						get_day_and_month(short int days, t_time *time);
char						*get_wday(int day);
t_time						*calculate_date_and_time(int epoch_time);
char						*convert_with_nessesery_zero(unsigned char num);

/*
** time
*/
void						convert_time(t_pholder *pholder);

#endif
