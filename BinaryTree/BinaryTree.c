#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_HEIGHT 1000
#define INFINITY (1<<20) 

//Ad Ve Soyad: Miran Besen || Öðrenci No: 190401080

struct dugum {
    int icerik;
    struct dugum *sol;
    struct dugum *sag;
};

struct dugum* dugum_olustur(int icerik){
	
	struct dugum *d = (struct dugum*)malloc(sizeof(struct dugum));
	if(d==NULL){
		printf(" Bellekte yer ayrilamadý otomatik cikis yapiliyor...\n ");
		exit(1);
	}

	d->icerik=icerik; 
	d->sol=NULL;
	d->sag=NULL;
	
	return d;

}
//----------------------------------------------------------------Silme Kismi-------------------------------------------------------------------------------------
struct dugum *deleteNode(struct dugum *root, int key){
	
	if(root==NULL){
		printf("Silinecek eleman kalmamistir veya agamicimizda boyle bir eleman yoktur ...\n");
		return root;
	}
	
	if(key> root->icerik){ //eger silmek istedigimiz eleman o anki dügümümüzden büyük ise saga devam ediyoruz.
		root->sag=deleteNode(root->sag,key);
	}
	else if(key<root->icerik){ //eger silmek istedigimiz eleman o anki dügümümüzden kucuk ise saga devam ediyoruz.
		root->sol=deleteNode(root->sol,key);
	}
	else{ //Elemana eristikten sonra kontrollerimizi yapýyoruz.
		if(root->sol==NULL && root->sag==NULL){ // sol ve sagýnda eleman yok ise dugumun kendisini cýkartýyoruz.
			free(root);
			return NULL;
		}
		
		if(root->sol==NULL){ //solu bos ise
			struct dugum *gecici=root->sag;
			free(root);
			return gecici;
			
		}
		else if(root->sag==NULL){ //sag tarafý bos ise 
			struct dugum *gecici=root->sol;
			free(root);
			return gecici;
		
		}
		else{ //Eger sag ve solunda child'ý var ise  bu parentin yerine gecicek degerin agacin duzenini bozmamasi gerekir, bunu da saglamak icin sagýnýn en solundaki elemana gidiyoruz.
		
		struct dugum *kokSagTaraf=root->sag;
		struct dugum *gecici=kokSagTaraf; 
		
		while (gecici && gecici->sol != NULL)// sagýnýn en solu yerine gecicek. 
    {
		gecici = gecici->sol; 
  	}
		root->icerik= gecici->icerik;
		root->sag=deleteNode(root->sag,gecici->icerik);		
	
	}
	}
	
	return root;	
	
}

//--------------------------------------------------------------Ekleme Kismi------------------------------------------------------------------
struct dugum *insert(struct dugum *root, int key) 
{ 
    //keyi içeren düðümümüzü oluþturduk.
    struct dugum* newnode = dugum_olustur(key); 
  
    struct dugum* x = root; 
  
  
    struct dugum* y = NULL; 
  
    while (x != NULL) { //þimdi eklememiz gereken  yeri buluyoruz.
        y = x; 
        if (key < x->icerik) //Eger key kucuk ise x imizi sol tarafa dogru agactan hareket ettiriyoruz. 
            x = x->sol; 
        else
            x = x->sag;  //Eger keyimiz buyuk ise sag tarafa hareket ediyoruz.
    } 
  
   
    if (y == NULL)  // root eger null olursa x' imiz while a girmez ve direk kökümüz oluþturdugumuz dügüm olur.
        y = newnode; 
  
    //eger keyimiz ulastigimiz dügümden kücük ise sola yerlesiyor. 
    else if (key < y->icerik)  
        y->sol = newnode; 
  
    // eðer keyimiz ulastýgýmýz dügümden buyuk ise sagýna yerlesiyor.
    else
        y->sag = newnode; 
  
    //yeni dügümün eklendigi iþaretci dönüyor.
    return y; 
} 
  

//--------------------------------------------------------------Listeleme Kismi---------------------------------------------------------------

typedef struct asciinode_struct asciinode;


int gap = 3; //sol ve sag dugum arasý bosluk ayarlama.

int print_next; // bir sonraki olan dugumu ayný duzeyde yazdýrmak için kullanýlýr. (Bu yazdýrýlan bir sonraki karakterin x koordinatý)

int MIN(int X, int Y) { // iki tane integer degeri kýyaslayýp minimumu yolluyor.
    return ((X) < (Y)) ? (X) : (Y);
}

int MAX(int X, int Y) { // iki tane integer degeri kýyaslayýp maksimumu yolluyor.
    return ((X) > (Y)) ? (X) : (Y);
}


struct asciinode_struct {
     asciinode *left, *right; // dugum struct tanýmlamasý ile  karýsmamasý için böyle yazdým açýsýndan yapýldý 

    
    int edge_length; // cocuklarýna olan uzunluklarýna bakýyor.

