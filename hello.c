#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
    char shuriken[] = {'|', '/', '-', '\\', '|', '/', '-', '\\'};
    char **lines = NULL;
    size_t count = 0;

    FILE *f = fopen("naruto.txt", "r");
    if (f)
    {
        char *line = NULL;
        size_t n = 0;
        ssize_t r;
        while ((r = getline(&line, &n, f)) != -1)
        {
            if (r > 0 && line[r-1] == '\n') line[r-1] = '\0';
            char **tmp = realloc(lines, sizeof(char*) * (count + 1));
            if (!tmp) { perror("realloc"); free(line); fclose(f); return 1; }
            lines = tmp;
            lines[count++] = strdup(line);
        }
        free(line);
        fclose(f);
    }
    else
    {
        // Fallback message if no ASCII art file is found
        lines = malloc(sizeof(char*) * 3);
        if (!lines) return 1;
        lines[0] = strdup("Naruto ASCII background not found.");
        lines[1] = strdup("Place an ASCII art file named 'naruto.txt' in the program directory.");
        lines[2] = strdup("");
        count = 3;
    }

    // Clear screen and print background ASCII art
    printf("\033[2J"); // clear
    printf("\033[H");  // move cursor to home
    for (size_t i = 0; i < count; i++)
        printf("%s\n", lines[i]);

    // Choose spinner position (center of the middle line)
    int spinner_row = (int)(count / 2);
    int spinner_col = 1;
    if (spinner_row >= 0 && spinner_row < (int)count)
    {
        spinner_col = (int)strlen(lines[spinner_row]) / 2;
        if (spinner_col < 1) spinner_col = 1;
    }

    // Hide cursor
    printf("\033[?25l");
    fflush(stdout);

    // Overlay rotating shuriken
    for (int i = 0; i < 40; i++)
    {
        // ANSI positions are 1-based
        printf("\033[%d;%dH%c", spinner_row + 1, spinner_col + 1, shuriken[i % 8]);
        fflush(stdout);
        usleep(100000); // 100ms
    }

    // Move cursor after art, show newline and restore cursor
    printf("\033[%d;1H", (int)count + 1);
    printf("\nDone!\n");
    printf("\033[?25h"); // show cursor

    // Free memory
    for (size_t i = 0; i < count; i++) free(lines[i]);
    free(lines);

    return 0;
}
