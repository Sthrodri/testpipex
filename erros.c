# 08: The program exits with the last command's status code                 [OK]
Your pipex:
Your tty output:
# 09: The program handles infile's open error                               [OK]
Your tty output:
Error opening input file: No such file or directory
Your exit status:
Exit status: 1
Expected: <128
# 10: The output when infile's open error occur is correct                  [OK]
Bash:
0
Your tty output:
Error opening input file: No such file or directory
Your exit status:
Exit status: 1
Expected: <128
# 12: The program handles execve errors                                     [OK]
Your pipex:
Your tty output:
Command not found: No such file or directory
Your exit status:
Exit status: 0
Expected: <128
# 26: The program exits with the right status code                          [OK]
Your pipex:
Your tty output:
Command not found: No such file or directory
Your exit status:
Exit status: 0
Expected: <128
# 30: The output of the command is correct                                  [OK]
Your pipex:
Bash:
"Now?"
"Now," said Deep Thought.
"Doesn't matter!" said Phouchg. "We must know it! Now!"
"Now?" inquired Deep Thought.
"Yes! Now ..."
Your tty output:
Command not found: No such file or directory
Your exit status:
Exit status: 0
Expected: <128

The next test will use the following command:
../pipex "/dev/urandom" "cat" "head -1" "outs/test-xx.txt"

