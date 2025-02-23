Philosophers

Introduction

The Philosophers project is part of the 42 curriculum and is designed to introduce students to concurrent programming, threads, and mutexes. The project is based on the classic Dining Philosophers Problem, where multiple philosophers sit around a table, alternating between eating, thinking, and sleeping while avoiding deadlocks and race conditions.

Objectives

Understand and implement multithreading.

Learn to use mutexes to prevent data races.

Manage synchronization to avoid deadlocks and starvation.

Work within strict time constraints to handle execution timing properly.

The Problem

There are N philosophers sitting around a table. Each philosopher follows this cycle:

Think

Take two forks (one at a time, shared with their neighbors)

Eat

Put down both forks

Sleep

Each philosopher needs two forks to eat, but each fork is shared between two neighboring philosophers, leading to potential deadlocks if not handled correctly.

Rules & Constraints

A philosopher can only take forks that are available (not being used by another philosopher).

A philosopher must eat within a specific time before they starve.

The program must be designed to avoid deadlocks and starvation.

Implementation Details

The program is written in C.

Uses threads to simulate philosophers.

Mutexes ensure safe access to shared resources (forks).

The program must handle timing constraints accurately.

Compilation & Execution

Compilation

make

This generates an executable called philo.

Usage

./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]

Arguments:

number_of_philosophers: Total number of philosophers.

time_to_die (ms): Time a philosopher can stay without eating before they die.

time_to_eat (ms): Time a philosopher takes to eat.

time_to_sleep (ms): Time a philosopher spends sleeping before thinking again.

[Optional] number_of_times_each_philosopher_must_eat: If provided, the program stops when all philosophers have eaten this many times.

Example

./philo 5 800 200 200

This runs the simulation with 5 philosophers where:

They die if they don’t eat within 800ms.

Eating takes 200ms.

Sleeping takes 200ms.

Key Features

Multithreading: Each philosopher is represented as a separate thread.

Mutex synchronization: Used to prevent race conditions when accessing forks.

Precise timing: Ensures accurate delays for eating, thinking, and sleeping.

Deadlock prevention: Implements strategies to prevent deadlocks, such as ordering fork pickup.

Possible Enhancements

Implement a version using semaphores.

Optimize for better performance with larger numbers of philosophers.

Improve timing accuracy with better thread scheduling.

Resources

Dining Philosophers Problem (Wikipedia)

POSIX Threads (pthread)

Author

This project was completed as part of the 42 School curriculum.
