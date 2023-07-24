#include <unistd.h>

/**
 * _putchar - puts
 * @c:arguments
 *
 * Return: int
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
