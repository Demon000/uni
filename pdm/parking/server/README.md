Parcari

Pentru a gestiona ocuparea parcarilor, o firma foloseste o aplicatie mobile si un server care ofera
servicii REST despre spatii de parcare, un spatiu avand urmatoarele proprietati:
  - id - un intreg pozitiv reprezentand id-ul intern al resursei, ex. 1
  - number - sir de caractere unic, reprezentand numele locului de parcare, ex 'A1'
  - address - sir de caractere reprezentand adresa locului de parcare, ex 'location 1'
  - status - sir de caractere reprezentand starea locului de parcare cu valorile posibile 'free' si 'taken'

Aplicatia mobila ofera urmatoarele ecrane separate:

1. Ecranul managerului cu operatii disponibile atat in modul online cat si in modul offline
  a. (1.5p) Permite inregistrarea unui spatiu nou prin introducerea proprietatilor number si address si declansarea 
  unui buton create care face un POST /space, punand in corpul cererii { number, address }.
  b. (1.5p) Afiseaza toate spatiile de parcare sortate dupa address si number. Datele sunt aduse de pe server
  via GET /space.

2. Ecranul angajatilor cu operatii disponibile in modul online
  a. (1p) Permite angajatilor sa filtreze locurile free sau taken. Datele vor fi aduse de pe server
  via GET /space?status=free, respectiv taken.  
  b. (1p) Afiseaza toate spatiile de parcare sortate dupa number.
  c. (1p) Permite angajatilor sa ia (take) sau sa returneze (return) un loc de parcare, apeland pe server
  PATCH space/:id cu corpul cererii { status }, unde status este taken, respectiv free.

(1p) Serverul emite evenimente prin web socket atunci cand starea unui loc de parcare se modifica.
Aplicatia client va afisa o notificare si va actualiza datele prezentate pe ecran.

(1p) In timpul executiei operatiilor de intrare/iesire, locale sau de pe server, aplicatia va afisa
un progress indicator.

(1p) Daca operatiile de intrare/iesire esueaza cu o eroare, utilizatorul va fi notificat si 
i se va permite sa reia (retry) operatia care a esuat. 
