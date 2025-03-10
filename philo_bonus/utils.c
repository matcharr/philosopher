/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:06:14 by marvin            #+#    #+#             */
/*   Updated: 2025/03/10 12:06:14 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * MICROSEC_MULTIPLIER + tv.tv_usec / MICROSEC_MULTIPLIER);
}

void	print_status(t_philo *philo, char *status)
{
	long	current_time;

	current_time = get_current_time();
	sem_wait(philo->print_sem);
	printf("%ld %d %s\n", current_time, philo->id, status);
	sem_post(philo->print_sem);
}

int	create_processes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].pid = fork();
		if (data->philos[i].pid < 0)
		{
			perror("fork");
			return (0);
		}
		else if (data->philos[i].pid == 0)
		{
			philo_routine(&data->philos[i]);
			exit(EXIT_SUCCESS);
		}
		usleep(SMALL_DELAY);
		i++;
	}
	return (1);
}
