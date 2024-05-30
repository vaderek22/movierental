#include "wypozyczalnia.h"

int rid=0;/**< Zmienna pomocnicza do określenia identyfikatora danego filmu */

/** \brief Funkcja odczytująca dane z pliku "rentals.txt"
 *
 * Otwiera plik, następnie rezerwuje pamięć na kolejne elementy listy rentals, w których zapisuje dane.
 *
 */
void readrentals()
{
    FILE *fp = fopen("rentals.txt", "r");

    firstr = NULL;

    if(fp)
    {
        firstr = (struct rentals *)malloc(sizeof(struct rentals));
        currentr = firstr;
        while(1)
        {
            newrental = (struct rentals *)malloc(sizeof(struct rentals));
            fread(currentr, sizeof(struct rentals), 1, fp);
            if(currentr -> next == NULL)
                break;
            currentr -> next = newrental;
            currentr = newrental;
        }
        fclose(fp);
        rid = currentr -> id;
    }
}
/** \brief Funkcja zapisująca dane do pliku "rentals.txt"
 *
 * Otwiera plik, następnie zapisuje dane z kolejnych elementów listy rentals do pliku.
 *
 */
void writerentals()
{
    FILE *fp = fopen("rentals.txt", "w");

    currentr = firstr;

    if(currentr == NULL)
        return;
    if(fp == NULL)
    {
        printf("Blad zapisu do pliku rentals.txt\n");
        return;
    }
    while(currentr != NULL)
    {
        fwrite(currentr, sizeof(struct rentals), 1, fp);
        currentr = currentr -> next;
    }
    fclose(fp);
}
/** \brief Funkcja zliczająca wypożyczenie filmu
 *
 * \param[in] movie_id identyfikator filmu, który jest sprawdzany
 *
 * \return Jeśli film nie jest wypożyczony to funkcja zwraca wartość 0, natomiast w przeciwnym przypadku zlicza ilość wypoźyczeń danego filmu i ją zwraca.
 *
 */

int count_rentals_by_movies(int movie_id)
{
    if (firstr == NULL)
        return 0;

    int counter = 0;

    currentr = firstr;
    while (currentr != NULL)
    {
        if (currentr->movie_id == movie_id)
            counter++;

        currentr = currentr -> next;
    }

    return counter;
}
/** \brief Funkcja sprawdzająca czy klient posiada wypożyczony film
 *
 * \param[in] client_id identyfikator klienta, który jest sprawdzany
 *
 * \return Jeśli klient nie posiada wypożyczenia to funkcja zwraca wartość 0, w przeciwnym wypadku zwraca ilość jego wypożyczeń.
 *
 */

int count_rentals_by_clients(int client_id)
{
    if (firstr == NULL)
        return 0;

    int counter = 0;

    currentr = firstr;
    while (currentr != NULL)
    {
        if (currentr->client_id == client_id)
            counter++;

        currentr = currentr -> next;
    }

    return counter;
}
/** \brief Funkcja zwracająca ilość kopii
 *
 * \param[in] movie_id identyfikator filmu, który jest sprawdzany
 *
 * \return W przypadku braku filmów funkcja zwraca warość -1, w przeciwnym wypadku zwraca ilość kopii filmu.
 *
 */

int get_movie_copies(int movie_id)
{
    currentm = firstm;

    while(currentm != NULL)
    {
        if(currentm -> id == movie_id)
            return currentm -> copies;

        currentm = currentm -> next;
    }

    return -1;
}
/** \brief Funkcja ustalająca klienta, który chce wypożyczyć film
 *
 * Pobiera od użytkownika numer karty klienta, a następnie sprawdza czy klient istnieje.
 * Po tym wyświetla jego dane i prosi o potwierdzenie. Funkcja trwa do momentu wybrania poprawnego klienta.
 *
 * \return W przypadku wpisania zmiennej "t"/"T" funkcja zwraca numer karty klienta, natomiast w przypadku wpisania "n"/"N" lub błędnego wyboru wraca do początku funkcji.
 *
 */

int renting_question_1()
{
    int client_id;

    printf("Karta klienta: ");
    scanf("%d", &client_id);

    if (findnumberc(client_id) < 1) {
        system("cls");
        printf("Karta klienta o id %d nie odnaleziona!\n", client_id);
        return renting_question_1();
    }
    printf("Klient: %s %s\n", current -> name,current -> surname);

    char option;
    printf("Chcesz kontynuowac? {T/N) ");
    getchar();
    scanf("%c", &option);
    if (option ==  't' || option == 'T')
    {
        system("cls");
        return client_id;
    }
    else if (option == 'n' || option == 'N')
    {
        system("cls");
        return renting_question_1();
    }
    else
    {
        system("cls");
        printf("Bledny wybor!");
        return renting_question_1();
    }
}
/** \brief Funkcja ustalająca film, który ma zostać wypożyczony
 *
 * Wyświetla informacje o kliencie.
 * Pobiera od użytkownika identyfikator filmu, a następnie sprawdza czy film istnieje.
 * Po tym wyświetla dane filmu i prosi o potwierdzenie. Funkcja trwa do momentu wybrania poprawnego filmu.
 *
 * \return W przypadku wpisania zmiennej "t"/"T" funkcja zwraca identyfikator filmu, natomiast w przypadku wpisania "n"/"N" lub błędnego wyboru wraca do początku funkcji.
 *
 */
