#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <errno.h>


#define oklidBoyutu 3
#define LINESIZE 10000
#define MAX_UC -100000
#define MIN_UC 100000
#define OZELLIK_SAYISI 17
#define OKLID_BOYUTU 3


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
    if(labelType == 1)
    {
        while(dosyaAdi[i] != '_')
        {
            label[i] = dosyaAdi[i];
            i++;
        }
        label[i] = '\0';
        
    }
    else if (labelType == 0)
    {
        while(dosyaAdi[i] != '_')
        {
            i++;
        }
        i++;
        while(dosyaAdi[i] != '_')
        {
            label[j] = dosyaAdi[i];
            i++;
            j++;
        }
        label[j] = dosyaAdi[i]; // _'da kalmamasi icin
        i++;
        j++;
        while(dosyaAdi[i] != '_')
        {
            label[j] = dosyaAdi[i];
            i++;
            j++;
        }
        label[j] = '\0';
    }
    
}

double ortalamaAritmetikBul(double *degerler,OZELLIK_MIN *fMin, OZELLIK_MAX *fMax)
{
    int i;
    int ozellikIndisi = 7;
    double toplam = 0;
    double ort;
    for(i=0; i<kontrolAdet; i++)
    {
        toplam += degerler[i];
    }
    if(toplam == HUGE_VAL)
    {
        printf("\n---------------------------------\n");
        for(i=0; i<kontrolAdet; i++)
        {
            printf("%f,",degerler[i]);
        }
        exit(0);
    }
    ort = toplam/kontrolAdet;
    
    if(ort>(fMax->ozellik[ozellikIndisi]))
    {
        fMax->ozellik[ozellikIndisi] = ort;
    }
    
    if(ort<(fMin->ozellik[ozellikIndisi]))
    {
        fMin->ozellik[ozellikIndisi] = ort;
    }
    
    
    
    
    return ort;
    
}


double ortalamaHarmonikBul(double *degerler,OZELLIK_MIN *fMin, OZELLIK_MAX *fMax)
{
    int i;
    int ozellikIndisi = 8;
    double toplam = 0;
    double ort;
    
    for(i=0; i<kontrolAdet; i++)
    {
        toplam += 1/degerler[i];
    }
    
    
    
    ort = kontrolAdet/toplam;
    
    if(ort>(fMax->ozellik[ozellikIndisi]))
    {
        fMax->ozellik[ozellikIndisi] = ort;
    }
    
    if(ort<(fMin->ozellik[ozellikIndisi]))
    {
        fMin->ozellik[ozellikIndisi] = ort;
    }
    
    
    return ort;
    
    
}

double ortalamaKuadratikBul(double *degerler,OZELLIK_MIN *fMin, OZELLIK_MAX *fMax)
{
    int i;
    int ozellikIndisi = 9;
    double toplam = 0;
    double ort;
    for(i=0; i<kontrolAdet; i++)
    {
        toplam += (degerler[i]*degerler[i]);
    }
    
    ort = sqrt(toplam/kontrolAdet);
    
    if(ort>(fMax->ozellik[ozellikIndisi]))
    {
        fMax->ozellik[ozellikIndisi] = ort;
    }
    
    if(ort<(fMin->ozellik[ozellikIndisi]))
    {
        fMin->ozellik[ozellikIndisi] = ort;
    }
    
    
    return ort;
}

double standartSapma(double varyans,OZELLIK_MIN *fMin, OZELLIK_MAX *fMax)
{
    int ozellikIndisi = 12;
    double stdSapma = sqrt(varyans);
    
    if(stdSapma>(fMax->ozellik[ozellikIndisi]))
    {
        fMax->ozellik[ozellikIndisi] = stdSapma;
    }
    
    if(stdSapma<(fMin->ozellik[ozellikIndisi]))
    {
        fMin->ozellik[ozellikIndisi] = stdSapma;
    }
    
    
    return stdSapma;
}



double varyansBul(double *degerler,double ortalama,OZELLIK_MIN *fMin, OZELLIK_MAX *fMax)
{
    int i;
    int ozellikIndisi = 13;
    double toplam = 0;
    double varyans;
    
    for(i=0; i<kontrolAdet; i++)
    {
        toplam += pow((degerler[i]-ortalama),2);
    }
    
    varyans = toplam/kontrolAdet;
    
    if(varyans>(fMax->ozellik[ozellikIndisi]))
    {
        fMax->ozellik[ozellikIndisi] = varyans;
    }
    
    if(varyans<(fMin->ozellik[ozellikIndisi]))
    {
        fMin->ozellik[ozellikIndisi] = varyans;
    }
    
    
    
    return varyans;
    
}


