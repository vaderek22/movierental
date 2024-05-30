#include "wypozyczalnia.h"
/** \brief Funkcja odczytująca dane z pliku "movies.txt"
 *
 * Otwiera plik, następnie rezerwuje pamięć na kolejne elementy listy movies, w których zapisuje dane.
 *
 */

void readmovies()
{
    FILE *fp = fopen("movies.txt", "r");

    firstm = NULL;

    if(fp)
    {
        firstm = (struct movies *)malloc(sizeof(struct movies));
        currentm = firstm;
        while(1)
        {
            newmovie = (struct movies *)malloc(sizeof(struct movies));
            fread(currentm, sizeof(struct movies), 1, fp);
            if(currentm -> next == NULL)
                break;
            currentm -> next = newmovie;
            currentm = newmovie;
        }
        fclose(fp);

    }
}
/** \brief Funkcja zapisująca dane do pliku "movies.txt"
 *
 * Otwiera plik, następnie zapisuje dane z kolejnych elementów listy movies do pliku.
 *
 */
void writemovies()
{
    FILE *fp = fopen("movies.txt", "w");

    currentm = firstm;

    if(currentm == NULL)
        return;
    if(fp == NULL)
    {
        printf("Blad zapisu do pliku movies.txt\n");
        return;
    }
    while(currentm != NULL)
    {
        fwrite(currentm, sizeof(struct movies), 1, fp);
        currentm = currentm -> next;
    }
    fclose(fp);
}
/** \brief Funkcja realizująca dodawanie filmów
 *
 * Rezerwuje miejsce w pamięci, aby dodać nowy element do listy movies, a następnie pobiera dane dotyczące danego filmu.
 *
 */
void add_movies()
{
    newmovie = (struct movies *)malloc(sizeof(struct movies));
    int mid=0;
    if(firstm == NULL)
    {
        firstm = currentm = currentm2 = newmovie;
    }
    else
    {
        currentm = firstm;
        while(currentm->next != NULL)
            currentm = currentm->next;
        currentm -> next = newmovie;
        currentm = newmovie;
    }

    for(currentm2=firstm;currentm2!=newmovie;currentm2=currentm2->next)
        {
        if(mid<=currentm2->id)
            mid=currentm2->id;
        }

    mid++;

    printf("ID filmu: %d\n", mid);
    currentm -> id = mid;

    printf("Podaj informacje o filmie\n");

    getchar();
    printf("Tytul: ");
    gets(currentm -> title);

    printf("Rezyser: ");
    gets(currentm -> director);

    printf("Gatunek: ");
    gets(currentm -> type);

    printf("Rok wydania: ");
    scanf("%d",&(currentm -> year));

    printf("Ilosc kopii: ");
    scanf("%d",&(currentm -> copies));

    printf("Film dodany pomyslnie!");
    currentm -> next = NULL;
}
/** \brief Funkcja sprawdzająca istnienie rekordu filmu
 *
 * \param[in] recordnumber zmienna przekazująca numer rekordu(identyfikatora)
 * \return W przypadku gdy rekord istnieje to funkcja zwraca wartość 1, a w przypadku nieodnalezienia go zwraca -1.
 *
 */
int findnumberm(int recordnumber)
{
    int record;
    record = recordnumber;
    currentm = firstm;
    while(currentm != NULL)
    {
        if(currentm -> id == record)
        {
            return 1;
        }
        else
        {
            currentm = currentm -> next;
        }
    }
    return -1;
}
/** \brief Funkcja realizująca wyœwitlanie listy filmów
 *
 * Umożliwia wyœwietlenie listy filmów w postaci tabeli z podziałem na dane informacje.
 *
 */
