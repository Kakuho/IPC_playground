The way I implemented this gives me a race condition.

Consider when a thread sets turn back to -1 (the sentinel value),
two simultaneous threads may read the turn variable as -1 and thus execute their critical region simultaneously.
