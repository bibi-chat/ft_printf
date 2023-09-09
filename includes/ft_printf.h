/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tang <tang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 20:18:30 by tang              #+#    #+#             */
/*   Updated: 2023/09/07 04:22:24 by tang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# define HEXA 	4
# define OCTAL 	2
# define BINARY 1

# define SIGN_BEFORE	1
# define SIGN_AFTER		0
# define SIGN_NOWHERE	-1

# define HAS_ALTERNATE	0x1		
# define HAS_PRECISION	0x2		
# define HAS_PADDING_L	0x4		
# define HAS_PADDING_0	0x8		
# define HAS_PADDING_R	0x10	
# define HAS_SPACE_BLK	0x20	
# define HAS_PLUS_SIGN	0x40	
# define HAS_MINUS_SGN	0x80	
# define MINUS_SET		0x100	
# define NO_MIN_WDTH	0x20000000	

# define FROM_INT	0x200   
# define FROM_STR	0x400
# define FROM_PTR	0x800	
# define FROM_UINT	0x80000 

# define TO_HEX		0x1000	
# define TO_UCHAR	0x2000	
# define TO_UINT	0x4000	
# define TO_INT		0x8000	
# define TO_BIT		0x10000	
# define TO_OCT		0x20000	
# define USE_CAP	0x40000	

# define PRECISION_MODE		0x100000
# define PADDING_L_MODE		0x400000
# define PADDING_R_MODE		0x800000
# define REGISTER__MODE		0x1000000
# define END_CONV_MODE		0x2000000
# define SWITCH_CONV_MODE	0x4000000
# define ORDINARY_MODE		0x8000000
# define CONVERSION_MODE	0x10000000

# define HEXA_LOWER "0123456789abcdef"
# define HEXA_UPPER "0123456789ABCDEF"

typedef union u_converter
{
	unsigned int			num;
	unsigned long long		llnum;
	unsigned int			hex:4;
	unsigned int			oct:2;
	unsigned int			bit:1;
}			t_converter;

typedef struct s_parser
{
	va_list			ap;
	unsigned int	flag[255];
	char			current_char;
	unsigned int	fresh_datas;
	unsigned int	datas;
	unsigned int	precision;
	t_converter		conv;
	int				padding_left;
	int				padding_right;
	int				max_width;
	char			padding_char;
	size_t			arg_len;
	int				arg_int;
	char			*arg_str;
	long long		arg_ptr;
	int				total_length;
}				t_parser;

int		ft_printf(const char *fmt, ...);
void	flag_init(unsigned int flag[255]);
void	parser_init(t_parser *parser);
void	auto_update(t_parser *p);
void	padding_left(t_parser *p);
void	padding_settings(t_parser *p);
void	print_padding(t_parser *p, int padding, int sign, char padding_c);
void	print_argument(t_parser *p);
void	print_flag(t_parser *p);
void	print_chr(t_parser *p, unsigned char c);
void	print_str(t_parser *p, char *str, int from_end);
void	print_int(t_parser *p, long i);
size_t	to_hex_oct_bit(t_parser *p, const char base[16], int n);
void	get_output_size_argument(t_parser *p);

#endif