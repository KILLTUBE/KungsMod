#ifndef OPSYSTEM_UTILS_H
#define OPSYSTEM_UTILS_H

int get_line_intersection(float p0_x, float p0_y, float p1_x, float p1_y, float p2_x, float p2_y, float p3_x, float p3_y, float *i_x, float *i_y);
unsigned int rand32();
int between(int min, int val, int max);
int between_faster_version(int min, int val, int max);

#endif