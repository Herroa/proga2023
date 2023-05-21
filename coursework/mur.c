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

int check_file(const char *file, char *substring)
{
    char *string = malloc(sizeof(char) * 256000); // 240 in txt
    FILE *in = fopen(file, "r");
    if (!in)
    {
        printf("Can't open file: %s!\n",file);
        return 1;
    }
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
    printf("total occurs in file: %d\n\n", file_count);
    free(string);
    return 0;
}

int check_this_dir(char *template, char *substring)
{
    DIR *dp = opendir(".");
    if (!dp)
    {
        printf("Can't open current directory!\n");
        return 1;
    }

    struct dirent *de;
    while ((de = readdir(dp)))
    {
        int tlen = strlen(template);
        int nlen = strlen(de->d_name);
        if (strcmp(((de->d_name) + nlen - tlen), template) == 0)
        {
            printf("%s\n", de->d_name);
            check_file(de->d_name, substring);
        }
    }
    closedir(dp);
    return 0;
}

int check_template(char *filename,char *template)
{
    int tlen = strlen(template);
    int i = 0;
    while(template[i]!='*'&&(i<tlen)&&template[i]!='.')
    {
        // printf("%c - %c\n",filename[i],template[i]);
        if(filename[i]!=template[i])
        {
            return 0;
        }
        i++;
    }
    int j=strlen(template);
    int k=strlen(filename);
    while(template[j]!='*'&&j>0)
    {
        // printf("%c - %c\n",filename[k],template[j]);
        if(filename[k]!=template[j])
        {
            return 0;
        }
        j--;
        k--;
    }
    return 1;
}

void nextdir(char folder[256],char *substring,char *template)
{
    DIR *dfd;
    dfd = opendir(folder);
    printf("Открытие папки %s \n", folder);
    struct dirent *dp;
    while ((dp = readdir(dfd)) != NULL)
        if (dp->d_type != 4 && check_template(dp->d_name,template)){
            check_file(dp->d_name,substring);
            // printf("%s\n", dp->d_name);
        }
        else if ((dp->d_type == 4) && ((strcmp(dp->d_name, ".") != 0) && (strcmp(dp->d_name, "..") != 0)))
        {
            folder = strcat(folder, "/");
            nextdir(strcat(folder, dp->d_name),substring,template);
        }
    closedir(dfd);
}

int main(int argc, char **argv)
{
    char *substring = "ABBC";
    char *template = "t*.txt";
    // check_this_dir(template, substring);
    char filename[256];
    if (argc < 2)
        strcpy(filename, ".");
    else
        strcpy(filename, argv[1]);
    printf("Корневой каталог %s\n\n", filename);
    nextdir(filename,substring,template);

    return 0;
}

