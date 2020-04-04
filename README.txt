C programming project to mimic unix/linux operating system terminal. My shell is capable of running builtin functions and system executable function with multiple process forking. The code is depending on the essential understanding of how OS threading with high text formatting skills.

Description:
Processing the user command:
Step 1: The shell should take the user command and its parameter(s), i.e.,
        “ls” and “–l” in this example, and convert them into C strings. (Recall that a C string
        terminates with a null string, i.e., \0.)
Step 2: The command shell creates a child process via fork ().
Step 3: The child process passes the C strings—the command and parameter(s)—to
        execvp ().
Step 4: The parent process, i.e., the command shell, should wait, via wait (), for the
        child process to finish.
Step 5: The command shell gets the next command and repeats the above steps. The
        command shell terminates itself when the user types exit.
        
In case a user wants to execute the command in background (i.e. as a background process),
he/she writes & at the end of the command. For example, a user command can be:
Shell > firefox &
In this case, your command shell should not wait for the child by skipping the Step 4.

The shell keeps a log file for all the shell history plus whenever a child process
terminates, the shell program appends the line “Child process was terminated” to the log file using signal handler.
