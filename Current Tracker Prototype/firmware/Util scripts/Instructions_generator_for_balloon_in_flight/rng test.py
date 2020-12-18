# from https://stackoverflow.com/a/53551417
# Return a randomized "range" using a Linear Congruential Generator
# to produce the number sequence. Parameters are the same as for
# python builtin "range".
#   Memory  -- storage for 8 integers, regardless of parameters.
#   Compute -- at most 2*"maximum" steps required to generate sequence.
#

import math
import random


def random_range(start, stop=None, step=None):
    # Set a default values the same way "range" does.
    if stop == None:
        start, stop = 0, start
    if step == None:
        step = 1
    # Use a mapping to convert a standard range into the desired range.
    mapping = lambda i: (i * step) + start
    # Compute the number of numbers in this range.
    maximum = (stop - start) // step

    # Seed range with a random integer.
    value = random.randint(0, maximum)
    #
    # Construct an offset, multiplier, and modulus for a linear
    # congruential generator. These generators are cyclic and
    # non-repeating when they maintain the properties:
    #
    #   1) "modulus" and "offset" are relatively prime.
    #   2) ["multiplier" - 1] is divisible by all prime factors of "modulus".
    #   3) ["multiplier" - 1] is divisible by 4 if "modulus" is divisible by 4.
    #
    offset = random.randint(0, maximum) * 2 + 1  # Pick a random odd-valued offset.
    multiplier = 4 * (maximum // 4) + 1  # Pick a multiplier 1 greater than a multiple of 4.
    modulus = int(
        2 ** math.ceil(math.log2(maximum)))  # Pick a modulus just big enough to generate all numbers (power of 2).
    # Track how many random numbers have been returned.
    found = 0
    while found < maximum:
        # If this is a valid value, yield it in generator fashion.
        if value < maximum:
            found += 1
            yield mapping(value)
        # Calculate the next value in the sequence.
        value = (value * multiplier + offset) % modulus


if __name__ == "__main__":
    # Show off random range.
    print()
    for v in range(3, 4):
        l = list(random_range(v))


        print("Need", v, "found", len(l), "(min,max)", (min(l), max(l)))
        print("", l)
        print()
