#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <float.h>

#define oklidBoyutu 3
#define LINESIZE 10000

void dosyaErr(FILE *);
void doubleMErr(double **);
void doubleDErr(double *);



int atlamaMik;
int kontrolAdet;


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
void labelBul(char *dosyaAdi, char *label, int labelType)
{
    int i=0,j=0;
    if(labelType == 1){
        while(dosyaAdi[i] != '_')
        {
            label[i] = dosyaAdi[i];
            i++;
        }
        label[i] = '\0';

    }
    else if (labelType == 0){
        while(dosyaAdi[i] != '_')
        {
            i++;
        }
        i++;
        while(dosyaAdi[i] != '_'){
            label[j] = dosyaAdi[i];
            i++;
            j++;
        }
        label[j] = dosyaAdi[i]; // _'da kalmamasi icin
        i++;
        j++;
        while(dosyaAdi[i] != '_'){
            label[j] = dosyaAdi[i];
            i++;
            j++;
        }
        label[j] = '\0';
    }

}

double ortalamaAritmetikBul(double *degerler)
{
    int i;
    double toplam = 0;
    for(i=0; i<kontrolAdet; i++)
    {
        toplam += degerler[i];
    }

    return toplam/kontrolAdet;

}


double ortalamaGeoBul(double *degerler)
{
    int i;
    double carpim = 1;
    double ust = 1.0/kontrolAdet;
    double ort;
    for(i=0; i<kontrolAdet; i++)
    {
        carpim *= degerler[i];
    }

    ort = pow(carpim,ust);

    if (ort==HUGE_VAL)
    {
        ort = DBL_MAX;
    }
    else if(isnan(ort))
    {
        ort = 0.0;
    }



    return ort;

}

double ortalamaHarmonikBul(double *degerler)
{
    int i;
    double toplam = 0;
    for(i=0; i<kontrolAdet; i++)
    {
        toplam += 1/degerler[i];
    }
    return kontrolAdet/toplam;

}

double ortalamaKuadratikBul(double *degerler)
{
    int i;
    double toplam = 0;
    for(i=0; i<kontrolAdet; i++)
    {
        toplam += (degerler[i]*degerler[i]);
    }
    return sqrt(toplam/kontrolAdet);

}

double standartSapma(double varyans)
{
    return sqrt(varyans);
}



double varyansBul(double *degerler,double ortalama)
{
    int i;
    double toplam = 0;

    for(i=0; i<kontrolAdet; i++)
    {
        toplam += pow((degerler[i]-ortalama),2);
    }


    return toplam/kontrolAdet;

}






void anlikOrtalamalar(double *degerler,double *anlikAritmetikOrt,double *anlikGeometrikOrt,double *anlikHarmonikOrt,double *anlikKuadratikOrt)
{
    int i;
    double fark;
    double aritmatikToplam , harmonikToplam , kuadratikToplam ;
    aritmatikToplam = harmonikToplam = kuadratikToplam = 0;
    double geometrikCarpim = 1;


    for(i=1; i<kontrolAdet; i++)
    {
        fark = degerler[i]-degerler[i-1];
        aritmatikToplam += fark;
        harmonikToplam += 1/fark;
        kuadratikToplam += fark*fark;
        geometrikCarpim *= fark;

    }

    *anlikAritmetikOrt = aritmatikToplam/kontrolAdet;

    *anlikGeometrikOrt = pow(geometrikCarpim,1.0/kontrolAdet);


    if (*anlikGeometrikOrt==HUGE_VAL)
    {
        *anlikGeometrikOrt = DBL_MAX;
    }
    else if (isnan(*anlikGeometrikOrt))
    {
        *anlikGeometrikOrt = 0.0;
    }
    *anlikHarmonikOrt = kontrolAdet/harmonikToplam;
    *anlikKuadratikOrt = sqrt(kuadratikToplam/kontrolAdet);

}


