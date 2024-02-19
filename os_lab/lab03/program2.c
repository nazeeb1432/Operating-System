#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>

int main() {
    printf("Executing program1.c\n");

    // Replace the current process with program2
    system("gcc program1.c -o program1");
    execl("./program1", "./program1", NULL);

    // If execl fails, the code below this line won't be executed
    perror("execl failed");
    return 1;
}
