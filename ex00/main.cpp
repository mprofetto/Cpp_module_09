/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:53:09 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/15 16:26:56 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <map>

int	main(void)
{
	BitcoinExchange	c("data.csv");

	c.convert_values("inputfile.txt");
	return(0);
}
