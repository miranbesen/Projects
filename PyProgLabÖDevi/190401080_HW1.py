def get_words():
    filenames = ['1.txt', '2.txt', '3.txt','4.txt','5.txt','6.txt','7.txt','8.txt','9.txt','10.txt'] #burada tüm txt dosylarını birleştirip dosyalar=şeklinde düşünüyoruz.Sonra my_file.txt adlı txt dosyasına tüm txtleri atıyoruz.

    with open('my_file.txt','w+') as dosyalar:
        for fname in filenames:
            with open(fname) as infile:
                dosyalar.write(infile.read())
    dosyalar.close()
    my_list=[]
    f=open("my_file.txt","r+")
    contents=f.readlines() #degisken tipi liste olan contensleri \n e göre parçalıyoruz burada
    print(type(contents)) #burada degiskenin tipinin liste oldugunu görüyoruz
    for line in contents:
        print(line) #cümle cümle bölüyoruz burada
        words=line.split(" ")#bosluga göre kelimeleri böldük
        for word in words:
            #print(word)  
            my_list.append(word) #kelime kelime listeye ekliyoruz.
    #print(contents)
    f.close()
    
    return my_list



def get_hist(my_list): #histograma liste degiskenini atıyoruz burada.
    my_hist={} #sözlük açıyoruz burada
    for w in my_list:
        if w in my_hist.keys(): #aynı olan kelimelerden kactane ıoldugunu anlamak için böyle bir kod yazıyoruz.
            my_hist[w]=my_hist[w]+1
        else:# eger kelime yoksa daha once burada o kelimeden sözlüge ekliyoruz.
            my_hist[w]=1
    return my_hist #histogramımızı döndürüyoruz.


list_1=get_words() #burada fonksyonumuzun return ettigi degeri list_1 adlı degiskenimizde tutuyoruz.
a=get_hist(list_1) #burada a adlı yeni sözlügümüzü  histogram fonksyonumuza esitliyoruz.
print(a)
print(50*"=")
kelime=input("lütfen string giriniz!= ") #bir sonraki kelimeyi tahmin etmek için input alıyoruz burada kac tane sözcük girecegini kullanıcı belirliyor.


def sonInputaGit():   
    
    kelimeler=kelime.split(" ") #kelimeler şu an bir liste bundan sonra eger kelimeler besten büyükse hata ver diyebilirsin #birde burda kelimeleri bosluga göre bölüyoruz
    #if kelimeler.len()>5:
    n=len(kelimeler) #burada kelimenin bosluga göre uzunlugunu buluyoruz
    if n>=5: #eger kelime sayisi 5 ten fazla olursa null deger dönderiyoruz.
        print("kelime sayısı beşten fazla olamaz!")
        return ''
    else:
        return kelimeler[-1] #eger 5 ten kelime sayisi az ise son kelimeyi yolluyoruz.



def nextwordhistogram(): #bir sonraki kelimelerin histogramını buluyoruz.
    nexthist=dict()
    sonkelime=sonInputaGit() #son kelimeyi burada alıyoruz.
    if sonkelime == '': #eger kelime sayisi 5 ten buyuk ise yine null degerli histogram döndürüyoruz.
        return nexthist
    else:
        for k in list_1:
            if k==sonkelime: # son kelimeye ulastıgımız an
                kIndex=list_1.index(k) #son kelimenin index numarasını buluyoruz.
                if kIndex != len(list_1)-1: #eger sonkelime degilse k 
                    sonrakikelime=list_1[kIndex+1] #bir sonraki kelimeyi alıyoruz indexini.
                    if sonrakikelime in nexthist.keys(): #burada sonraki kelime histogramını olusturuyoruz.
                        nexthist[sonrakikelime]=nexthist[sonrakikelime]+1
                    else:
                        nexthist[sonrakikelime]=1
           
                    list_1.remove(k) #sonraki kelime hep aynı olmasın diye listeden kelimeyi histograma yazdıktan sonra siliyoruz.
               
    return nexthist #sonraki kelime histogramını burada yolluyoruz.


import operator

sonrakiKelimeHistogrami=nextwordhistogram() #sonraki kelime histogramını fonskyona esitleyip histogramımızı degiskene atıyoruz.
if len(sonrakiKelimeHistogrami) == 0: #eger sonraki kelime histogramı bos ise  hic birsey yapmıyoruz.
    print("")
else: #eger bos degilse sonraki kelime histogramı bu islemleri yapıyoruz.
    print(50*"=")
    print("Sonraki Kelimelerin Histogramı:")
    print(sonrakiKelimeHistogrami)
    print(50*"=")
    def enCokTekrarEdenKelime(sonrakiKelimeHistogrami:dict): #sonraki kelime histogramındaki kelimelerin en cok tekrar edeni bulmak için suzlugu value ve keys diye iki degiskene bölüyoruz.
            vList=list(sonrakiKelimeHistogrami.values())
            keyList=list(sonrakiKelimeHistogrami.keys())
    
            return keyList[vList.index(max(vList))] #burada en cok tekrar eden kelimeyi bulmak için böyle birşey yapuyoruz 
    
    
    print(kelime,end=" ") #ilk basta kelimeyi ekrana bastırıyoruz.
    if len(sonrakiKelimeHistogrami) == 0: #histogramda eleman yoksa ise burayı uyguluyoruz.
        print("Önerilecek kelime bulunamadı.") #burayı neden böyle yazdım emin degilim ama  
    else: #histogramda kelime var ise bu kısmı yapıyoruz
        print(enCokTekrarEdenKelime(sonrakiKelimeHistogrami)) #sonraki kelimeyi burada ekrana bastırıyoruz bunuda encoktekraredenkelime adlı fonksyona sonrakikelime histogramını yollayarak yapıyoruz.
        print(50*"=")
        
        dosya=open("input.txt","a") #burada input.txt adlı ornekleri tutan bir txt acıp icine giridgimiz inputları yazıyoruz.

        dosya.write(kelime+"--->"+enCokTekrarEdenKelime(sonrakiKelimeHistogrami)+"\n")

        dosya.close()