/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angalsty <angalsty@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 19:22:41 by angalsty          #+#    #+#             */
/*   Updated: 2023/04/02 21:16:14 by angalsty         ###   ########.fr       */
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
	while (argv[i])
	{
		if (ft_is_digit_str(argv[i]) == 1 || ft_atol(argv[i]) > 2147483647
			|| ft_atol(argv[1]) > MAX_PHILO)
			return (0);
		if (i > 1 && i < 5 && ft_atol(argv[i]) < 60)
			return (0);
		i++;
	}
	if (ft_atol(argv[1]) < 1)
		return (0);
	ft_init_args(data, argc, argv);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	data.start_time = get_time();
	if (!ft_check_arg(&data, argc, argv))
		return (write(2, "Wrong arguments\n", 17), 1);
	ft_philos_init(&data);
	ft_mutex_init(&data);
	ft_threads_init(&data);
	ft_join_threads(&data);
	return (0);
}
