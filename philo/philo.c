/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:05:45 by marvin            #+#    #+#             */
/*   Updated: 2025/03/10 12:51:00 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_args(t_data *data, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
	{
		printf("Usage: ./philo_bonus number_of_philosophers time_to_die ");
		printf("time_to_eat time_to_sleep ");
		printf("[number_of_times_each_philosopher_must_eat]\n");
		return (0);
	}
	data->num_philos = atoi(argv[1]);
	data->time_to_die = atoi(argv[2]);
	data->time_to_eat = atoi(argv[3]);
	data->time_to_sleep = atoi(argv[4]);
	if (argc == 6)
		data->num_times_must_eat = atoi(argv[5]);
	else
		data->num_times_must_eat = NO_MEAL_LIMIT;
	if (data->num_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0
		|| (argc == 6 && data->num_times_must_eat <= 0))
	{
		printf("Error: All arguments must be positive numbers\n");
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_data		data;
	pthread_t	monitor;

	if (!init_data(&data, argc, argv))
		return (1);
	if (!init_mutexes(&data))
	{
		free(data.philos);
		free(data.forks);
		return (1);
	}
	init_philosophers(&data);
	if (!create_threads(&data, &monitor))
	{
		cleanup(&data);
		return (1);
	}
	pthread_join(monitor, NULL);
	cleanup(&data);
	return (0);
}
