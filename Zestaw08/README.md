# Markdown

## Pytania
- Czym się różni wątek od procesu?


    Między innymi:
    1. Wątki współdzielą zasoby(przestrzeń adresową), a procesy nie(każy ma osobne zasoby).
    2. Tworzenie procesów "kosztuje" o wiele więcej niż wątków

- Opisać działanie, argumenty i wartość zwracaną przez funkcję pthread_create().


    Funkcja pthread_create tworzy nowy wątek, który będzie działał razem z poprzednio utworzonymi wątkami danego procesu. W przypadku sukcesu zwraca 0, w przypadku błedu != 0. Argumenty pthread_t *pthreadID - wskaźnik na obiek typu pthread_t(unikalny indentyfikator wątku), const pthread_attr_t *attr - struktura atrybtutów wątku, void * (*start_fun) (void *) - wskaźnik na funkcję, która będzie wykonywana jako nowy wątek, void *arg - wskaźnik na argumenty przekazywane du funkcji wykonywanej przez wątek.

- Funkcja pthread_join() jest odpowiednikiem której funkcji dla procesów?


    Funkcja pthread_join() jest odpowiednikiem wait().

- Czym się różnią muteksy od semaforów?

    
    Muteksy mogą tylko posiadać wartość 0 liub 1. Odwrotnie niż dla semaforów w muteksach 1 oznacza, że muteks jest zamknięty a 0, że jest otwarty.


- Jak stworzyć muteks (dwa sposoby)?


    1. pthread mutex t myMutex = PTHREAD MUTEX INITIALIZER;
    2. pthread mutex init(&myMutex, NULL);

- Opisać działanie operacji, które możemy wykonać na muteksach.


    pthread_mutex_lock - zamykanie muteksu, jeśli muteks jest już zamknięty to spowoduje zablokwoanie wątku, w przypadku otwartego zabloguje go i przywłaszczy go wywołujący wątek
    pthread_mutex_unlock - otwiera muteks, ale tylko przez wątek, który zamknął muteks
    pthread_mutex_trylock - podobnie jak pthread_mutex_lock zamyka dany muteks, ale go nie blokuje, w przypadku, gdy muteks jest już zamknięty
    pthread_mutex_destroy - usuwa muteks, sprawia, że staje się niezainicjowany.

- Dlaczego musimy zdefiniować makro _REENTRANT?


    Należy zdefiniować powyższe makro, ponieważ oznacza to, że dany kod jest wielokrotnego użytku.

- Co oznacza typ void* (*) ()?


    Jest to wskaźnik na funkcję, która zwaraca wskaźnik na typ voida i nie przmuje argumentów.

- Co to sa operacje atomowe? Czy są konieczne?


    Operacja atomowa to operacja, która jest niepodzielna. Jest ona konieczna do prawidłowego działania, w przypadku operacji wielowątkowych. 