double varyasyonKatSayisi(double stdSapma,double ortalama)
{
    if (ortalama == 0){
        if(ortalama>0){
            return DBL_MAX;
        }
        else if (ortalama<0){
            return -DBL_MAX;
        }
        else {
            return 0;
        }
    }
    else{
        return stdSapma/ortalama;
    }
}


double minBul(double *degerler)
{

    int i;
    double min;
    min = degerler[0];

    for(i=1; i<kontrolAdet; i++)
    {
        if (degerler[i]<min)
        {
            min = degerler[i];
        }

    }
    return min;

}

double maxBul(double *degerler)
{
    int i;
    double max;
    max = degerler[0];

    for(i=1; i<kontrolAdet; i++)
    {
        if (degerler[i]>max)
        {
            max = degerler[i];
        }

    }
    return max;
}






double ranjBul(double min, double max)
{
    return max - min;
}







double minIncBul(double *degerler)  //minimum artis
{

    int i,j;
    i = 0;
    double min,fark;

    do
    {
        i++;
    }
    while ((i<kontrolAdet) && (degerler[i]<=degerler[i-1]));

    if (i>=kontrolAdet)  // eger artis bulunamadiysa
    {
        min = 0; // artis default degeri kac olmali?..
    }
    else
    {
        min = degerler[i]-degerler[i-1];

        for(j=i+1; j<kontrolAdet; j++)
        {
            fark = degerler[j]-degerler[j-1];
            if ((fark>0) && (fark<min))
            {
                min = fark;

            }

        }
    }
    return min;
}

double maxIncBul(double *degerler)  //maximum artis
{


    int i,j;
    i = 0;
    double max,fark;
    do
    {
        i++;
    }
    while ((i<kontrolAdet) && (degerler[i]<=degerler[i-1]));

    if (i>=kontrolAdet)  // eger artis bulunamadiysa
    {
        max = 0; // artis default degeri kac olmali?..
    }
    else
    {
        max = degerler[i]-degerler[i-1];

        for(j=i+1; j<kontrolAdet; j++)
        {
            fark = degerler[j]-degerler[j-1];
            if ((fark>0) && (fark>max))
            {
                max = fark;

            }

        }
    }
    return max;
}




double minRedBul(double *degerler)  //minimum azalis
{
    int i,j;
    i = 0;
    double min,fark;
    do
    {
        i++;
    }
    while ((i<kontrolAdet) && (degerler[i]>=degerler[i-1]));

    if (i>=kontrolAdet)  // eger azalis bulunamadiysa
    {
        min = 0; // azalis default degeri kac olmali?..
    }
    else
    {
        min = degerler[i]-degerler[i-1];

        for(j=i+1; j<kontrolAdet; j++)
        {
            fark = degerler[j]-degerler[j-1];
            if ((fark<0) && (fark>min))
            {
                min = fark;

            }

        }
    }
    return min;

}



double maxRedBul(double *degerler)  //maximum artis
{
    int i,j;
    i = 0;
    double max,fark;

    do
    {
        i++;
    }
    while ((i<kontrolAdet) && (degerler[i]>=degerler[i-1]));

    if (i>=kontrolAdet)  // eger artis bulunamadiysa
    {
        max = 0; // artis default degeri kac olmali?..
    }
    else
    {
        max = degerler[i]-degerler[i-1];

        for(j=i+1; j<kontrolAdet; j++)
        {
            fark = degerler[j]-degerler[j-1];
            if ((fark<0) && (fark<max))
            {
                max = fark;

            }

        }
    }
    return max;

}

void quickS(double dizi[],int l, int r)
{
    int pivotAddr;
    if(l<r)
    {
        pivotAddr = partition(dizi,l,r);
        quickS(dizi,l,pivotAddr-1);
        quickS(dizi,pivotAddr+1,r);
    }
}

