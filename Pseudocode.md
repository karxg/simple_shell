# Shell Pseudocode Draft
* * *
 initialize the shell structure to store arguments information
 populate structure to store environment related information
 execute the shell program with the provided command line arguments

 loop until the user exits or encounters an error:
     reset the internal state of the shell
     if the shell is operating in interactive mode:
         display the shell prompt ($)
     flush the output buffer

     read user input
     if the input is not empty:
         prepare the internal state for command execution
         check if the command/*Pesudo-code*/ is a built-in function
         if it's not a built-in function:
             execute the external command

         if the shell is not in interactive mode:
             print a newline to separate output

         free up memory

 		if the shell is not in interactive mode and there is an error:
    		exit the program with the error status

 		if the result of running the shell program is -2:
    		if the error code is -1:
        		exit the program with the current status
     	else:
         	exit the program with the error code
 exit the program with a success status

