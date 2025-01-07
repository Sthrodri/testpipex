/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthrodri <sthrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:12:07 by sthrodri          #+#    #+#             */
/*   Updated: 2025/01/07 14:31:17 by sthrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Função auxiliar para juntar o caminho e o comando
char    *join_path(char *path, char *cmd)
{
    char    *full_path;
    size_t  len;

    len = ft_strlen(path) + ft_strlen(cmd) + 2; // +2 para '/' e terminador nulo
    full_path = (char *)malloc(len);
    if (!full_path)
        return (NULL);
    snprintf(full_path, len, "%s/%s", path, cmd);
    return (full_path);
}

// Função para obter o caminho completo de um comando
char    *get_path(char *cmd, char **envp)
{
    char    *path_env;
    char    **paths;
    char    *full_path;
    int     i;

    while (*envp && strncmp(*envp, "PATH=", 5) != 0)
        envp++;
    if (!*envp)
        return (NULL);
    path_env = *envp + 5;
    paths = ft_split(path_env, ':');
    if (!paths)
        return (NULL);
    i = 0;
    while (paths[i])
    {
        full_path = join_path(paths[i], cmd);
        if (access(full_path, X_OK) == 0)
        {
            int j = 0;
            while (paths[j])
                free(paths[j++]);
            free(paths);
            return (full_path);
        }
        free(full_path);
        i++;
    }
    i = 0;
    while (paths[i])
        free(paths[i++]);
    free(paths);
    return (NULL);
}

// Função auxiliar para contar as palavras em uma string
static int  count_words(const char *str, char c)
{
    int count;
    int in_word;

    count = 0;
    in_word = 0;
    while (*str)
    {
        if (*str != c && !in_word)
        {
            in_word = 1;
            count++;
        }
        else if (*str == c)
            in_word = 0;
        str++;
    }
    return (count);
}

// Função auxiliar para duplicar uma palavra
static char *word_dup(const char *start, const char *end)
{
    char    *word;
    size_t  len;

    len = end - start;
    word = (char *)malloc(len + 1);
    if (!word)
        return (NULL);
    strncpy(word, start, len);
    word[len] = '\0';
    return (word);
}

// Função para dividir uma string em substrings com base em um delimitador
char    **ft_split(char const *s, char c)
{
    char    **array;
    char    *start;
    int     i;

    if (!s)
        return (NULL);
    array = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
    if (!array)
        return (NULL);
    i = 0;
    start = NULL;
    while (*s)
    {
        if (*s != c && !start)
            start = (char *)s;
        else if ((*s == c || *(s + 1) == '\0') && start)
        {
            array[i++] = word_dup(start, s + (*s == c ? 0 : 1));
            start = NULL;
        }
        s++;
    }
    array[i] = NULL;
    return (array);
}
