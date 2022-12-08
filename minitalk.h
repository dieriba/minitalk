/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtoure <dtoure@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 14:42:25 by dtoure            #+#    #+#             */
/*   Updated: 2022/11/16 14:42:25 by dtoure           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define BUFFER_SIZE 5
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include <unistd.h>
# include "./libft/libft.h"

int		is_valid_pid(char *pid);
void	is_process_running(pid_t pid, char *str);
#endif