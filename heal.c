#include <stdio.h>
#include <stdlib.h>

#define DUZELTME_ORANI 3
#define THRESHOLD 5

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
	int maxKontrol;
	int tmpFrekans;
	int tahminiDeger[];
	int duzeltilenDeger[];


	i = 1;
	while(i<tahminSayisi)
	{
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
		
	}

	for(i = 0; i < tahminSayisi; i+=aralik)
	{
		


	}
















	return 0;
}