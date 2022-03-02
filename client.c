/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 05:56:55 by binam             #+#    #+#             */
/*   Updated: 2022/03/02 18:42:58 by binam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sig_init(int signum, unsigned char *msg)
{
	int	i;
	int	c;

	c = 0;
	i = 128;
	while (msg[c] != '\0')
	{
		while (i >= 1)
		{
			if (msg[c] / i)
			{
				kill(signum, SIGUSR1);
				msg[c] = msg[c] - i;
			}
			else
				kill(signum, SIGUSR2);
			usleep(100);
			i /= 2;
		}
		i = 128;
		c++;
	}
}

void	sig_fback(int signum, siginfo_t *siginfo, void *unused)
{
	(void)unused;
	(void)siginfo;
	(void)signum;
	write(1, "Sinyal Feedback Alındı\n", 25);
}

int	main(int argc, char **argv)
{
	struct sigaction	came;

	came.sa_flags = SA_SIGINFO;
	came.sa_sigaction = sig_fback;
	if ((sigaction(SIGUSR2, &came, 0)) == -1)
		putstr("Sinyal Gönderme Hatası\n");
	if (argc == 3)
		sig_init(ascitoint(argv[1]), (unsigned char *)argv[2]);
	else
		putstr("Gönderilemedi yanlış parametre\n");
	while (1)
		pause();
}