int partition(double dizi[],int l, int r)
{
    double pivot = dizi[l];
    int i = l;
    int j = r+1;
    double tmp;

    do
    {
        do
        {
            i++;
        }
        while(i<j && dizi[i]<=pivot);

        do
        {
            j--;
        }
        while(dizi[j]>pivot);

        tmp = dizi[i];
        dizi[i]=dizi[j];
        dizi[j]=tmp;
    }
    while(i<j);

    tmp = dizi[i];
    dizi[i]=dizi[j];
    dizi[j]=tmp;

    tmp = dizi[l];
    dizi[l]=dizi[j];
    dizi[j]=tmp;

    return j;
}

void modMedianBul (double *degerler,double *median, double *mod)
{

    int i,j=0;
    double *tmp;
    double maxMod=1.0;
    double tmpMod=1.0;
    int maxModI=0;
    int bolum,kalan,indis;
    tmp = (double *) malloc(kontrolAdet*sizeof(double));

    for(i=0; i<kontrolAdet; i++)
    {
        tmp[i]=degerler[i];
    }
    //quickSort(tmp,0,kontrolAdet);
    quickS(tmp,0,kontrolAdet-1);
    /**
     buradaki islemlerin amaci cift sayida veri oldugu taktirde ortadaki iki sayiyi bulup ortalamasini almak. if kullanmak pahali geldi.
     */
    bolum = kontrolAdet/2;
    kalan = kontrolAdet%2;
    indis = bolum + kalan - 1;
    *median = (tmp[bolum] + tmp[indis])/2;
    //cift sayıda olma durumunda kontrol edip ortalamasını almak lazım

    j=1;
    while (j<kontrolAdet)
    {
        while(j<kontrolAdet && tmp[j]==tmp[j-1])
        {
            j++;
            tmpMod++;
        }
        if(tmpMod>maxMod)
        {
            maxModI=j-1;
            maxMod=tmpMod;
        }
        j++;
        tmpMod=1;
    }

    *mod = tmp[maxModI];
    free(tmp);
}




void islem(double **degerler, int argSayisi, char ayrac, FILE **fWrite)
{

    int x;
    double min;
    double max;
    double ranj;
    double minInc;
    double maxInc;
    double minRed;
    double maxRed;
    double median;
    double mod;
    double aritmetikOrtalama;
    double geometrikOrtalama;
    double harmonikOrtalama;
    double kuadratikOrtalama;
    double stdSapma;
    double varyans;
    double anlikAritmetikOrt;
    double anlikGeometrikOrt;
    double anlikHarmonikOrt;
    double anlikKuadratikOrt;
    double varyasyonKatSayi;

    for(x=0; x<argSayisi; x++)
    {
        min = minBul(degerler[x]);
        max = maxBul(degerler[x]);
        ranj = ranjBul(min,max);
        minInc = minIncBul(degerler[x]);
        maxInc = maxIncBul(degerler[x]);
        minRed = minRedBul(degerler[x]);
        maxRed = maxRedBul(degerler[x]);

        aritmetikOrtalama = ortalamaAritmetikBul(degerler[x]);
        geometrikOrtalama = ortalamaGeoBul(degerler[x]);
        harmonikOrtalama = ortalamaHarmonikBul(degerler[x]);
        kuadratikOrtalama = ortalamaKuadratikBul(degerler[x]);
        varyans = varyansBul(degerler[x],aritmetikOrtalama);
        stdSapma = standartSapma(varyans);
        anlikOrtalamalar(degerler[x],&anlikAritmetikOrt,&anlikGeometrikOrt,&anlikHarmonikOrt,&anlikKuadratikOrt);
        varyasyonKatSayi = varyasyonKatSayisi(stdSapma,aritmetikOrtalama);
        modMedianBul(degerler[x],&median,&mod);
        //printf("\nMin: %lf, Max: %lf,",geometrikOrtalama,varyans);
        fprintf(*fWrite,"%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c",minRed,ayrac,maxRed,ayrac,minInc,ayrac,maxInc,ayrac,min,ayrac,max,ayrac,ranj,ayrac,aritmetikOrtalama,ayrac,geometrikOrtalama,ayrac,harmonikOrtalama,ayrac,kuadratikOrtalama,ayrac,mod,ayrac,median,ayrac,stdSapma,ayrac,varyans,ayrac,anlikAritmetikOrt,ayrac,anlikGeometrikOrt,ayrac,anlikHarmonikOrt,ayrac,anlikKuadratikOrt,ayrac,varyasyonKatSayi,ayrac);
    }

}

