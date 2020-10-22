# Markdown

## Pytania
- Zadanie 3 - Czy drugi komunikat zostanie wyświetlony?


        Drugi komunikat nie wyświetli się, jest to związane z działaniem funkcji execl(), którą opisałem niżej.

- Ile teraz powstaje procesów w zadaniu 2. i dlaczego?


        W zadaniu poswstaną 3 procesy potomne oraz 1 macierzysty, ponieważ funkcja execl() przerywa działanie programu, więc w momencie powstania procesu potomnego program "popełnia samobójstwo.
- Ile procesów powstanie przy n-krotnym wywołaniu funkcji fork-exec jak w zadaniu 2. i dlaczego?


        Powstanie 'n' procesów, ponieważ iteracje już się nie wykonają, bo exec() przerwał działanie programu.
- Co robi funkcja execl()? Czym się różni od funkcji execv()?


        Funkcja ta zastępuje działający program na ten wywołany. Funkcja powraca do programu tylko, wtedy jeśli zwróci błąd. execl() i execv() różnią się formatem i liczbą argumentów.
- Jaką rolę pełni proces init lub systemd?


        Te procesy wyczytują i uruchamiają procesy związane z inicjalizacją systemu oraz nadzorują prace systemu.
- Co to są procesy zombi?


        Jeśli proces umiera to rodzin zostaje powiadomiony, ze jego proces potomny zginął. Proces macierzysty, wtedy funkcją wait() moze odczytać informację i dopiero wtedy proces potomny zostaje całkowicie usunięty z pamięci.

- Co to są procesy osierocone?


        Jeśli zakończymy działanie procesu macierzystego to proces potomny staje się osierocony. Init natychmiast "przygarnia" te procesy.
