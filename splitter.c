//
//  main.c
//  splitter
//
//  Created by Burak Dusun on 26/07/16.
//  Copyright © 2016 Burak Dusun. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#define LINESIZE 10000

int main(int argc, const char * argv[]) {
    
    
    int split=0;
    int i,j,header;
    char filenameRead[50];
    char filenameWrite1[50];
    char filenameWrite2[50];
    char line[LINESIZE];
    FILE *fRead;
    FILE *fWrite1;
    FILE *fWrite2;
    
    // insert code here...
    printf("Enter split percentage(as integer): ");
    scanf("%d",&split);
    
    printf("enter file name: ");
    scanf("%s", filenameRead);
    //fgets("%s", 49, stdin);
    //printf("%s\n",filename);
    
    strcpy(filenameWrite1,filenameRead);
    strcat(filenameWrite1,"_part1.arff");
    strcpy(filenameWrite2,filenameRead);
    strcat(filenameWrite2,"_part2.arff");
    
    fRead = fopen(filenameRead, "r");
    fWrite1 = fopen(filenameWrite1, "w");
    fWrite2 = fopen(filenameWrite2,"w");
    
    fgets(line, LINESIZE, fRead);
    fputs(line,fWrite1);
    fputs(line,fWrite2);
    fputc('\n',fWrite1);
    fputc('\n',fWrite2);
    fgets(line, LINESIZE, fRead);
    
    header=0;
    //i=1;
    do {
        fgets(line, LINESIZE, fRead);
        fputs(line,fWrite1);
        fputs(line,fWrite2);
        header++;
        //i++;
    }while (line[0]=='@');
    fgets(line, LINESIZE, fRead);
    fputs(line,fWrite1);
    fputs(line,fWrite2);
    header+=3;
    
    j=0;
    while((fgets(line, LINESIZE, fRead))!=NULL){
        j++;
    }
    printf("Number of data lines= %d\n",j);
    split *= (j/100);
    
    fclose(fRead);
    fRead = fopen(filenameRead, "r");
    
    for(i=0;i<header;i++){
        fgets(line, LINESIZE, fRead);
    }
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
    printf("file2 data lines= %d\n",i-split);
    
    
    
    fclose(fRead);
    fclose(fWrite1);
    fclose(fWrite2);
    
    return 0;
}