    int height; //yükseklik

    int lablen; // buda düðümün basamak sayýsý.

    //-1=I am left, 0=I am root, 1=right
    int parent_dir; // -1 ise sol cocuk, 0 ise kök, 1 ise sað çocuk.

    char label[11]; //maksimum 10 basamak alabiliyorum.
};

asciinode *build_ascii_tree_recursive(struct dugum *t) {
    asciinode *node;

    if (t == NULL) return NULL;
	
    node = (asciinode*)malloc(sizeof(asciinode));
    node->left = build_ascii_tree_recursive(t->sol);
    node->right = build_ascii_tree_recursive(t->sag);

    if (node->left != NULL) { // bu þekilde çocuklarýn solda olduðunu belirledik. Eðer childi solda ise :
        node->left->parent_dir = -1; // sol cocugun parent_dir=-1 yaparak solda oldugunu belirtiyor.
    }

    if (node->right != NULL) 
	{ 
		// sag eðer bos degilse sag cocugu 1 yapýyor.
        node->right->parent_dir = 1;
    }

    sprintf(node->label, "%d", t->icerik); //sprintf kullaným node->label olan kýsma t->icerigi yaz.
    
	node->lablen = (int) strlen(node->label); // bu da düðümün kaç basamaklý olduðunu gösteriyor.

    return node;
}

// Aðacý ascii düðümü yapýsýna kopyalayýn
asciinode *build_ascii_tree(struct dugum *t) {
    asciinode *node;
    if (t == NULL) return NULL;
    node = build_ascii_tree_recursive(t);
    node->parent_dir = 0; // parent olanlara 0 veriyor. 
    return node;
}


//Verilen aðacýn tüm düðümlerini serbest býrak
void free_ascii_tree(asciinode *node) {
    if (node == NULL) return;
    free_ascii_tree(node->left);
    free_ascii_tree(node->right);
    free(node);
}


//Aþaðýdaki iþlev, verilen aðaç için lprofile dizisini doldurur.
//Bu aðacýn kökü etiketinin merkezinin bir konumda (x, y) bulunduðu varsayýlmaktadýr.
//Bu aðaç için kenar uzunluðu alanlarýnýn hesaplandýðýný varsayar.
int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];
// maksimum yükseklik 1000 verilmis.

void compute_lprofile(asciinode *node, int x, int y) {  // sol kýsým hesaplamak için yazýlan fonksiyon
    int i, isleft;
    if (node == NULL) return;
    isleft = (node->parent_dir == -1); 
    lprofile[y] = MIN(lprofile[y], x - ((node->lablen - isleft) / 2));
    if (node->left != NULL) {
        for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++) {
            lprofile[y + i] = MIN(lprofile[y + i], x - i);
        }
    }
    compute_lprofile(node->left, x - node->edge_length - 1, y + node->edge_length + 1);
    compute_lprofile(node->right, x + node->edge_length + 1, y + node->edge_length + 1);
}

void compute_rprofile(asciinode *node, int x, int y) {
    int i, notleft;
    if (node == NULL) return;
    notleft = (node->parent_dir != -1);
    rprofile[y] = MAX(rprofile[y], x + ((node->lablen - notleft) / 2));
    if (node->right != NULL) {
        for (i = 1; i <= node->edge_length && y + i < MAX_HEIGHT; i++) {
            rprofile[y + i] = MAX(rprofile[y + i], x + i);
        }
    }
    compute_rprofile(node->left, x - node->edge_length - 1, y + node->edge_length + 1);
    compute_rprofile(node->right, x + node->edge_length + 1, y + node->edge_length + 1);
}


// Bu iþlev, belirtilen aðacýn kenar uzunluðu ve yükseklik alanlarýný doldurur. 
//compute_edge_lengths:kenar uzunluklarýný hesapla
void compute_edge_lengths(asciinode *node) {
    int h, hmin, i, delta;
    if (node == NULL) return;
    compute_edge_lengths(node->left);
    compute_edge_lengths(node->right);

    
    // önce düðümün kenar uzunluðunu doldurun
    if (node->right == NULL && node->left == NULL) 
	{ //edge_length=cocuklarýna olan uzunluklarýna bakýyor.
        node->edge_length = 0; //cocugu yoksa 0' de
    } 
	
	else{
        if (node->left != NULL) 
		{
            for (i = 0; i < node->left->height && i < MAX_HEIGHT; i++) {
                rprofile[i] = -INFINITY;
            }
            compute_rprofile(node->left, 0, 0);
            hmin = node->left->height;
        } 
		else 
		{
            hmin = 0;
        }
        if (node->right != NULL) 
		{
            for (i = 0; i < node->right->height && i < MAX_HEIGHT; i++) {
                lprofile[i] = INFINITY;
            }
            compute_lprofile(node->right, 0, 0);
            hmin = MIN(node->right->height, hmin);
        } 
		else 
		{
            hmin = 0;
        }
        delta = 4;
        for (i = 0; i < hmin; i++) {
            delta = MAX(delta, gap + 1 + rprofile[i] - lprofile[i]);
        }

      
        // düðümün yüksekliði 1 olan 2 çocuðu var ise  
        if (((node->left != NULL && node->left->height == 1) ||
             (node->right != NULL && node->right->height == 1)) && delta > 4) {
            delta--;
        }

        node->edge_length = ((delta + 1) / 2) - 1;
    }

    //Düðümün yüksekliðini doldururuz.
    h = 1;
    if (node->left != NULL) {
        h = MAX(node->left->height + node->edge_length + 1, h);
    }
    if (node->right != NULL) {
        h = MAX(node->right->height + node->edge_length + 1, h);
    }
    node->height = h;
}

