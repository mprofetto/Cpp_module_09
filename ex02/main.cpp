/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:17:59 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/20 15:09:38 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int	main(int argc, char **argv)
{
	try
	{
		PmergeMe	a(argv);

		a.execute();
	}
	catch(const std::exception& e)
	{
		std::cerr << e.what() << '\n';
	}
	(void) argc;
	return (0);
}
