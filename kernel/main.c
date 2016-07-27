#include <arch.h>
#include <stdio.h>

extern char *arch;

int main(void) {
    printf("%s\n", arch);
}
