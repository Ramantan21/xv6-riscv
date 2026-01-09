#include "kernel/types.h"
#include "kernel/pstat.h"
#include "user/user.h"

int main(void) {
  int pid1, pid2;
  
  pid1 = fork();
  if(pid1 == 0){
    // Child 1: CPU intensive (should get demoted)
    for(int i = 0; i < 100000000; i++);
    exit(0);
  }
  
  pid2 = fork();
  if(pid2 == 0){
    // Child 2: CPU intensive
    for(int i = 0; i < 100000000; i++);
    exit(0);
  }
  
  // Parent: wait a bit then check priorities
  pause(10);
  
  struct pstat ps;
  getpinfo(&ps);
  
  printf("PID\tPRIO\tQ0\tQ1\tQ2\tQ3\tNAME\n");
  for(int i = 0; i < ps.num_processes; i++){
    printf("%d\t%d\t%d\t%d\t%d\t%d\t%s\n",
           ps.pid[i], ps.priority[i],
           ps.ticks[i][0], ps.ticks[i][1],
           ps.ticks[i][2], ps.ticks[i][3],
           ps.name[i]);
  }
  
  wait(0);
  wait(0);
  exit(0);
}