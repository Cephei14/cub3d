/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdhaibi <rdhaibi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 15:50:45 by rdhaibi           #+#    #+#             */
/*   Updated: 2025/10/31 11:52:21 by rdhaibi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.h"

int map_check(char **map)
{
	return 0;
}

int main(int ac, char **av)
{
	if(av != 2)
	{
		return 1;
	}
	if(map_check == 1)
	{
		return 1;
	}
	t_game game;
	
	game.mlx_ptr = mlx_init();
}