#include "dir.h"
#include "mur.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int nextdir(char *template, char *path)
{
    DIR *dir;
    struct dirent *dp;
    char *temp=malloc(sizeof(char)*255);
    int flag;
    flag = thisdir(template,path);
    if(flag==1)
    {
        return 1;
    }
    dir = opendir(path);
    if (dir == NULL)
    {
        printf("Cant open directory!\n");
        return 1;
    }
    while ((dp = readdir(dir)) != NULL){
        if (dp->d_type == DT_DIR && strcmp(dp->d_name, "..") != 0 && strcmp(dp->d_name, ".") != 0)
        {
            int length = strlen(dp->d_name);
            char cur_dir[length];
            
            strcpy(cur_dir,dp->d_name);
            strcpy(temp, path);
            strcat(temp, "/");
            strcat(temp, cur_dir);
            nextdir(template, temp);
            memset(temp, 0, strlen(temp));
        }
    }
    closedir(dir);
    return 0;
}

int thisdir(char *template, char *path)
{
    DIR *dir;
    struct dirent *dp;
    dir = opendir(path);
    if (dir == NULL)
    {
        printf("Cant open directory!\n");
        return 1;
    }
    int len = strlen(path);
    char temp[len+1];
    strcpy(temp,path);

    printf("Open dir '%s'\n", path);
    while ((dp = readdir(dir)) != NULL){
        if (dp->d_type != 4)
        {   
            path = malloc(255 * sizeof(char));
            strcpy(path, temp);
            strcat(path, "/");
            strcat(path, dp->d_name);
            check_file(template,path);
            free(path);
        }
    }
    closedir(dir);
    printf("^^^\n");
    return 0;
}

int check_file(char *template, const char *path)
{
    char *string = malloc(sizeof(char) * 255); // 240 in txt
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