#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define NO_OF_CHARS 256

int max(int a, int b) { return (a > b) ? a : b; }

void badCharHeuristic(char *str, int size, int badchar[NO_OF_CHARS])
{
    int i;
    for (i = 0; i < NO_OF_CHARS; i++)
        badchar[i] = -1;

    for (i = 0; i < size; i++)
        badchar[(int)str[i]] = i;
}

int boyer_mur(char *txt, char *pat)
{
    int count = 0;
    int m = strlen(pat);
    int n = strlen(txt);

    int badchar[NO_OF_CHARS];

    badCharHeuristic(pat, m, badchar);

    int shift = 0;
    while (shift <= (n - m))
    {
        int j = m - 1; // last char

        /* Keep reducing index j of pattern while
        characters of pattern and text are
        matching at this shift s */
        while (j >= 0 && pat[j] == txt[shift + j])
            j--;

        /* If the pattern is present at current
        shift, then index j will become -1 after
        the above loop */
        if (j < 0)
        {
            printf("pattern occurs at shift = %d\n", shift);
            count++;

            /* Shift the pattern so that the next
            character in text aligns with the last
            occurrence of it in pattern.
            The condition s+m < n is necessary for
            the case when pattern occurs at the end
            of text */
            shift += (shift + m < n) ? m - badchar[(int)txt[shift + m]] : 1;
        }

        else
            /* Shift the pattern so that the bad character
            in text aligns with the last occurrence of
            it in pattern. The max function is used to
            make sure that we get a positive shift.
            We may get a negative shift if the last
            occurrence of bad character in pattern
            is on the right side of the current
            character. */
            shift += max(1, j - badchar[(int)txt[shift + j]]);
    }

    return count;
}

void check_file(const char *file, char *substring)
{
    char *string = malloc(sizeof(char) * 256); // 240
    FILE *in = fopen(file, "r");
    printf("In file '%s':\n", file);
    int line = 1;
    int count = 0;
    int file_count = 0;
    while (!feof(in))
    {
        fscanf(in, "%s", string);
        count = boyer_mur(string, substring);
        if (count != 0)
        {
            printf("On line(%d) found %d occurs\n", line, count);
        }
        file_count += count;
        line++;
    }
    printf("total occurs in file: %d\n", file_count);
    free(string);
}

int main()
{
    check_file("test", "ABBC");
    return 0;
}
