/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: isel-bar <isel-bar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 19:04:27 by isel-bar          #+#    #+#             */
/*   Updated: 2024/12/10 19:04:37 by isel-bar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char *read_line(int fd, char *buffer)
{
    char *morceau;
    int read_bytes;

    morceau = malloc(sizeof(char) * BUFFER_SIZE + 1);
    if (!morceau)
        return (NULL);
    read_bytes = 1;
    while (!ft_chr_new_line(buffer) && read_bytes != 0)
    {
        read_bytes = read(fd, morceau, BUFFER_SIZE);
        if (read_bytes == -1)
        {
            free(morceau);
            morceau = NULL;
            return (NULL);
        }
        morceau[read_bytes] = '\0';
        buffer = ft_strjoin(buffer, morceau);
    }
    free(morceau);
    morceau = NULL;
    return (buffer);
}

static char *create_line(char *buffer)
{
    int i;
    char *line;

    i = 0;
    if (!buffer[i])
        return (NULL);
    while (buffer[i] && buffer[i] != '\n')
        i++;
    i++;
    line = malloc(sizeof(char) * i + 1);
    line[i--] = 0;
    while (i >= 0)
        line[i--] = buffer[i];
    return (line);
}

static char *refactor_line(char *buffer)
{
    size_t i;
    size_t j;
    char *new_buffer;
    size_t len_buffer;

    i = 0;
    j = 0;
    while (buffer[i] && buffer[i] != '\n')
        i++;
    if (!buffer[i])
    {
        free(buffer);
        buffer = NULL;
        return (NULL);
    }
    len_buffer = ft_strlen(buffer);
    new_buffer = malloc(len_buffer - i + 1);
    i++;
    while (i <= len_buffer)
        new_buffer[j++] = buffer[i++];
    new_buffer[j] = 0;
    free(buffer);
    buffer = NULL;
    return (new_buffer);
}

char *get_next_line(int fd)
{
    char *line;
    static char *buffer;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buffer = read_line(fd, buffer);
    if (!buffer)
        return (NULL);
    line = create_line(buffer);
    buffer = refactor_line(buffer);
    return (line);
}
#include <stdio.h>
int main()
{
    int fd = open("test.txt", O_RDONLY);
    char *line;
    while (line = get_next_line(fd))
    {
        printf("%s", line);
        free(line);
    }
}
/*
int main()
{
    int     fd;
     char *line;
    fd =  open("/home/aybareic/Desktop/get_next_line/analyse.txt", O_RDONLY);
    //write(fd, "AAAA", 4);
   // printf("%d\n", fd);

     while((line = get_next_line(fd)))
     {
        printf("%s", line);
        free(line);
     }
     close(fd);
     printf("%s", line = get_next_line(fd));
     free(line);
     line = NULL;

    //printf("%s", line = get_next_line(fd));
    //free(line);
    //printf("%s", line = get_next_line(fd));
    //free(line);
//	printf("%s", get_next_line(fd));
    printf("%d\n", fd);
    line = get_next_line(fd);
    printf("%s", line);
    close(fd);
    fd =  open("/home/aybareic/Desktop/get_next_line/text1.txt", O_RDONLY);
    printf("%d\n", fd);
    line = get_next_line(fd);
    printf("%s", line);
    free(line);
        return (0);
    //printf("%s",	get_next_line(fd));
    //printf("%s",	get_next_line(fd));
}*/