void anlikOrtalamalar(double *degerler,int baslangic, double *anlikAritmetikOrt,double *anlikKuadratikOrt,OZELLIK_MIN *fMin, OZELLIK_MAX *fMax)
{
    int i;
    int ozellikIndisiA = 14;
    int ozellikIndisiK = 15;
    
    double fark;
    double aritmatikToplam , harmonikToplam , kuadratikToplam ;
    aritmatikToplam = harmonikToplam = kuadratikToplam = 0;
    int j = baslangic;
    baslangic++;
    baslangic %= kontrolAdet;
    
    for(i=1; i<kontrolAdet; i++)
    {
        
        fark = degerler[baslangic]-degerler[j];
        aritmatikToplam += fark;
        harmonikToplam += 1/fark;
        kuadratikToplam += fark*fark;
        
        j = baslangic;
        baslangic++;
        baslangic %= kontrolAdet;
        
    }
    
    *anlikAritmetikOrt = aritmatikToplam/kontrolAdet;
    if(*anlikAritmetikOrt>(fMax->ozellik[ozellikIndisiA]))
    {
        fMax->ozellik[ozellikIndisiA] = *anlikAritmetikOrt;
    }
    
    if(*anlikAritmetikOrt<(fMin->ozellik[ozellikIndisiA]))
    {
        fMin->ozellik[ozellikIndisiA] = *anlikAritmetikOrt;
    }
    
    
    *anlikKuadratikOrt = sqrt(kuadratikToplam/kontrolAdet);
    if(*anlikKuadratikOrt>(fMax->ozellik[ozellikIndisiK]))
    {
        fMax->ozellik[ozellikIndisiK] = *anlikKuadratikOrt;
    }
    
    if(*anlikKuadratikOrt<(fMin->ozellik[ozellikIndisiK]))
    {
        fMin->ozellik[ozellikIndisiK] = *anlikKuadratikOrt;
    }
    
    
}


double varyasyonKatSayisi(double stdSapma,double ortalama,double min,double max,OZELLIK_MIN *fMin, OZELLIK_MAX *fMax)
{
    int ozellikIndisi = 16;
    double vk;
    
    if (ortalama == 0)
    {
        if(stdSapma>0)
        {
            vk = max;
        }
        else if (stdSapma<0)
        {
            vk = min;
        }
        else
        {
            vk = 0;
        }
    }
    else
    {
        vk = stdSapma/ortalama;
    }
    
    if(vk>(fMax->ozellik[ozellikIndisi]))
    {
        fMax->ozellik[ozellikIndisi] = vk;
    }
    
    if(vk<(fMin->ozellik[ozellikIndisi]))
    {
        fMin->ozellik[ozellikIndisi] = vk;
    }
    
    
    return vk;
}


double minBul(double *degerler,OZELLIK_MIN *fMin, OZELLIK_MAX *fMax)
{
    
    int i;
    int ozellikIndisi = 4;
    double min;
    min = degerler[0];
    
    for(i=1; i<kontrolAdet; i++)
    {
        if (degerler[i]<min)
        {
            min = degerler[i];
        }
        
    }
    
    if(min>(fMax->ozellik[ozellikIndisi]))
    {
        fMax->ozellik[ozellikIndisi] = min;
    }
    
    if(min<(fMin->ozellik[ozellikIndisi]))
    {
        fMin->ozellik[ozellikIndisi] = min;
    }
    
    
    return min;
    
}

double maxBul(double *degerler,OZELLIK_MIN *fMin, OZELLIK_MAX *fMax)
{
    int i;
    int ozellikIndisi = 5;
    double max;
    max = degerler[0];
    
    for(i=1; i<kontrolAdet; i++)
    {
        if (degerler[i]>max)
        {
            max = degerler[i];
        }
        
    }
    
    if(max>(fMax->ozellik[ozellikIndisi]))
    {
        fMax->ozellik[ozellikIndisi] = max;
    }
    
    if(max<(fMin->ozellik[ozellikIndisi]))
    {
        fMin->ozellik[ozellikIndisi] = max;
    }
    
    
    return max;
}



