/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-bar <isel-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:04:27 by isel-bar          #+#    #+#             */
/*   Updated: 2025/01/20 14:43:41 by isel-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_line(int fd, char *buffer)
{
	char	*temp_buffer;
	int		bytes_read;

	temp_buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp_buffer)
		return (NULL);
	bytes_read = 1;
	while (!ft_chr_new_line(buffer) && bytes_read != 0)
	{
		bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			free(temp_buffer);
			return (NULL);
		}
		temp_buffer[bytes_read] = '\0';
		buffer = ft_strjoin(buffer, temp_buffer);
	}
	free(temp_buffer);
	return (buffer);
}

static char	*extract_line_from_buffer(char *buffer)
{
	int		line_length;
	char	*extracted_line;

	line_length = 0;
	if (!buffer[line_length])
		return (NULL);
	while (buffer[line_length] && buffer[line_length] != '\n')
		line_length++;
	line_length++;
	extracted_line = malloc(sizeof(char) * (line_length + 1));
	if (!extracted_line)
		return (NULL);
	extracted_line[line_length] = '\0';
	while (--line_length >= 0)
		extracted_line[line_length] = buffer[line_length];
	return (extracted_line);
}

static char	*update_buffer_after_line(char *buffer)
{
	size_t	newline_pos;
	size_t	buffer_len;
	char	*remaining_text;

	newline_pos = 0;
	while (buffer[newline_pos] && buffer[newline_pos] != '\n')
		newline_pos++;
	if (!buffer[newline_pos])
		return (free(buffer), NULL);
	buffer_len = ft_strlen(buffer);
	remaining_text = malloc(sizeof(char) * (buffer_len - newline_pos));
	if (!remaining_text)
		return (free(buffer), NULL);
	newline_pos++;
	buffer_len = 0;
	while (buffer[newline_pos])
		remaining_text[buffer_len++] = buffer[newline_pos++];
	remaining_text[buffer_len] = '\0';
	free(buffer);
	return (remaining_text);
}

char	*get_next_line(int fd)
{
	char		*current_line;
	static char	*storage_buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	storage_buffer = read_line(fd, storage_buffer);
	if (!storage_buffer)
		return (NULL);
	current_line = extract_line_from_buffer(storage_buffer);
	storage_buffer = update_buffer_after_line(storage_buffer);
	return (current_line);
}
// #include <stdio.h>

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("test.txt", O_RDONLY);
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return (0);
// }