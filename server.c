/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: binam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 05:59:43 by binam             #+#    #+#             */
/*   Updated: 2022/03/02 18:41:55 by binam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sig_write(int signum, siginfo_t *siginfo, void *unused)
{
	static int	i = 7;
	static int	character = 0;
	int			c;

	(void)unused;
	if (signum == SIGUSR1)
		c = 1;
	else
		c = 0;
	character += c << i;
	if (i == 0)
	{
		write(1, &character, 1);
		i = 7;
		character = 0;
		if (kill(siginfo->si_pid, SIGUSR2) == -1)
			putstr("Error signal\n");
	}
	else
		i--;
}

int	main(void)
{
	struct sigaction	came;

	write(1, "server pid = : ", 13);
	inttoasci(getpid());
	write(1, "\n", 1);
	came.sa_flags = SA_SIGINFO;
	came.sa_sigaction = sig_write;
	if ((sigaction(SIGUSR1, &came, 0)) == -1)
		putstr("Error sigaction\n");
	if ((sigaction(SIGUSR2, &came, 0)) == -1)
		putstr("Error sigaction\n");
	while (1)
		pause();
}
