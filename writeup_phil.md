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
This is pretty proportionate as the philosophers are eating and sleeping for the same amount of times.
- Run it longer by changing sleep(60)
- Make 1 philosophers time different than others/