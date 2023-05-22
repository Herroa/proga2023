#include "dir.h"
#include "mur.h"
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void nextdir(char *template, char *folder, int call)
{
    DIR *dfd;
    dfd = opendir(folder);
    // for(int i = 0;i<call;i++)
    //     printf("\t");
    // printf("Open directory '%s': \n", folder);
    struct dirent *dp;
    int count = 0;
    
    while ((dp = readdir(dfd)) != NULL){
        if ((dp->d_type != 4) && boyer_mur(dp->d_name, template)!=0)
        {
            printf("\t%s\n", dp->d_name);
            count++;
        }
        else if ((dp->d_type == 4) && ((strcmp(dp->d_name, ".") != 0) && (strcmp(dp->d_name, "..") != 0)))
        {
            
            folder = strcat(folder, "/");
            nextdir(template, strcat(folder, dp->d_name),++call);
            call--;
            memset(folder, 0, strlen(folder));
            folder = strcat(folder, ".");
        }
    }
    if(count==0)
        printf("Didnt find pattern '%s'\n", template);
    printf("Close directory '%s': \n", folder);
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