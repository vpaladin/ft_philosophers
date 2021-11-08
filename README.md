# ft_philosophers

"I’ve never thought philosophy would be so deadly"

![Alt text](https://github.com/lucaslefrancq/42_philosophers/blob/main/philo_example.png)

## About

Philosophers is a project of the mandatory part of the cursus.
It's only made in C and the main goal was to understand how threads works in language C and use them to solve a logical problem.
The simulation will stop if all philosophers have eaten enough or if one philosopher die.

- There are three different version of the algorithm :
    - philo is about using threads and mutexs
    - philo_bonus is about using processes and semaphores

- Here is the [subject][1]

`This project was code for MACOS`

### Building and running the project

1. Download/Clone this repo

        git clone https://github.com/vpaladin/ft_philosophers.git
2. `cd` into the root directory, then `cd` into philo (bonus) and run `make`

        cd philo
        make

3.  run `./philo_x arg1 arg2 arg3 arg4 (arg5)` from the directory philo_x.
    - arg1 is the number of philosopher
    - arg2 is the time to die in ms
    - arg3 is the time to eat in ms
    - arg4 is the time to sleep in ms
    - arg5 (optional) is the number of time each philosopher needs to eat to end the simulation

[1]: https://github.com/vpaladin/ft_philosophers/blob/main/philosophers.pdf
