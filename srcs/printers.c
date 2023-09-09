/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tang <tang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 15:56:21 by tang              #+#    #+#             */
/*   Updated: 2023/08/24 15:58:11 by tang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_padding(t_parser *p, int padding, int sign, char padding_c)
{
	if (sign == SIGN_AFTER && padding_c == '0')
		sign = SIGN_BEFORE;
	if (sign == SIGN_BEFORE && p->datas & HAS_MINUS_SGN)
		print_chr(p, '-');
	else if (sign == SIGN_BEFORE && p->datas & HAS_PLUS_SIGN)
		print_chr(p, '+');
	if (sign == SIGN_BEFORE || sign == SIGN_AFTER)
		if (p->datas & HAS_MINUS_SGN)
			padding++;
	if (p->datas & HAS_SPACE_BLK && p->arg_int >= 0)
	{
		print_chr(p, ' ');
		p->datas &= ~HAS_SPACE_BLK;
		padding--;
	}
	while (padding-- > 0)
		print_chr(p, padding_c);
	if (sign == SIGN_AFTER && p->datas & HAS_MINUS_SGN)
		print_chr(p, '-');
	else if (sign == SIGN_AFTER && p->datas & HAS_PLUS_SIGN)
		print_chr(p, '+');
	return ;
}

void	padding_settings(t_parser *p)
{
	if (p->datas & HAS_PADDING_0 && !(p->datas & HAS_PRECISION))
		p->padding_char = '0';
	if ((p->datas & HAS_PRECISION) && p->precision == 0 && p->arg_int == 0)
		p->arg_len = 0;
	if (p->precision > p->arg_len && p->datas & FROM_STR)
		p->precision = p->arg_len;
	if (p->padding_left)
	{
		if (p->datas & HAS_MINUS_SGN || p->datas & HAS_PLUS_SIGN)
			p->padding_left--;
		if (p->datas & HAS_ALTERNATE)
			p->padding_left -= 2;
	}
	if (p->padding_right && !(p->datas & FROM_STR))
	{
		if (p->precision < p->arg_len)
			p->padding_right = p->padding_right - p->arg_len;
		else if (p->precision >= p->arg_len)
			p->padding_right = p->padding_right - p->precision;
		else
			p->padding_right = 0;
		if ((p->datas & HAS_MINUS_SGN || p->datas & HAS_PLUS_SIGN) \
		&& p->precision >= p->arg_len)
			p->padding_right--;
	}
}

void	padding_left(t_parser *p)
{
	if (p->precision && p->padding_left)
	{
		if (p->precision < p->arg_len)
		{
			if (p->datas & HAS_MINUS_SGN || p->datas & HAS_PLUS_SIGN)
				p->padding_left++;
			print_padding(p, p->padding_left - p->arg_len, SIGN_NOWHERE, ' ');
		}
		else
			print_padding(p, p->padding_left - p->precision, SIGN_NOWHERE, ' ');
		if (p->datas & HAS_MINUS_SGN || p->datas & HAS_PLUS_SIGN)
			p->padding_left++;
		if (p->datas & HAS_ALTERNATE)
			p->padding_left += 2;
		print_padding(p, p->precision - p->arg_len, SIGN_BEFORE, '0');
	}
	if (p->padding_left && !p->precision)
		print_padding(p, p->padding_left - p->arg_len, SIGN_AFTER, \
			p->padding_char);
	if (p->precision && !p->padding_left)
		print_padding(p, p->precision - p->arg_len, SIGN_BEFORE, '0');
	if (!p->precision && !p->padding_left)
		print_padding(p, -1, SIGN_BEFORE, '.');
}

void	print_flag(t_parser *p)
{
	if (p->datas & FROM_STR)
		return ;
	if (((p->datas & HAS_ALTERNATE) && (p->arg_int != 0))
		|| (p->datas & FROM_PTR))
	{
		if (p->datas & USE_CAP)
			print_str(p, "0X", 0);
		else
			print_str(p, "0x", 0);
	}
}

void	print_argument(t_parser *p)
{
	if (p->datas & FROM_INT && p->arg_int == 0 && p->arg_len == 0)
		return ;
	else if (p->datas & TO_INT)
		print_int(p, p->arg_int);
	else if (p->datas & TO_UINT)
		print_int(p, (unsigned int)p->arg_int);
	else if ((p->datas & TO_HEX) && (p->datas & USE_CAP))
		to_hex_oct_bit(p, HEXA_UPPER, HEXA);
	else if ((p->datas & TO_HEX) && !(p->datas & USE_CAP))
		to_hex_oct_bit(p, HEXA_LOWER, HEXA);
	else if (p->datas & TO_BIT)
		to_hex_oct_bit(p, HEXA_LOWER, BINARY);
	else if (p->datas & TO_OCT)
		to_hex_oct_bit(p, HEXA_LOWER, OCTAL);
	else if (p->datas & FROM_STR)
	{
		if (p->datas & HAS_PRECISION)
			while (p->arg_len--)
				print_chr(p, *(p->arg_str++));
		else
			print_str(p, p->arg_str, 0);
	}
	else if (p->datas & TO_UCHAR)
		print_chr(p, (unsigned char)p->arg_int);
}
