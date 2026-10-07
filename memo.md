# Sean Carroll
# Benton Hershberger
# Oct 6, 2026
# Embedded Systems Lab 6


1) What priority did you assign to each thread?
We assigned the prime generation task osPrioritylow7 because all the other tasks rely on it to complete and will hand over execution whenever they need data.
We assigned the formatter task osPriorityAboveNormal14 so that the SPI task is forced to hand over execution only when it needs a number, then if the formatter doesn't have a number execution will go to the primes task.
We assigned the SPI task osPriorityHigh5 so that SPI is prioritized over the formatter so as to avoid interrupting an active spi transmission. 

2) What technique did you use to suppress readiness in each thread, if any?
In the SPI and formatter tasks we used a combination of mutex's and queues whenever data needed to be accessed. The rtos knows to switch execution if the data isn't readily available.
Then in the primes task, we used osDelay to sleep until the next 2 ms cycle which hands off execution as well.
