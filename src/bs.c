#include <stdio.h>

int main(int argc, char *argv[])
{
	char buf[256], *p;

	while(fgets(buf, sizeof(buf), stdin) > 0 && !feof(stdin)) {
		for(p = buf; *p != 0; p++) {
			if(p != buf && *p == '\\' && (*(p - 1) & 0x80))
				putc('\\', stdout);
			putc(*p, stdout);
		}
	}

	return 0;
}
