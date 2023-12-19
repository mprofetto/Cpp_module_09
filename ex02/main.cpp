/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:17:59 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/19 15:30:49 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <unistd.h>

int	main(void)
{
	struct timespec	begin;
	struct timespec	end;
	double			result;

	clock_gettime(CLOCK_REALTIME, &begin);
	usleep(300);
	clock_gettime(CLOCK_REALTIME, &end);
	result = end.tv_sec - begin.tv_sec  + (end.tv_nsec - begin.tv_nsec) * 1e-9;
	std::cout << result << std::endl;
	return (0);
}