int renting_question_2()
{
    int movie_id;

    printf("Karta klienta: %d\n",current -> id);
    printf("Klient: %s %s\n\n", current -> name,current -> surname);

    printf("ID filmu: ");
    scanf("%d", &movie_id);

    if (findnumberm(movie_id) < 1) {
        system("cls");
        printf("Film o id %d nie odnaleziony!\n", movie_id);
        return renting_question_2();
    }
    printf("Tytul: %s\n", currentm -> title);

    char option;
    printf("Chcesz kontynuowac? {T/N) ");
    getchar();
    scanf("%c", &option);
    if (option ==  't' || option == 'T')
    {
        return movie_id;
    }
    else if (option == 'n' || option == 'N')
    {
        system("cls");
        return renting_question_2();
    }
    else
    {
        system("cls");
        printf("Bledny wybor!");
        return renting_question_2();
    }
}
/** \brief Funkcja służąca do dodawania wypożyczeń
 *
 * Pobiera dane dotyczące wypożyczenia, następnie sprawdza czy film jest dostępny na magazynie.
 * Po tym pyta użytkownika na podstawie jakich dat chce zrealizowaæ wypożyczenie filmu.
 *
 * \return W przypadku braku filmu na magazynie wraca do menu wypożyczeń filmów.
 *
 */

void add_rentals()
{
    int client_id, movie_id;

    rid++;
    printf("ID wypozyczenia: %d\n", rid);

    printf("Podaj informacje o wypozyczeniu\n");

    getchar();

    client_id=renting_question_1();

    movie_id=renting_question_2();

    if (get_movie_copies(movie_id) - count_rentals_by_movies(movie_id) <= 0) {
        printf("Filmu o id %d nie ma juz na magazynie!\n", movie_id);
        rid--;
        return;
    }

    newrental = (struct rentals*) malloc(sizeof(struct rentals));

    if(firstr == NULL)
    {
        firstr = currentr = newrental;
    }
    else
    {
        currentr = firstr;
        while(currentr->next != NULL)
            currentr = currentr->next;
        currentr -> next = newrental;
        currentr = newrental;
    }

    currentr -> id = rid;
    currentr -> client_id = client_id;
    currentr -> movie_id = movie_id;

    int choice;
    time_t today_time;

        printf("\nWybierz:\n");
        printf("1.Biezaca data\n2.Wlasna data\n");
        printf("Wybor: ");
        scanf("%d",&choice);

        switch(choice)
        {
            default: printf("Brak wybranej opcji!\n");
                        break;

            case 1:

                time(&today_time);

                struct tm* today_info = localtime(&today_time);

                 currentr->rental_date.day=today_info->tm_mday;
                 currentr->rental_date.month=today_info->tm_mon + 1;
                 currentr->rental_date.year=today_info->tm_year + 1900;
                    break;

            case 2:

                printf("Dzien wypozyczenia ");
                scanf("%d", &(currentr -> rental_date.day));

                printf("Miesiac wypozyczenia ");
                scanf("%d", &(currentr -> rental_date.month));

                printf("Rok wypozyczenia ");
                scanf("%d", &(currentr -> rental_date.year));
                break;
        }

    printf("Dzien oddania ");
    scanf("%d", &(currentr -> return_date.day));

    printf("Miesiac oddania ");
    scanf("%d", &(currentr -> return_date.month));

    printf("Rok oddania ");
    scanf("%d", &(currentr -> return_date.year));

    printf("Wypozyczenie dodane pomyslnie!");
    currentr -> next = NULL;

}

const int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};/**< Tablica stałych zmiennych przechowująca ilość dni w poszczególnym miesiącu. */

/** \brief Funkcja sprawdzająca czy dany rok jest przestępny
 *
 * Gdy rok jest przestępny to funkcja pomaga w ustaleniu kary za nieoddanie filmu.
 *
 * \param[in] date struktura przekazująca date
 *
 * \return Zwraca wartość całkowitą pomagająca przy roku przestępnym.
 *
 */

int countLeapYears(struct date date)
{
    int years = date.year;

    if (date.month <= 2)
        years--;

    return years / 4 - years / 100 + years / 400;
}
/** \brief Funkcja obliczająca różnice między datami
 *
 * \param[in] date1 struktura przekazująca date zwrotu filmu
 * \param[in] date2 struktura przekazująca aktualną date
 *
 * \return Zwraca ilość dni pomiędzy podanymi datami.
 *
 */

