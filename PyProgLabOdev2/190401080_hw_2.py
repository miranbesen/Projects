import sys
from csv import reader

if len(sys.argv)<2:
    print ("Fatal: You forgot to include the directory name on the command line.")
    print ("Usage:  python %s <directoryname>" % sys.argv[0])
    sys.exit(1)


with open(sys.argv[1]+'/input_hw_2.csv',"r") as read_obj:
  
    csv_reader = reader(read_obj)
   
    list_of_rows = list(csv_reader) #list of list oluyor burda yani her satır bir liste gibi oluyor
    #print(list_of_rows)

n=len(list_of_rows)
#print(n) 

import itertools

merged_list = list(itertools.chain(*list_of_rows)) #listeleri tek liste haline getiriyoruz 

#print(merged_list)
n=len(merged_list)
#print(n)

my_list=[]

for line in merged_list: #yeni listemiz ';' e göre ayrılıyor.
        #print(line)
        words=line.split(";")
        for word in words:
            #print(word)
            my_list.append(word)


#print(my_list)

n=len(my_list)

my_list2=[] 

for i in range(3,n,+4):
    my_list2.append(my_list[i]) #ayrılış tarihlerini bir liste haline getiriyoruz.


#print(my_list2)

my_list3=[]   

for line in my_list2: #ayrılış yıllarını '-' e göre parçalıyoruz.
        #print(line)
        words=line.split("-")
        for word in words:
            #print(word)
           my_list3.append(word)


#print(my_list3)

n=len(my_list3)
my_list4=[] 
for i in range(1,n,+3): #ayrılış aylarını listeliyoruz.
    my_list4.append(my_list3[i])



#print(my_list4)  

for i in range(0, len(my_list4)): #elemanlarını int'e çevirdik
    my_list4[i] = int(my_list4[i])

#print(my_list4)




def get_hist(my_list5): #histogram fonksiyonu
    my_hist={} 
    for w in my_list5:
        if w in my_hist.keys():
            my_hist[w]=my_hist[w]+1
        else:
            my_hist[w]=1
    return my_hist 


my_hist=get_hist(my_list4)

#print(my_hist)

#print(dir(dict))





def histogram_not_months(my_hist2):
    for i in range(1,12,+1):
        if i not in my_hist2.keys():
            my_hist2[i]=0

     
    return my_hist2




my_hist2=histogram_not_months(my_hist)
#print(my_hist2)



my_list5=list(my_hist2.values())

#print(type(my_list5))
#print(my_list5)


def my_bubble_sort(my_list):
    n=len(my_list)

    for i in range(n-1,-1,-1): #listenin en sonuncu elemanindan bir bir azalarak  devam eder. 
        for j in range(0,i):
            if not(my_list[j]<my_list[j+1]):
                temp=my_list[j]
                my_list[j]=my_list[j+1]
                my_list[j+1]=temp


    return my_list






my_list6=my_bubble_sort(my_list5)

#print(type(my_list6))
#print(my_list6)



def my_median(my_list7): #medyan değerini bulan fonksiyon
    my_list7=my_bubble_sort(my_list7)

    #print(my_list_6)

    n=len(my_list7)

    if (n%2==1):
        middle=int(n/2)+1
        median=my_list7[middle-1]
        

    else:
        middle_1=int(n/2)-1
        middle_2=middle_1+1
        median=(my_list7[middle_1]+my_list7[middle_2])/2
    return median


def my_mean(my_list7): #ortalama bulan fonksiyon.
    s,t=0,0 #s=eleman sayisi ,t=eleman sayilari toplami

    for item in my_list7:
        s=s+1
        t=t+item

    mean_=t/s

    return mean_


#print(my_list6)

ortalama=int(my_mean(my_list6))
medyan=my_median(my_list6)

#print("ortalama:",ortalama)
#print("medyan:",medyan)
#print("argv:",str(sys.argv))
#print("1.eleman:",sys.argv[1])
#print("2.eleman:",sys.argv[2])


dosya=open(sys.argv[2]+'/190401080_hw_2_output.txt',"w") #burada input.txt adlı ornekleri tutan bir txt acıp icine giridgimiz inputları yazıyoruz.

dosya.write("ortalama:"+str(ortalama)+"\n"+"medyan:"+str(medyan))

dosya.close()


