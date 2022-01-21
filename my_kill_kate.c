#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <errno.h>

#define FN_LEN 256

struct Options {
	bool using_h;
	bool using_f;
	char filename[FN_LEN];
};

static void init_opts(struct Options* opts) {
	opts->using_f = false;
	opts->using_h = false;
	for (int i = 0; i < FN_LEN; i++)
	{
		opts->filename[i] = 0;
	}
}

struct Options get_opts(int count, char* args[]) {
	struct Options opts;
	init_opts(&opts);
	int opt;

	while ((opt = getopt(count, args, ":f:had")) != -1)
	{
		switch(opt) {
			case 'h':
				opts.using_h = true;
				printf("Hello World\n");
				break;
			case 'f':
				opts.using_f = true;
				strcpy(opts.filename, optarg);
				FILE *fptr = fopen(opts.filename, "r");
				if (fptr==NULL)
				{
					printf("Can't open file\n");
					exit(-1);
				}
				else
				{
					char c = fgetc(fptr);
					while(c!=EOF)
					{
						printf("%c", c);
						c = fgetc(fptr);
					}
				}
				break;
		}
	}
}

int main(int argc, char *argv[]) {
	struct Options o = get_opts(argc, argv);
	if (argc - optind != 1) {
		printf("Error - command format is $ my_kill -options pid\n");
		exit(-1);
        }
	printf("my_kill pid: %d\n", getpid());
	int pid_to_kill = atoi(argv[optind]);
	int status = kill(pid_to_kill, SIGINT);
	int errnum = errno;
	if(status == -1)
	{
		fprintf(stderr, "Value of errno: %d\n", errno);
		perror("Error printed by perror");
		fprintf(stderr, "Error killing process: %s\n", strerror( errnum));
		exit(-1);
	}
	return 0;
}
