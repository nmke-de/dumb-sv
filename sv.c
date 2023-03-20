#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <signal.h>

extern char **environ;
#define sys(args) execve(*(args), (args), environ)

#define print(str) write(1, (str), strlen((str)))

// Kill child process and stop supervising.
pid_t child;
char *childname;
int running = 1;
void fine(int signum) {
	print("Killing ");
	print(childname);
	print("\n");
	kill(child, SIGINT);
	running = 0;
}

// Supervise a single service without arguments
int main(int argc, char **argv) {
	// Can't supervise null process, right?
	if (argc < 2)
		return 1;
	// Check whether specified executable even exists
	if (access(argv[1], F_OK) != 0)
		return 2;
	// Idk if this is necessary.
	chdir("/");
	// Prepare command
	for (int i = 0; i < argc - 1;)
		argv[i] = argv[++i];
	argv[argc - 1] = NULL;
	// Prepare signal handler
	childname = *argv;
	signal(SIGINT, fine);
	// Main loop. Wait until child quits before restarting.
	for (;;) {
		child = fork();
		if (child == 0)
			sys(argv);
		wait(&child);
		if (!running)
			return 0;
		print("Restarting ");
		print(argv[0]);
		print("...\n");
	}
}
