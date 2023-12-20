/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:18:27 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/20 17:33:06 by mprofett         ###   ########.fr       */
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
		std::string					_sequence;
		struct timespec				_starting_time;
		struct timespec				_ending_time;
		double						_list_execution_time;
		double						_vector_execution_time;
		std::list<unsigned int>		_list;
		std::vector<unsigned int>	_vector;

		PmergeMe();
		double			get_elapsed_time(void) const;
		void			fill_list(void);
		void			fill_vector(void);
		void			sort_list(void);
		void			merge_lists(std::list<unsigned int> &result, std::list<unsigned int> &pending);
		void			sort_vector(void);
		void			merge_vector(std::vector<unsigned int> &result, std::vector<unsigned int> &pending);
		void			print_list(void);

	public:
		class WrongInputException : public std::exception
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
