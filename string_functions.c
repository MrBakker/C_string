/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string_functions.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbakker <jbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/25 20:40:17 by jbakker       #+#    #+#                 */
/*   Updated: 2024/06/25 21:00:14 by jbakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

int	string_resize(char **string, int new_capacity)
{
	t_string_header	*old_header;
	t_string_header	*new_header;
	char			*new_str;
	int				index;

	old_header = (t_string_header *)(*string - sizeof(t_string_header));
	new_header = malloc(sizeof(t_string_header) + new_capacity);
	if (!new_header)
		return (EXIT_FAILURE);
	new_str = (char *)(new_header + 1);
	index = -1;
	while (++index < old_header->length)
		new_str[index] = (*string)[index];
	*string = new_str;
	new_header->capacity = new_capacity;
	new_header->length = old_header->length;
	free(old_header);
	return (EXIT_SUCCESS);
}

int	string_push(char **string, char c)
{
	t_string_header	*header;

	header = (t_string_header *)(*string - sizeof(t_string_header));
	if (header->length == header->capacity - 1)
		if (string_resize(string, header->capacity * STRING_RESIZE_FACTOR) \
			== EXIT_FAILURE)
			return (EXIT_FAILURE);
	header = (t_string_header *)(*string - sizeof(t_string_header));
	(*string)[header->length++] = c;
	(*string)[header->length] = '\0';
	return (EXIT_SUCCESS);
}

int	string_append(char **string, char *str)
{
	t_string_header	*header;
	int				length;
	int				new_capacity;

	length = 0;
	while (str[length])
		length++;
	header = (t_string_header *)(*string - sizeof(t_string_header));
	if (header->length + length >= header->capacity - 1)
	{
		new_capacity = header->capacity * STRING_RESIZE_FACTOR;
		while (header->length + length >= new_capacity - 1)
			new_capacity *= STRING_RESIZE_FACTOR;
		if (string_resize(string, new_capacity) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	header = (t_string_header *)(*string - sizeof(t_string_header));
	while (*str)
		(*string)[header->length++] = *str++;
	(*string)[header->length] = '\0';
	return (EXIT_SUCCESS);
}

int	string_length(char *str)
{
	return (((t_string_header *)((t_string_header *)(str) - 1))->length);
}

int	string_capacity(char *str)
{
	return (((t_string_header *)((t_string_header *)(str) - 1))->capacity);
}