int main()
{



    int i,j,k,x,y;
    int indis;
    double oklidDegeri;
    int f = 0;
    int r ;
    int argSayisi = 0;
    char dosyaAdiOkuma[100];
    char dosyaAdiYazma[] = "features2.arff";
    char tmpSatir[LINESIZE];
    char ayrac;
    int kelimeUzunlugu;

    double **degerler;
    double **oklids;

    int degerSayisi;
    double tmpDeger = 0;
    double dDonustur = 1;
    double isaret = 1;


    double min;
    double max;
    double ranj;
    double minInc;
    double maxInc;
    double minRed;
    double maxRed;
    double median;
    double mod;
    double aritmetikOrtalama;
    double geometrikOrtalama;
    double harmonikOrtalama;
    double kuadratikOrtalama;
    double stdSapma;
    double varyans;
    double anlikAritmetikOrt;
    double anlikGeometrikOrt;
    double anlikHarmonikOrt;
    double anlikKuadratikOrt;
    double varyasyonKatSayi;




    int sure;
    int frekans;
    int atlamaOrani;
    int labelType = 0;

    char *ozellikler[] = {"MINRED","MAXRED","MININC","MAXINC","MINVAL","MAXVAL", "RANGE",
        "ARTMEAN", "GEOMEAN","HARMEAN", "QUADMEAN", "MOD", "MEDIAN", "STD","VAR", "IEARTMEAN", "IEGEOMEAN", "IEHARMEAN",
        "IEQUADMEAN", "COV"
    };

    // char *labels[] = {"walking","car","bus","tram","metro1","metro2","marmaray","metrobus","bicycle","ferry","n"};
    char *labels[] = {"walking","minibus_sitting","minibus_standing","car","bus_sitting","tram_sitting","metroH_sitting","metroK_sitting","marmaray_sitting","metrobus_sitting","ferry_sitting","bus_standing","tram_standing","metroH_standing","metroK_standing","marmaray_standing","metrobus_standing","ferry_standing"};

    char *labels1[]= {"walking","minibus","car","bus","tram","metro","metrobus","ferry"};

    char label[100];
    char alan[100];
    int kacinciKelime;
    int yazildi=0;
    int ozellikSayisi = 20;
    int labelSayisi = 18;
    int labelSayisi1= 8;

    FILE *fRead;
    FILE *fWrite;

    //fRead = fopen(dosyaAdiOkuma,"r");
    //dosyaErr(fRead);

    //printf("\nDosya Adi: ");
    //scanf("%s",dosyaAdiYazma);

    printf("\nAzaltilmis labellar?(1 - evet, 0 - hayir) ");
    scanf("%d",&labelType);

    fWrite = fopen(dosyaAdiYazma,"w");
    dosyaErr(fWrite);

    fprintf(fWrite,"@RELATION vehicle_classification\n\n");


    //  fputs(tmpSatir,fWrite);

    DIR *dp;
    struct dirent *ep;

    dp = opendir ("./");
    if (dp == NULL)
    {
        exit(1);
    }
    while (ep = readdir (dp))
    {
        // printf("\n%d,",ep);
        strcpy(dosyaAdiOkuma,ep->d_name);
        if (isCSV(dosyaAdiOkuma))
        {
            labelBul(dosyaAdiOkuma,label,labelType);
            fRead = fopen(dosyaAdiOkuma,"r");
            //printf("Dosya isleniyor: %s ...\n",dosyaAdiOkuma);
            fgets(tmpSatir,LINESIZE,fRead);

            i = 0;

            if(!yazildi)
            {


                while(tmpSatir[i])
                {

                    if(tmpSatir[i] == ',' || tmpSatir[i] == ';')
                    {

                        argSayisi++;
                        //printf("argSayisi= %d\n",argSayisi);
                        ayrac = tmpSatir[i];
                    }
                    i++;
                }
                i = 1;
                j= 0;
                /**
                 Bir azaltma sebebim sondaki iki kolonun ölçülecek bir yanı olmaması.
                 */
                argSayisi--;
                i=0;
                kacinciKelime=0;
                k=0;
                kelimeUzunlugu=0;
                while(kacinciKelime<argSayisi)
                {
                    if(tmpSatir[i] != ayrac)
                    {
                        alan[kelimeUzunlugu] = tmpSatir[i];
                        printf("%c",alan[kelimeUzunlugu]);
                        kelimeUzunlugu++;
                    }
                    else
                    {
                        alan[kelimeUzunlugu] = '\0';
                        printf("\n");
                        for(k=0; k<ozellikSayisi; k++)
                        {
                            fprintf(fWrite,"@ATTRIBUTE \"%s_%s\" NUMERIC\n",alan,ozellikler[k]);
                        }
                        kelimeUzunlugu=0;
                        kacinciKelime++;
                    }
                    i++;
                }

                for(k=0; k<ozellikSayisi; k++)
                {
                    fprintf(fWrite,"@ATTRIBUTE \"ACC_%s\" NUMERIC\n",ozellikler[k]);
                }

                for(k=0; k<ozellikSayisi; k++)
                {
                    fprintf(fWrite,"@ATTRIBUTE \"GYRO_%s\" NUMERIC\n",ozellikler[k]);
                }
                for(k=0; k<ozellikSayisi; k++)
                {
                    fprintf(fWrite,"@ATTRIBUTE \"MAG_%s\" NUMERIC\n",ozellikler[k]);
                }

                fprintf(fWrite,"@ATTRIBUTE label {");
                labelSayisi--;
                if(labelType == 0){
                    for(i=0; i<labelSayisi; i++)
                    {
                        fprintf(fWrite,"%s,",labels[i]);
                    }
                }
                else if (labelType == 1) {
                    for(i=0; i<labelSayisi1; i++)
                    {
                        fprintf(fWrite,"%s,",labels1[i]);
                    }
                }

                fprintf(fWrite,"}\n\n@DATA\n");


                printf("Arg Sayisi= %d\n",argSayisi);






                printf("\nFrekans Nedir? (hz) ");
                scanf("%d",&frekans);

                printf("\nNe Kadarlik Zaman Araliginin Ozelligini Cikarmak İstersiniz? (milisaniye cinsinden) ");
                scanf("%d",&sure);

                printf("\nAtlama oranini yuzde olarak giriniz(Tam Sayi) ");
                scanf("%d",&atlamaOrani);









                kontrolAdet = (sure*frekans)/1000;
                atlamaMik = (kontrolAdet*atlamaOrani)/100;
                //   ozellikSayisi = (degerSayisi-kontrolAdet)/atlamaMik + 1;
                oklids = (double**) malloc(oklidBoyutu*sizeof(double*));
                doubleMErr(oklids);
                for(i=0; i<oklidBoyutu; i++)
                {
                    oklids[i] = (double*) malloc(kontrolAdet * sizeof(double));
                    doubleDErr(oklids[i]);
                }

                degerler = (double**) malloc(argSayisi * sizeof(double*));
                doubleMErr(degerler);
                for(i=0; i<argSayisi; i++)
                {
                    degerler[i] = (double*) malloc(kontrolAdet * sizeof(double));
                    doubleDErr(degerler[i]);
                }

                yazildi=1;
            }

            degerSayisi = 0;
            r = 0;

            while(fgets(tmpSatir,LINESIZE,fRead))
            {

                if(degerSayisi >= kontrolAdet)
                {
                    degerSayisi = kontrolAdet - atlamaMik;

                    for(x=0; x<oklidBoyutu; x++)
                    {
                        indis = x*3;

                        for(y=0; y<kontrolAdet; y++)
                        {
                            oklidDegeri = degerler[indis][y]*degerler[indis][y] + degerler[indis+1][y]*degerler[indis+1][y] + degerler[indis+2][y]*degerler[indis+2][y];
                            oklids[x][y] = sqrt(oklidDegeri);
                        }
                    }



                    //                    for(x=0; x<argSayisi; x++)
                    //                    {
                    //                        min = minBul(degerler[x]);
                    //                        max = maxBul(degerler[x]);
                    //                        ranj = ranjBul(min,max);
                    //                        minInc = minIncBul(degerler[x]);
                    //                        maxInc = maxIncBul(degerler[x]);
                    //                        minRed = minRedBul(degerler[x]);
                    //                        maxRed = maxRedBul(degerler[x]);
                    //
                    //                        aritmetikOrtalama = ortalamaAritmetikBul(degerler[x]);
                    //                        geometrikOrtalama = ortalamaGeoBul(degerler[x]);
                    //                        harmonikOrtalama = ortalamaHarmonikBul(degerler[x]);
                    //                        kuadratikOrtalama = ortalamaKuadratikBul(degerler[x]);
                    //                        varyans = varyansBul(degerler[x],aritmetikOrtalama);
                    //                        stdSapma = standartSapma(varyans);
                    //                        anlikOrtalamalar(degerler[x],&anlikAritmetikOrt,&anlikGeometrikOrt,&anlikHarmonikOrt,&anlikKuadratikOrt);
                    //                        varyasyonKatSayi = varyasyonKatSayisi(stdSapma,aritmetikOrtalama);
                    //                        modMedianBul(degerler[x],&median,&mod);
                    //                        //printf("\nMin: %lf, Max: %lf,",geometrikOrtalama,varyans);
                    //                        fprintf(fWrite,"%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c",minRed,ayrac,maxRed,ayrac,minInc,ayrac,maxInc,ayrac,min,ayrac,max,ayrac,ranj,ayrac,aritmetikOrtalama,ayrac,geometrikOrtalama,ayrac,harmonikOrtalama,ayrac,kuadratikOrtalama,ayrac,mod,ayrac,median,ayrac,stdSapma,ayrac,varyans,ayrac,anlikAritmetikOrt,ayrac,anlikGeometrikOrt,ayrac,anlikHarmonikOrt,ayrac,anlikKuadratikOrt,ayrac,varyasyonKatSayi,ayrac);
                    //                    }


                    islem(degerler,argSayisi,ayrac,&fWrite);
                    islem(oklids,oklidBoyutu,ayrac,&fWrite);

                    fprintf(fWrite,"%s",label);
                    putc('\n',fWrite);


                }

                j=0;
                for(i=0; i<argSayisi; i++)
                {
                    isaret = 1;
                    tmpDeger = 0;
                    dDonustur = 1;
                    if(tmpSatir[j]== '-')
                    {
                        isaret = -1;
                        j++;
                    }

                    while(tmpSatir[j] != ayrac && tmpSatir[j] != '.')
                    {

                        tmpDeger *= 10;
                        tmpDeger += (tmpSatir[j] - '0');
                        j++;
                    }
                    j++;
                    while(tmpSatir[j] != ayrac)
                    {
                        dDonustur *= 10;
                        tmpDeger = tmpDeger + (tmpSatir[j] - '0')/dDonustur;
                        j++;
                    }
                    degerler[i][r] = tmpDeger*isaret;

                    j++;

                }
                r++;
                r %= kontrolAdet;
                degerSayisi++;
            }
            fclose(fRead);
        }
    }

    printf("\n%d,",ep);

    for(i=0; i<argSayisi; i++)
    {
        free(degerler[i]);

    }


    free(degerler);


    fclose(fWrite);




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

