#include "wypozyczalnia.h"
/** \brief Funkcja odczytuj�ca dane z pliku "clients.txt"
 *
 * Otwiera plik, nast�pnie rezerwuje pami�� na kolejne elementy listy clients, w kt�rych zapisuje dane.
 *
 */

void readclients()
{

    FILE *fp = fopen("clients.txt", "r");

    first = NULL;

    if(fp)
    {
        first = (struct clients *)malloc(sizeof(struct clients));
        current = first;
        while(1)
        {
            newclient = (struct clients *)malloc(sizeof(struct clients));
            fread(current, sizeof(struct clients), 1, fp);
            if(current -> next == NULL)
                break;
            current -> next = newclient;
            current = newclient;
        }
        fclose(fp);
    }
}
/** \brief Funkcja zapisuj�ca dane do pliku "clients.txt"
 *
 * Otwiera plik, nast�pnie zapisuje dane z kolejnych element�w listy clients do pliku.
 *
 */

void writeclients()
{
    FILE *fp = fopen("clients.txt", "w");

    current = first;

    if(current == NULL)
        return;
    if(fp == NULL)
    {
        printf("Blad zapisu do pliku clients.txt\n");
        return;
    }
    while(current != NULL)
    {
        fwrite(current, sizeof(struct clients), 1, fp);
        current = current -> next;
    }
    fclose(fp);
}
/** \brief Funkcja realizuj�ca dodawanie klient�w
 *
 * Rezerwuje miejsce w pami�ci, aby doda� nowy element do listy clients, a nast�pnie pobiera dane klienta.
 *
 */

void add_clients()
{
    newclient = (struct clients *)malloc(sizeof(struct clients));
    int cid=0;
    if(first == NULL)
    {
        first = current = newclient;
    }
    else
    {
        current = first;
        while(current->next != NULL)
            current = current->next;
        current -> next = newclient;
        current = newclient;
    }

    for(current=first;current!=newclient;current=current->next)
        {
        if(cid<=current->id)
            cid=current->id;
        }

    cid++;

    printf("Karta klienta: %d\n", cid);
    current -> id = cid;

    printf("Podaj dane kontaktowe\n");
    printf("Imie: ");
    scanf("%s",(current -> name));

    printf("Nazwisko: ");
    scanf("%s",(current -> surname));

    printf("Numer kontaktowy:");
    scanf("%s",(current -> phone));

    printf("Adres e-mail: ");
    scanf("%s",(current -> email));

    printf("Karta klienta dodana pomyslnie!");
    current -> next = NULL;
}
/** \brief Funkcja sprawdzaj�ca istnienie rekordu klienta
 *
 * \param[in] recordnumber zmienna przekazuj�ca numer rekordu(identyfikatora)
 * \return W przypadku gdy rekord istnieje to funkcja zwraca warto�� 1, a w przypadku nieodnalezienia go zwraca -1.
 *
 */

int findnumberc(int recordnumber)
{
    int record;
    record = recordnumber;
    current = first;
    while(current != NULL)
    {
        if(current -> id == record)
        {
            return 1;
        }
        else
        {
            current = current -> next;
        }
    }
    return -1;
}
/** \brief Funkcja realizuj�ca wy�witlanie listy klient�w
 *
 * Umo�liwia wy�wietlenie listy klient�w w postaci tabeli z podzia�em na dane informacje.
 *
 */

void print_clients()
{
    if(first == NULL)
    {
        puts("Brak klientow do wyswietlenia!");
        return;
    }
    else
    {
        printf("%-6s %-20s %-20s %-15s %-20s\n","ID","Imie","Nazwisko","Telefon","E-mail");
        puts("------ -------------------- -------------------- --------------- --------------------");
        current=first;

        do
        {
            printf("%-6d %-20s %-20s %-15s %-20s\n",\
            current -> id,
                   current -> name,
                   current -> surname,
                   current -> phone,
                   current -> email);
        }
        while((current = current -> next) != NULL);
    }
}
/** \brief Funkcja realizuj�ca usuwanie klient�w
 *
 * Usuwa podanego klienta z listy, przy czym sprawdza czy istnieje lub ma dopisane wypo�yczenie.
 * Nast�pnie informuje o przebiegu operacji usuwania.
 *
 */

