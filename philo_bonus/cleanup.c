/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:15:54 by marvin            #+#    #+#             */
/*   Updated: 2025/03/10 12:15:54 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	cleanup(t_data *data)
{
	int		i;
	int		status;
	pid_t	pid;

	pid = waitpid(-1, &status, 0);
	if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_DEATH)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (data->philos[i].pid != pid && data->philos[i].pid > 0)
				kill(data->philos[i].pid, SIGTERM);
			i++;
		}
	}
	while (waitpid(-1, NULL, 0) > 0)
	{
	}
	sem_close(data->forks);
	sem_close(data->print_sem);
	sem_unlink(FORK_SEM_NAME);
	sem_unlink(PRINT_SEM_NAME);
	free(data->philos);
}
