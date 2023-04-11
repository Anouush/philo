/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angalsty <angalsty@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/13 20:06:42 by angalsty          #+#    #+#             */
/*   Updated: 2023/04/03 18:44:06 by angalsty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atol(const char *str)
{
	long int	i;
	long int	pos;
	long int	res;

	i = 0;
	pos = 1;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			pos = -1;
		i++;
	}
	while (str[i])
	{
		if (str[i] >= 48 && str[i] <= 57)
			res = (res * 10) + (str[i] - '0');
		else
			break ;
		i++;
	}
	return (res * pos);
}

int	ft_is_digit_str(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

void	ft_sleep(t_philo *philo)
{
	ft_print_action(philo, "is sleeping\n");
	ft_usleep(philo, philo->data->time_to_sleep);
}

void	ft_print_action(t_philo *philo, char *str)
{
	if (!ft_continue_condition(philo))
	{
		pthread_mutex_lock(&philo->data->writing);
		printf("%ld %d %s", get_time() - philo->data->start_time, philo->index
			+ 1, str);
		pthread_mutex_unlock(&philo->data->writing);
	}
}

void	ft_usleep(t_philo *philo, long time)
{
	long	time_to_wait;

	time_to_wait = get_time() + time;
	while (get_time() < time_to_wait)
	{
		pthread_mutex_lock(&philo->data->checking);
		if (!philo->data->run)
		{
			pthread_mutex_unlock(&philo->data->checking);
			return ;
		}
		pthread_mutex_unlock(&philo->data->checking);
		usleep(235);
	}
}
