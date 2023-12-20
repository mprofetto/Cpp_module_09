/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:18:59 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/20 18:46:21 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

const char	*PmergeMe::WrongInputException::what(void) const throw()
{
	return ("Bad input given");
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

void	get_min_max(unsigned int *a, unsigned int *b, unsigned int *min, unsigned int *max)
{
	if (*a > *b)
	{
		*max = *a;
		*min = *b;
	}
	else
	{
		*min = *a;
		*max = *b;
	}
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

void	PmergeMe::fill_list(void)
{
	unsigned int	nbr;
	size_t			start;
	size_t			end;
	std::string		nbr_to_convert;

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
			this->_list.push_back(nbr);
			start = end + 1;
		}
	}
}

void	PmergeMe::fill_vector(void)
{
	unsigned int	nbr;
	size_t			start;
	size_t			end;
	std::string		nbr_to_convert;

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
			this->_vector.push_back(nbr);
			start = end + 1;
		}
	}
}

void			debug_list(std::list<unsigned int> list)
{
	std::list<unsigned int>::iterator	it;

	it = list.begin();
	while (it != list.end())
	{
		std::cout << " " << *it;
		++it;
	}
	std::cout << std::endl;
}

void			debug_vector(std::vector<unsigned int> list)
{
	std::vector<unsigned int>::iterator	it;

	it = list.begin();
	while (it != list.end())
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

std::list<unsigned int>::iterator	get_insertion_pos(std::list<unsigned int>::iterator it, std::list<unsigned int>::iterator end, unsigned int *nbr)
{
	while (it != end)
	{
		if (*it > *nbr)
			return (it);
		else if (*it == *nbr)
			throw PmergeMe::WrongInputException();
		else
			++it;
	}
	return (--it);
}

void			PmergeMe::merge_lists(std::list<unsigned int> &result, std::list<unsigned int> &pending)
{
	std::list<unsigned int>::iterator	it;

	it = result.begin();
	while (pending.empty() == false)
	{
		if (*it < pending.front())
			++it;
		else
		{
			result.insert(it, pending.front());
			pending.pop_front();
		}
	}
	this->_list = result;
}

void			PmergeMe::sort_list(void)
{
	bool					list_is_even;
	unsigned int			straggler;
	unsigned int			min;
	unsigned int			max;
	std::list<unsigned int>	result;
	std::list<unsigned int>	pending;

	if (this->_list.size () % 2 != 0)
	{
		straggler = this->_list.back();
		this->_list.pop_back();
		list_is_even = false;
	}
	else
		list_is_even = true;
	while(this->_list.empty() == false)
	{
		if (this->_list.back() == this->_list.front())
			throw WrongInputException();
		get_min_max(&this->_list.back(), &this->_list.front(), &min, &max);
		if (result.empty())
		{
			result.push_back(max);
			pending.push_back(min);
		}
		else
		{
			result.insert(get_insertion_pos(result.begin(), result.end(), &max), max);
			pending.insert(get_insertion_pos(pending.begin(), pending.end(), &min), min);
		}
		this->_list.pop_back();
		this->_list.pop_front();
	}
	if (pending.empty() == false)
	{
		result.insert(result.begin(), pending.front());
		pending.pop_front();
	}
	if (list_is_even == false)
		result.insert(get_insertion_pos(result.begin(), result.end(), &straggler), straggler);
	merge_lists(result, pending);
}


void			PmergeMe::merge_vector(std::vector<unsigned int> &highest, std::vector<unsigned int> &lowest)
{
	std::vector<unsigned int>::iterator	highest_it;
	std::vector<unsigned int>::iterator	lowest_it;
	std::vector<unsigned int>::iterator	result;

	highest_it = highest.begin();
	lowest_it = lowest.begin();
	result = this->_vector.begin();
	while(!(highest_it == highest.end() && lowest_it == lowest.end()))
	{
		if (lowest_it == lowest.end())
		{
			this->_vector.insert(result, *highest_it);
			++highest_it;
		}
		else if (highest_it == highest.end())
		{
			this->_vector.insert(result, *lowest_it);
			++lowest_it;
		}
		else if (*highest_it < *lowest_it)
		{
			this->_vector.insert(result, *highest_it);
			++highest_it;
		}
		else
		{
			this->_vector.insert(result, *lowest_it);
			++lowest_it;
		}
		++result;
	}
}

std::vector<unsigned int>::iterator	get_vector_insertion_pos(std::vector<unsigned int>::iterator it, std::vector<unsigned int>::iterator end, unsigned int *nbr)
{
	while (it != end)
	{
		if (*it > *nbr)
			return (it);
		else if (*it == *nbr)
			throw PmergeMe::WrongInputException();
		else
			++it;
	}
	return (it);
}

void			PmergeMe::sort_vector(void)
{
	bool						vector_is_even;
	unsigned int				straggler;
	unsigned int				a;
	unsigned int				b;
	unsigned int				min;
	unsigned int				max;
	std::vector<unsigned int>	result;
	std::vector<unsigned int>	pending;

	if (this->_vector.size () % 2 != 0)
	{
		straggler = this->_vector.back();
		this->_vector.pop_back();
		vector_is_even = false;
	}
	else
		vector_is_even = true;
	while(this->_vector.empty() == false)
	{
		a = this->_vector.back();
		this->_vector.pop_back();
		b = this->_vector.back();
		this->_vector.pop_back();
		if (a == b)
			throw WrongInputException();
		get_min_max(&a, &b, &min, &max);
		if (result.empty())
		{
			result.push_back(max);
			pending.push_back(min);
		}
		else
		{
			result.insert(get_vector_insertion_pos(result.begin(), result.end(), &max), max);
			pending.insert(get_vector_insertion_pos(pending.begin(), pending.end(), &min), min);
		}
	}
	if (vector_is_even == false)
		result.insert(get_vector_insertion_pos(result.begin(), result.end(), &straggler), straggler);
	if (pending.empty() == false)
		merge_vector(result, pending);
	else
		this->_vector = result;
}


void			PmergeMe::execute(void)
{
	clock_gettime(CLOCK_REALTIME, &this->_starting_time);
	fill_list();
	sort_list();
	clock_gettime(CLOCK_REALTIME, &this->_ending_time);
	this->_list_execution_time = get_elapsed_time();
	clock_gettime(CLOCK_REALTIME, &this->_starting_time);
	fill_vector();
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
