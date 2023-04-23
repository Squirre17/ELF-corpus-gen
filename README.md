# ELF-corpus-gen

generate crafted elf corpus for fuzz.
not coverage-directed now, simply heuristic.


# problem now

my mutation is write back directly... so it influence following mutate which depend on this data field...