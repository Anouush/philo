/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angalsty <angalsty@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:22:41 by angalsty          #+#    #+#             */
/*   Updated: 2023/03/31 20:42:16 by angalsty         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

int	ft_check_arg(t_data *data, int argc, char **argv)
{
	int	i;

	i = 1;
	if (argc != 5 && argc != 6)
		return (0);
	if (argc == 5 || argc == 6)
	{
		while (argv[i])
		{
			if (ft_is_digit_str(argv[i]) == 1 || ft_atol(argv[i]) > 2147483647 || ft_atol(argv[1]) > MAX_PHILO)
				return (0);
			i++;
		}
	}
	ft_init_args(data, argc, argv);
	return (1);
}

void ft(void){system("leaks -q philo");}

int	main(int argc, char **argv)
{
	t_data	data;

    atexit(ft);
	data.start_time = get_time();
	if (!ft_check_arg(&data, argc, argv))
		return (write(2, "Wrong arguments\n", 17), 1);
	ft_philos_init(&data);
	ft_mutex_init(&data);
	ft_threads_init(&data);
	ft_join_threads(&data);
	return (0);
}
