//
//  main.c
//  Heal
//
//  Created by Burak Dusun on 09/08/16.
//  Copyright © 2016 Burak Dusun. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#define SATIR_BOYUTU 10000
//#define DOSYA_ACMA_HATA 5



int main(int argc, const char * argv[]) {

    
    int tahminSayisi;
    int i,j,sayac;
    
    FILE *fRead;
    FILE *fWrite;
    
    char dosyaAdiRead[100];
    char dosyaAdiWrite[100];
    char tmpSatir[SATIR_BOYUTU];
    
    int *gercekDegerler;
    int *tahminler;
    int *duzeltilenDegerler;
    
    
    printf("Tahmin dosyasinin adini giriniz: ");
    scanf("%s",dosyaAdiRead);
    
    //printf("Düzeltilmiş dosyasinin adini giriniz: ");
    //scanf("%s",dosyaAdiWrite);
    
    fRead = fopen(dosyaAdiRead,"r");

    //fWrite = fopen(dosyaAdiWrite, "w");
    
    sayac = 0;
    
    
    while(sayac<3){
        fgets(tmpSatir, SATIR_BOYUTU, fRead);
        if(tmpSatir[0] == '='){
            sayac++;
        }
    }
    fgets(tmpSatir, SATIR_BOYUTU, fRead);
    fgets(tmpSatir, SATIR_BOYUTU, fRead);
    //fgets(tmpSatir, SATIR_BOYUTU, fRead);
    //printf("%s",tmpSatir);
    
    tahminSayisi = 0;
    
    while (tmpSatir[0] != '\n'){
        fgets(tmpSatir, SATIR_BOYUTU, fRead);
        tahminSayisi++;
    }
    tahminSayisi--;
    printf("Tahmin Sayisi = %d\n",tahminSayisi);
    
    fclose(fRead);
    
    gercekDegerler = (int *) calloc(tahminSayisi, sizeof(int));
    tahminler = (int *) calloc(tahminSayisi, sizeof(int));
    duzeltilenDegerler = (int *) calloc(tahminSayisi, sizeof(int));
    
    fRead = fopen(dosyaAdiRead, "r");
    
    sayac = 0;
    while(sayac<3){
        fgets(tmpSatir, SATIR_BOYUTU, fRead);
        if(tmpSatir[0] == '='){
            sayac++;
        }
    }
    fgets(tmpSatir, SATIR_BOYUTU, fRead);
    fgets(tmpSatir, SATIR_BOYUTU, fRead);
    //fgets(tmpSatir, SATIR_BOYUTU, fRead);
    //printf("%s",tmpSatir);
    
    sayac=0;
    i=0;
    j=0;
    fgets(tmpSatir, SATIR_BOYUTU, fRead);
    while (tmpSatir[0] != '\n'){
        while(tmpSatir[j] != ','){
            j++;
        }
        j++;
        gercekDegerler[i] = tmpSatir[j] - '0';
        while(tmpSatir[j] != ','){
            j++;
        }
        j++;
        tahminler[i] = tmpSatir[j] - '0';
        i++;
        j=0;
        fgets(tmpSatir, SATIR_BOYUTU, fRead);
    }
    
    for(i=0;i<tahminSayisi;i++){
        printf("gercekDeger = %d, tahmin = %d\n",gercekDegerler[i],tahminler[i]);
    }
    
    
    fclose(fRead);
    //fclose(fWrite);
    
    return 0;
}