void print_movies()
{
    if(firstm == NULL)
    {
        puts("Brak filmow do wyswietlenia!");
        return;
    }
    else
    {
        printf("%-6s %-25s %-25s %-25s %-25s %-6s\n","ID","Tytul","Rezyser","Gatunek","Rok premiery","Ilosc");
        puts("------ ------------------------- ------------------------- ------------------------- ------------------------- ------");
        currentm=firstm;

        do
        {
            int copies_rented = count_rentals_by_movies(currentm->id);

            printf("%-6d %-25s %-25s %-25s %-25d %-6d\n",\
            currentm -> id,
                   currentm -> title,
                   currentm -> director,
                   currentm -> type,
                   currentm -> year,
                   currentm -> copies - copies_rented);
        }
        while((currentm = currentm -> next) != NULL);
    }
}
/** \brief Funkcja realizująca usuwanie filmów
 *
 * Usuwa podany film z listy, przy czym sprawdza czy istnieje lub jest wypożyczony.
 * Następnie informuje o przebiegu operacji usuwania.
 *
 */
void delete_movies()
{
    int number;
    struct movies *prev;

    if(firstm == NULL)
    {
        puts("Brak filmow do usuniecia!");
        return;
    }
    else
    {
        printf("Podaj id filmu do usuniecia: ");
        scanf("%d", &number);
    }

    currentm = firstm;

    while(currentm != NULL)
    {
        if(currentm->id == number)
        {
            if (count_rentals_by_movies(number) > 0) {
                printf("Film o id %d jest wypozyczony i nie moze zostac usuniety!\n", number);
                return;
            }

            if(currentm == firstm)
                firstm = currentm -> next;
            else
                prev -> next = currentm -> next;
            free(currentm);
            printf("Film o id %d usuniety pomyslnie!\n", number);
            return;
        }
        else
        {
            prev = currentm;
            currentm = currentm -> next;
        }
    }
    printf("Film o id %d nie odnaleziony!\n", number);
}
/** \brief Funkcja realizująca pytanie potwierdzające decyzje odnośnie edycji filmów
 *
 * \return W przypadku wpisania zmiennej "t"/"T" funkcja umożliwi dalesze działanie, natomiast gdy wpiszemy "n"/"N" lub inny znak wraca do początku funkcji edit_movies().
 *
 */
void movies_question()
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
        return edit_movies();
    }
    else
    {
        printf("Bledny wybor!\n");
        return edit_movies();
    }
}
/** \brief Funkcja umożliwiająca edycje danych filmów
 *
 * Pobiera identyfikator filmu do edycji, a następnie prosi o potwierdzenie wyboru. Po czym można edytowaæ dowolne pole lub wrócić do menu głównego.
 *
 * \return W przypadku braku filmów wraca do menu głównego lub jeśli nie znajdzie podanego filmu wraca do początku funkcji.
 *
 */
void edit_movies()
{
    int number, result, option;

    if(firstm == NULL)
    {
        puts("Brak filmow do edycji!");
        return;
    }
    else
    {
        printf("Podaj id filmu do edycji: ");
        scanf("%d", &number);
    if (findnumberm(number) < 1)
    {
        printf("Film o id %d nie odnaleziony!\n\n", number);
        return edit_movies();
    }
        printf("Film: %s\n", currentm -> title);
        movies_question();
    }

    result = findnumberm(number);

    while(1)
    {
    if(result>0)
    {
        printf("ID filmu: %d\n", currentm -> id);

        printf("Wybierz co chcesz edytowac:\n");
        printf("1.Tytul\n2.Rezyser\n3.Gatunek\n4.Rok\n0.Wroc do menu\nWybor: ");
        scanf("%d",&option);

        switch(option)
        {
            case 0:
                system("cls");
                writemovies();
                return main();
                break;
            case 1:
                printf("Tytul: %s\n", currentm -> title);
                printf("\nPodaj nowy tytul: ");
                getchar();
                gets(currentm -> title);
                break;
            case 2:
                printf("Rezyser: %s\n", currentm -> director);
                printf("\nPodaj nowego rezysera: ");
                getchar();
                gets(currentm -> director);
                break;
            case 3:
                printf("Gatunek: %s\n", currentm -> type);
                printf("\nPodaj nowy gatunek: ");
                getchar();
                gets(currentm -> type);
                break;
            case 4:
                printf("Rok produkcji: %d\n", currentm -> year);
                printf("\nPodaj nowy rok: ");
                getchar();
                scanf("%d",&currentm -> year);
                break;
            default:
                printf("Brak pola do edycji.\n");
                break;
        }
        system("cls");
    }
    }
}
/** \brief Funkcja wyszukująca pojedynczy film
 *
 * Wyszukuje film po identyfikatorze, a następnie wyświetla jego dane.
 *
 *\return W przypadku braku filmów wraca do menu głównego.
 */

