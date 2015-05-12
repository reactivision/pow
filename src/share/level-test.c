#undef NDEBUG
#include <assert.h>
#include "level.h"

static char *input =
	"1.000000 1.000000 -1.000000 "
	"1.000000 -1.000000 -1.000000 "
	"-1.000000 -1.000000 -1.000000 \n"

	"-1.000000 -1.000000 -1.000000 "
	"-1.000000 1.000000 -1.000000 "
	"1.000000 1.000000 -1.000000 \n"

	"1.000000 0.999999 1.000000 "
	"-1.000000 1.000000 1.000000 "
	"-1.000000 -1.000000 1.000000 \n"

	"-1.000000 -1.000000 1.000000 "
	"0.999999 -1.000001 1.000000 "
	"1.000000 0.999999 1.000000 \n";

static float expected_geometry[] = {
	1.0, 1.0, -1.0,
	1.0, -1.0, -1.0,
	-1.0, -1.0, -1.0,

	-1.0, -1.0, -1.0,
	-1.0, 1.0, -1.0,
	1.0, 1.0, -1.0,

	1.0, 0.999999, 1.0,
	-1.0, 1.0, 1.0,
	-1.0, -1.0, 1.0,

	-1.0, -1.0, 1.0,
	0.999999, -1.000001, 1.0,
	1.0, 0.999999, 1.0
};

int main(void)
{
	struct level expected, real;
	long i;

	expected.geom = expected_geometry;
	expected.ngeom = sizeof expected_geometry / sizeof expected_geometry[0];

	assert(level_parse(&real, input) == 0);
	assert(real.ngeom == expected.ngeom);
	for (i = 0; i < real.ngeom; i++)
		assert(real.geom[i] == expected.geom[i]);
	return 0;
}
