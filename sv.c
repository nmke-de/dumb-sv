#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

extern char **environ;
#define sys(args) execve(*(args), (args), environ)

#define print(str) write(1, (str), strlen((str)))

// Supervise a single service without arguments
int main(int argc, char **argv) {
	// Can't supervise empty process, right?
	if (argc < 2)
		return 1;
	// Idk if this is necessary.
	chdir("/");
	// Prepare command
	for (int i = 0; i < argc - 1;)
		argv[i] = argv[++i];
	argv[argc - 1] = NULL;
	// Main loop. Wait until child quits before restarting.
	for (;;) {
		pid_t child = fork();
		if (child == 0)
			sys(argv);
		wait(&child);
		print("Restarting ");
		print(argv[0]);
		print("...\n");
	}
}
