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
    char *temp_buffer;
    int bytes_read;

    temp_buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
    if (!temp_buffer)
        return (NULL);
    bytes_read = 1;
    while (!has_newline(buffer) && bytes_read != 0)
    {
        bytes_read = read(fd, temp_buffer, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            free(temp_buffer);
            temp_buffer = NULL;
            return (NULL);
        }
        temp_buffer[bytes_read] = '\0';
        buffer = ft_strjoin(buffer, temp_buffer);
    }
    free(temp_buffer);
    temp_buffer = NULL;
    return (buffer);
}

static char *extract_line_from_buffer(char *buffer)
{
    int line_length;
    char *extracted_line;

    line_length = 0;
    if (!buffer[line_length])
        return (NULL);
    
    // Find length up to newline or end
    while (buffer[line_length] && buffer[line_length] != '\n')
        line_length++;
    line_length++; // Include newline if present
    
    // Allocate space for line plus null terminator
    extracted_line = malloc(sizeof(char) * (line_length + 1));
    if (!extracted_line)
        return (NULL);
        
    // Copy characters in reverse to preserve original buffer
    extracted_line[line_length] = '\0';
    while (--line_length >= 0)
        extracted_line[line_length] = buffer[line_length];
        
    return (extracted_line);
}

static char *update_buffer_after_line(char *buffer)
{
    size_t newline_pos;
    size_t buffer_len;
    char *remaining_text;

    // Find position of newline character
    newline_pos = 0;
    while (buffer[newline_pos] && buffer[newline_pos] != '\n')
        newline_pos++;

    // If no newline found, free buffer and return NULL
    if (!buffer[newline_pos])
        return (free(buffer), NULL);

    buffer_len = ft_strlen(buffer);
    
    // Allocate space for remaining text after newline
    remaining_text = malloc(buffer_len - newline_pos + 1);
    if (!remaining_text)
        return (free(buffer), NULL);

    // Copy remaining text after newline
    newline_pos++;
    buffer_len = 0;
    while (buffer[newline_pos])
        remaining_text[buffer_len++] = buffer[newline_pos++];
    remaining_text[buffer_len] = '\0';

    free(buffer);
    buffer = NULL;
    return (remaining_text);
}

char *get_next_line(int fd)
{
    char *current_line;
    static char *storage_buffer;

    // Validate input parameters
    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);

    // Read content from file into buffer
    storage_buffer = read_line(fd, storage_buffer);
    if (!storage_buffer)
        return (NULL);

    // Extract the next line from buffer
    current_line = extract_line_from_buffer(storage_buffer);

    // Update buffer to contain remaining content
    storage_buffer = update_buffer_after_line(storage_buffer);

    return (current_line);
}
#include <stdio.h>
int main()
{
    int fd;
    char *line;
    
    // Test 1: Normal file reading
    fd = open("test.txt", O_RDONLY);
    while ((line = get_next_line(fd)))
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    
    // Test 2: Invalid file descriptor
    printf("\nTesting invalid fd:\n");
    line = get_next_line(-1);
    printf("Result with fd=-1: %s\n", line);
    free(line);
    
    // Test 3: Reading from closed file
    printf("\nTesting closed file:\n");
    fd = open("test.txt", O_RDONLY);
    close(fd);
    line = get_next_line(fd);
    printf("Result from closed file: %s\n", line);
    free(line);
    
    // Test 4: Reading empty file
    printf("\nTesting empty file:\n");
    fd = open("empty.txt", O_RDONLY);
    line = get_next_line(fd);
    printf("Result from empty file: %s\n", line);
    free(line);
    close(fd);

    // Test 5: Multiple reads from same file
    printf("\nTesting multiple reads:\n");
    fd = open("test.txt", O_RDONLY);
    for (int i = 0; i < 3; i++)
    {
        line = get_next_line(fd);
        printf("Read %d: %s", i + 1, line);
        free(line);
    }
    close(fd);
    

    return (0);
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
