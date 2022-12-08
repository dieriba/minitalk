/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:52:08 by dtoure            #+#    #+#             */
/*   Updated: 2022/11/16 14:52:08 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_received = 0;

void	handle_char(pid_t pid, unsigned char c)
{
	int	i;

	i = 7;
	while (i >= 0)
	{
		g_received = 0;
		if (kill(pid, 0) < 0)
		{
			ft_putstr_fd("An error occured while trying to\
			reach out for the process ID : ", 2);
			ft_putnbr_fd(pid, 2);
			ft_putchar_fd('\n', 2);
			exit(EXIT_FAILURE);
		}
		if ((1 << i) & c)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		while (!g_received)
			usleep(20);
		i--;
	}
}

void	handle_string(int pid, char *msg)
{
	int	i;

	i = -1;
	while (msg[++i])
		handle_char(pid, (unsigned char)msg[i]);
	handle_char(pid, 0);
}

void	handler(int signal, siginfo_t *client, void *ucontext)
{
	(void)ucontext;
	if (signal == SIGUSR1)
		g_received = 1;
	else if (signal == SIGUSR2)
	{
		ft_putstr_fd("Message successfully sent to the server : ", 1);
		ft_putnbr_fd(client->si_pid, 1);
		ft_putstr_fd(" Good Job !\n", 1);
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char *argv[])
{
	pid_t				pid;
	struct sigaction	sig;

	if (argc != 3)
	{
		ft_putstr_fd("Usage : ./client <pid> <message_to_send>\n", 1);
		exit(EXIT_FAILURE);
	}
	sig.sa_flags = SA_SIGINFO;
	sig.sa_sigaction = handler;
	sigemptyset(&(sig.sa_mask));
	sigaction(SIGUSR2, &sig, NULL);
	sigaction(SIGUSR1, &sig, NULL);
	if (!is_valid_pid(argv[1]))
	{
		ft_putstr_fd("This PID is not valid\n", 1);
		exit(EXIT_FAILURE);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		ft_putstr_fd("This PID is not reachable..., \
		please stop joking enter the real value!\n", 1);
		exit(EXIT_FAILURE);
	}
	handle_string(pid, argv[2]);
}
