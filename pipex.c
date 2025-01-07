/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sthrodri <sthrodri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 14:11:52 by sthrodri          #+#    #+#             */
/*   Updated: 2025/01/07 14:11:53 by sthrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    error_exit(const char *msg)
{
    perror(msg);
    exit(EXIT_FAILURE);
}

void    execute_command(char *cmd, char **envp)
{
    char    **args;
    char    *path;

    args = ft_split(cmd, ' ');
    path = get_path(args[0], envp);
    if (!path)
        error_exit("Command not found");
    execve(path, args, envp);
    error_exit("Execution failed");
}

int main(int argc, char **argv, char **envp)
{
    if (argc != 5)
    {
        fprintf(stderr, "Usage: %s file1 cmd1 cmd2 file2\n", argv[0]);
        return (EXIT_FAILURE);
    }
    int fd1 = open(argv[1], O_RDONLY);
    if (fd1 < 0)
        error_exit("Error opening input file");

    int fd2 = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd2 < 0)
        error_exit("Error opening/creating output file");

    int pipe_fd[2];
    if (pipe(pipe_fd) == -1)
        error_exit("Pipe failed");

    pid_t   pid1 = fork();
    if (pid1 == -1)
        error_exit("Fork failed");
    if (pid1 == 0)
    {
        dup2(fd1, STDIN_FILENO);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        execute_command(argv[2], envp);
    }

    pid_t   pid2 = fork();
    if (pid2 == -1)
        error_exit("Fork failed");
    if (pid2 == 0)
    {
        dup2(pipe_fd[0], STDIN_FILENO);
        dup2(fd2, STDOUT_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        execute_command(argv[3], envp);
    }

    close(fd1);
    close(fd2);
    close(pipe_fd[0]);
    close(pipe_fd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return (EXIT_SUCCESS);
}
