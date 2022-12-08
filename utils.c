/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:50:30 by dtoure            #+#    #+#             */
/*   Updated: 2022/11/16 14:50:30 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	is_process_running(pid_t pid, char *msg)
{
	if (kill(pid, 0) < 0)
	{
		ft_putstr_fd(("An error occured while trying reach out to \
			proccess, exiting...\n"), 2);
		if (msg)
			free(msg);
		exit(EXIT_FAILURE);
	}
}

int	is_valid_pid(char *pid)
{
	size_t	i;

	i = -1;
	while (pid[++i])
	{
		if (!ft_isdigit(pid[i]))
			return (0);
	}
	return (1);
}
