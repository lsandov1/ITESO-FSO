#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
  pid_t p = fork();

  if(p == 0) {
    printf("child started: %d %d\n", getpid(), getppid());
    sleep(20);
    printf("child completed: %d %d\n", getpid(), getppid());
  }
  else {
    printf("\nparent started: %d\n", getpid());
    sleep(1);
    printf("parent completed: %d\n", getpid());
  }

  return 0;
}