double ranjBul(double min, double max,OZELLIK_MIN *fMin, OZELLIK_MAX *fMax)
{
    int ozellikIndisi = 6;
    double ranj;
    ranj = max - min;
    
    if(ranj>(fMax->ozellik[ozellikIndisi]))
    {
        fMax->ozellik[ozellikIndisi] = ranj;
    }
    
    if(ranj<(fMin->ozellik[ozellikIndisi]))
    {
        fMin->ozellik[ozellikIndisi] = ranj;
    }
    
    
    return ranj;
}

double minIncBul(double *degerler,int baslangic,OZELLIK_MIN *fMin, OZELLIK_MAX *fMax)  //minimum artis
{
    
    int i;
    int ozellikIndisi = 2;
    
    double min = 100000.0,fark;
    int j = baslangic;
    baslangic++;
    baslangic %= kontrolAdet;
    
    for(i = 1; i<kontrolAdet; i++)
    {
        fark = degerler[baslangic]-degerler[j];
        if ((fark>0) && (fark<min))
        {
            min = fark;
        }
        j = baslangic;
        baslangic++;
        baslangic %= kontrolAdet;
        
    }
    
    if(min == 100000.0)
    {
        min = 0;
    }
    
    if(min>(fMax->ozellik[ozellikIndisi]))
    {
        fMax->ozellik[ozellikIndisi] = min;
    }
    
    if(min<(fMin->ozellik[ozellikIndisi]))
    {
        fMin->ozellik[ozellikIndisi] = min;
    }
    
    
    return min;
}

double maxIncBul(double *degerler,int baslangic,OZELLIK_MIN *fMin, OZELLIK_MAX *fMax)  //maximum artis
{
    
    int i;
    int ozellikIndisi = 3;
    
    double max = 0,fark;
    int j = baslangic;
    baslangic++;
    baslangic %= kontrolAdet;
    
    for(i = 1; i<kontrolAdet; i++)
    {
        fark = degerler[baslangic]-degerler[j];
        if ((fark>0) && (fark>max))
        {
            max = fark;
        }
        j = baslangic;
        baslangic++;
        baslangic %= kontrolAdet;
        
    }
    
    if(max>(fMax->ozellik[ozellikIndisi]))
    {
        fMax->ozellik[ozellikIndisi] = max;
    }
    
    if(max<(fMin->ozellik[ozellikIndisi]))
    {
        fMin->ozellik[ozellikIndisi] = max;
    }
    
    
    return max;
}




double minRedBul(double *degerler,int baslangic,OZELLIK_MIN *fMin, OZELLIK_MAX *fMax)  //minimum azalis
{
    int i;
    int ozellikIndisi = 0;
    
    double min = -100000.0,fark;
    int j = baslangic;
    baslangic++;
    baslangic %= kontrolAdet;
    
    for(i = 1; i<kontrolAdet; i++)
    {
        fark = degerler[baslangic]-degerler[j];
        if ((fark<0) && (fark>min))
        {
            min = fark;
        }
        j = baslangic;
        baslangic++;
        baslangic %= kontrolAdet;
        
    }
    if(min == -100000.0)
    {
        min = 0;
    }
    
    if(min>(fMax->ozellik[ozellikIndisi]))
    {
        fMax->ozellik[ozellikIndisi] = min;
    }
    
    if(min<(fMin->ozellik[ozellikIndisi]))
    {
        fMin->ozellik[ozellikIndisi] = min;
    }
    
    return min;
}



