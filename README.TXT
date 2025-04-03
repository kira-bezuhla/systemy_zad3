Wykonawca: Kira Bezuhla
        
Zawartość:
- plik README.txt 
- plik makefile 
- pliki z kodem żródłowym 

-uruchomianie:
    podpunkt a: 
        kompilacja: "make runA"
        uruchomienie: "./runA <numer sygnalu> <mode: default | ignore | custom>"
    podpunkt b: przed uruchomianiem prosze skompiliowac program z podpunktu a
        kompilacja: "make runB"
        uruchomianie: "./runB <numer sygnalu dla procesu potomnego> <numer sygnalu dla procesu macierzystego> <mode: default | ignore | custom>"
    podpunkt c: przed uruchomianiem prosze skompiliowac program z podpunktu a
        kompilacja: "make runC"
        uruchomianie: "./runC <numer sygnalu> <ilosc procesow potomnych>"
    
- sprzatanie 
    usuwamy wszystkie programy obiektowe i wykonywalne
    aby go uruchomić wpisujemy komendę "make clean"
- kompresja
    sprzata i kompresuje folder
    aby to zrobic wpisujemy komende "make tar"
    
Opis programu:
    podpunkt a: 
        w zaleznosci od podanego argumentu obsluguje sygnaly
    podpunkt b: 
        w procesie potomnym uruchamia program z podpunktu a, w procesie macierzystym wysyla sygnal dla procesu potomnego oraz zwraca status zakonczenia procesu potomnego
    podpunkt c: 
        proces potomny staje sie liderem grupy procesow oraz uruchamia program C additional, ktory tworzy kolejne procesy potomne (ilosc tych procesow zalezy od podanego argumentu). Te procesy potomne uruchamiaja program z podpunktu a. Lider grupy ignoruje sygnaly od procesu macierzystego, czeka na zakonczenie procesow potomnych oraz zwraca ich status zakonczenia. Proces macierzsty wysyla do tej grupy procesow sygnal, czeka na zakonczenie lideru oraz zwraca jego status zakonczenia