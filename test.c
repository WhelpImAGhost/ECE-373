
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
int main(int argc, char* argv[]){


	// Exit the program if the program was not run with a command argument
	if (argc < 2){

		printf("Too few arguments. Please format as %s <command to time>\n", argv[0]);
		exit(-1);
	}

	// Create structs with type "timespec" from the time.h library to contaion the start and end program times
	struct timespec start_time, end_time;

	// Create a variable for the PIDs
	pid_t pid;

	// Get the program start time and store it
	clock_gettime(CLOCK_MONOTONIC, &start_time);

	// Fork the program
	pid = fork();

	if (pid < 0){			// Exit if fork fails
		perror("fork");
		exit(-2);
	}
	else if (pid == 0){		// Child process runs passed command

		execvp(argv[1], &argv[1]);
		perror("execvp");
		exit(-3);
	}
	else{				// Parent process waits for child, then calculates elapsed time
		int status;
		if ((pid = waitpid(pid, &status, 0)) == -1) {
       			perror("aitpid");
        		exit(EXIT_FAILURE);
    		}

		clock_gettime(CLOCK_MONOTONIC, &end_time);

		double time_elapsed = (end_time.tv_sec - start_time.tv_sec);
		double elapsed_ns = (end_time.tv_nsec - start_time.tv_nsec); 

		printf("Total time elapsed to run '%s' is %f seconds.\n", argv[1], time_elapsed + elapsed_ns / 1000000000);
	}



	exit(0);
}

