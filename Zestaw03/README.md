# Markdown

## Opis programów

        obsluga.c - program pobiera dwa argumenty z lini komend, a następnie na podstawie tego ustawia akcję w przypadku odebrania sygnału. Pierwszy argument określa rodzaj akcji, a drugi numer signału.

        wysylaj.c - program tworzy proces potomny poprzez funkcję fork(), a następnie funkcją execl() uruchamia program obsluga.c zastępujac(obraz) proces potomny. W procesie macierzysty 


## Pytania
- Krótko opisać funkcję i znaczenie czterech wybranych sygnałów, w tym dwóch nieprzechwytywalnych

        SIGKILL - Zakończenie procesu(nieprzechwytywalny)
        SIGSTOP - Zatrzymanie procesu(nieprzechwytywalny)
        SIGHUP - Zerwanie łączności
        SIGXFSZ - Przekroczenie rozmiaru pliku

- Do czego służą sygnały?

        Sygnały służą do komunikacji międzyprocesorowej w systemie UNIX.

- Co robi a czego nie robi funkcja signal()?

        Funkcja signal() służy do zawiadomienia procesów o sytuacjach wyjątkowych, innaczej mówiąc ustawia akcję w przypadku odebrania danego sygnału. Funckja ta nie wysyła sygnału, jedynie modifikuje jego działanie w momencie odebrania.

- Jak działa funkcja kill()? Podaj trzy przykłady uwzględniające rolę pierwszego argumentu?

        Funkcja kill() służy do wysyłania sygnałów. Funkcja przyjmuje dwa argumenty pid oraz numer signalu. Jeśli pid > 0  to procesy o podanym pidzie odbiorą sygnał, gdy pid = 0 procesy należące do tej samej grupy co proces wysyłający odbiorą sygnał, gdy pid < -1 procesy należące do grupy o PGID = -pid odbiorą sygnał.

- Jak sprawdzić czy istnieje proces pid lub grupa pgid i czy możemy do nich wysyłać sygnały?

        Wystarczy wysłać sygnał funcką kill() z numerem sygnału równym 0, jeśli proces nie istnieje to errno = ESRCH.

- Jaki sens ma wywołanie kill(0, 0)?

        Można w ten sposób sprawdzić czy wszystkie procesy należące do tej samej grupy co proces wysyłający istnieją.

- Jak i dlaczego należy uodpornić proces macierzysty w programie grupa.c na sygnał?

        Należy uodpornić proces macierzysty używając signal(signalNumb, SIG_IGN), aby funkcja pause() działała zgodnie z naszym celem.

- Jak wznowić proces zatrzymany sygnałem SIGSTOP

        Aby wznowić zatrzymany proces należy wysłać sygnał SIGCONT.

- Opisać sygnał SIGCHLD.

        Gdy proces potomny zakończy swoje działanie, do procesu macierzystego wysyłany jest ten sygnał.

- Które sygnały możemy wysłać w terminalu przy użyciu skrótów klawiszowych?

        SIGINT - Sygnal przerwania
        SIGQUIT - Zakonczenie
        SIGTSTP - Wprowadzenie znaku zatrzymania

- Jak działa funkcja pause()?

        Funckja pause() zawiesza proces do czasu odebrania sygnału. Funkcja wraca w przypadku przechwycenia sygnału i podczas powrotu funkcji obsługi sygnału.
