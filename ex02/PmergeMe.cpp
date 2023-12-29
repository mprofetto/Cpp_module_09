/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:18:59 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/29 10:06:39 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

const char	*PmergeMe::WrongInputException::what(void) const throw()
{
	return ("Bad input given");
}

const char	*PmergeMe::DuplicateException::what(void) const throw()
{
	return ("There is some duplicate in integers sequence");
}

bool	is_zero(std::string input)
{
	std::string::iterator	it;

	it = input.begin();
	while (it != input.end())
	{
		if (*it != '0')
			return (false);
		++it;
	}
	return (true);
}

PmergeMe::PmergeMe()
{
	return;
}

PmergeMe::~PmergeMe()
{
	return;
}

PmergeMe::PmergeMe(char **argv)
{
	int	i;

	if (argv && argv[0] && argv[1])
	{

		i = 1;
		while(argv[i])
		{
			this->_sequence += argv[i];
			if (argv[++i])
				this->_sequence += " ";
		}
	}
	else
		throw WrongInputException();
}

PmergeMe::PmergeMe(const PmergeMe &copy) :
	_sequence(copy._sequence),
	_starting_time(copy._starting_time),
	_ending_time(copy._ending_time),
	_list_execution_time(copy._list_execution_time),
	_vector_execution_time(copy._vector_execution_time),
	_list(copy._list),
	_vector(copy._vector)
{
	return;
}

PmergeMe		&PmergeMe::operator=(const PmergeMe &copy)
{
	this->_sequence = copy._sequence;
	this->_starting_time = copy._starting_time;
	this->_ending_time = copy._ending_time;
	this->_list_execution_time = copy._list_execution_time;
	this->_vector_execution_time = copy._vector_execution_time;
	this->_list = copy._list;
	this->_vector = copy._vector;
	return (*this);
}

double			PmergeMe::get_elapsed_time(void) const
{
	return (this->_ending_time.tv_sec - this->_starting_time.tv_sec
		+ (this->_ending_time.tv_nsec - this->_starting_time.tv_nsec) * 1e-9);
}

void		PmergeMe::print_vector(void)
{
	std::vector<unsigned int>::iterator	it;

	it = this->_vector.begin();
	while (it != this->_vector.end())
	{
		std::cout << " " << *it;
		++it;
	}
	std::cout << std::endl;
}

void			PmergeMe::print_list(void)
{
	std::list<unsigned int>::iterator	it;

	it = this->_list.begin();
	while (it != this->_list.end())
	{
		std::cout << " " << *it;
		++it;
	}
	std::cout << std::endl;
}


void			PmergeMe::fill_unsorted_list(void)
{
	unsigned int				nbr;
	size_t						start;
	size_t						end;
	std::string					nbr_to_convert;
	std::list<unsigned int>		new_elem;

	if (this->_sequence.find_first_not_of(" 0123456789", 0) != std::string::npos)
		throw WrongInputException();
	start = 0;
	while (start != std::string::npos)
	{
		start = this->_sequence.find_first_of("0123456789", start);
		if (start != std::string::npos)
		{
			end = this->_sequence.find_first_of(" ", start);
			if (end == std::string::npos)
				end = this->_sequence.size() - 1;
			nbr_to_convert = this->_sequence.substr(start, end - start + 1);
			nbr = strtol(nbr_to_convert.c_str(), NULL, 10);
			if (nbr == 0 && is_zero(nbr_to_convert) == false)
				throw WrongInputException();
			new_elem.push_back(nbr);
			this->_unsorted_list.push_back(new_elem);
			new_elem.clear();
			start = end + 1;
		}
	}
	if (this->_unsorted_list.size() == 0)
		throw WrongInputException();
}

void	PmergeMe::fill_unsorted_vector(void)
{
	unsigned int				nbr;
	size_t						start;
	size_t						end;
	std::string					nbr_to_convert;
	std::vector<unsigned int>	new_elem;

	if (this->_sequence.find_first_not_of(" 0123456789", 0) != std::string::npos)
		throw WrongInputException();
	start = 0;
	while (start != std::string::npos)
	{
		start = this->_sequence.find_first_of("0123456789", start);
		if (start != std::string::npos)
		{
			end = this->_sequence.find_first_of(" ", start);
			if (end == std::string::npos)
				end = this->_sequence.size() - 1;
			nbr_to_convert = this->_sequence.substr(start, end - start + 1);
			nbr = strtol(nbr_to_convert.c_str(), NULL, 10);
			if (nbr == 0 && is_zero(nbr_to_convert) == false)
				throw WrongInputException();
			new_elem.push_back(nbr);
			this->_unsorted_vector.push_back(new_elem);
			new_elem.clear();
			start = end + 1;
		}
	}
	if (this->_unsorted_vector.size() == 0)
		throw WrongInputException();
}

