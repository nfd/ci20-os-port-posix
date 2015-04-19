// *Really* minimal PCG32 code / (c) 2014 M.E. O'Neill / pcg-random.org
// Licensed under Apache License 2.0 (NO WARRANTY, etc. see website)

#include <inttypes.h>

typedef struct { uint64_t state;  uint64_t inc; } pcg32_random_t;

static pcg32_random_t _pcgrandom = { 0x853c49e6748fea9bULL, 0xda3e39cb94b95bdbULL };

unsigned int rand(void)
{
	uint64_t oldstate = _pcgrandom.state;
	// Advance internal state
	_pcgrandom.state = oldstate * 6364136223846793005ULL + (_pcgrandom.inc|1);
	// Calculate output function (XSH RR), uses old state for max ILP
	uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
	uint32_t rot = oldstate >> 59u;
	return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
}

