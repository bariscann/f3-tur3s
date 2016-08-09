#include <stdio.h>
#include <stdlib.h>

#define DUZELTME_ORANI 3
#define THRESHOLD 5
#define ARTI_EKSI 10

int main()	
{

	int i;
	int tahminSayisi;
	int bas,son;
	int aralik;
	int duzeltmeAraligi;
	int max1, max2;
	int maxKordinat1;
	int maxKordinat2;
	int maxFrekans1;
	int maxFrekans2;
	int max2Kontrol;
	int tmpFrekans;
	int tahminiDeger[];
	int duzeltilenDeger[];


	i = 1;
	while((i+aralik)<tahminSayisi)
	{
		baslangic = i-1;
		max1 = tahminiDeger[i-1];
		max2 = tahminiDeger[i-1];
		maxFrekans1 = 1;
		maxFrekans2 = 1;
		tmpFrekans = 1;
		maxKordinat1 = i-1;
		maxKordinat2 = i-1;
		for(j = 1; j < aralik; j++)
		{
			if(tahminiDeger[i]==tahminiDeger[i-1])
			{
				tmpFrekans++;
			}
			else
			{
				if(tmpFrekans>=maxFrekans1)
				{
					maxFrekans1 = tmpFrekans;
					maxKordinat1 = i;
					max1 = tahminiDeger[i-1];
				}
				else
				{
					if(tmpFrekans>=maxFrekans2 && tahminiDeger[i-1] != max1)
					{
						maxFrekans2 = tmpFrekans;
						maxKordinat2 = i;
						max2 = tahminiDeger[i-1];
					}
				}
				tmpFrekans = 1;
			}
			i++;
		}	

		if((maxKordinat2 + ARTI_EKSI) >=  i)
		{
			j = maxKordinat2+1;
			max2Kontrol = 0;
			while((j < tahminSayisi) && (j < (j+2*ARTI_EKSI))
			{
				if(max2 == tahminiDeger[j])
				{
					max2Kontrol++;
				}
				j++;
			}
			if(max2Kontrol > THRESHOLD)
			{
				j = maxKordinat2-maxFrekans2;
				max2Kontrol = THRESHOLD;
				while((max2Kontrol >= THRESHOLD )
				{
					max2Kontrol = 0;
					for(k = j; k > j-ARTI_EKSI; k--)
					{
						if(tahminiDeger[k]==max2)
						{
							max2Kontrol++;
						}
					}
					j -= ARTI_EKSI;
				}
				j += ARTI_EKSI;
				for(k = j; k < i; k++)
				{
					duzeltilenDeger[k] = max2;
				}
				for(k = baslangic; k < j; k++)
				{
					duzeltilenDeger[k] = max1;
				}
			}
		}
		else
		{
			if((maxKordinat2 - maxFrekans2 - ARTI_EKSI) <=  baslangic)
			{
				j = (maxKordinat2 - maxFrekans2 - ARTI_EKSI);
				
				if(j < 0)
				{
					j = 0;	
				}
				
				max2Kontrol = 0;
				while(j <= (maxKordinat2-maxFrekans2))
				{
					if(max2 == tahminiDeger[j])
					{
						max2Kontrol++;
					}
					j++;
				}


				if(max2Kontrol > THRESHOLD)
				{
					j = maxKordinat2;
					max2Kontrol = THRESHOLD;
					while((max2Kontrol >= THRESHOLD )
					{
						max2Kontrol = 0;
						for(k = j; k < j+ARTI_EKSI; k++)
						{
							if(tahminiDeger[k]==max2)
							{
								max2Kontrol++;
							}
						}
						j += ARTI_EKSI;
					}
					j -= ARTI_EKSI;
					for(k = baslangic; k < j; k++)
					{
						duzeltilenDeger[k] = max2;
					}
					for(k = j; k < i; k++)
					{
						duzeltilenDeger[k] = max1;
					}
				}
			}
			else
			{
				for(k = baslangic; k < i; k++)
					{
						duzeltilenDeger[k] = max1;
					}
			}	
		}
		i++;
	}

	for(i = 0; i < tahminSayisi; i+=aralik)
	{
		


	}
















	return 0;
}