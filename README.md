_This project has been created as part of the 42 curriculum by dshirais._

# Philosopers

## Description
This project is a practical exploration of concurrent programming and the "Dining Philosophers" problem. The goal is to create a simulation where multiple threads (philosophers) share limited resources (forks) without running into deadlocks or data races.

**Goal**: Implement a robust threading system where philosophers eat, sleep, and think. The simulation must end immediately if a philosopher dies of starvation.

**Overview**:

Each philosopher is represented by a thread.

Each fork is a Mutex, placed between two philosophers.

To eat, a philosopher must successfully lock the Mutex of the fork to their left and the fork to their right.

A dedicated monitoring system ensures that no philosopher exceeds the time_to_die threshold without eating.

## Instruction
**Compilatiom**: The project is compiled using a provided Makefile.
```
make
```

**Excusion**: Run the program with the following parameters (all times are in milliseconds):
```
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [optional: number_of_times_each_must_eat]
```

**Example**
```
./philo 5 800 200 200
```

## Resources

To understand how thread works, I accessed the following resources

Geeksforgeeks: https://www.geeksforgeeks.org/operating-systems/difference-between-process-and-thread/

**AI Usage**: I used Gemini as a personal tutor in the design phase and did not ask it to write codes. Accrodingly, all codes in this project were written by me.
