#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/wait.h>
#include <stdlib.h>

void closefd(int fd) {
	int res = close(fd);
	if (res == -1) {
		exit(errno);
	}
	return;
}

void dupfd(int fd1, int fd2) {
	int res = dup2(fd1, fd2);
	if (res == -1) {
		exit(errno);
	}
	return;
}

int main(int argc, char *argv[])
{
	int n = argc - 1;
	if (n == 0) {
		exit(EINVAL);
	}
	if (n == 1) {
		pid_t pid = fork();
		if (pid < 0) {
			exit(errno);
		} else if (pid == 0) {
			int res = execlp(argv[1], argv[1], NULL);
			if (res < 0) {
				exit(errno);
			}
		} else {
			int res = waitpid(pid, NULL, 0);
			if (res == -1) {
				exit(errno);
			}
		}
		return 0;
	}
	int pids[n];
	int fds[n - 1][2];
	int res;

	for (int i = 0; i < n - 1; i++) {
		res = pipe(fds[i]);
		if (res == -1) {
			exit(errno);
		}
	}

	int fid = 0;
	for (; fid < n; fid++) {
		pid_t pid;
		pid = fork();
		if (pid < 0) {
			exit(errno);
		} else if (pid == 0) {
			break;
		} else {
			pids[fid] = pid;
		}
	}
	if (fid < n) {
		if (fid == 0) {
			for (int i = 1; i < n - 1; i++) {
				closefd(fds[i][0]);
				closefd(fds[i][1]);
			}
			closefd(fds[0][0]);
			dupfd(fds[0][1], 1);
		} else if(fid == n - 1) {
			for (int i = 0; i < n - 2; i++) {
				closefd(fds[i][0]);
				closefd(fds[i][1]);
			}
			closefd(fds[n - 2][1]);
			dupfd(fds[n - 2][0], 0);
		} else {
			for (int i = 0; i < fid - 1; i++) {
				closefd(fds[i][0]);
				closefd(fds[i][1]);
			}
			for (int i = fid + 1; i < n - 1; i++) {
				closefd(fds[i][0]);
				closefd(fds[i][1]);
			}
			closefd(fds[fid - 1][1]);
			closefd(fds[fid][0]);
			dupfd(fds[fid - 1][0], 0);
			dupfd(fds[fid][1], 1);
		}
		int res = execlp(argv[fid + 1], argv[fid + 1], NULL);
		if (res == -1) {
			exit(errno);
		}
	} else {
		for (int i = 0; i < n - 1; i++) {
			closefd(fds[i][0]);
			closefd(fds[i][1]);
		}
		int res;
		for (int i = 0; i < n; i++) {
			res = waitpid(pids[i], NULL, 0);
			if (res == -1){
				exit(errno);
			}
		}
	}
	return 0;

}

