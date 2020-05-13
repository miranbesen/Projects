#include <stdio.h>
#include <stdlib.h>
#define SIZE  30  // Ogrenci sayýmýz
/* run this program using the console pauser or add your own getch, system("pause") or input loop */


int  *ortalamaHesapla(int *vize1,int *vize2,int *final);
char *harfNotuHesapla(int *ortalama,int *final);
void sayisalIstatislikHesapla(int *ortalama);
void harfIstatistikHesapla(char *harfNotu);

int main() {


	int secim;
	int *ort;
	int i;
	int harfnotu;
	int vize1 [SIZE]={80,67,38,44,64,63,90,100,40,20,15,80,62,85,78,63,52,48,95,70,95,12,67,100,96,87,52,12,36,54};
	int vize2 [SIZE]={80,67,30,40,64,45,90,76,57,85,100,78,74,65,45,56,52,78,95,20,45,12,67,100,45,90,87,63,55,78};
	int final [SIZE]={80,67,100,44,99,63,47,63,40,20,78,65,62,48,78,89,44,69,12,95,69,90,63,100,63,90,88,44,87,99};
	
	
ort=ortalamaHesapla(vize1,vize2,final);    
char * harfNotu = harfNotuHesapla(ort,final); 
sayisalIstatislikHesapla(ort);
harfIstatistikHesapla(harfNotu);
}

int  *ortalamaHesapla(int *vize1,int *vize2,int *final) // vize1 %30, vize2 %20, final %50 alýnýyor. Buna göre ortalama hesaplýyoruz. Her kisi icin
{
	int i;
	int *ort1;
    ort1=(int *)malloc(30*sizeof(int)); // 30 tane int deger icin yer actik.

       
	for(i=0;i<SIZE;i++)
{
	ort1[i]= (vize1[i])*0.3 + (vize2[i])*0.2 + (final[i])*0.5;
	
	printf("%d.ogrenciortalamasi=%d\n",i+1,ort1[i]);		
}
	 return ort1; 
	
}
char *harfNotuHesapla(int *ortalama,int *final) 
{
	char  *harfnotu;
	harfnotu=(char *)malloc(30);
     int i;
     for(i=0;i<30;i++)
     {
     	
     	if(final[i]<=55)
     	harfnotu[i]='F';
     	else if(ortalama[i]>=91 && ortalama[i]<=100)
     	harfnotu[i]='A';
     	else if(ortalama[i]>=81 && ortalama[i]<91)
     	harfnotu[i]='B';
     	else if(ortalama[i]>=71 && ortalama[i]<81)
     	harfnotu[i]='C';
     	else if(ortalama[i]>=61 && ortalama[i]<71)
     	harfnotu[i]='D';
		else if (ortalama[i]>=51 && ortalama[i]<61)
		harfnotu[i]='E';
		else if (ortalama[i]>=00 && ortalama[i]<51 )
		harfnotu[i]='F'; 
     	}
         return harfnotu;
	
		
	}
void sayisalIstatislikHesapla(int *ortalama) // her nottan kac tane oldugunu ekrana bastýrýyoruz.
{
	int i,j;
	int sayac=0;
	int kontrolPrint;
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			if(ortalama[i]==ortalama[j]){
				sayac++;
				kontrolPrint=j;	
			}
		}
		if(i==kontrolPrint) // Bir kez her birini print etmek için boyle yaptýk.
		{
		printf("PUANLAR: %d\t OgrenciSayisi: %d\n",ortalama[i],sayac);
		}
		sayac=0;	
	}
	
}

void harfIstatistikHesapla(char *harfNotu)
{

int a=0,b=0,c=0,d=0,e=0,f=0;
int i;

for(i=0;i<30;i++)
{	
     if(harfNotu[i]=='A')
	a++;
	else if(harfNotu[i]=='B')
	b++;
	else if(harfNotu[i]=='C')
	c++;
	else if(harfNotu[i]=='D')
	d++;
	else if(harfNotu[i]=='E')
	e++;
	else if(harfNotu[i]=='F')
	f++;
	
}

    printf("HARF NOTLARI:   A\t | B\t | C\t | D\t | E\t | F\t \nOGRENCI SAYISI: %d\t | %d\t | %d\t | %d\t | %d\t | %d\t",a,b,c,d,e,f);
    
}
