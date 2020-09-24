#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

#include <pthread.h>
#include <cycles.h>

const int iter = 1000;
const int N    = 10;

typedef int (*computation_fn_t)(int);

/**
 * The prototypes for `pthread_create` to create a thread that
 * executes a function (`start_routine`), in that new thread;
 * `pthread_exit` that exits the current thread (must be executing in
 * a thread created with `pthread_create`), passing in a return value
 * (`retval`), and `pthread_join` (like `wait`) that waits for another
 * thread to terminate, and returns its `retval`.
 *
 * int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
 *		   void *(*start_routine) (void *), void *arg);
 *
 * IMPORTANT: `attr` can be `NULL`. `arg` is the value passed as the
 * argument to your `start_routine`. I've provided a sample
 * `start_routine` below.
 *
 * void pthread_exit(void *retval);
 *
 * int pthread_join(pthread_t thread, void **retval);
 */

int thread_onacci(int n);

/* The logic for the recursive call, in a new thread */
void *
start_routine(void *arg)
{
	int n = (int)(long)arg;

	n = thread_onacci(n);

	/* TODO: How should we return n to the parent thread? */
	return NULL;
}

int
thread_onacci(int n)
{
	if (n == 0 || n == 1) return n;

	/* TODO: Create a new thread for each recursive call here! */

	/* TODO: Wait for the child threads to exit, and get their results */
	return 0;
}

int
fib(int n)
{
	if (n == 0 || n == 1) return n;

	return fib(n - 1) + fib(n - 2);
}

int
fibork(int n)
{
	pid_t pid;
	int n1, n2;

	if (n == 0 || n == 1) return n;

	pid = fork();
	if (pid < 0) {
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	if (pid == 0) {
		/* child 1, first recursive call! */
		exit(fibork(n - 1));
	}
	pid = fork();
	if (pid < 0) {
		perror("fork error");
		exit(EXIT_FAILURE);
	}
	if (pid == 0) {
		/* child 2, second recursive call! */
		exit(fibork(n - 2));
	}
	wait(&n1);
	wait(&n2);

	return n1 + n2;
}

ps_tsc_t
benchmark(computation_fn_t fn, int arg, int *retval)
{
	ps_tsc_t start;
	int i;

	start = ps_tsc();
	for (i = 0; i < iter; i++) {
		 *retval = fn(arg);
	}

	return (ps_tsc() - start) / iter;
}

int
main(int argc, char *argv[])
{
	ps_tsc_t cycles;
	int ret;

	(void)argc;
	(void)argv;

	cycles = benchmark(fib, N, &ret);
	printf("fib(%d) = %d takes %lld cycles\n", N, ret, cycles);
	cycles = benchmark(fibork, N, &ret);
	printf("fibork(%d) = %d takes %lld cycles\n", N, ret, cycles);
	cycles = benchmark(thread_onacci, N, &ret);
	printf("thread_onacci(%d) = %d takes %lld cycles\n", N, ret, cycles);

	return 0;
}
