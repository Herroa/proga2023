#include "dir_processing.h"
#include "mur.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void nextdir(char *template, char *folder)
{

    DIR *dfd;
    dfd = opendir(folder);
    printf("Open dir '%s': \n", folder);
    struct dirent *dp;
    while ((dp = readdir(dfd)) != NULL){
        if ((dp->d_type != 4) && boyer_mur(dp->d_name, template)!=0)
        {
            printf("-%s\n", dp->d_name);
        }
        else if ((dp->d_type == 4) && ((strcmp(dp->d_name, ".") != 0) && (strcmp(dp->d_name, "..") != 0)))
        {
            
            folder = strcat(folder, "/");
            nextdir(template, strcat(folder, dp->d_name));
            memset(folder, 0, strlen(folder));
            folder = strcat(folder, ".");
        }
    }
    printf("^^^\n");
    closedir(dfd);
}

void thisdir(char *template, char *folder)
{
    DIR *dfd;
    dfd = opendir(folder);
    printf("Open dir %s \n", folder);
    struct dirent *dp;
    while ((dp = readdir(dfd)) != NULL){
        if (boyer_mur(dp->d_name, template)!=0)
        {
            printf("%s\n", dp->d_name);
        }
    }
    printf("^^^\n");
}