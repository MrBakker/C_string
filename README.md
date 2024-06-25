# A memory safe simple string library for C.

It's quite annoying to always calculate the length of a new string before mallocing it, especially when the complexity of your program is growing. A common solution is to use some sort of container, which is automatically adjusting it's size. You can just add chars to your string, and the library will take care of the space.

## How does it work?

The library is mallocing some space in which a string can be build. But the first 8 bytes are used to store data about the capacity and length of the current string. This will give a memory layout like this:

| Length   | Capacity | String...      |
| -------- | -------- | -------------- |
| 4 bytes  | 4 bytes  | Capacity bytes |

So when our capacity is 16, a total of 24 bytes will be allocated to store the string and it's metadata. Because a pointer to the first caracter of the string is returned, and the library is making sure this string is **always** null-terminated, it could be used as any normal C string.

The downside here is that you cannot free the string like you can do with normal strings: the start of the allocated memory is not the start of your string. And every call that's changing the length of the string should be protectd, since a memory reallocation could happen at any time.

## Code example

```c
#include "string.h"
#include <stdio.h>

int main(void)
{
	// -------- example 1 --------
	char	*str;

	// Init a string with any given length.
	str = string_init(STRING_DEFAULT_SIZE);
	if (!str)
		return (EXIT_FAILURE);
	
	/* Loop through all the characters in the alphabet and push them to the string. It will malloc more space if needed, and will always null-terminate the end. If the malloc fails, it will return EXIT_FAILURE. It's up to the programmer to act accordingly. */
	for (int i = 0; i < 26; i++)
	{
		if (string_push(&str, 'a' + i) == EXIT_FAILURE)
		{
			return (string_free(&str), EXIT_FAILURE);
		}
	}

	/* The string can be printed like any other C-strings, since the library will always make sure it's null-terminated. The length and the capacity of any string can be read through the STRING_LENGTH and STRING_CAPACITY macros. */
	printf("%s\nLength: %d\nCapacity: %d\n", str, string_length(str), string_capacity(str));
	/* Output
		abcdefghijklmnopqrstuvwxyz
		Length: 26
		Capacity: 32
	*/

	/* Calling this function will remove the metadata about the strings and copy all the string elements to the start of the last allocated block. From now on, it's just a normal C string, and can be freed using the normal free() function. Obviously, the library functions wont work anymore. */
	string_to_default(&str);

	// It's a normal string now, which we can use to print, and free afterwards.
	printf("%s\n", str);
	/* Output
		abcdefghijklmnopqrstuvwxyz
	*/

	free(str);

	// -------- example 2 --------
	char	*str2;

	// Create a new string, but fill it with a default string.
	str2 = string_init_str("Hello, ");
	if (!str2)
		return (EXIT_FAILURE);
	
	// Append another string to our string
	if (string_append(&str2, "you beautiful world!") == EXIT_FAILURE)
		return (string_free(&str2), EXIT_FAILURE);
	
	/* Print the string and get it's properties like usual. Note that we just use the string_free function this time, since we don't need to convert it. */
	printf("%s\nLength: %d\nCapacity: %d\n", str2, string_length(str2), string_capacity(str2));
	/* Output
		Hello, you beautiful world!
		Length: 27
		Capacity: 32
	*/
	string_free(&str2);

	/* The string_free function will set the value of the string to NULL, to prevent possible undefined behaviour in the future. */
	printf("%p\n", str2);
	/* Output
		(nil)
	*/

	return (0);
}
```
---
_Made as a module for my 42 minishell project. Due to certain rules in wiriting code for their projects, we are not allowed to use "Macro functions", therefore the somewhat non-intuitive code at some places. More information about them can be found at their [website](https://www.42network.org/)._