#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>

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
        int j = m - 1;
        while (j >= 0 && pat[j] == txt[shift + j])
            j--;

        if (j < 0)
        {
            printf("Pattern occurs at shift = %d\n", shift);
            count++;

            shift += (shift + m < n) ? m - badchar[(int)txt[shift + m]] : 1;
        }
        else
            shift += max(1, j - badchar[(int)txt[shift + j]]);
    }

    return count;
}

int check_template(char *filename, char *template)
{
    int tlen = strlen(template);
    int i = 0;
    while (template[i] != '*' && (i < tlen) && template[i] != '.')
    {
        // printf("%c - %c\n",filename[i],template[i]);
        if (filename[i] != template[i])
        {
            return 0;
        }
        i++;
    }
    int j = strlen(template);
    int k = strlen(filename);
    while (template[j] != '*' && j > 0 && template[j] != '.')
    {
        // printf("%c - %c\n",filename[k],template[j]);
        if (filename[k] != template[j])
        {
            return 0;
        }
        j--;
        k--;
    }
    return 1;
}

void nextdir(char folder[256], char *template)
{
    DIR *dfd;
    dfd = opendir(folder);
    printf("Open dir %s \n", folder);
    struct dirent *dp;
    while ((dp = readdir(dfd)) != NULL)
        if (dp->d_type != 4 && check_template(dp->d_name, template))
        {
            printf("%s\n", dp->d_name);
        }
        else if ((dp->d_type == 4) && ((strcmp(dp->d_name, ".") != 0) && (strcmp(dp->d_name, "..") != 0)))
        {
            folder = strcat(folder, "/");
            nextdir(strcat(folder, dp->d_name), template);
        }
    closedir(dfd);
}

int main(int argc, char **argv)
{
    char *template = "*.c";
    char filename[256];
    if (argc < 2)
        strcpy(filename, ".");
    else
        strcpy(filename, argv[1]);
    printf("Root dir %s\n\n", filename);
    nextdir(filename,template);

    return 0;
}