void find_movies()
{
    int number, result;
    if(firstm == NULL)
    {
        puts("Brak filmow!");
        return;
    }
    else
    {
        printf("Podaj ID filmu: ");
        scanf("%d", &number);
    }
    result = findnumberm(number);

    if(result>0)
    {

        printf("%-20s %-20s %-15s %-20s %-6s\n","Tytul","Rezyser","Gatunek","Rok premiery","Ilosc");
        puts("-------------------- -------------------- --------------- -------------------- ------");

            int copies_rented = count_rentals_by_movies(currentm->id);
            printf("%-20s %-20s %-15s %-20d %-6d\n",\

                   currentm -> title,
                   currentm -> director,
                   currentm -> type,
                   currentm -> year,
                   currentm -> copies - copies_rented);
    }
    else
    printf("Film o ID %d nie odnaleziony!\n", number);

}
/** \brief Funkcja realizująca pytanie odnośnie sortowania filmów
 *
 * \return W przypadku wpisania zmiennej "r"/"R" funkcja zwraca 1, natomiast gdy wpiszemy "m"/"M" to zwraca -1, w przypadku innej zmiennej informuje o b³êdnym wyborze.
 *
 */
int question_sort()
{
    char option;
    printf("\nChcesz sortowac rosnaco czy malejaco? {R/M) ");
    printf("R-rosnaco | M-malejaco\nWybor: ");
    getchar();
    scanf("%c", &option);
    if (option ==  'r' || option == 'R')
    {
        return 1;
    }
    else if (option == 'm' || option == 'M')
    {

        return -1;
    }
    else
        printf("Bledny wybor!\n");
}
/** \brief Funkcja będąca menu sortowania filmów
 *
 * Wyświetla wszystkie filmy, a następnie pyta w jaki sposób filmy mają być posortowane i po jakim polu.
 *
 */

void sort_movies()
{
    int choice;
    while(1)
    {
    print_movies();

    printf("\nSortuj po:\n");
    printf("1.Tytul\n2.Rezyser\n3.Gatunek\n4.Rok\n5.ID\n6.Ilosc kopii\n\n0.Wroc do menu\n");
    printf("Wybor: ");
    scanf("%d",&choice);

    switch(choice)
    {
    case 0:
        system("cls");
        return;
        break;
    case 1:
        sort_movies_by_title(question_sort());
        system("cls");
        break;
    case 2:
        sort_movies_by_director(question_sort());
        system("cls");
        break;
    case 3:
        sort_movies_by_type(question_sort());
        system("cls");
        break;
    case 4:
        sort_movies_by_year(question_sort());
        system("cls");
        break;
    case 5:
        sort_movies_by_id(question_sort());
        system("cls");
        break;
    case 6:
        sort_movies_by_copies(question_sort());
        system("cls");
        break;
    default:
        system("cls");
        printf("Bledny wybor!\n");
        break;
    }
    }
}
/** \brief Funkcja służąca do zamiany danych listy
 *
 * Zamienia dane dwóch elementów listy. Przypisuje pierwszemu dane drugiego, a drugiemu dane pierwszego.
 *
 */

