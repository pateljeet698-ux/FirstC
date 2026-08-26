#include <stdio.h>
#include <unistd.h>

int main(void)
{
    char shuriken[] = {'|', '/', '-', '\\', '|', '/', '-', '\\'};
    
    printf("Clockwise rotating Shuriken:\n");
    
    for (int i = 0; i < 40; i++)
    {
        printf("\r%c", shuriken[i % 8]);
        fflush(stdout);
        usleep(100000);  // 100ms delay
    }
    
    printf("\nDone!\n");
    return 0;
}
