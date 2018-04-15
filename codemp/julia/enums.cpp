// lets test something

typedef struct testtype_s {
	
	/* some comment */
	int firstInt;
	float secondFloat;
	idk secondFloat;
} testtype_t;


int main() {
	int a = 123;
	int b = 200;
	a--;
	a -= 2;
	int c = a + b;
	printf("%d + %d = %d\n", a, b, c);
	
}

static void **foo();

const float *wut( void);

int globalFoo;

/*
ok, thinking about how to parse types...
int main(); ---> Name Name BracketOpen BracketClose Semicolon
float main(); ---> Name Name BracketOpen BracketClose Semicolon
float main(); ---> Name Name BracketOpen BracketClose Semicolon
static float main(); ---> Static Name Name BracketOpen BracketClose Semicolon
const float main(); ---> Const Name Name BracketOpen BracketClose Semicolon
*/
