# Markdown

## Pytania
- Szczegółowo opisz działanie semaforów z zadaniu 3.

        
        Do rozwiązania zadania potrzebne są 2 semafory, pełny i pusty. Semafor pusty ma wartość początkową równą rozmiarowi buffora cyklicznego, a semfor pusty 0. Semafor pusty jest dekrementowany przed produkcją, więc jeśli buffor będzie pełny to producent nie może już dodać do buffora. Nas†ępnie semafor pełny jest inkrementowany co umożliwia konsumentowi pobranie towaru z buffora.

- Podać w pseudokodzie uogólnienie rozwiązania problemu z zadania 3. na przypadek wielu producentów i konsumentów.
        

        Tworzymy 4 semafory, 2 takie same jak powyżej, a kolejne dwa binarne.
        Realizacja problemu jest podoba jak w przypadku jednego producenta i jednego konsumenta, lecz ogarniczami dotęp do buffora semaforami binarnymi, tak aby "jednocześnie" mógł produkować tylko jeden producent i pobierać towar tylko jeden konsument. Semaforami blokujemy innych producentów i konsumentów. 

- W jaki sposób niezależne procesy mają dostęp do tego samego segmentu pamięci dzielonej?


        Różne procesy mają dostęp do tego samego segmentu pamięci dzielonej, ponieważ jest ona utworzona w specjalnym segmencie pamięci wirtualnej i procesy uzyskują dostęp poprzez adres dowiązania o ile posiadą odpowiednie uprawnienia.

- Czym jest biblioteka dynamiczna? Jakie są jej zalety?


        Biblioteka jest to zbiór funkcji. Biblioteka dynamiczna, różni się od statycznej tym, że jest "łączona" z programem dopiero w trakcie jego wykonywania. Biblioteki dynamiczne ładowane są do pamięci i mogą być współdzielone przez różne programy. Zaletami takich bibliotek jest to, że w przypadku dokonywania zmian w takiej biblotece nie jest wymagana ponowna kompilacja programów oraz oszczędzają pamięc. 

- Jak utworzyć bibliotekę dynamiczną? Jak jej używać? Jakie są nazwy plików, które są bibliotekami dynamicznymi?


        Biblioteki dynamiczne mają rozszerzenia na windowsie .dll, a na linuxie .so. Aby utworzyć taką bibliotekę należy przekompilować kod źródłowy z flag ą -fPIC do obiektowego, następnie utowrzyć bibliotekę gcc -shared -o libx.so x.o. Teraz kompilujemy program przy użyciu flagi -L. -lx. Ostatnim krokiem jest dodanie do zmiennej środowiskowej ściężkę do katalogu zawierającego bibliotekę.