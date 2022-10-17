#include <unistd.h>

extern size_t mystrlen(const char *);

int main(int argc, char * const argv[])
{
	char *msg = "Hola mundo.\n";
	write(1, msg, mystrlen(msg));
	return 0;
}
