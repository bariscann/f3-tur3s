#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>


#define oklidBoyutu 3
#define LINESIZE 100000

#define OZELLIK_SAYISI 17



typedef struct
{
    double ozellik[OZELLIK_SAYISI];
} OZELLIK_MIN;

typedef struct
{
    double ozellik[OZELLIK_SAYISI];
} OZELLIK_MAX;

void dosyaErr(FILE *);
void doubleMErr(double **);
void doubleDErr(double *);


int atlamaMik;
int kontrolAdet;

//global olamaz bu buyuk ihtimal



double normalizeYap(double sayi, double min, double max)
{
    double nSayi = (sayi-min)/(max-min);

    return nSayi;
}

void normalize(double *tmp, OZELLIK_MIN  fMin, OZELLIK_MAX fMax, FILE **fWrite)
{
    double normalizeDeger;
    int i;

    for(i = 0; i < OZELLIK_SAYISI; i++)
    {
        normalizeDeger = normalizeYap(tmp[i],fMin.ozellik[i],fMax.ozellik[i]);
        // printf("%lf,",normalizeDeger);
        // printf("\n%lf,%lf,%lf,%lf,",tmp[i],fMin.ozellik[i],fMax.ozellik[i],normalizeDeger);
        fprintf(*fWrite, "%lf,", normalizeDeger);
    }

}




int main()
{
    OZELLIK_MIN *fMin;
    OZELLIK_MAX *fMax;


    int i,j,k,y;

    double isaret = 1.0;
    double tmpDeger;
    double dDonustur;

    char test_trainAdi[2][100];
    char *tur[] = {"TRAIN.arff","TEST.arff"};

    char min_maxYAZ[50];

    FILE *fRead1;
    FILE *fWrite1;



    int degerlerMin_MaxBoyut = 12;
    int adimSayisi;
    int sayac;

    char tmpSatir[LINESIZE];
    char label[100];

    double tmpDouble[OZELLIK_SAYISI];



    fMax = (OZELLIK_MAX *) malloc(degerlerMin_MaxBoyut*sizeof(OZELLIK_MAX));


    fMin = (OZELLIK_MIN *) malloc(degerlerMin_MaxBoyut*sizeof(OZELLIK_MIN));

    //burda fmin fmax okuması yap. fread ile
    printf("Min Max degerlerinin oldugu dosyayi giriniz: ");
    scanf("%s",min_maxYAZ);

    fRead1 = fopen(min_maxYAZ, "rb");

    fread(fMin, degerlerMin_MaxBoyut, sizeof(OZELLIK_MIN), fRead1 );
    fread(fMax, degerlerMin_MaxBoyut, sizeof(OZELLIK_MAX), fRead1 );

    fclose(fRead1);




    printf("Train edilecek dosya adini giriniz: ");
    scanf("%s",test_trainAdi[0]);
    printf("Test edilecek dosya adini giriniz: ");
    scanf("%s",test_trainAdi[1]);

    adimSayisi = degerlerMin_MaxBoyut*OZELLIK_SAYISI;
    for(k = 0; k < 2; k++)
    {

        fRead1 = fopen(test_trainAdi[k], "r");
        //strcat(test_trainAdi[k],tur[k]);
        fWrite1 = fopen(tur[k], "w");

        fgets(tmpSatir, LINESIZE, fRead1);
        fputs(tmpSatir,fWrite1);
        //printf("%s",line);
        // fputc('\n',fWrite);
        fgets(tmpSatir, LINESIZE, fRead1);
        fputs(tmpSatir,fWrite1);


        for(i=0; i<adimSayisi; i++)
        {
            fgets(tmpSatir, LINESIZE, fRead1);
            printf("%s",tmpSatir);
            fputs(tmpSatir,fWrite1);

        }
        fgets(tmpSatir, LINESIZE, fRead1);
        printf("%s",tmpSatir);
        fputs(tmpSatir,fWrite1);
        //fputc("\n",fWrite);
        fgets(tmpSatir, LINESIZE, fRead1);
        fputs(tmpSatir,fWrite1);
        fgets(tmpSatir, LINESIZE, fRead1);
        fputs(tmpSatir,fWrite1);

        while(fgets(tmpSatir,LINESIZE,fRead1))
        {


            j = 0;
            sayac = 0;
            //printf("%s\n",tmpSatir);
            while(sayac<adimSayisi)
            {
                if(tmpSatir[j]==',')
                {

                    sayac++;
                }
                j++;
            }
            i=0;

            while(tmpSatir[j])
            {
                label[i]=tmpSatir[j];
                //printf("%c",tmpSatir[j]);

                i++;
                j++;
            }
            label[i]=0;

            //printf("\n%s",tmpSatir);
            j=0;
            for(i=0; i<degerlerMin_MaxBoyut; i++)
            {
                for(y=0; y<OZELLIK_SAYISI; y++)
                {
                    isaret = 1.0;
                    tmpDeger = 0.0;
                    dDonustur = 1.0;
                    if(tmpSatir[j]== '-')
                    {
                        isaret = -1.0;
                        j++;
                    }

                    while(tmpSatir[j] != ',' && tmpSatir[j] != '.')
                    {

                        tmpDeger *= 10;
                        tmpDeger += (tmpSatir[j] - '0');
                        j++;
                    }
                    if(tmpSatir[j] != ',')
                        j++;
                    while(tmpSatir[j] != ',')
                    {
                        dDonustur *= 10;
                        tmpDeger = tmpDeger + (tmpSatir[j] - '0')/dDonustur;
                        j++;
                    }
                    // printf("%f,",tmpDeger*isaret);
                    tmpDouble[y] = tmpDeger*isaret;

                    j++;
                }

                normalize(tmpDouble,fMin[i],fMax[i],&fWrite1);




            }
            fprintf(fWrite1,"%s",label);
           // putc('\n',fWrite1);
        }



        fclose(fWrite1);
        fclose(fRead1);
    }


    //i=1;




    free(fMin);
    free(fMax);



    return 0;
}



/********************************************************/


void dosyaErr(FILE *f)
{
    if(!f)
    {
        printf("Dosya Bulunamadi");
        exit(0);
    }
}

void doubleMErr(double **d)
{
    if(!d)
    {
        printf("Matris Olusturulamadi");
        exit(0);
    }
}

void doubleDErr(double *d)
{
    if(!d)
    {
        printf("Alan Olusturulamadi");
        exit(0);
    }
}


/*******************************************************************/
