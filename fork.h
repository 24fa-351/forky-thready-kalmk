#ifndef FORK_H
#define FORK_H

unsigned int sleep_time();

void run(int num_of_processes, int pattern);

void pattern_1(int num_of_processes);

void pattern_2_child_process(int process_num, int num_of_processes);

void pattern_2(int num_of_processes);


#endif