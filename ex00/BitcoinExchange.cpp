/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 15:54:30 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/29 11:50:20 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

/*Exceptions*/

const char *BitcoinExchange::WrongDatabaseFileFormat::what() const throw()
{
	return ("Wrong database file formating");
}

const char *BitcoinExchange::WrongInputFileFormat::what() const throw()
{
	return ("Wrong input file formating");
}

const char *BitcoinExchange::OpeningDatabaseFile::what() const throw()
{
	return ("Database file cannot be open");
}

const char *BitcoinExchange::OpeningInputFile::what() const throw()
{
	return ("Input file cannot be open");
}

/*Constructors*/

BitcoinExchange::BitcoinExchange()
{
	return;
}

BitcoinExchange::~BitcoinExchange()
{
	return;
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &copy) : _database(copy._database)
{
	return;
}

BitcoinExchange::BitcoinExchange(std::string filename)
{
	std::ifstream							src;
	std::string								line;
	std::pair<std::string, double>			new_elem;

	src.open(filename);
	if (src.is_open() == false)
		throw OpeningDatabaseFile();
	std::getline(src, line);
	if (line.compare("date,exchange_rate\n") == false)
		throw WrongDatabaseFileFormat();
	while (src)
	{
		std::getline(src, line);
		if (!line.empty())
		{
			new_elem = extractDatabaseLineContent(line);
			this->_database.insert(new_elem);
		}
	}
	if (this->_database.empty() == true)
		throw WrongDatabaseFileFormat();
}

/*Operators Overload*/


BitcoinExchange					&BitcoinExchange::operator=(const BitcoinExchange &copy)
{
	this->_database = copy._database;
	return (*this);
}

/*Debug Utils*/

void							BitcoinExchange::print_exchange_database(void)
{
	std::map<std::string, double>::iterator	it;

	it = this->_database.begin();
	while (it != this->_database.end())
	{
		std::cout << it->first << ": " << it->second << std::endl;
		++it;
	}
}

/*Parsing Utils*/

bool	is_bissextile(long int year)
{
	if (year % 4 == 0)
	{
		if (year % 100 == 0)
		{
			if (year % 400 == 0)
				return (true);
			else
				return (false);
		}
		return (true);
	}
	return (false);
}

bool	is_date_format(std::string date)
{
	long int year;
	long int month;
	long int day;

	year = strtol(date.c_str(), NULL, 10);
	month = strtol(date.c_str() + 5, NULL, 10);
	day = strtol(date.c_str() + 8, NULL, 10);
	if (year <= 0 || month <= 0 || month > 12 || day <= 0 || day > 31)
		return (false);
	else if ((month == 4 || month == 6 || month == 9 || month == 11) && day == 31)
		return (false);
	else if ((month == 2 && is_bissextile(year) == true && day > 29) ||
		(month == 2 && is_bissextile(year) == false && day > 28))
		return (false);
	return (true);
}

/*Database Extraction*/

double	BitcoinExchange::getExchangeRate(std::string value)
{
	double					rate;
	size_t					delimiter;
	std::string::iterator	it;

	delimiter = value.find_first_of('.');
	it = value.begin();
	while (*it != '.' && it != value.end())
	{
		if (!isdigit(*it))
			throw WrongDatabaseFileFormat();
		++it;
	}
	if (delimiter != std::string::npos)
	{
		while (++it != value.end())
		{
			if (!isdigit(*it))
				throw WrongDatabaseFileFormat();
		}
	}
	rate = strtod(const_cast<char *>(value.c_str()), NULL);
	if (rate < 0)
		throw WrongDatabaseFileFormat();
	return (rate);
}

std::pair<std::string, double>	BitcoinExchange::extractDatabaseLineContent(std::string &line)
{
	std::string						date;
	std::string						exchangeRate;
	size_t							delimiter;
	std::pair<std::string, double>	result;

	delimiter = line.find_first_of(',');
	if (delimiter == std::string::npos || delimiter + 1 == '\0')
		throw BitcoinExchange::WrongDatabaseFileFormat();
	date = line.substr(0, 10);
	if (is_date_format(date) == false)
		throw BitcoinExchange::WrongDatabaseFileFormat();
	exchangeRate = line.substr(delimiter + 1);
	result.first = date;
	result.second = getExchangeRate(exchangeRate);
	return (result);
}

/*Input file Exctraction*/

double	handleValue(std::string value, std::string line)
{
	double					result;
	size_t					delimiter;
	std::string::iterator	it;

	delimiter = value.find_first_of('.');
	it = value.begin();
	while (*it != '.' && it != value.end())
	{
		if (!isdigit(*it))
		{
			std::cout << "Error: bad input ==> " << line << std::endl;
			return (-1);
		}
		++it;
	}
	if (delimiter != std::string::npos)
	{
		while (++it != value.end())
		{
			if (!isdigit(*it))
			{
				std::cout << "Error: bad input ==> " << line << std::endl;
				return (-1);
			}
		}
	}
	result = strtod(const_cast<char *>(value.c_str()), NULL);
	if (result < 0.0)
	{
		std::cout << "Error: not a positive number.\n";
		return (-1);
	}
	else if (result > 1000.0)
	{
		std::cout << "Error: too large a number.\n";
		return (-1);
	}
	return (result);
}

double	BitcoinExchange::getRate(std::string date)
{
	std::map<std::string, double>::iterator	it;

	it = this->_database.find(date);
	if (it != this->_database.end())
		return (it->second);
	it = this->_database.lower_bound(date);
	if (it-- != this->_database.end())
		return (it->second);
	else
		return (0.0);
}

void	BitcoinExchange::handleInputLineContent(std::string &line)
{
	std::string		date;
	std::string		value;
	size_t			delimiter;
	double			result;

	delimiter = line.find(" | ");
	if (delimiter == std::string::npos || delimiter + 3 == '\0')
	{
		std::cout << "Error: bad input ==> " << line << std::endl;
		return;
	}
	date = line.substr(0, 10);
	if (is_date_format(date) == false)
	{
		std::cout << "Error: bad input ==> " << line << std::endl;
		return;
	}
	value = line.substr(delimiter + 3);
	result = handleValue(value, line);
	if (result >= 0)
	{
		std::cout << date << " => " << value << " = " << result * getRate(date) << std::endl;
	}
}

void		BitcoinExchange::convert_values(std::string filename)
{
	std::ifstream							src;
	std::string								line;
	std::pair<std::string, double>			new_elem;
	std::map<std::string, double>			result;

	src.open(filename);
	if (src.is_open() == false)
		throw OpeningInputFile();
	std::getline(src, line);

	if (line.compare("date | value\n") == false)
		throw BitcoinExchange::WrongInputFileFormat();
	while (src)
	{
		std::getline(src, line);
		if (!line.empty())
			handleInputLineContent(line);
	}
}
