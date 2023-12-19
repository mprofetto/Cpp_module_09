/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:03:09 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/19 12:14:10 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP

# include <exception>
# include <climits>
# include <stack>
# include <string>
# include <iostream>

class RPN
{
	private:
		std::stack<char>		_expression;

		RPN();
		void	parse_input(std::string input);
		int		get_next_elem(void);
		int		operate(void);
		void	set_operations(void);

	public:

		class Error : public std::exception
		{
			virtual const char *what() const throw();
		};

		~RPN();
		RPN(const RPN &copy);
		RPN(std::string input);

		RPN		&operator=(const RPN &copy);
		int		execute(void);
};

#endif
