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

void nextdir(char *template, char *folder)
{

    DIR *dfd;
    dfd = opendir(folder);
    printf("Open dir %s \n", folder);
    struct dirent *dp;
    while ((dp = readdir(dfd)) != NULL){
        if (dp->d_type != 4 && boyer_mur(dp->d_name, template)!=0)
        {
            printf("%s\n", dp->d_name);
        }
        else if ((dp->d_type == 4) && ((strcmp(dp->d_name, ".") != 0) && (strcmp(dp->d_name, "..") != 0)))
        {
            folder = strcat(folder, "/");
            nextdir(template, strcat(folder, dp->d_name));
        }
    }
    closedir(dfd);
}

void thisdir(char *template, char *folder)
{
    DIR *dfd;
    dfd = opendir(folder);
    printf("Open dir %s \n", folder);
    struct dirent *dp;
    while ((dp = readdir(dfd)) != NULL){
        if (dp->d_type != 4 && boyer_mur(dp->d_name, template)!=0)
        {
            printf("%s\n", dp->d_name);
        }
    }
}

int main(int argc, char **argv)
{
    char *template;
    char *folder;
    if (strcmp(argv[1], "-r") == 0)
    {
        if (argc < 4)
        {
            printf("Not enough arguments");
            return -1;
        }
        else
        {
            template = argv[2];
            folder = argv[3];
            nextdir(template, folder);
            //recursive
        }
    }
    else
    {
        if (argc < 3)
        {
            printf("Not enough argumetns");
            return -1;
        }
        else
        {
            template = argv[1];
            folder = argv[2];
            thisdir(template, folder);
            //not recursive
        }
    }


    return 0;
}