void delete_clients()
{
    int number;
    struct clients *prev;

    if(first == NULL)
    {
        puts("Brak klientow do usuniecia!");
        return;
    }
    else
    {
        printf("Podaj numer karty klienta do usuniecia: ");
        scanf("%d", &number);
    }

    current = first;

    while(current != NULL)
    {
        if(current->id == number)
        {
            if (count_rentals_by_clients(number) > 0) {
                printf("Klient o id %d ma wypozyczenia i nie moze zostac usuniety!\n", number);
                return;
            }

            if(current == first)
                first = current -> next;
            else
                prev -> next = current -> next;
            free(current);
            printf("Karta klienta %d usunieta pomyslnie!\n", number);
            return;
        }
        else
        {
            prev = current;
            current = current -> next;
        }
    }
    printf("Karta klienta %d nie odnaleziona!\n", number);
}
/** \brief Funkcja realizuj�ca pytanie potwierdzaj�ce decyzje odno�nie edycji klient�w
 *
 * \return W przypadku wpisania zmiennej "t"/"T" funkcja umo�liwi dalesze dzia�anie, natomiast gdy wpiszemy "n"/"N" lub inny znak wraca do pocz�tku funkcji edit_clients().
 *
 */

void clients_question()
{
    char option;
    printf("Chcesz kontynuowac? {T/N) ");
    getchar();
    scanf("%c", &option);
    if (option ==  't' || option == 'T')
    {
        return;
    }
    else if (option == 'n' || option == 'N')
    {
        return edit_clients();
    }
    else
    {
        printf("Bledny wybor!\n");
        return edit_clients();
    }
}

/** \brief Funkcja umo�liwiaj�ca edycje danych klient�w
 *
 * Pobiera identyfikator klienta do edycji, a nast�pnie prosi o potwierdzenie wyboru. Po czym mo�na edytowa� dowolne pole lub wr�ci� do menu g��wnego.
 *
 * \return W przypadku braku klient�w wraca do menu g��wnego lub je�li nie znajdzie podanego klienta wraca do pocz�tku funkcji.
 *
 */

void edit_clients()
{
    int number, result, option;

    if(first == NULL)
    {
        puts("Brak klientow do edycji!");
        return;
    }
    else
    {
        printf("Podaj numer karty klienta do edycji: ");
        scanf("%d", &number);
    if (findnumberc(number) < 1)
    {
        printf("Karta klienta o id %d nie odnaleziona!\n\n", number);
        return edit_clients();
    }
        printf("Klient: %s %s\n", current -> name,current -> surname);
        clients_question();
    }

    result = findnumberc(number);

    while(1)
    {
    if(result>0)
    {
        printf("Numer karty: %d\n\n", current -> id);

        printf("Wybierz co chcesz edytowac:\n");
        printf("1.Imie\n2.Nazwisko\n3.Numer kontaktowy\n4.Adres e-mail\n0.Wroc do menu\nWybor: ");
        scanf("%d",&option);

        switch(option)
        {
            case 0:
                system("cls");
                writeclients();
                return main();
                break;
            case 1:
                printf("Imie: %s\n", current -> name);
                printf("\nPodaj nowe imie: ");
                getchar();
                gets(current -> name);
                break;
            case 2:
                printf("Nazwisko: %s\n", current -> surname);
                printf("\nPodaj nowe nazwisko: ");
                getchar();
                gets(current -> surname);
                break;
            case 3:
                printf("Numer kontaktowy: %s\n", current -> phone);
                printf("\nPodaj nowy numer kontaktowy: ");
                getchar();
                gets(current -> phone);
                break;
            case 4:
                printf("Adres e-mail: %s\n", current -> email);
                printf("\nPodaj nowy adres e-mail: ");
                getchar();
                gets(current -> email);
                break;
            default:
                printf("Brak pola do edycji.\n");
                break;
        }
        system("cls");
    }
    }
}
