# Markdown

## Pytania
- Do czego służą semafory w systemach UN*X?


        Semafory znajdują zastosowanie w synchronizowaniu działania kilku procesów.

- Opisz operacje, które można wykonać na semaforach.


        Opiszę operację na semaforach nazwanych.
        sem_open - tworzy lub otwiera istniejący semafor
        sem_close - zwalnia zasoby przydzielone do semafora
        sem_unlink - usuwanie semafora
        sem_post - podnoszenie semafora
        sem_wait - opusczenie semafora
        sem_getvalue - zwraca wartość semafora

- W jaki sposób niezależne procesy mogą korzystać ze wspólnych semaforów?


        Semafory nienazwane, aby mógły być użyte w innych procesach muszą być zamieszczone w ich pamięci wspólinej. W przypadku semaforów nazwanych sprawa wygląda prościej, bo wystarczy jeśli proces posiada nazwę semafora. 

- Czym jest biblioteka statyczna? Jakie są jej zalety?


        Biblioteka jest to zbiór funkcji. Co wyróżnia bibliotekę statyczną od dynamicznej to, że jest używana przez program tylko w trakcie jego kompilacji. Zalet używania bibliotek jest wiele, między innymi: porządek w kodzie, możliwość zastosowania w wielu projektach

- Jak utworzyć bibliotekę statyczną? Jak jej używać?


        Na początku należy stworzyż plik źródłowy oraz nagłówkowy, następnie przekopilować plik źródłowy do obiektowego. W kolejnym kroku używamy polecenia ar z flagami rv i gotowe. Aby użyć biblioteki w naszym programie należy skompilować kod z flagą L i nazwą utworzonej biblioteki.