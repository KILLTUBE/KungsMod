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

static void staticVoidFunc(int a, int b) {
	// doesnt matter, aslong they close each other out
	{{{}}}{}{}{{{}}}
	return 321;
}

static void **staticVoidPointerPointer();

const float *constFloatPointerPrototype( void);

int justInt;

int **intStarStar;

void *voidPointer;

static const void *staticConstVoidPointer;

float floatTwoDims[1024][321];

/*
ok, thinking about how to parse types...
int main(); ---> Name Name BracketOpen BracketClose Semicolon
float main(); ---> Name Name BracketOpen BracketClose Semicolon
float main(); ---> Name Name BracketOpen BracketClose Semicolon
static float main(); ---> Static Name Name BracketOpen BracketClose Semicolon
const float main(); ---> Const Name Name BracketOpen BracketClose Semicolon
*/
