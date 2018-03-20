#include <stdio.h>
#include <stdlib.h>

// http://stackoverflow.com/questions/563198/how-do-you-detect-where-two-line-segments-intersect
// Returns 1 if the lines intersect, otherwise 0. In addition, if the lines 
// intersect the intersection point may be stored in the floats i_x and i_y.
int get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y, float p2_x, float p2_y, float p3_x, float p3_y, float *i_x, float *i_y)
{
    float s1_x, s1_y, s2_x, s2_y;
    s1_x = p1_x - p0_x;     s1_y = p1_y - p0_y;
    s2_x = p3_x - p2_x;     s2_y = p3_y - p2_y;

    float s, t;
    s = (-s1_y * (p0_x - p2_x) + s1_x * (p0_y - p2_y)) / (-s2_x * s1_y + s1_x * s2_y);
    t = ( s2_x * (p0_y - p2_y) - s2_y * (p0_x - p2_x)) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        // Collision detected
        if (i_x != NULL)
            *i_x = p0_x + (t * s1_x);
        if (i_y != NULL)
            *i_y = p0_y + (t * s1_y);
        return 1;
    }

    return 0; // No collision
}


unsigned int rand32() {
	unsigned int x = rand() & 0xff;
	x |= (rand() & 0xff) << 8;
	x |= (rand() & 0xff) << 16;
	x |= (rand() & 0xff) << 24;
	return x;
}


int between(int min, int val, int max) {
	if ((min <= val) && (max >= val)) return 1;
	// 200, 150, 100 is "between" aswell
	if ((max <= val) && (min >= val)) return 1;

	return 0;
}

// i guess you get why its faster... it doesnt implies > 200, 150, 100 is "between" aswell
int between_faster_version(int min, int val, int max) {
	return (min <= val) && (max >= val);
}