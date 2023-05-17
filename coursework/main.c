#include <stdio.h>
#include <string.h>

char *mystrstr(char *str1,char *str2){
    char *istr = NULL;
    for(int i=0; str1[i]!='\0'; i++) {
        for(int j=i, k=0; str2[k]!='\0' && str1[j]==str2[k]; j++, k++){
            if(k>0 && str2[k+1]=='\0')
            {
                istr = &str1[i];
                break;
            } 
        }
    }
    return istr;
}

int main()
{
    char str1[100] = "0123456789";
    char str2[10] = "12";

    printf("%s\n",mystrstr(str1,str2));
    return 0;
}