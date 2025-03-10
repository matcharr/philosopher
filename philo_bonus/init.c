/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:06:00 by marvin            #+#    #+#             */
/*   Updated: 2025/03/10 12:06:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_semaphores(t_data *data)
{
	sem_unlink(FORK_SEM_NAME);
	sem_unlink(PRINT_SEM_NAME);
	data->forks = sem_open(FORK_SEM_NAME, O_CREAT, PERMISSION_MODE,
			data->num_philos);
	data->print_sem = sem_open(PRINT_SEM_NAME, O_CREAT, PERMISSION_MODE, 1);
	if (data->forks == SEM_FAILED || data->print_sem == SEM_FAILED)
	{
		perror("sem_open");
		free(data->philos);
		return (0);
	}
	return (1);
}

int	init_data(t_data *data, int argc, char **argv)
{
	if (!validate_args(data, argc, argv))
		return (0);
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	if (!data->philos)
	{
		perror("malloc");
		return (0);
	}
	if (!init_semaphores(data))
		return (0);
	return (1);
}

void	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		data->philos[i].id = i + 1;
		data->philos[i].num_philos = data->num_philos;
		data->philos[i].time_to_die = data->time_to_die;
		data->philos[i].time_to_eat = data->time_to_eat;
		data->philos[i].time_to_sleep = data->time_to_sleep;
		data->philos[i].num_times_must_eat = data->num_times_must_eat;
		data->philos[i].eaten_count = 0;
		data->philos[i].last_meal = get_current_time();
		data->philos[i].forks = data->forks;
		data->philos[i].print_sem = data->print_sem;
		data->philos[i].monitor_thread = 0;
		i++;
	}
}
