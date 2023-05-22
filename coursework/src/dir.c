#include "dir.h"
#include "mur.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void nextdir(char *template, char *path)
{
    DIR *dfd;
    dfd = opendir(path);
    printf("Open directory '%s': \n", path);
    struct dirent *dp;
    
    while ((dp = readdir(dfd)) != NULL){
        if (dp->d_type != 4)
        {
            printf("\t%s\n", dp->d_name);
            strcat(path,"/");
            strcat(path,dp->d_name);
            check_file(template,path);
        }
        else if ((dp->d_type == 4) && ((strcmp(dp->d_name, ".") != 0) && (strcmp(dp->d_name, "..") != 0)))
        {
            
            path = strcat(path, "/");
            path = strcat(path, dp->d_name);
            nextdir(template, path);
            memset(path, 0, strlen(path));
            // path = strcat(path, ".");
        }
    }
    printf("Close directory '%s': \n", path);
    closedir(dfd);
}

void thisdir(char *template, char *path)
{
    DIR *dfd;
    dfd = opendir(path);
    printf("Open dir %s \n", path);
    struct dirent *dp;
    while ((dp = readdir(dfd)) != NULL){
        if (dp->d_type != 4)
        {
            check_file(template,dp->d_name);
        }
    }
    printf("^^^\n");
}

int check_file(char *template, const char *path)
{
    char *string = malloc(sizeof(char) * 256000); // 240 in txt
    FILE *in = fopen(path, "r");
    if (!in)
    {
        printf("Can't open file: %s!\n",path);
        return 1;
    }
    printf("In file '%s':\n", path);
    int line = 1;
    int count = 0;
    int file_count = 0;
    while (!feof(in))
    {
        fscanf(in, "%s", string);
        count = boyer_mur(string, template);
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