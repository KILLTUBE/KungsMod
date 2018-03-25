#ifndef OP_ALL_H
#define OP_ALL_H

#if defined(_MSC_VER) || defined(EMSCRIPTEN)

//#include "../include_gl.h"
#include "op.h"
#include "../opsys/opsys.h"

void InitPermanentOps();
extern std::vector<Op *> permanent_ops;

// these ops are directly called from code and always in Ops View
#include "op_matrix.h"
extern OpMatrix            *craft_matrix_persp;
extern OpMatrix            *craft_matrix_ortho;


#define OPLIST_TYPE_MATH       (1<<1)
#define OPLIST_TYPE_OPENGL     (1<<2)
#define OPLIST_TYPE_JAVASCRIPT (1<<3)
#define OPLIST_TYPE_STUFF      (1<<4)
#define OPLIST_TYPE_IDTECH3    (1<<5)
#define OPLIST_TYPE_META       (1<<6)
#define OPLIST_TYPE_FLOAT      (1<<7)

typedef struct oplist_s {
	char *name;
	Op *(*create_op)();
	int type;
} oplist_t;

oplist_t ops_stuff[];
oplist_t ops_meta[];
oplist_t ops_javascript[];
oplist_t ops_math[];
oplist_t ops_float[];
oplist_t ops_opengl[];
oplist_t ops_idtech3[];

#endif

#endif