int getDifference(struct date date1, struct date date2)
{
    long int n1 = date1.year * 365 + date1.day;

    for (int i = 0; i < date1.month - 1; i++)
        n1 += monthDays[i];

    n1 += countLeapYears(date1);

    long int n2 = date2.year * 365 + date2.day;
    for (int i = 0; i < date2.month - 1; i++)
        n2 += monthDays[i];

    n2 += countLeapYears(date2);

    return (n2 - n1);
}
/** \brief Funkcja wyœwietlająca wypożyczenia filmów
 *
 * Wyświetla listę filmów w postaci tabeli z podziałem na dane informacje.
 * Informuje rówież o karach w przypadku nieoddania filmu w terminie.
 * Karż za każdy dzieñ zwłoki jest mnożona przez 1.
 *
 * \return Jeśli nie ma żadnych wypożyczeń wraca do menu wypożyczeń.
 *
 */

void print_rentals()
{
    if(firstr == NULL)
    {
        puts("Brak wypozyczen do wyswietlenia!");
        return;
    }
    else
    {
        printf("%-6s %-15s %-12s %-25s %-25s %-12s\n","ID","Karta klienta","ID filmu","Data wypozyczenia","Data oddania", "Kara");
        puts("------ --------------- ------------ ------------------------- ------------------------- ------------");
        currentr = firstr;

        do
        {
            char* rental_date = (char*) malloc(10 * sizeof(char));
            sprintf(rental_date, "%d-%d-%d", currentr->rental_date.day, currentr->rental_date.month, currentr->rental_date.year);

            char* return_date = (char*) malloc(10 * sizeof(char));

            sprintf(return_date, "%d-%d-%d", currentr->return_date.day, currentr->return_date.month, currentr->return_date.year);

            char* rental_fine = (char* ) malloc(12 * sizeof(char));

            time_t today_time;
            time(&today_time);

            struct tm* today_info = localtime(&today_time);

            struct date today_date;
            today_date.year = today_info->tm_year + 1900;
            today_date.month = today_info->tm_mon + 1;
            today_date.day = today_info->tm_mday;

            struct date return_date_struct;
            return_date_struct.year = currentr->return_date.year;
            return_date_struct.month = currentr->return_date.month;
            return_date_struct.day = currentr->return_date.day;

            int date_diff = getDifference(return_date_struct, today_date);

            if (date_diff <= 0)
                sprintf(rental_fine, "BRAK");
            else
                sprintf(rental_fine, "%d PLN", 1 * date_diff);

            printf("%-6d %-15d %-12d %-25s %-25s %-12s\n", \
            currentr -> id,
                   currentr -> client_id,
                   currentr -> movie_id,
                   rental_date,
                   return_date,
                   rental_fine);
        }
        while((currentr = currentr -> next) != NULL);
    }
}
/** \brief Funkcja realizująca usuwanie wypożyczeń
 *
 * Usuwa podane wypożyczenie z listy, przy czym sprawdza czy istnieje.
 * Nastêępnie informuje o przebiegu operacji usuwania.
 *
 * \return W przypadku braku wypożyczeń wraca do menu wypożyczeń.
 */

void delete_rentals()
{
    int number;
    struct rentals *prev;

    if(firstr == NULL)
    {
        puts("Brak wypozyczen do usuniecia!");
        return;
    }
    else
    {
        printf("Podaj id wypozyczenia do usuniecia: ");
        scanf("%d", &number);
    }

    currentr = firstr;

    while(currentr != NULL)
    {
        if(currentr->id == number)
        {
            if(currentr == firstr)
                firstr = currentr -> next;
            else
                prev -> next = currentr -> next;
            free(currentr);
            printf("Wypozyczenie o id %d usuniety pomyslnie!\n", number);
            return;
        }
        else
        {
            prev = currentr;
            currentr = currentr -> next;
        }
    }
    printf("Wypozyczenie o id %d nie odnaleziony!\n", number);
}
/** \brief Funkcja realizująca menu wypożyczeń
 *
 * Korzysta z funkcji potrzebnych do realizacji wypożyczeń.
 *
 */

void renting()
{
    int choice;

    while (choice != 10) {
        printf("\nWybierz co chcesz wykonac\n");
        printf("1.Wyswietl wszystkie wypozyczenia\n");
        printf("2.Dodaj nowe wypozyczenie\n");
        printf("3.Usun istniejace wypozyczenie\n");
        printf("0.Zapisz i wyjdz\n");
        printf("Wybor: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 0:
                system("cls");
                writerentals();
                return main();
            case 1:
                system("cls");
                print_rentals();
                break;
            case 2:
                system("cls");
                add_rentals();
                break;
            case 3:
                system("cls");
                delete_rentals();
                break;
            default:
                system("cls");
                printf("Bledny wybor\n");
                break;
        }
    }
}
