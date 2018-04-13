// lets test something

typedef struct testtype_s {
	
	/* some comment */
	int firstInt;
	float secondFloat;
} testtype_t;


int main() {
	int a = 123;
	int b = 200;
	a--;
	a -= 2;
	int c = a + b;
	printf("%d + %d = %d\n", a, b, c);
	
}