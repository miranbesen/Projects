#include <stdio.h>
#include <stdlib.h>
#include<string.h>
struct hasta{
	int hastano;
	char hastaAdi[50];
	int hastaYasi;
	int odaNo;
	char odakayittarih[10];
	int ilacNo;
    char ilacadi[50];
    int gunlukilacadet;
    
}bilgi;

int menu(void);
void ekle();
void sil();
void ara();
void listele();
void guncelle();

int main()
{
	FILE *d;
	d=fopen("hastane.txt","a+");


	int secenek;
	printf("yapmak istediginiz islemi seciniz lutfen:\n");

	while(secenek!=6)
{
	

	secenek=menu();
	switch(secenek){
		case 1:
			ekle();
			break;
		case 2:
			sil();
			break;
		case 3:
			ara();
			break;
		case 4:
			listele();
			break;
		case 5:
			guncelle();
			break;
			case 6:
				exit(0);
		default :
			printf("yanlis bir tus girdiniz\n<otomatik  cikis islemi gerceklesiyor>\n");
			exit (0);
		
	}
}
}

int menu(void) {
	int sec;
	printf("\n 1-ekle");
	printf("\n 2-sil");
	printf("\n 3-ara");
	printf("\n 4-listele");
	printf("\n 5-guncelle");
	printf("\n 6-cikis\n");
	scanf("%d",&sec);
	return sec;
	
}

void ekle(){
	struct hasta bilgi,temp;	
	FILE *d;
	d=fopen("hastane.txt","r+");
	rewind(d);
      int hastaNo;
      printf("Hasta no:  ");
      scanf("%d",&hastaNo);
      printf("Hasta adi:  ");
      scanf("%s",bilgi.hastaAdi);
      printf("Hasta yasi:  ");
      scanf("%d",&bilgi.hastaYasi);
      printf("Hasta oda No:  ");
      scanf("%d",&bilgi.odaNo);
      printf("Hasta oda kayit tarihi:  ");
      scanf("%s",bilgi.odakayittarih);
      printf("Hasta ilac No:  ");
      scanf("%d",&bilgi.ilacNo);
      printf("Hasta ilacinin adi:  ");
      scanf("%s",bilgi.ilacadi);
      printf("Hasta gunluk ilac adedi:  ");
      scanf("%d",&bilgi.gunlukilacadet);
      fseek(d,(hastaNo-1)*sizeof(struct hasta),SEEK_SET);
      fread(&temp,sizeof(struct hasta),1,d);
      if(temp.hastano==0){
      	bilgi.hastano=hastaNo;
      	fseek(d,(hastaNo-1)*sizeof(struct hasta),SEEK_SET);
      	fwrite(&bilgi,sizeof(bilgi),1,d);
      	printf("kayit eklendi\n");
	  }else{
	  	printf("kayit zaten mevcut\n");
	  }
      
      
	  fclose(d);
	
}

void sil() {
    int hasNo;
    FILE *d;
	d=fopen("hastane.txt","w");
	struct hasta bilgi, bos={0,"",0,0,"",0,"",0};

	
	printf("silmek istediginiz hastanin nosunu giriniz lutfen\n");
	scanf("%d",&hasNo);
	
	fseek(d,(hasNo-1)*sizeof(struct hasta),SEEK_SET);
	fread(&bilgi,sizeof(bilgi),1,d);
	if(bilgi.hastano!=0){
		fseek(d,(hasNo-1)*sizeof(struct hasta),SEEK_SET);
		fwrite(&bos,sizeof(bos),1,d);
		printf("kayit silindi\n");
	}
	else 
		printf("silmek istediginiz hasta no bulunamadi\n");
	
	fclose(d);
}
	
void listele(){
	struct hasta bilgi;

	FILE *d;
	d=fopen("hastane.txt","r");
	rewind(d);
	printf("%s | %s |%s  | %s | %s | %s |  %s  | %s\n ","hastano","hastaAdi","hastaYasi","odaNo","odakayittarih","ilacNo","ilacadi","gunlukilacadet");
	while(!feof(d))
	{	
		fread(&bilgi,sizeof(bilgi),1,d);
		if(bilgi.hastano!=0)
			printf(" %-3d    %-10s     %-2d       %-5d      %-3s     %-5d    %-10s   %-20d\n",bilgi.hastano,bilgi.hastaAdi,bilgi.hastaYasi,bilgi.odaNo,bilgi.odakayittarih,bilgi.ilacNo,bilgi.ilacadi,bilgi.gunlukilacadet);
	}
	
	fclose(d);
	
}

void ara() {

	struct hasta bilgi;
	
	FILE *d;
	d=fopen("hastane.txt","r");
	int hasNo;
	rewind(d);
	printf("aramak istediginiz hastaNoyu giriniz\n");
	scanf("%d",&hasNo);
		fseek(d,(hasNo-1)*sizeof(struct hasta),SEEK_SET);
	    fread(&bilgi,sizeof(bilgi),1,d);
	    	if(bilgi.hastano!=0)
			printf("%d %s %d %d %s %d %s %d\n",bilgi.hastano,bilgi.hastaAdi,bilgi.hastaYasi,bilgi.odaNo,bilgi.odakayittarih,bilgi.ilacNo,bilgi.ilacadi,bilgi.gunlukilacadet);
	else 
	printf("aradiginiz kayit bulunamadi\n");

	fclose(d);
	
}

void guncelle(){
	

	struct hasta bilgi, bos={0,"",0,0,"",0,"",0};
	
	FILE *d;
	d=fopen("hastane.txt","r+");
	rewind(d);
	int hasNo;
	printf("guncellemek istediginiz hastano yu giriniz\n");
	scanf("%d",&hasNo);
	fseek(d,(hasNo-1)*sizeof(struct hasta),SEEK_SET);
	fread(&bilgi,sizeof(bilgi),1,d);
		if(bilgi.hastano!=0){
		fseek(d,(hasNo-1)*sizeof(struct hasta),SEEK_SET);
		fwrite(&bos,sizeof(bos),1,d);
		bilgi.hastano=hasNo;
		printf("Hasta adi:  ");
      scanf("%s",bilgi.hastaAdi);
      printf("Hasta yasi:  ");
      scanf("%d",&bilgi.hastaYasi);
      printf("Hasta oda No:  ");
      scanf("%d",&bilgi.odaNo);
      printf("Hasta oda kayit tarihi:  ");
      scanf("%s",bilgi.odakayittarih);
      printf("Hasta ilac No:  ");
      scanf("%d",&bilgi.ilacNo);
      printf("Hasta ilacinin adi:  ");
      scanf("%s",bilgi.ilacadi);
      printf("Hasta gunluk ilac adedi:  ");
      scanf("%d",&bilgi.gunlukilacadet);
    fseek(d,(hasNo-1)*sizeof(struct hasta),SEEK_SET);
    fwrite(&bilgi,sizeof(bilgi),1,d);
    
		}
	else 
		printf("guncellemek istediginiz hasta no bulunamadi\n");
		
	fclose(d);
	
	
}

