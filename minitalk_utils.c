/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 06:01:02 by binam             #+#    #+#             */
/*   Updated: 2022/02/27 06:01:03 by binam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	inttoasci(int pid)
{
	char	c;

	if (pid >= 10)
		inttoasci(pid / 10);
	c = (pid % 10) + 48;
	write(1, &c, 1);
}

int	ascitoint(char *str)
{
	int	number;

	number = 0;
	while (*str)
		number = (10 * number) + (*str++ - 48);
	return (number);
}

void	putstr(char *str)
{
	while (*str)
		write(1, &(*str++), 1);
	exit(0);
}
