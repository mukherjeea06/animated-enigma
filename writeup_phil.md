Writeup for Dining Philosophers

1. Running alg1 with an argument results in:
./alg1 5
philosopher 0 is holding left fork 0
philosopher 3 is holding left fork 3
philosopher 1 is holding left fork 1
philosopher 2 is holding left fork 2
philosopher 4 is holding left fork 4
philsopher alg1 end
This shows that all philosophers are left to hold the left fork, while they wait for a right fork to be available. This leads to deadlock and it is difficult for a philosopher to finish properly eating.
-The DELAY sleep between the two forks and the shared think time makes everyone hungry together.
- This is the same issue we talked about in class, where there is circular wait.

2. Running alg2
 ./alg2 5
philosopher 0 is eating...yay!
philosopher 2 is eating...yay!
philosopher 4 is eating...yay!
philosopher 1 is eating...yay!
philosopher 3 is eating...yay!
philosopher 0 is eating...yay!
philosopher 2 is eating...yay!
philosopher 4 is eating...yay!
philosopher 1 is eating...yay!
philosopher 3 is eating...yay!
philosopher 0 is eating...yay!
philosopher 2 is eating...yay!
philosopher 4 is eating...yay!
philosopher 1 is eating...yay!
philosopher 3 is eating...yay!
philosopher 2 is eating...yay!
philosopher 0 is eating...yay!
philosopher 4 is eating...yay!
philosopher 1 is eating...yay!
philosopher 3 is eating...yay!
philosopher 0 is eating...yay!
philosopher 2 is eating...yay!
meals per philosopher: 
philosopher 0 ate 5 times
philosopher 1 ate 4 times
philosopher 2 ate 5 times
philosopher 3 ate 4 times
philosopher 4 ate 4 times

philsopher alg2 end
- This is pretty proportionate as the philosophers are eating and sleeping for the same amount of times.
- I changed the sleep amount in the main function to sleep(60). This keeps the philosopher count proportional. It does not starve any particular philosopher.
- Make 1 philosophers time different than others/
- This does not cause deadlock as nobody holds one fork while waiting for another.

3. Created a new semaphore for the table to allow for N-1 to sit at once. This solves the deadlock that I created in algorithm 1.
- The meals were roughly equal across all philosophers.
- Since there are N-1 seated philosophers and N forks, there will always be 1 fork left free and therefore there will never be deadlock.
- I removed sleep time for the philosophers and that made everyone hungry at the same time, which seems like it could be a setup for deadlock.
- I changed the number of philosophers in the command line with 3, 4 and 5 and it seems like each time the number of meals per philosopher is either 3 or 4.

4. Rogue Philosopher: Tried to grab whatever fork is available. Although this implementation ended up in the same deadlock as before where all philosophers grab the left fork and nobody gets to eat.
- With everyone hungry at the same time, the rogue does not prevent deadlock. It only changes behavior if it sees a taken fork.
- If I increase the rogue time, it leads to the rogue philosopher (phil 0) grabbing the left fork last and still leads to deadlock.
philosopher 1 is holding left fork 1
philosopher 4 is holding left fork 4
philosopher 3 is holding left fork 3
philosopher 2 is holding left fork 2
philosopher 0 is holding left fork 0

meals per philosopher: 
philosopher 0 ate 0 times
philosopher 1 ate 0 times
philosopher 2 ate 0 times
philosopher 3 ate 0 times
philosopher 4 ate 0 times
philsopher alg4 end
- Due to all threads waking up from sleep(THINK_TIME) at the same moment, everyone is waiting for forks to be available to grab and this leads to deadlock.