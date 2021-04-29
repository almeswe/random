# About
 Toy pseudorandom number generator, based on LFSR algorithm using rdtsc like source of entropy.
 The lower 32bits of rdtsc are used like pure random number, that will be processed by the LFSR, and then, if it needed, normalized for some range (see __randrange procedure)
 I haven't tested this generator too much, but it seems work correctly (use it only for educational purposes!).

# References
 - [LFSR](https://en.wikipedia.org/wiki/Linear-feedback_shift_register) 
 - [Rdtsc](https://docs.microsoft.com/en-us/cpp/intrinsics/rdtsc?view=msvc-160)
