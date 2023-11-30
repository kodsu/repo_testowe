import random 


def losuj(a, b): #funkcja losująca liczbe całkowita z jednorodnym prawdopodobienstwem z przedzialu [a,b]
    return random.randint(a, b)


    # generator, na podstawie sufiksu slowa dlugosci dl losujemy nastepny znak slowa, * oznacza spacje(na poczatku slowa i ona je konczy) 
    # znaki losujemy dopoki nie wylosujemy znaku * konczacego umownie wyraz(zwracamy slowo tych gwiazdek) 
    #parametr dl powinien byc zalezny od dlugosci listy, im wiecej slow znamy, tym wieksza wartosc parametru powinnismy wybrac(do 6) 
    #zwieksza to jakosc generowanych slow, moze sie zdarzyc ze wygenerowane zostanie slowo z listy
def generator(slowa, ile = 5, dl=3):    
    lista = slowa.copy()
    mapa = {} #trzymamy spotkane w slowach danego jezyka podslowa dlugosci dl i ich indeks w tablicy nastepnik
    nastepnik = [] #dla kazdego wystepujacego podslowa trzymamy wszystkie jego nastepniki w ilosciach jak wystapily w slowach jezyka 
    nrkombinacji = 0 
    for i in range(0, len(lista)): #znajdujemy podslowa i wypelniamy dla nich tablice nastepnik 
        lista[i] = "*"*dl + lista[i] + "*" 
        for j in range(0, len(lista[i])-dl): 
            subslowo = lista[i][j:j+dl]  
            if(subslowo in mapa): 
                nastepnik[mapa[subslowo]].append(lista[i][j+dl]) 
            else:  
                mapa[subslowo] = nrkombinacji 
                nastepnik.append([]) 
                nastepnik[nrkombinacji].append(lista[i][j+dl])   
                nrkombinacji += 1  
    wyniki = [] #lista na wynikowe wygenerowane slowa 
    for it in range(ile): 
        mojeslowo = "*"*dl 
        wskaznik = 0 
        nowyznak = "*"  
        subslowo = "*"
        while True: 
            subslowo = mojeslowo[wskaznik:wskaznik+dl]  
            #print(subslowo, end = " ")
            nowyznak = nastepnik[mapa[subslowo]][losuj(0, len(nastepnik[mapa[subslowo]])-1)] #jako nowy znak wybieramy losowo nastepnik aktualnego sufiksu slowa dlugosci dl   
            #print(nowyznak)
            wskaznik += 1
            if(nowyznak == "*"): #jesli wylosowany znak to * to konczymy nasze slowo i dodajemy je do listy wynikow
                break 
            mojeslowo += nowyznak   
            if(len(mojeslowo)== 30): 
                break
        wyniki.append(mojeslowo[dl:])
    return wyniki   #zwracamy liste wygenerowanych slow 


