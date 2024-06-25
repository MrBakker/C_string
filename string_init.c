/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string_init.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbakker <jbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/25 16:11:29 by jbakker       #+#    #+#                 */
/*   Updated: 2024/06/25 20:59:42 by jbakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "string.h"

char	*string_init(int size)
{
	t_string_header	*header;

	if (size < 0)
		return (NULL);
	if (size == 0)
		size = STRING_DEFAULT_SIZE;
	header = malloc(sizeof(t_string_header) + size);
	if (!header)
		return (NULL);
	header->capacity = size;
	header->length = 0;
	*((char *)(header + 1)) = '\0';
	return ((char *)(header + 1));
}

char	*string_init_str(char *str)
{
	t_string_header	*header;
	char			*new_str;
	int				length;

	length = 0;
	while (str[length])
		length++;
	header = malloc(sizeof(t_string_header) + length + 1);
	if (!header)
		return (NULL);
	header->capacity = length + 1;
	header->length = length;
	new_str = (char *)(header + 1);
	new_str[length] = '\0';
	while (length--)
		new_str[length] = str[length];
	return (new_str);
}

void	string_free(char **string)
{
	free((t_string_header *)(*string - sizeof(t_string_header)));
	*string = NULL;
}

char	*string_to_default(char **string)
{
	t_string_header	*header;
	int				length;
	int				index;

	header = (t_string_header *)(*string - sizeof(t_string_header));
	length = header->length;
	index = -1;
	while (++index < length)
		((char *)header)[index] = (*string)[index];
	((char *)header)[index] = '\0';
	*string = (char *)header;
	return (*string);
}
