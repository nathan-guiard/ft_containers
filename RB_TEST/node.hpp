/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nguiard <nguiard@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 10:49:27 by nguiard           #+#    #+#             */
/*   Updated: 2022/10/26 15:45:38 by nguiard          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_HPP
#define NODE_HPP

#include <iostream>

enum	colors
{
	black = 1,
	red = -1,
}	;

template <typename T>
class	node
{
public:
	node() {
		T	val = new T();
		color = red;
		parent = 0;
		right = 0;
		left = 0;
		value = *val;
		delete val;
	}
	node(const T &val) {
		color = red;
		parent = 0;
		right = 0;
		left = 0;
		value = val;
	}
	node(node *p, const T &val) {
		color = red;
		if (val > p->value)
			p->right = this;
		else
			p->left = this;
		parent = p;
		right = 0;
		left = 0;
		value = val;
	}
	node(const node &copy) {
		this = copy;
	}
	~node() {};

	node	&operator = (const node &copy) {
		color = copy.color;
		parent = copy.parent;
		value = parent->value;
		right = copy.right;
		left = copy.left;
	}

	node	*borther()
	{
		if (parent->right == this)
			return parent->left;
		return parent->right;
	}

//private:
	int			color;
	node		*parent;
	node		*right;
	node		*left;
	T			value;
};

#endif