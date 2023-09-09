/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inititalizers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tang <tang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 21:33:23 by tang              #+#    #+#             */
/*   Updated: 2023/09/09 13:18:48 by tang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

static size_t	ft_intlen(long long n, int base)
{
	size_t	len;

	len = 0;
	if (n < 0)
	{
		n = -n;
		len++;
	}
	while (n >= base)
	{
		len++;
		n = (n / base);
	}
	len = len + 1;
	return (len);
}

static size_t	ft_strlen(char *str)
{
	size_t	len;

	len = 0;
	if (str == NULL)
		return (6);
	while (str[len] != '\0')
		len++;
	return (len);
}

void	get_output_size_argument(t_parser *p)
{
	p->arg_len = ft_intlen(p->conv.llnum, 16) + 2;
	if (p->datas & FROM_PTR && (p->conv.llnum == ULONG_MAX))
		p->arg_len = 18;
	else if (p->datas & TO_HEX && !(p->datas & FROM_PTR))
		p->arg_len = (ft_intlen((unsigned int)p->arg_int, 16));
	else if (p->datas & TO_INT)
		p->arg_len = (ft_intlen(p->arg_int, 10));
	else if (p->datas & TO_UINT)
		p->arg_len = (ft_intlen((unsigned int)p->arg_int, 10));
	else if (p->datas & TO_BIT)
		p->arg_len = (ft_intlen((unsigned int)p->arg_int, 2));
	else if (p->datas & TO_OCT)
		p->arg_len = (ft_intlen((unsigned int)p->arg_int, 8));
	else if (p->datas & FROM_STR)
	{
		if (p->arg_str == NULL)
			p->arg_len = (6);
		else
			p->arg_len = ft_strlen(p->arg_str);
		if (p->datas & HAS_PRECISION && p->precision < p->arg_len)
			p->arg_len = p->precision;
	}
	else if (p->datas & TO_UCHAR)
		p->arg_len = 1;
}

void	flag_init(unsigned int flag[255])
{
	int	i;

	i = -1;
	while (++i < 255)
		flag[i] = 0;
	flag['%'] = SWITCH_CONV_MODE;
	flag['#'] = (HAS_ALTERNATE);
	flag['.'] = (HAS_PRECISION | PRECISION_MODE | NO_MIN_WDTH);
	flag['0'] = (HAS_PADDING_0 | PADDING_L_MODE | NO_MIN_WDTH);
	i = '0';
	while (++i <= '9')
		flag[i] = (REGISTER__MODE);
	flag['-'] = (HAS_PADDING_R | PADDING_R_MODE | NO_MIN_WDTH);
	flag[' '] = (HAS_SPACE_BLK);
	flag['+'] = (HAS_PLUS_SIGN);
	flag['c'] = (FROM_INT | TO_UCHAR | END_CONV_MODE);
	flag['b'] = (FROM_INT | TO_BIT | END_CONV_MODE);
	flag['d'] = (FROM_INT | TO_INT | END_CONV_MODE);
	flag['i'] = (FROM_INT | TO_INT | END_CONV_MODE);
	flag['o'] = (FROM_INT | TO_UINT | END_CONV_MODE);
	flag['u'] = (FROM_INT | TO_UINT | END_CONV_MODE);
	flag['x'] = (FROM_INT | TO_HEX | END_CONV_MODE);
	flag['X'] = (FROM_INT | TO_HEX | USE_CAP | END_CONV_MODE);
	flag['p'] = (FROM_PTR | TO_HEX | END_CONV_MODE);
	flag['s'] = (FROM_STR | END_CONV_MODE);
}

void	parser_init(t_parser *parser)
{
	if (parser->flag['%'] != SWITCH_CONV_MODE)
	{
		flag_init(parser->flag);
	}
	parser->conv.llnum = 0;
	parser->conv.num = 0;
	parser->datas = ORDINARY_MODE;
	parser->current_char = 0;
	parser->max_width = 0;
	parser->precision = 0;
	parser->padding_left = 0;
	parser->padding_right = 0;
	parser->padding_char = 32;
	parser->padding_right = 0;
	parser->arg_len = 0;
	parser->arg_int = 0;
}