std::vector<unsigned int>			merge_vector(std::vector<unsigned int> &highest, std::vector<unsigned int> &lowest)
{
	std::vector<unsigned int>::iterator	highest_it;
	std::vector<unsigned int>::iterator	lowest_it;
	std::vector<unsigned int>			ret;

	highest_it = highest.begin();
	lowest_it = lowest.begin();
	while(!(highest_it == highest.end() && lowest_it == lowest.end()))
	{
		if (lowest_it == lowest.end())
		{
			ret.push_back(*highest_it);
			++highest_it;
		}
		else if (highest_it == highest.end())
		{
			ret.push_back(*lowest_it);
			++lowest_it;
		}
		else if (*highest_it < *lowest_it)
		{
			ret.push_back(*highest_it);
			++highest_it;
		}
		else
		{
			ret.push_back(*lowest_it);
			++lowest_it;
		}
	}
	return (ret);
}

void			PmergeMe::sort_vector(void)
{
	std::vector<std::vector<unsigned int> >	new_vector;
	std::vector<unsigned int>				a;
	std::vector<unsigned int>				b;
	std::vector<unsigned int>				temp;

	while (this->_unsorted_vector.size() != 1)
	{
		while (this->_unsorted_vector.empty() == false)
		{
			a = this->_unsorted_vector.back();
			this->_unsorted_vector.pop_back();
			if (this->_unsorted_vector.empty() == false)
			{
				b = this->_unsorted_vector.back();
				this->_unsorted_vector.pop_back();
				temp = merge_vector(a, b);
				new_vector.push_back(temp);
			}
			else
			{
				if (new_vector.empty() == false)
				{
					b = new_vector.back();
					new_vector.pop_back();
					temp = merge_vector(a, b);
					new_vector.push_back(temp);
				}
				else
					new_vector.push_back(a);
			}
		}
		this->_unsorted_vector = new_vector;
		new_vector.clear();
	}
	this->_vector = this->_unsorted_vector.back();
	this->_unsorted_vector.pop_back();
}

void			PmergeMe::merge_sort_list(void)
{
	std::list<std::list<unsigned int> >	new_list;
	std::list<unsigned int>				a;
	std::list<unsigned int>				b;

	while (this->_unsorted_list.size() != 1)
	{
		while (this->_unsorted_list.empty() == false)
		{
			a = this->_unsorted_list.back();
			this->_unsorted_list.pop_back();
			if (this->_unsorted_list.empty() == false)
			{
				b = this->_unsorted_list.back();
				this->_unsorted_list.pop_back();
				a.merge(b);
				new_list.push_back(a);
			}
			else
			{
				if (new_list.empty() == false)
				{
					b = new_list.back();
					new_list.pop_back();
					a.merge(b);
					new_list.push_back(a);
				}
				else
					new_list.push_back(a);
			}
		}
		this->_unsorted_list = new_list;
		new_list.clear();
	}
	this->_list = this->_unsorted_list.back();
	this->_unsorted_list.pop_back();
}

void			PmergeMe::execute(void)
{
	clock_gettime(CLOCK_REALTIME, &this->_starting_time);
	fill_unsorted_list();
	merge_sort_list();
	clock_gettime(CLOCK_REALTIME, &this->_ending_time);
	this->_list_execution_time = get_elapsed_time();
	clock_gettime(CLOCK_REALTIME, &this->_starting_time);
	fill_unsorted_vector();
	sort_vector();
	clock_gettime(CLOCK_REALTIME, &this->_ending_time);
	this->_vector_execution_time = get_elapsed_time();
	std::cout << "Before: " << this->_sequence << std::endl;
	std::cout << "After: ";
	print_list();
	std::cout << std::endl;
	std::cout << std::setprecision(10) << std::fixed;
	std::cout << "Time to process a range of " << this->_list.size() << " elements with std::list :   ";
	std::cout << this->_list_execution_time << "s" << std::endl;
	std::cout << "Time to process a range of " << this->_vector.size() << " elements with std::vector : ";
	std::cout << this->_vector_execution_time << "s" << std::endl;
}
