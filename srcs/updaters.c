/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   updaters.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tang <tang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 04:07:09 by tang              #+#    #+#             */
/*   Updated: 2023/08/25 20:42:52 by tang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	register_mode(t_parser *p)
{
	int	digit;

	digit = p->current_char - '0';
	if (digit < 0 || digit > 9)
		return ;
	if (!(p->datas & NO_MIN_WDTH))
		p->padding_left = p->padding_left * 10 + digit;
	else if (p->datas & PRECISION_MODE)
		p->precision = p->precision * 10 + digit;
	else if (p->datas & PADDING_L_MODE)
		p->padding_left = p->padding_left * 10 + digit;
	else if (p->datas & PADDING_R_MODE)
		p->padding_right = p->padding_right * 10 + digit;
}

static void	register_argument(t_parser *p)
{
	if (p->datas & FROM_INT)
	{
		p->arg_int = va_arg(p->ap, int);
		p->conv.num = p->arg_int;
		if ((p->datas & TO_INT) && p->arg_int < 0)
			p->datas |= HAS_MINUS_SGN;
	}
	else if (p->datas & FROM_STR)
	{
		p->arg_str = va_arg(p->ap, char *);
		if (!p->arg_str)
			p->arg_str = "(null)";
	}
	else if (p->datas & FROM_PTR)
		p->conv.llnum = (unsigned long long)va_arg(p->ap, void *);
}

static void	process_print(t_parser *p)
{
	get_output_size_argument(p);
	padding_settings(p);
	if (p->padding_right && (p->datas & HAS_SPACE_BLK) && p->arg_int > 0)
		p->padding_right--;
	padding_left(p);
	print_flag(p);
	print_argument(p);
	if (p->padding_right && p->datas & FROM_STR && p->precision)
		p->padding_right = p->padding_right - p->precision;
	else if (p->padding_right && p->datas & FROM_STR)
		p->padding_right = p->padding_right - p->arg_len;
	print_padding(p, p->padding_right, SIGN_NOWHERE, ' ');
}

void	auto_update(t_parser *p)
{
	if ((p->fresh_datas & PADDING_L_MODE) && \
		(p->datas & (REGISTER__MODE | PRECISION_MODE | PADDING_R_MODE)))
		p->fresh_datas = REGISTER__MODE;
	else if (!(p->fresh_datas & REGISTER__MODE) && (p->datas & REGISTER__MODE))
		p->datas &= ~REGISTER__MODE;
	p->datas |= p->fresh_datas;
	if (p->datas & SWITCH_CONV_MODE)
	{
		if (p->datas & CONVERSION_MODE)
			print_chr(p, p->current_char);
		p->datas ^= (ORDINARY_MODE | CONVERSION_MODE | SWITCH_CONV_MODE);
	}
	else if ((p->datas & ORDINARY_MODE) && !(p->datas & SWITCH_CONV_MODE))
	{
		p->datas = ORDINARY_MODE;
		print_chr(p, p->current_char);
	}
	else if (p->datas & END_CONV_MODE)
	{
		register_argument(p);
		process_print(p);
		parser_init(p);
	}
	else if (p->datas & (CONVERSION_MODE | REGISTER__MODE))
		register_mode(p);
}