//iþlevi, düðümün verilen x kordonine sahip olduðunu varsayarak, verilen aðacýn verilen seviyesini yazdýrýr.
void print_level(asciinode *node, int x, int level) {
    int i, isleft;
    if (node == NULL) return;
    isleft = (node->parent_dir == -1);
    if (level == 0) {
        for (i = 0; i < (x - print_next - ((node->lablen - isleft) / 2)); i++) {
            printf(" ");
        }
        print_next += i;
        printf("%s", node->label);
        print_next += node->lablen;
    } else if (node->edge_length >= level) {
        if (node->left != NULL) {
            for (i = 0; i < (x - print_next - (level)); i++) {
                printf(" ");
            }
            print_next += i;
            printf("/");
            print_next++;
        }
        if (node->right != NULL) {
            for (i = 0; i < (x - print_next + (level)); i++) {
                printf(" ");
            }
            print_next += i;
            printf("\\");
            print_next++;
        }
    } else {
        print_level(node->left,
                    x - node->edge_length - 1,
                    level - node->edge_length - 1);
        print_level(node->right,
                    x + node->edge_length + 1,
                    level - node->edge_length - 1);
    }
}

//Verilen aðaç yapýsý için ascii aðacýný yazdýrýr.
void print_ascii_tree(struct dugum *t) {
    asciinode *proot; // bu sekilde cizilecek olan agac için struct yapýsý tanýmlýyoruz.
    int xmin, i;
    if (t == NULL) return;
    proot = build_ascii_tree(t);
    compute_edge_lengths(proot);
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) {
        lprofile[i] = INFINITY;
    }
    compute_lprofile(proot, 0, 0);
    xmin = 0;
    for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) {
        xmin = MIN(xmin, lprofile[i]);
    }
    for (i = 0; i < proot->height; i++) {
        print_next = 0;
        print_level(proot, -xmin, i);
        printf("\n");
    }
    if (proot->height >= MAX_HEIGHT) {
        printf("(Bu agaç eger %d'den daha uzun ise yanlis çizilme ihtimali vardir\n", MAX_HEIGHT);
    }
    free_ascii_tree(proot);
}

//---------------------------------------------------------------Listeleme Kismi Sonu----------------------------------------------------------

int main() 
{	srand(time(NULL));
	int dizi[10]={0}; // elimizde 10 elemanlý bir dizi var ve random elemanlarý bu dizimizde tutucaz.
	int randomIndex; //random elemanýmýz.
	int i;
	struct dugum *root=NULL;
	int silinecek=0;
	int bayrak=1;
	for(i=0;i<10;i++)
	{
		randomIndex=rand()%100+1; 
		dizi[i]+=randomIndex;	//random 10 elamani diziye ekledik ve bu diziden hareket ederek agac olusturacaz.	
	}	
	printf("random elemanlar:");
	printf("\n");
	for(i=0;i<10;i++)
	{
		printf("%d",dizi[i]);	
		printf("\t");	
	}
	
	root=insert(root,dizi[0]); //Random olusturdugumuz ilk elemani agacimizin köküne ekledik, artik kök sayesinde diger elemanlari da ekleme yapabiliriz köke göre.
	
	for(i=1;i<10;i++)
	{	
		insert(root,dizi[i]);	//geri kalan 9 elemani ekleme yaptýk.		
	}
	printf("\n");
	printf("Agacimizin ilk hali:");
	printf("\n");
	print_ascii_tree(root);
	printf("\n");
	printf("silme kismi:\n");
	
	while(1)
	{
		
	
		if(bayrak==1)
		{
					
			printf("agactan cikarmak istediginiz sayiyi giriniz:\n");
			scanf("%d",&silinecek);	
			root=deleteNode(root,silinecek);
			printf("\n");
			printf("Agacimiz:\n");
			print_ascii_tree(root);
		}
		else
		{
			printf("cikiliyor...\n");
			break;
		}
			
		printf("Agacimizindan eleman cikarmaya devam etmek istiyorsaniz 1'e basiniz,yoksa 0'a basiniz: \n");
		scanf("%d",&bayrak);
	}
	return 0;
}

