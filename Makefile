NAME = libftprintf.a

SRC_FILES = ft_printf.c \
			char.c \
			float.c \
			integer.c \
			pointer.c \
			procent.c \
			string.c \
			time.c \
			uinteger.c \
			adding_types_to_arg_uses.c \
			arg_uses_creation.c \
			arg_uses_management.c \
			colours_managemrnt.c \
			colours_switchers.c \
			converting_args_to_string.c \
			creating_output_line.c exit.c \
			filling_pholder_struct.c \
			float_additional_move_to_libft_01.c \
			float_additional_move_to_libft_02.c \
			float_convert_f_e_g.c \
			float_convert_for_diff_exp.c \
			float_convert_parts.c \
			float_flags.c \
			float_fnum_checkers_and_free.c \
			float_hex_convert_rounding.c \
			float_misc_calculations.c \
			float_modifiers.c \
			freeing_memory.c \
			modifier_checkers.c \
			modifiers_initializers.c \
			num_arg_checkers.c \
			num_args_validation.c \
			parsing_modifiers.c \
			pholder_managment.c \
			procent_checkers.c \
			reading_va_list_args.c \
			reading_va_list_properties.c \
			time_calculations.c \
			uint_modifiers.c \
			validation.c

LIB_FILES = ft_abs.c \
			ft_bzero.c \
			ft_isalpha.c \
			ft_isdigit.c \
			ft_itoa.c \
			ft_llint_to_str_base.c \
			ft_memalloc.c \
			ft_memcpy.c \
			ft_memdel.c \
			ft_memmove.c \
			ft_memset.c \
			ft_str_free_array.c \
			ft_strchr.c \
			ft_strcmp.c \
			ft_strcpy.c \
			ft_strdel.c \
			ft_strdup.c \
			ft_strequ.c \
			ft_strjoin.c \
			ft_strlen.c \
			ft_strnchr.c \
			ft_strncmp.c \
			ft_strncpy.c \
			ft_strnequ.c \
			ft_strnew.c \
			ft_strnstr.c \
			ft_strtol.c \
			ft_toupper.c \
			ft_ullint_to_str_base.c \
			ft_chrtoint.c \
			ft_isspace.c \
			ft_tolower.c

SRC_DIR = ./src/

LIB_DIR = ./libft/

SOURCES = $(addprefix $(SRC_DIR), $(SRC_FILES))

LIB_SOURCES = $(addprefix $(LIB_DIR), $(LIB_FILES))

INC_PRINTF_DIR = .

INC_LIB_DIR = ./libft/

INC_PRINTF = ./ft_printf.h

INC_LIBFT = $(LIB_DIR)libft.h

OBJECTS_DIR = ./objects/

LIB_OBJECTS_DIR = ./libft/objects/

OBJECTS = 	$(OBJECT_FILES) \
			$(addprefix $(LIB_OBJECTS_DIR), $(LIB_OBJECT_FILES))

OBJECT_FILES = $(patsubst %.c,$(OBJECTS_DIR)%.o,$(SRC_FILES))

LIB_OBJECT_FILES = $(LIB_FILES:.c=.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -ggdb

EXAMPLE = example

EXAMPLE_MAIN = example.c

all: $(NAME)

$(EXAMPLE): $(EXAMPLE_MAIN) $(NAME)
	 @$(CC) -ggdb $(EXAMPLE_MAIN) -o $(EXAMPLE) -I $(INC_PRINTF_DIR) -I $(INC_LIB_DIR) -L . $(NAME)


$(NAME): $(OBJECTS_DIR) $(OBJECTS)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)
	@echo "$(NAME) is successfully compiled"

$(OBJECTS_DIR)%.o: $(SRC_DIR)%.c $(INC_PRINTF)
	@$(CC) $(CFLAGS) -I $(INC_PRINTF_DIR) -I $(INC_LIB_DIR) -c $< -o $@

$(LIB_OBJECTS_DIR)%.o: $(LIB_DIR)%.c $(INC_LIBFT)
	@$(CC) $(CFLAGS) -ggdb -I $(LIB_DIR) -c $< -o $@

$(OBJECTS_DIR):
	@mkdir $(OBJECTS_DIR)
	@mkdir $(LIB_OBJECTS_DIR)

clean:
	@/bin/rm -f $(OBJECTS)
	@/bin/rm -fr $(OBJECTS_DIR)
	@/bin/rm -fr $(LIB_OBJECTS_DIR)
	@echo "Removed object files"

fclean: clean
	@/bin/rm -f $(NAME)
	@echo "Removed $(NAME)"

re: fclean all

.PHONY: all clean fclean re
