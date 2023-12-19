/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:18:27 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/19 16:38:14 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <exception>
# include <iostream>
# include <string>
# include <ctime>
# include <list>
# include <set>

class APmergeMe
{
	protected:
		struct timespec	_starting_time;
		struct timespec	_ending_time;
		bool			_executed;
		double			_last_execution_time;
		size_t			_size;

		APmergeMe();
		double			get_elapsed_time(void) const;

	public:
		class WrongInputException : public std::exception
		{
			virtual const char	*what(void) const throw();
		};

		~APmergeMe();
		APmergeMe(const APmergeMe &copy);
		APmergeMe		&operator=(const APmergeMe &copy);
		virtual void	parse_argument(std::string input) = 0;
		virtual void	sort(void) = 0;
		virtual void	display_sequence(void) const = 0;
		virtual void	display_processing_time(void) const = 0;
};

class ListMerge : public APmergeMe
{
	private:
		std::list<unsigned int>	_sequence;
		ListMerge();

	public:
		~ListMerge();
		ListMerge(const ListMerge &copy);
		ListMerge(std::string input);
		ListMerge	&operator=(const ListMerge &copy);
		virtual void	parse_argument(std::string input);
		virtual void	sort(void);
		virtual void	display_sequence(void) const;
		virtual void	display_processing_time(void) const;
};

class SetMerge : public APmergeMe
{
	private:
		std::set<unsigned int>	_sequence;
		SetMerge();

	public:
		~SetMerge();
		SetMerge(const SetMerge &copy);
		SetMerge(std::string input);
		SetMerge	&operator=(const SetMerge &copy);
		virtual void	parse_argument(std::string input);
		virtual void	sort(void);
		virtual void	display_sequence(void) const;
		virtual void	display_processing_time(void) const;
};

#endif
