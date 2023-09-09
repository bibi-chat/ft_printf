/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tang <tang@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 20:18:30 by tang              #+#    #+#             */
/*   Updated: 2023/09/07 04:10:59 by tang             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *fmt, ...)
{
	t_parser		parser;

	flag_init(parser.flag);
	parser_init(&parser);
	parser.total_length = 0;
	va_start(parser.ap, fmt);
	while (*fmt)
	{
		parser.current_char = *fmt;
		parser.fresh_datas = parser.flag[(unsigned int)parser.current_char];
		auto_update(&parser);
		fmt++;
	}
	va_end(parser.ap);
	return (parser.total_length);
}

void	print_chr(t_parser *p, unsigned char c)
{
	write(1, &c, 1);
	p->total_length++;
}

void	print_str(t_parser *p, char *str, int from_end)
{
	size_t	i;

	i = 0;
	if (!str || str == NULL)
		str = "(null)";
	while (str[i])
	{
		if (!from_end)
			print_chr(p, str[i]);
		i++;
	}
	if (from_end)
		while (i--)
			print_chr(p, str[i]);
}

void	print_int(t_parser *p, long i)
{
	char	c;

	c = 0;
	if (i < 0)
	{
		i = -i;
	}
	if (i >= 10)
	{
		c = (i % 10) + '0';
		print_int(p, i / 10);
		print_chr(p, c);
	}
	else
		print_chr(p, i + '0');
}

size_t	to_hex_oct_bit(t_parser *p, const char base[16], int n)
{
	static int	count = 0;
	static char	numll[128] = {0};
	int			count_cpy;

	while (p->conv.llnum)
	{
		if (n == HEXA)
			numll[count] = base[p->conv.hex];
		else if (n == OCTAL)
			numll[count] = base[p->conv.oct];
		else if (n == BINARY)
			numll[count] = base[p->conv.bit];
		p->conv.llnum >>= n;
		count++;
	}
	if (count == 0)
		numll[count++] = '0';
	numll[count] = '\0';
	print_str(p, numll, 1);
	count_cpy = count;
	count = 0;
	return (count_cpy);
}
