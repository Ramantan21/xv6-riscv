#ifndef _PSTAT_H_
#define _PSTAT_H_
#define NPROC 64

/*
  a struct that our new syscall will simple fill with all the necessary
  info it needs

*/

struct pstat{
  int num_processes;
  int pid[NPROC]; // process id
  int ppid[NPROC];
  int priority[NPROC];
  int state[NPROC]; // state of the process
  char name[NPROC][16]; //process name
  int ticks[NPROC][4]; // number of ticks each process has accumulated at each of 4 priorities
  uint64 size[NPROC];
};

#endif 