double maxRedBul(double *degerler,int baslangic,OZELLIK_MIN *fMin, OZELLIK_MAX *fMax)  //maximum artis
{
    int i;
    int ozellikIndisi = 1;
    
    double max = 0,fark;
    int j = baslangic;
    baslangic++;
    baslangic %= kontrolAdet;
    
    for(i = 1; i<kontrolAdet; i++)
    {
        fark = degerler[baslangic]-degerler[j];
        if ((fark<0) && (fark<max))
        {
            max = fark;
        }
        j = baslangic;
        baslangic++;
        baslangic %= kontrolAdet;
        
    }
    
    if(max>(fMax->ozellik[ozellikIndisi]))
    {
        fMax->ozellik[ozellikIndisi] = max;
    }
    
    if(max<(fMin->ozellik[ozellikIndisi]))
    {
        fMin->ozellik[ozellikIndisi] = max;
    }
    
    
    return max;
    
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

void modMedianBul (double *degerler,double *median, double *mod,OZELLIK_MIN *fMin, OZELLIK_MAX *fMax)
{
    
    int i,j=0;
    int ozellikIndisiMod = 10;
    int ozellikIndisiMedian = 11;
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
    
    if(*median>(fMax->ozellik[ozellikIndisiMedian]))
    {
        fMax->ozellik[ozellikIndisiMedian] = *median;
    }
    
    if(*median<(fMin->ozellik[ozellikIndisiMedian]))
    {
        fMin->ozellik[ozellikIndisiMedian] = *median;
    }
    
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
    if(*mod>(fMax->ozellik[ozellikIndisiMod]))
    {
        fMax->ozellik[ozellikIndisiMod] = *mod;
    }
    
    if(*mod<(fMin->ozellik[ozellikIndisiMod]))
    {
        fMin->ozellik[ozellikIndisiMod] = *mod;
    }
    
    free(tmp);
}




void islem(double **degerler,int baslangic, int argSayisi, char ayrac, FILE **fWrite,OZELLIK_MIN *fMin, OZELLIK_MAX *fMax)
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
    double harmonikOrtalama;
    double kuadratikOrtalama;
    double stdSapma;
    double varyans;
    double anlikAritmetikOrt;
    double anlikHarmonikOrt;
    double anlikKuadratikOrt;
    double varyasyonKatSayi;
    
    for(x=0; x<argSayisi; x++)
    {
        min = minBul(degerler[x],(fMin+x),(fMax+x));
        max = maxBul(degerler[x],(fMin+x),(fMax+x));
        ranj = ranjBul(min,max,(fMin+x),(fMax+x));
        minInc = minIncBul(degerler[x],baslangic,(fMin+x),(fMax+x));
        maxInc = maxIncBul(degerler[x],baslangic,(fMin+x),(fMax+x));
        minRed = minRedBul(degerler[x],baslangic,(fMin+x),(fMax+x));
        maxRed = maxRedBul(degerler[x],baslangic,(fMin+x),(fMax+x));
        
        aritmetikOrtalama = ortalamaAritmetikBul(degerler[x],(fMin+x),(fMax+x));
        harmonikOrtalama = ortalamaHarmonikBul(degerler[x],(fMin+x),(fMax+x));
        kuadratikOrtalama = ortalamaKuadratikBul(degerler[x],(fMin+x),(fMax+x));
        varyans = varyansBul(degerler[x],aritmetikOrtalama,(fMin+x),(fMax+x));
        stdSapma = standartSapma(varyans,(fMin+x),(fMax+x));
        anlikOrtalamalar(degerler[x],baslangic,&anlikAritmetikOrt,&anlikKuadratikOrt,(fMin+x),(fMax+x));
        varyasyonKatSayi = varyasyonKatSayisi(stdSapma,aritmetikOrtalama,min,max,(fMin+x),(fMax+x));
        modMedianBul(degerler[x],&median,&mod,(fMin+x),(fMax+x));
        //printf("\nMin: %lf, Max: %lf,",geometrikOrtalama,varyans);
        
        fprintf(*fWrite,"%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c%lf%c",minRed,ayrac,maxRed,ayrac,minInc,ayrac,maxInc,ayrac,min,ayrac,max,ayrac,ranj,ayrac,aritmetikOrtalama,ayrac,harmonikOrtalama,ayrac,kuadratikOrtalama,ayrac,mod,ayrac,median,ayrac,stdSapma,ayrac,varyans,ayrac,anlikAritmetikOrt,ayrac,anlikKuadratikOrt,ayrac,varyasyonKatSayi,ayrac);
        //fprintf(*fWrite,"%lf%c",min,ayrac);
    }
    
}

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
    
    
    int i,j,k,x,y;
    int degerlerMin_MaxBoyut;
    int indis;
    double oklidDegeri;
    
    int quoteCount=0;
    char line[LINESIZE];
    char stringToAdd[] = " NORM\" NUMERIC\n";
    double tmpDouble[OZELLIK_SAYISI];
    
    
    int r ;
    int argSayisi = 0;
    char dosyaAdiOkuma[100];
    char dosyaAdiYazma[100] ;
    char tmpSatir[LINESIZE];
    char ayrac;
    int kelimeUzunlugu;
    
    double **degerler;
    double **oklids;
    
    int degerSayisi;
    double tmpDeger = 0.0;
    double dDonustur = 1.0;
    double isaret = 1.0;
    
    
    int sure;
    int frekans;
    int atlamaOrani;
    int labelType = 0;
    
    char *ozellikler[] = {"MINRED","MAXRED","MININC","MAXINC","MINVAL","MAXVAL", "RANGE",
        "ARTMEAN","HARMEAN", "QUADMEAN", "MOD", "MEDIAN", "STD","VAR", "IEARTMEAN",
        "IEQUADMEAN", "COV"
    };
    
    // char *labels[] = {"walking","car","bus","tram","metro1","metro2","marmaray","metrobus","bicycle","ferry","n"};
    char *labels[] = {"walking_walking","minibus_sitting","minibus_standing","car_car","bus_sitting","tram_sitting","metroH_sitting","metroK_sitting","marmaray_sitting","metrobus_sitting","ferry_sitting","bus_standing","tram_standing","metroH_standing","metroK_standing","marmaray_standing","metrobus_standing","ferry_standing"};
    
    char *labels1[]= {"walking","minibus","car","bus","tram","metro","metrobus","ferry"};
    
    char label[100];
    char alan[100];
    int kacinciKelime;
    int yazildi=0;
    int labelSayisi = 18;
    int labelSayisi1= 8;
    
    
    printf("Ozellik dosyasinin adini giriniz: ");
    scanf("%s",dosyaAdiYazma);
    
    FILE *fRead;
    FILE *fWrite;
    FILE *fRead1;
    FILE *fWrite1;
    
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
    while ((ep = readdir (dp)))
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
                        for(k=0; k<OZELLIK_SAYISI; k++)
                        {
                            fprintf(fWrite,"@ATTRIBUTE \"%s_%s\" NUMERIC\n",alan,ozellikler[k]);
                        }
                        kelimeUzunlugu=0;
                        kacinciKelime++;
                    }
                    i++;
                }
                
                for(k=0; k<OZELLIK_SAYISI; k++)
                {
                    fprintf(fWrite,"@ATTRIBUTE \"ACC_%s\" NUMERIC\n",ozellikler[k]);
                }
                
                for(k=0; k<OZELLIK_SAYISI; k++)
                {
                    fprintf(fWrite,"@ATTRIBUTE \"GYRO_%s\" NUMERIC\n",ozellikler[k]);
                }
                for(k=0; k<OZELLIK_SAYISI; k++)
                {
                    fprintf(fWrite,"@ATTRIBUTE \"MAG_%s\" NUMERIC\n",ozellikler[k]);
                }
                
                fprintf(fWrite,"@ATTRIBUTE label {");
                labelSayisi--;
                if(labelType == 0)
                {
                    for(i=0; i<labelSayisi-1; i++)
                    {
                        fprintf(fWrite,"%s,",labels[i]);
                    }
                    fprintf(fWrite,"%s",labels[i]);
                }
                else if (labelType == 1)
                {
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
                //   OZELLIK_SAYISI = (degerSayisi-kontrolAdet)/atlamaMik + 1;
                degerlerMin_MaxBoyut = argSayisi + oklidBoyutu;
                fMax = (OZELLIK_MAX *) malloc(degerlerMin_MaxBoyut*sizeof(OZELLIK_MAX));
                for(i = 0; i < degerlerMin_MaxBoyut; i++)
                {
                    for(j = 0; j < OZELLIK_SAYISI; j++)
                    {
                        fMax[i].ozellik[j] = MAX_UC;
                    }
                    
                }
                
                fMin = (OZELLIK_MIN *) malloc(degerlerMin_MaxBoyut*sizeof(OZELLIK_MIN));
                for(i=0; i<degerlerMin_MaxBoyut; i++)
                {
                    for(j = 0; j < OZELLIK_SAYISI; j++)
                    {
                        fMin[i].ozellik[j] = MIN_UC;
                    }
                }
                
                
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
                    
                    
                    islem(degerler,r,argSayisi,ayrac,&fWrite,fMin,fMax);
                    islem(oklids,r,oklidBoyutu,ayrac,&fWrite,(fMin+argSayisi),(fMax+argSayisi));
                    
                    fprintf(fWrite,"%s",label);
                    putc('\n',fWrite);
                    
                    
                }
                
                j=0;
                for(i=0; i<argSayisi; i++)
                {
                    isaret = 1.0;
                    tmpDeger = 0.0;
                    dDonustur = 1.0;
                    if(tmpSatir[j]== '-')
                    {
                        isaret = -1.0;
                        j++;
                    }
                    
                    while(tmpSatir[j] != ayrac && tmpSatir[j] != '.')
                    {
                        
                        tmpDeger *= 10;
                        tmpDeger += (tmpSatir[j] - '0');
                        j++;
                    }
                    if(tmpSatir[j] != ayrac)
                        j++;
                    while(tmpSatir[j] != ayrac)
                    {
                        dDonustur *= 10;
                        tmpDeger = tmpDeger + (tmpSatir[j] - '0')/dDonustur;
                        j++;
                    }
                    // printf("%f,",tmpDeger*isaret);
                    degerler[i][r] = tmpDeger*isaret;
                    
                    j++;
                    
                }
                // printf("\n");
                r++;
                r %= kontrolAdet;
                degerSayisi++;
            }
            //printf("\n\n");
            
            fclose(fRead);
        }
    }
    
    
    
    for(i=0; i<argSayisi; i++)
    {
        free(degerler[i]);
        
    }
    
    
    free(degerler);
    
    
    fclose(fWrite);
    
    
    
    
    
    fRead1 = fopen(dosyaAdiYazma, "r");
    
    // strcat(dosyaAdiYazma,"_normalized.arff");
    fWrite1 = fopen("ali.arff", "wt");
    
    fgets(line, LINESIZE, fRead1);
    fputs(line,fWrite1);
    //printf("%s",line);
    // fputc('\n',fWrite);
    fgets(line, LINESIZE, fRead1);
    fputs(line,fWrite1);
    
    
    //i=1;
    int adimSayisi;
    adimSayisi = (argSayisi+OKLID_BOYUTU)*OZELLIK_SAYISI;
    for(i=0; i<adimSayisi; i++)
    {
        fgets(line, LINESIZE, fRead1);
        printf("%s",line);
        fputs(line,fWrite1);
        
    }
    fgets(line, LINESIZE, fRead1);
    printf("%s",line);
    fputs(line,fWrite1);
    //fputc("\n",fWrite);
    fgets(line, LINESIZE, fRead1);
    fputs(line,fWrite1);
    fgets(line, LINESIZE, fRead1);
    fputs(line,fWrite1);
    
    
    
    
    
    
    while(fgets(tmpSatir,LINESIZE,fRead1))
    {
        
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
                
                while(tmpSatir[j] != ayrac && tmpSatir[j] != '.')
                {
                    
                    tmpDeger *= 10;
                    tmpDeger += (tmpSatir[j] - '0');
                    j++;
                }
                if(tmpSatir[j] != ayrac)
                    j++;
                while(tmpSatir[j] != ayrac)
                {
                    dDonustur *= 10;
                    tmpDeger = tmpDeger + (tmpSatir[j] - '0')/dDonustur;
                    j++;
                }
                // printf("%f,",tmpDeger*isaret);
                tmpDouble[y] = tmpDeger*isaret;
                
                
                
                
                j++;
            }
            //             for(j=0;j<OZELLIK_SAYISI;j++){
            //                printf("%lf,",tmpDouble[j]);
            //             }
            //             printf("\n%lf,%lf",fMin[i].ozellik[i],fMax[i].ozellik[i]);
            //             exit(0);
            normalize(tmpDouble,fMin[i],fMax[i],&fWrite1);
            
            
            
            
        }
        fprintf(fWrite1,"%s",label);
        putc('\n',fWrite1);
    }
    
    
    //        for(i=0; i<degerlerMin_MaxBoyut; i++)
    //        {
    //            printf("\n%f,",fMax[i].ozellik[4]);
    //
    //        }
    
    fclose(fRead1);
    fclose(fWrite1);
    
    
    
    
    
    //        for(i=0; i<degerlerMin_MaxBoyut; i++)
    //        {
    //            for(j = 0; j < OZELLIK_SAYISI; j++)
    //            {
    //
    //            }
    //
    //        }
    
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