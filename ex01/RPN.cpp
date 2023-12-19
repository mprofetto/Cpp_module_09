/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mprofett <mprofett@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 10:03:31 by mprofett          #+#    #+#             */
/*   Updated: 2023/12/19 12:16:41 by mprofett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

const char *RPN::Error::what() const throw()
{
	return ("Error");
}

bool	is_valid_char(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || isdigit(c))
		return (true);
	return (false);
}

void	RPN::parse_input(std::string input)
{
	std::string::iterator	it;
	bool					space_expected;

	it = input.begin();
	if (it == input.end())
		throw Error();
	space_expected = false;
	while (it != input.end())
	{
		if (space_expected == false)
		{
			if (is_valid_char(*it))
			{
				this->_expression.push(*it);
				space_expected = true;
			}
			else
				throw Error();
		}
		else
		{
			if (*it == ' ')
				space_expected = false;
			else
				throw Error();
		}
		++it;
	}
	--it;
	if (is_valid_char(*it) == false)
		throw Error();
}

RPN::RPN()
{
	;
}

RPN::~RPN()
{
	;
}

RPN::RPN(const RPN &copy) : _expression(copy._expression)
{
	;
}

RPN::RPN(std::string input)
{
	parse_input(input);
}

RPN		&RPN::operator=(const RPN &copy)
{
	this->_expression = copy._expression;
	return (*this);
}

int		RPN::operate(void)
{
	int				elem1;
	int				elem2;
	int				operand;
	long long int	result;

	if (this->_expression.empty())
		throw Error();
	operand = this->_expression.top();
	this->_expression.pop();
	elem1 = get_next_elem();
	elem2 = get_next_elem();
	if (operand == '+')
		result = elem1 + elem2;
	else if (operand == '-')
		result = elem1 - elem2;
	else if (operand == '*')
		result = elem1 * elem2;
	else
	{
		if (elem2 == 0)
			throw Error();
		result = elem1 / elem2;
	}
	if (result > INT_MAX || result < INT_MIN)
		throw Error();
	return (static_cast<int>(result));
}

int		RPN::get_next_elem(void)
{
	int	result;

	if (this->_expression.empty())
		throw Error();
	if (isdigit(this->_expression.top()))
	{
		result = this->_expression.top() - 48;
		this->_expression.pop();
	}
	else
		result = operate();
	return (result);
}

int		RPN::execute(void)
{
	int		result;

	if (isdigit(this->_expression.top()))
	{
		result = this->_expression.top() - 48;
		this->_expression.pop();
		if (this->_expression.empty() == false)
			throw Error();
		return (result);
	}
	result = operate();
	if (this->_expression.empty() == false)
			throw Error();
	return (result);
}
