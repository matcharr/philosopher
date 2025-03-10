/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:05:53 by marvin            #+#    #+#             */
/*   Updated: 2025/03/10 12:05:53 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_current_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * MICROSEC_MULTIPLIER + tv.tv_usec / MICROSEC_MULTIPLIER);
}

void	print_status(t_philo *philo, char *status)
{
	long	current_time;
	int		should_print;

	current_time = get_current_time();
	pthread_mutex_lock(philo->death_mutex);
	should_print = !(*philo->someone_died);
	pthread_mutex_unlock(philo->death_mutex);
	if (should_print || !strcmp(status, "died"))
	{
		pthread_mutex_lock(philo->print_mutex);
		printf("%ld %d %s\n", current_time, philo->id, status);
		pthread_mutex_unlock(philo->print_mutex);
	}
}

int	create_threads(t_data *data, pthread_t *monitor)
{
	int	i;

	if (data->num_philos == 1)
	{
		handle_single_philo(data);
		return (1);
	}
	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]) != 0)
		{
			perror("pthread_create");
			return (0);
		}
		usleep(SMALL_DELAY);
		i++;
	}
	if (pthread_create(monitor, NULL, monitor_philos, data) != 0)
	{
		perror("pthread_create");
		return (0);
	}
	return (1);
}
