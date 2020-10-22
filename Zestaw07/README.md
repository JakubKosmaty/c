# Markdown

## Pytania
- Opisać działanie, argumenty i wartość zwracaną przez funkcję mq_open


    Funkcja mq_open pozwala na utworzenie lub otwarcie kolejki komunikatów. Funkcja zwraca deskryptor kolejki komunikatów, w przypadku błędu -1. Argumenty: const char *name - nazwa kolejki musi zaczynać się od "/", int oflag opcje, jeśli jako argument przyjmiemy O_CREAT to musimy dodać dwa argumenty mode - prawa dostępu i attr wskaźnik do struktury atrybutów kolejki komunikatów.

- Opisać działanie, argumenty i wartość zwracaną przez funkcję mq_send i mq_receive


    Funkcje mq_send i mq_receive odpowiadą za wysyłanie/odbieranie komunikatów. Zwracają 0 w przypadku sukcesu i -1 w przypadku błedu. Argumenty mq_send i mq_receive: mqd_t mqdes - deskryptor kolejki, const char *msg_ptr - wiadomość, size_t msg_len - długość wiadomości, unsigned int msg_prio - priorytet komunikatu.


- Czy kolejki komunikatów standardu POSIX są widoczne w systemie plików, gdzie?


    Kolejki komunikatów standardu POSIX zwykle są tworzene w wirtualnym systemie plików w "/dev/mqueue".

- Jak otrzymać informacje o parametrach kolejki komunikatów?


    Informacje o parametrach kolejki komunikatów za pomocą funkcji mq_getattr, która zwraca następującą informacje o kolejce: flagi, długość wiadomości, maksymalna ilość wiadomości, ilość wiadomości w kolejce.
