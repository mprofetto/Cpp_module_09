/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:18:27 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/28 17:04:23 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
# define PMERGEME_HPP

# include <exception>
# include <iostream>
# include <iomanip>
# include <iterator>
# include <string>
# include <ctime>
# include <list>
# include <vector>

class PmergeMe
{
	private:
		std::string								_sequence;
		struct timespec							_starting_time;
		struct timespec							_ending_time;
		double									_list_execution_time;
		double									_vector_execution_time;
		std::list<std::list<unsigned int> >		_unsorted_list;
		std::vector<std::vector<unsigned int> >	_unsorted_vector;
		std::list<unsigned int>					_list;
		std::vector<unsigned int>				_vector;

		PmergeMe();
		double			get_elapsed_time(void) const;
		void			fill_unsorted_list(void);
		void			fill_unsorted_vector(void);
		void			merge_sort_list(void);
		void			sort_vector(void);
		void			print_list(void);
		void			print_vector(void);

	public:
		class WrongInputException : public std::exception
		{
			virtual const char	*what(void) const throw();
		};

		class DuplicateException : public std::exception
		{
			virtual const char	*what(void) const throw();
		};

		~PmergeMe();
		PmergeMe(char **argv);
		PmergeMe(const PmergeMe &copy);
		PmergeMe		&operator=(const PmergeMe &copy);
		void			execute(void);
};


#endif
