/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:53:47 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/29 11:32:45 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <map>
# include <fstream>
# include <string>
# include <exception>
# include <iterator>
# include <iostream>

class BitcoinExchange
{
	private:
		std::map<std::string, double>	_database;

		BitcoinExchange();
		std::pair<std::string, double>			extractDatabaseLineContent(std::string &line);
		double									getExchangeRate(std::string value);
		void									handleInputLineContent(std::string &line);

	public:

		class WrongDatabaseFileFormat : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

		class WrongInputFileFormat : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

		class OpeningDatabaseFile : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

		class OpeningInputFile : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

		~BitcoinExchange();
		BitcoinExchange(std::string filename);
		BitcoinExchange(const BitcoinExchange &copy);

		BitcoinExchange		&operator=(const BitcoinExchange &copy);
		void				print_exchange_database(void);
		void				convert_values(std::string filename);
		double				getRate(std::string date);
};
#endif