void swap_movies()
{
    char temp_title[50];
    int temp_year;
    char temp_director[50];
    char temp_type[50];
    int temp_copies;
    int temp_id;

            strcpy(temp_title,currentm2->title);
            temp_year=currentm2->year;
            strcpy(temp_director,currentm2->director);
            strcpy(temp_type,currentm2->type);
            temp_copies=currentm2->copies;
            temp_id=currentm2->id;

            strcpy(currentm2->title,currentm->title);
            currentm2->year=currentm->year;
            strcpy(currentm2->director,currentm->director);
            strcpy(currentm2->type,currentm->type);
            currentm2->copies=currentm->copies;
            currentm2->id=currentm->id;

            strcpy(currentm->title,temp_title);
            currentm->year=temp_year;
            strcpy(currentm->director,temp_director);
            strcpy(currentm->type,temp_type);
            currentm->copies=temp_copies;
            currentm->id=temp_id;

}
/** \brief Funkcja sortująca filmy według pola reżyser
 *
 * \param[in] x zmienna, która określa sposób sortowania filmów
 *
 */

void sort_movies_by_director(int x)
{
    if(firstm==NULL)
        return;

    for(currentm2=firstm;currentm2->next!=NULL;currentm2=currentm2->next)
      for(currentm=currentm2->next;currentm!=NULL;currentm=currentm->next)
        {
         if(strcmp(currentm2->director,currentm->director)==x)
         {
            swap_movies();
         }
        }
}

/** \brief Funkcja sortująca filmy według pola tytuł
 *
 * \param[in] x zmienna, która określa sposób sortowania filmów
 *
 */

void sort_movies_by_title(int x)
{
    if(firstm==NULL)
        return;

    for(currentm2=firstm;currentm2->next!=NULL;currentm2=currentm2->next)
      for(currentm=currentm2->next;currentm!=NULL;currentm=currentm->next)
        {
         if(strcmp(currentm2->title,currentm->title)==x)
         {
            swap_movies();
         }
        }
}
/** \brief Funkcja sortująca filmy według pola gatunek
 *
 * \param[in] x zmienna, która określa sposób sortowania filmów
 *
 */
void sort_movies_by_type(int x)
{
    if(firstm==NULL)
        return;

    for(currentm2=firstm;currentm2->next!=NULL;currentm2=currentm2->next)
      for(currentm=currentm2->next;currentm!=NULL;currentm=currentm->next)
        {
         if(strcmp(currentm2->type,currentm->type)==x)
         {
            swap_movies();
         }
        }
}
/** \brief Funkcja sortująca filmy według pola rok produkcji
 *
 * \param[in] x zmienna, która określa sposób sortowania filmów
 *
 */
void sort_movies_by_year(int x)
{
    if(firstm==NULL)
        return;

  for(currentm2=firstm;currentm2->next!=NULL;currentm2=currentm2->next)
      for(currentm=currentm2->next;currentm!=NULL;currentm=currentm->next)
        {
         if((currentm2->year>currentm->year)&&(x==1))
            swap_movies();

         if((currentm2->year<currentm->year)&&(x==-1))
            swap_movies();
        }
}
/** \brief Funkcja sortująca filmy według pola identyfikator(ID)
 *
 * \param[in] x zmienna, która określa sposób sortowania filmów
 *
 */
void sort_movies_by_id(int x)
{
    if(firstm==NULL)
        return;

    for(currentm2=firstm;currentm2->next!=NULL;currentm2=currentm2->next)
      for(currentm=currentm2->next;currentm!=NULL;currentm=currentm->next)
        {
         if((currentm2->id>currentm->id)&&(x==1))
            swap_movies();

         if((currentm2->id<currentm->id)&&(x==-1))
            swap_movies();
        }
}
/** \brief Funkcja sortująca filmy według pola ilość kopii
 *
 * \param[in] x zmienna, która określa sposób sortowania filmów
 *
 */
void sort_movies_by_copies(int x)
{
    if(firstm==NULL)
        return;

    for(currentm2=firstm;currentm2->next!=NULL;currentm2=currentm2->next)
      for(currentm=currentm2->next;currentm!=NULL;currentm=currentm->next)
        {
         if((currentm2->copies>currentm->copies)&&(x==1))
            swap_movies();

         if((currentm2->copies<currentm->copies)&&(x==-1))
            swap_movies();
        }
}


