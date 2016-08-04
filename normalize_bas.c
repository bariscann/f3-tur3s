//
//  main.c
//  normalizeArff
//
//  Created by Burak Dusun on 02/08/16.
//  Copyright © 2016 Burak Dusun. All rights reserved.
//


#include <stdio.h>
#include <string.h>

#define LINESIZE 10000
#define OZELLIK_SAYISI 18
#define OKLID_BOYUTU 3

int main(int argc, const char * argv[]) {
    
    
    int i=0,j=0;
    int quoteCount=0;
    char filenameRead[50];
    char filenameWrite1[50];
    char line[LINESIZE];
    FILE *fRead;
    FILE *fWrite1;
    char stringToAdd[] = " NORM\" NUMERIC\n";
    char ayrac = ',';
    
    int argSayisi = 9;
    
    
    printf("enter file name: ");
    scanf("%s", filenameRead);
    //fgets("%s", 49, stdin);
    //printf("%s\n",filename);
    
    strcpy(filenameWrite1,filenameRead);
    strcat(filenameWrite1,"_normalized.arff");
    
    fRead = fopen(filenameRead, "r");
    fWrite1 = fopen(filenameWrite1, "w");
    
    fgets(line, LINESIZE, fRead);
    fputs(line,fWrite1);
    //printf("%s",line);
    fputc('\n',fWrite1);
    fgets(line, LINESIZE, fRead);

    
    //i=1;
    int adimSayisi = (argSayisi+OKLID_BOYUTU)*OZELLIK_SAYISI;
    for(i=0;i<adimSayisi;i++){
        fgets(line, LINESIZE, fRead);
        //printf("%s",line);
        
        while(quoteCount<2){
            if(line[j] == '\"'){ // dogru mu
                quoteCount++;
                //printf("quoteCount++");
            }
            if(quoteCount < 2){
                fputc(line[j],fWrite1);
                printf("%c",line[j]);
            }
            j++;
        }
        quoteCount=0;
        fputs(stringToAdd,fWrite1);
        j=0;
        //i++;
    }
    fgets(line, LINESIZE, fRead);
    printf("%s",line);
    fputs(line,fWrite1);
    fputc("\n",fWrite1);
    fgets(line, LINESIZE, fRead);
    fgets(line, LINESIZE, fRead);
    fputs(line,fWrite1);
    
    
    
    fclose(fRead);
    fclose(fWrite1);

    return 0;
}
