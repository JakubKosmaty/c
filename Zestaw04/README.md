# Markdown

## Pytania
- Co zwraca funkcja pipe()?

                Funkcja pipe() zwraca dwa deskryptory plików. Jeden używany jest do zapisu, a drugi do odczytu.

- Czym się różni funkcja pipe() od mkfifo()? Co robią te funkcje?

                W przypadku funkcji pipe(), może łączyć tylko procesy potomne, a mkfifo umożliwia wymiane między wszystkimi procesami niekoniecznie potomnymi. Obie funkcję tworzą potok. 

- Co oznacza akronim FIFO?

                Skrót FIFO oznacza 'First In First Out' element, który zostanie umieszczony w buforze jako pierwszy, również pierwszy opuści go.

- Co to jest deskryptor?

                Deskryptor jest to indentyfikator(indeks) do struktury danych, który zawiera inforamcję o otwartych plikach. 

- Jak i dlaczego zamykamy deskryptory w zadaniu 1.?ś

                Deskryptory zamykamy funkcją close(), robimy to z paru powodów. Deskryptorów jest ograniczona ilość, kod jest bardziej przejrzysty, pozwala to uniknąć błędów.

- Proszę sprawdzić co się stanie jeżeli nie zamkniemy deskryptorów w zadaniu 1.?

                Program nie zakończy się i będzie czekał na kolejne wejście, bo nie otrzymał EOF'a. 

- Jak utworzyć i usunąć potok nazwany z linii komend a jak z poziomu programu?

                Do utworzenia potoku z liniki komend służy komenda 'mkfifo [-m mode] file name', a z poziomi programu 'int mkfifo(const char *path, mode t mode)'.
                Aby usunąć potok w programie należy użyć funkcji unlink(), w przypadku lini komend 'rm'.
