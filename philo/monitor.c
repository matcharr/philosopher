/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 12:05:40 by marvin            #+#    #+#             */
/*   Updated: 2025/03/10 12:05:40 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_philo_death(t_data *data, int i)
{
	long	current_time;

	pthread_mutex_lock(&data->death_mutex);
	current_time = get_current_time();
	if (current_time - data->philos[i].last_meal >= data->time_to_die)
	{
		data->someone_died = 1;
		pthread_mutex_unlock(&data->death_mutex);
		print_status(&data->philos[i], "died");
		pthread_mutex_lock(&data->print_mutex);
		usleep(10000);
		return (1);
	}
	pthread_mutex_unlock(&data->death_mutex);
	return (0);
}

void	*monitor_philos(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (check_philo_death(data, i))
				return (NULL);
			i++;
		}
		usleep(MONITOR_DELAY);
	}
	return (NULL);
}
