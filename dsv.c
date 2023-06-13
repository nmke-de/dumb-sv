#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/prctl.h>
#include <string.h>
#include <signal.h>
#include "print/print.h"

extern char **environ;
#define sys(args) execve(*(args), (args), environ)

// Kill child process and stop supervising.
pid_t child;
char *childname;
int running = 1;
void fine(int signum) {
	logln("Killing ", childname);
	kill(child, SIGTERM);
	running = 0;
}

// Supervise a single service without arguments
int main(int argc, char **argv) {
	// Can't supervise null process, right?
	if (argc < 2) {
		print("dsv - The Dumb Process Supervisor. By nmke-de (c) 2023 - ???
Version: 0.1
Syntax: dsv [absolute-path] [arguments...]

dsv will start a child process at [absolute-path] and
restart it once the child process finishes. Killing
dsv will also send SIGTERM to the child process.\n");
		return 1;
	}
	// Idk if this is necessary.
	chdir("/");
	// Check whether specified executable even exists (and whether it is a regular executable file)
	struct stat sb;
	if (stat(argv[1], &sb) < 0) {
		log("File not Found.\n");
		return 2;
	}
	if (!S_ISREG(sb.st_mode)) {
		log("File is not a regular file.\n");
		return 3;
	}
	if (access(argv[1], X_OK) != 0) {
		log("File is not executable.\n");
		return 4;
	}
	// Prepare command
	for (int i = 0; i < argc - 1;)
		argv[i] = argv[++i];
	argv[argc - 1] = NULL;
	// Prepare signal handler
	prctl(PR_SET_PDEATHSIG, SIGTERM);
	childname = *argv;
	signal(SIGINT, fine);
	signal(SIGTERM, fine);
	// Main loop. Wait until child quits before restarting.
	for (;;) {
		child = fork();
		if (child == 0)
			sys(argv);
		wait(&child);
		if (!running)
			return 0;
		println("Restarting ", argv[0], "...");
	}
}
