# Markdown

## Opis


        main.x: wypisuje indentyfikatory
        kopiuj.x: kopiuje zawartość pliku do innego pliku użycie "./kopiuj.x plik_macierzysty plik_docelowy"
        procesy.x: wypisanie procesów od najstarszych do najmłodszych
        lider.x: proces potomny staje się liderem własnej grupy

        make - kompilacja wszystkich plików źródłowych do obiektowych i wykonywalnych
        make clean - usuwanie plików obiektowych i wykonywalnych
        drzewo_ genealogiczne.png - drzewo procesów

## Pytania
- Opisać dokładnie jak działa funkcja fork()?


        Funckja fork() pozwala na stworzenie procesu potomnego, który w chwili tworzenia jest kopią procesu macierzystego. Funkcja moze zwrócić następujące wartości: 
        a) -1 błąd
        b) 0 w procesie potomnym
        c) > 0 w procesie macierzystym, zwracany jest PID procesu potomnego

        
- Ile powstaje procesów w zadaniu procesy i dlaczego?


        Przy iteracji funkcji fork() powstanie 2^n - 1 procesów.
        W zadaniu będzie to 7 procesów. 

                0    // 1 proces potomny stworzony przez pierwszego fork()
             /     \
            1       1 // 2 procesy potomne stworzone przez kolejnego fork()  
           /  \    /  \
          2   2  2     2 // itd.



- Ile procesów powstanie przy n-krotnym wywołaniu funkcji fork i dlaczego?


        Powstanie 2^n
        Przykładowo dla wywołania:
        fork();
        fork();
        fork();
        Powstanie 7 procesów potomnych, ale 8 ogólnie. Dzieje się tak, bo każdy proces tworzy kolejne 2 potomne. Niestety nie wiem jak to udowodnić poprzez indukcję matematyczną.

- Jak używając funkcji sleep i bez odwoływania się do funkcji wait() zapewnić aby procesy macierzyste kończyły się dopiero po procesach potomnych.

        Poniższy kod rozwiązuje problem: 

```c
for(int i = 0; i < 3; i++) {
    switch(fork()) {
        case -1: {
            perror("fork error");
            exit(1);
        }
        case 0: {

            int pid = getpid();
            setpgid(pid, pid);
            msleep(500 - i * 100);
        }
    }
}
```

- Jaką wartość zwraca open()?

        Funkcja open() zwraca deskryptor pliku: jeśli -1 to błąd
- Jaką wartość zwraca read() i write()?

        Funkcja read() zwraca liczbę wyczytanych bajtów: 0, gdy napotka na koniec pliku, -1 błąd

        Funkcja write() zwraca liczbę zapisanych bajtów: jeśli -1 to błąd
         

