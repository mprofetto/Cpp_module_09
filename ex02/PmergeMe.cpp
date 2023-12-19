/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:18:59 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/19 16:40:21 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

const char	*APmergeMe::WrongInputException::what(void) const throw()
{
	return ("Bad input given");
}

APmergeMe::APmergeMe() : _executed(false), _last_execution_time(0), _size(0)
{
	return;
}

APmergeMe::~APmergeMe()
{
	return;
}

APmergeMe::APmergeMe(const APmergeMe &copy) : _executed(copy._executed), _last_execution_time(copy._last_execution_time), _size(copy._size)
{
	return;
}

APmergeMe		&APmergeMe::operator=(const APmergeMe &copy)
{
	this->_executed = copy._executed;
	this->_last_execution_time = copy._last_execution_time;
	this->_size = copy._size;
	return (*this);
}

double			APmergeMe::get_elapsed_time(void) const
{
	return (this->_ending_time.tv_sec - this->_starting_time.tv_sec  + (this->_ending_time.tv_nsec - this->_starting_time.tv_nsec) * 1e-9);
}

ListMerge::ListMerge()
{
	return;
}

ListMerge::~ListMerge()
{
	return;
}

ListMerge::ListMerge(const ListMerge &copy) : _sequence(copy._sequence)
{
	this->_executed = copy._executed;
	this->_last_execution_time = copy._last_execution_time;
	this->_size = copy._size;
	return;
}

ListMerge	&ListMerge::operator=(const ListMerge &copy)
{
	this->_executed = copy._executed;
	this->_last_execution_time = copy._last_execution_time;
	this->_size = copy._size;
	this->_sequence = copy._sequence;
}

ListMerge::ListMerge(std::string input)
{
	parse_argument(input);
}

void	parse_argument(std::string input)
{
	;
}

// virtual void	sort(void);
// virtual void	display_sequence(void) const;
// virtual void	display_processing_time(void) const;

	// private:
	// 	std::list<unsigned int>	_sequence;
