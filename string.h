/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   string.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: jbakker <jbakker@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/06/25 16:10:16 by jbakker       #+#    #+#                 */
/*   Updated: 2024/06/25 20:57:00 by jbakker       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRING_H
# define STRING_H

# include <stdlib.h>
# include <unistd.h>

# define STRING_DEFAULT_SIZE 16
# define STRING_RESIZE_FACTOR 2

typedef struct s_string_header
{
	int		length;
	int		capacity;
}	t_string_header;

char	*string_init(int size);
char	*string_init_str(char *str);
char	*string_to_default(char **string);
void	string_free(char **string);

int		string_resize(char **string, int new_capacity);
int		string_push(char **string, char c);
int		string_append(char **string, char *str);
int		string_length(char *string);
int		string_capacity(char *string);

#endif