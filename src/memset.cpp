#include "../inc/ft_irc.hpp"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*s_byte;
	unsigned char	c_byte;
	size_t			i;

	s_byte = (unsigned char *)s;
	c_byte = (unsigned char)c;
	i = 0;
	while (i < n)
		s_byte[i++] = c_byte;
	return (s);
}