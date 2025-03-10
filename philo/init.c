/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:05:31 by marvin            #+#    #+#             */
/*   Updated: 2025/03/10 12:05:31 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_data(t_data *data, int argc, char **argv)
{
	if (!validate_args(data, argc, argv))
		return (0);
	data->someone_died = 0;
	data->philos = malloc(sizeof(t_philo) * data->num_philos);
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_philos);
	if (!data->philos || !data->forks)
	{
		perror("malloc");
		return (0);
	}
	return (1);
}

int	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			perror("pthread_mutex_init");
			return (0);
		}
		i++;
	}
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0
		|| pthread_mutex_init(&data->death_mutex, NULL) != 0)
	{
		perror("pthread_mutex_init");
		return (0);
	}
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
		data->philos[i].left_fork = &data->forks[i];
		data->philos[i].right_fork = &data->forks[(i + 1) % data->num_philos];
		data->philos[i].print_mutex = &data->print_mutex;
		data->philos[i].someone_died = &data->someone_died;
		data->philos[i].death_mutex = &data->death_mutex;
		i++;
	}
}
