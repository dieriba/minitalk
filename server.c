/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:44:31 by dtoure            #+#    #+#             */
/*   Updated: 2022/11/16 14:44:31 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

size_t	g_i = -1;

char	*ft_realloc(char *msg, int *count)
{
	char	*new_msg;
	size_t	i;

	i = -1;
	new_msg = ft_calloc(((BUFFER_SIZE * 2) + g_i + 1), sizeof(char));
	if (!new_msg)
	{
		free(msg);
		ft_putstr_fd("Failed To Re-allocate Memory\n", 2);
		exit(EXIT_FAILURE);
	}
	while ((msg[++i]))
		new_msg[i] = msg[i];
	free(msg);
	*count = 0;
	return (new_msg);
}

void	create_char(char *msg, char *c, size_t *i, int *count)
{
	msg[++(*i)] = *c;
	*count = *count + 1;
	*c = 0;
}

void	end_client(char **msg, siginfo_t *client, int *count, size_t *i)
{
	write(1, *msg, (*(i) + 1));
	free(*msg);
	*i = -1;
	*msg = NULL;
	*count = 0;
	kill(client->si_pid, SIGUSR2);
}

void	handler(int signal, siginfo_t *client, void *ucontext)
{
	static int	shift = -1;
	static char	c;
	static char	*msg;
	static int	count;

	is_process_running(client->si_pid, msg);
	(void)ucontext;
	if (!msg)
		msg = ft_calloc(BUFFER_SIZE + 1, (sizeof(char)));
	if (!msg)
		exit(EXIT_FAILURE);
	if (shift < 0)
		shift = 7;
	if (signal == SIGUSR1)
		c |= (1 << shift);
	shift--;
	if (shift < 0 && c)
		create_char(msg, &c, &g_i, &count);
	else if (shift < 0 && !c)
		end_client(&msg, client, &count, &g_i);
	if (count == BUFFER_SIZE - 1)
		msg = ft_realloc(msg, &count);
	kill(client->si_pid, SIGUSR1);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sig;

	sig.sa_flags = SA_SIGINFO | SA_RESTART;
	sig.sa_sigaction = handler;
	sigemptyset(&(sig.sa_mask));
	pid = getpid();
	ft_putstr_fd("Server PID is : ", 1);
	ft_putnbr_fd(pid, 1);
	ft_putchar_fd('\n', 1);
	sigaction(SIGUSR2, &sig, NULL);
	sigaction(SIGUSR1, &sig, NULL);
	while (1)
		sleep(1);
}
