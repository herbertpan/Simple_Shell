# Simple_Shell
Simple_Shell
Mini-Project Option: Command Shell
==================================

For this mini-project you will write a "baby" command shell.

Step 1: Read a command name, run it
  You should write a program called "myShell".
  Whenever your command shell expects input, it should print a prompt ("myShell $")
  It should read one line of input (from stdin) which is the name of a command
  For this step, you may assume that the user will type the full path to the command
  they want to run.

  Your shell should then run the specified command---see fork, execve, and waitpid.
  Note that there is a library function "system" which combines all three of these,
  which may be easier for now, but will not work for later steps.

  After the specified program exits, your shell should print

  Program exited with status 0
  [replace 0 with the actual exit status]
  OR
  Program was killed by signal 11
  [replace 11 with the actual signal]

  See man waitpid, and the WIFSIGNALED(status) macro.

  Then your shell should print the "myShell$" prompt again, and repeat the process.

  If the user types the command "exit", or EOF is encountered reading from stdin, then
  the shell should exit.

Step 2: Improving commands
  For this steps, you will improve your handling of commands in two ways:
  - Search the PATH environment variable for commands

  You will want to use the PATH environment variable that exists when
  your shell starts (see man getenv), which will be a colon delimited
  list of paths.  When the user types a command name which does not
  have a / in it, you should search each directory specified in the PATH
  (in order) for the specified program.  If the program is found, your shell
  should execute it.  If not, your shell should print

  Command commandName not found
  [replace commandName with the actual command name]

  If the path name does contain a / in it, you should only look in the specified
  directory (which may not be on the PATH at all).  Note that a path with
  a / in it could be relative (.e.g, ./myProgram) or absolute (e.g. /bin/ls).

  - Commands can take arguments (separated by white spaces)
   You should also make commands such that they can take arguments separated
   by white space.  For example
     ./myProgram a b 23
   runs myProgram with arguments "a"  "b" and "23".  There may be an arbitrary
   amount of whitespace in between arguments, so
     ./myProgram         a               b     23
   has the same behavior as the previous example.  However, any white space
   which is escaped with a \ should be literally included in the argument, and
   not used as a separator:

    ./myProgram  a\ b c\ \ d

    Should run myProgram with two arguments "a b" and "c  d"  Note that

     ./myProgram a\  b c \ d

     whould have arguments "a " "b" "c" and " d", as the non-escaped spaces
     separate arguments.


Step 3: Directories
  - Add the "cd" command to change the current directory
    See the chdir function.
  - The prompt should show the current directory before the $
    That is, if your current directory is /home/drew, the prompt should be
    myShell:/home/drew $
  - Add the "pushd", "popd", and "dirstack" commands.  The pushd command takes
    one argument (which names a directory) and "cd"s to that directory,
    but pushes the old directory onto a stack.
    The "popd" command pops the top of the directory stack, and "cd"s
    to that directory.  If the directory stack is empty, the popd command
    prints an error message.  The "dirstack" command lists the directory
    stack, with the top of the stack last, and the bottom first.
    For example:
    myShell:/home/drew $ pushd /home/ece551/grader
    myShell:/home/ece551/grader $ cd ../
    myShell:/home/ece551 $ pushd /var
    myShell:/var $ dirstack
    /home/drew
    /home/ece551
    myShell:/var $ popd
    myShell:/home/ece551 $

Step 4: Pipes and redirection
  - Implement input redirection (<) and output redirection (>)
     < filename   redirects standard input for the command
     > filename   redirects standard ouput
     2> filename  redirects standard error
   Note that you will need to implement these between the fork()
   and execve() calls.  You will need to make use of close()
   on the relevant file descriptors (0 = stdin, 1 = stdout, 2 = stderr)
   use open() to open the appropriate file.  You may also need to make
   use of dup2().

  - Implement pipes (|)
   You should be able to run one command and pipe its output to another's input:

   ./myProgram | ./anotherProgram

   See the pipe() system call.

Note that you need to be able to mix and match these in ways that make sense,
along with having command line arguments:

   ./myProgram a b c < anInputFile | ./anotherProgram 23 45 > someOutputFile
