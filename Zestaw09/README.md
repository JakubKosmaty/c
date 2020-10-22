# Markdown

## Pytania
- Dlaczego dwa procesy nie mają jednocześnie dostępu do sekcji krytycznej? Przedstawić dowód poprawności algorytmu. Wprowadzić 
drobną zmianę, która zepsuje tą właściwość i podać przykład.


    Watki, które próbują wejść do sesji krytycznej mają nadawane wartości, które określają ich miejsce w kolejce. Może zdarzyć się sytuacja, w której wątki będą miały taki sam numer, wtedy pierwszeństwo ma z niższym indexem. Algorytm zmienną boolowską określa czy dany wątek ma w danej chwili przydzielany numer w kolejce lub nie ma go w ogóle, albo ma już nadany. Aby zepsuć algorytm można przykładowo nie inkrementować nadawanej wartości wątkowi(miejsca w kolejce).


- Dlaczego algorytm nie prowadzi do zakleszczenia? Wprowadzić drobną zmianę, która zepsuje tą właściwość i podać przykład.
    
    
    Algorytm nie prowadzi do zakleszczenia(conajmniej dwa różne wątki czekają na siebie nawzajem), ponieważ mamy pewność, że wszystkie wątki będą miały nadany numer, który będzie spełniał jeden z dwóch warunków, czyli numer1 < numer2 lub, gdy będą równe to index zadecyduje. Również pętla while (entering[i]) nie doprowadzi do zakleszczenia, ponieważ wątek, któremu już został przyznany numer ma ustawioną zmieną na 0. Można przykładowo usunąć/zakomentować linijkę 87 (//entering[thIndex] = false;), to spowoduje, że wątki będą na siebie czekały w nieskończoność.

- Dlaczego algorytm nie prowadzi do zagłodzenia? Wprowadzić drobną zmianę, która zepsuje tą właściwość i podać przykład.


    Algorytm nie prowadzi do zagłodzenia(dany proces nie jest w stanie zakończyć działania, ponieważ nie ma dostępu do procesora lub innego współdzielonego zasobu), ponieważ mamy pewność, że wątki o niższym piorytecie wykonają się jako pierwsze. Można przykładowo w linijce 94 zmienić operatory z (thNumbers[i] < thNumbers[thIndex]) na (thNumbers[i] <= thNumbers[thIndex])

- Jakie minimalne warunki muszą zostać spełnione przez kompilator i model pamięci aby algorytm działał poprawnie?


    Kompilator musi posiadać barierę pamięci, czyli punkt w programie, który wymusza się na systemie komputerowym zsynchronizowanie zawartości pamięci, a model pamięci spójność sekwencyjna https://www.youtube.com/watch?v=AUxFuD_IfqA.

