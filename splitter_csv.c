//
//  main.c
//  splitterCsv
//
//  Created by Burak Dusun on 08/08/16.
//  Copyright © 2016 Burak Dusun. All rights reserved.
//


#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>


#define LINESIZE 10000


/*
    exe ile aynı klasörde bir 'raw' dosyasina konan csv'ler
    'splitted' klasorunde girilen yuzdeye gore ikiye ayrilmis olarak bulunur
    raw klasoru olusturulmalidir
*/
int isCSV(char *dosyaAdi)
{
    int i = strlen(dosyaAdi);
    i--;
    if ((dosyaAdi[i]=='v')&&(dosyaAdi[--i]=='s')&&(dosyaAdi[--i]=='c')&&(dosyaAdi[--i]=='.'))
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


int main(int argc, const char * argv[]) {
    
    
    int split=0;
    int splitPercentage=0;
    int i,j;
    char filenameRead[50];
    char filenameWrite1[200];
    char filenameWrite2[200];
    char line[LINESIZE];
    FILE *fRead;
    FILE *fWrite1;
    FILE *fWrite2;
    char dirNameWrite[] = "splitted";
    char dirNameWrite2[] = "/splitted";
    char dirNameRead[] = "raw";
    char dirNameRead2[] = "/raw";
    
    // insert code here...
    printf("Enter split percentage(as integer): ");
    scanf("%d",&splitPercentage);
    
    //printf("enter file name: ");
    //scanf("%s", filenameRead);
    //fgets("%s", 49, stdin);
    //printf("%s\n",filename);
    
    DIR *dp;
    struct dirent *ep;
    
    mkdir("splitted",0777);
    mkdir("raw",0777);
    
    dp = opendir ("./raw/");
    if (dp == NULL)
    {
        exit(1);
    }
    

    while ((ep = readdir (dp)))
    {
        
        printf("%s\n",ep->d_name);
        
        if (isCSV(ep->d_name))
        {
            
            strcpy(filenameRead,"raw/");
            strcat(filenameRead,ep->d_name);
            
            strcpy(filenameWrite1,"splitted/");
            strcat(filenameWrite1,ep->d_name);
            strcat(filenameWrite1,"_part1.csv");
            
            strcpy(filenameWrite2,"splitted/");
            strcat(filenameWrite2,ep->d_name);
            strcat(filenameWrite2,"_part2.csv");
            
            //strcpy(filenameWrite1,filenameRead);
            //strcat(filenameWrite1,"_part1.csvx");
            //strcpy(filenameWrite2,filenameRead);
            //strcat(filenameWrite2,"_part2.csvx");
    
            fRead = fopen(filenameRead, "r");
            fWrite1 = fopen(filenameWrite1, "w");
            fWrite2 = fopen(filenameWrite2,"w");
    
            fgets(line, LINESIZE, fRead);
            fputs(line,fWrite1);
            fputs(line,fWrite2);
    
            split=splitPercentage;
            j=0;
            while((fgets(line, LINESIZE, fRead))!=NULL){
                j++;
            }
            printf("Number of data lines= %d\n",j);
            split *= (j/100);
            //split += j%100;
            fclose(fRead);
            fRead = fopen(filenameRead, "r");
    
            fgets(line, LINESIZE, fRead);

            //printf("%s",line);
            for(i=0;i<split;i++){
                fgets(line, LINESIZE, fRead);
                fputs(line,fWrite1);
            }
            printf("file1 data lines= %d\n",i);
            for(i=split;i<j;i++){
                fgets(line, LINESIZE, fRead);
                fputs(line,fWrite2);
            }
            printf("file2 data lines= %d\n\n",i-split);
            
            
            fclose(fRead);
            fclose(fWrite1);
            fclose(fWrite2);
            
        }
    }
    
    return 0;
}