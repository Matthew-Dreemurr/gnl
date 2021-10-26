/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mahadad <mahadad@student.s19.be>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 14:02:38 by mahadad           #+#    #+#             */
/*   Updated: 2021/10/26 15:51:54 by mahadad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"


void	debug_nl(char *str)
{
	while (str && *str)
	{
		if (*str == '\n')
			printf("[\\n]");
		else
			putchar(*str);
		str++;
	}
	puts("\n");
}

char	*ret_next_line(char **str)
{
	char	*ret;
	char	*str_ptr;
	char	*ptr;

	ret = (char *)malloc((1 + len_chrchr(*str, '\n')) * sizeof(char));
	if (!ret)
		return (NULL);
	str_ptr = *str;
	ptr = ret;
	while (*str_ptr)
	{
		*ptr++ = *str_ptr;
		if (*str_ptr++ == '\n')
			break ;
	}
	*ptr = '\0';
	ptr = *str;
	while (*str_ptr)
		*ptr++ = *str_ptr++;
	*ptr = '\0';
	// printf("ret_next_line |||%s|||\n", ret);
	return (ret);
}

/**
 * @brief 
 * 
 * @param buff 
 * @return int 
 */
ssize_t		read_next_line(char *buff, int fd)
{
	ssize_t	ret;

	ret = read(fd, buff, BUFFER_SIZE);
	if (ret > 0)
		buff[ret] = '\0';
	return (ret);
}

/**
 * @brief Get the next line object
 *
 * @param fd File descriptor to read from.
 * @return char* Read line:  correct behavior NULL: nothing else to read
 *               or anerror occurred.
 */
char	*get_next_line(int fd)
{
	static t_gnl	gnl[OPEN_MAX];

	if (fd < 0 || fd > OPEN_MAX)
		return (NULL);
	gnl[fd].rret = 1;
	gnl[fd].buff[0] = '\0';
	while (gnl[fd].rret > 0 && !len_chrchr(gnl[fd].buff, '\n'))
	{
		gnl[fd].rret = read_next_line(gnl[fd].buff, fd);
		if (!gnl[fd].rret || gnl[fd].rret == -1)
			return (free_return(&gnl[fd].tmp));
		// puts("====buff nextline===");
		// debug_nl(gnl[fd].buff);
		// BR;
		gnl[fd].tmp = strjoin_and_free(&gnl[fd].tmp, gnl[fd].buff);
		if (!gnl[fd].tmp)
			return (free_return(&gnl[fd].tmp));
		// puts("====strjoin===");
		// debug_nl(gnl[fd].tmp);
		// BR;
	}
	return (ret_next_line(&gnl[fd].tmp));
}