# lista, listb - listy ze slowami jezykow; namea,nameb - nazwy jezykow; query - lista slow do przyporzadkowania, dl - parametr opcjonalny, wplywa na dlugosc badanego podslowa
def classificator(lista, listb,  namea, nameb,query,  dl = 1): 
    #metoda - sumujemy "prawdopodobienstwo slowa" to znaczy sumujemy prawdopodobienstwo podniesione do pewnego wykladnika(eksperymentalnie wyznaczone 0.1) dla wszystkich podslow dlugosci dl slowa ze nastepna literka jest taka jak w slowie na podstawie danych zebranych ze slow jezyka 
    # dla malej ilosci slow (do 1000) wejsiowych najlepsza jest dl = 1, dla 100 slow uzyskujemy poprawnosc ~85% (na jezykach angielski i polski)
    #dla wiekszej ilosci badanych slow (np 90 000) lepsze jest dl = 3 dla dobrze dobranego wykladnika(0.5) dostajemy poprawnosc w ~98% werdyktow na jezykach angielski i polski  
    #slowa o ktore pytalem nie byly brane do "uczenia" klasyfikatora
    mapa = {} #mapa zliczajaca nastepniki dla podslow w pierwszym jezyku
    for i in range(0, len(lista)): 
        lista[i] = "*"*dl + lista[i] + "*" #modyfikujemy slowo tak aby uwzglednic puste znaki przed nim i po nim 
        for j in range(0, len(lista[i])-dl): 
            subslowo = lista[i][j:j+dl]  
            if(subslowo not in mapa):  
                mapa[subslowo] = {}
                mapa[subslowo][lista[i][j+dl]] = 1
                mapa[subslowo][0] = 1 
            else:   
                if(lista[i][j+dl] in mapa[subslowo]): 
                    mapa[subslowo][lista[i][j+dl]] += 1  
                    mapa[subslowo][0] += 1
                else: 
                    mapa[subslowo][lista[i][j+dl]] = 1  
                    mapa[subslowo][0] += 1
    mapb = {} #mapa zliczajaca nastepniki dla podslow w drugim jezyku 
    for i in range(0, len(listb)): 
        listb[i] = "*"*dl + listb[i] + "*" #modyfikujemy slowo tak aby uwzglednic puste znaki przed nim i po nim  
        for j in range(0, len(listb[i])-dl): 
            subslowo = listb[i][j:j+dl]  
            if(subslowo not in mapb):  
                mapb[subslowo] = {}
                mapb[subslowo][listb[i][j+dl]] = 1
                mapb[subslowo][0] = 1 
            else:   
                if(listb[i][j+dl] in mapb[subslowo]): 
                    mapb[subslowo][listb[i][j+dl]] += 1  
                    mapb[subslowo][0] += 1
                else: 
                    mapb[subslowo][listb[i][j+dl]] = 1  
                    mapb[subslowo][0] += 1   
    odpowiedzi = [] 
    for i in query: 
        slowo = "*"*dl + i + "*" 
        prob1, prob2 = 0, 0 #sumy prawdopodobienstw w dwoch jezykach 
        for j in range(0,len(slowo)-dl): 
            subslowo = slowo[j:j+dl] 
            if(subslowo in mapa): 
                if(slowo[j+dl] in mapa[subslowo]): 
                    prob1 += (mapa[subslowo][slowo[j+dl]]/mapa[subslowo][0])**0.1
            if subslowo in mapb: 
                if(slowo[j+dl] in mapb[subslowo]): 
                    prob2 += (mapb[subslowo][slowo[j+dl]]/mapb[subslowo][0])**0.1
        if prob1 != prob2: 
            if prob1 > prob2: 
                odpowiedzi.append(namea) 
            else: 
                odpowiedzi.append(nameb)
            continue 
        if losuj(0,1) :  #kiedy sumy sa rowne losujemy wynik
            odpowiedzi.append(namea) 
        else : 
            odpowiedzi.append(nameb)
    return odpowiedzi

#obsulga testowania generatora 
""" ilebierzemy = 1000000
polish_words = open("slowa.txt").read().split()  
random.shuffle(polish_words) 
slowa = polish_words[:ilebierzemy]  
zbior = set(polish_words)
# print(slowa) 
# english_words = open("words_alpha.txt").read().split() 
# random.shuffle(english_words) 
# words = english_words[:ilebierzemy] 
# print(words)   
nowepl = generator_lepszy(slowa, 2000,6)  
for c in nowepl: 
    if c not in zbior: 
        print(c) 
"""   
# obsluga testowania klasyfikatora
ilebierzemy = 1000 #liczba slow z jezyka "do nauki"
extra = 5000 #liczba slow/2 o ktore bedziemy pytac nasz klasyfikator, jest to zbior rozlaczny ze zbiorem do nauki klasyfikatora
polish_words = open("slowa.txt").read().split()  
random.shuffle(polish_words) 
slowa = polish_words[:ilebierzemy]   
print(slowa) 
exit()
doprobkipol = polish_words[ilebierzemy:ilebierzemy+extra]

english_words = open("words_alpha.txt").read().split() 
random.shuffle(english_words) 
words = english_words[:ilebierzemy]  
doprobkiang = english_words[ilebierzemy:ilebierzemy+extra] 
testing = doprobkipol + doprobkiang 

# zbiory = [set(polish_words), set(english_words)]
# random.shuffle(testing)  
# jaki = classificator(slowa, words, testing, "polski", "angielski", 1)  
# maxi = 0 
# good = 0
# for i in range(0, len(testing)): 
#     if testing[i] in zbiory[jaki[i]]: 
#         good += 1 
#     maxi += 1
# print(good,"/", maxi)
# 






