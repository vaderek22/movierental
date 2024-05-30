#include "wypozyczalnia.h"
/** \brief Funckja informujaca o przejsciu do glownego menu
 *
 */
void wait()
{
             printf("\n\n\n\n\n\n\t\t\t\t\tLadowanie");
            for(int i=0; i<3; i++)
            {
            printf(".");
            Sleep(300);
            }
             printf("\n");
             system("cls");
}
/** \brief Funkcja realizujaca menu programu oraz wszystkie jego skladowe
 *
 *
 */

int main()
{
    readclients();
    readmovies();
    readrentals();

    system("color e0");
    int choice;

    wait();
    printf("-------------------------------------------------------------------------");
    printf("\n\t\t\tWitaj w wypozyczalni filmow\n");
    printf("-------------------------------------------------------------------------");
    time_t t;
    time(&t);
    printf("\n\t\t\t%s", ctime(&t));

    while (choice != 11) {
        printf("\n-------------------------------------------------------------------------");
        printf("\n\t\t\tWybierz dzialanie\n\n");
        printf("1.Dodanie nowego klienta\t\t2.Wyswietl dane klientow\n3.Usun klienta\t\t\t\t4.Edycja klientow\n");
        printf("5.Dodanie nowego filmu\t\t\t6.Wyswietlenie filmow\n7.Usun film\t\t\t\t8.Edycja filmow\n");
        printf("9.Wypozyczenia\t\t\t\t10.Wyszukaj film\n");
        printf("0.Zapisz i wyjdz\n");
        printf("\n-------------------------------------------------------------------------");
        printf("\n\n\t\t\tWybor: ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 0:
                system("cls");
                writeclients();
                writemovies();
                exit(0);
                break;
            case 1:
                system("cls");
                add_clients();
                break;
            case 2:
                system("cls");
                print_clients();
                break;
            case 3:
                system("cls");
                delete_clients();
                break;
            case 4:
                system("cls");
                edit_clients();
                break;
            case 5:
                system("cls");
                add_movies();
                break;
            case 6:
                system("cls");
                sort_movies();
                break;
            case 7:
                system("cls");
                delete_movies();
                break;
            case 8:
                system("cls");
                edit_movies();
                break;
            case 9:
                system("cls");
                writeclients();
                writemovies();
                renting();
                break;
            case 10:
                system("cls");
                find_movies();
                break;
            default:
                system("cls");
                printf("Bledny wybor\n");
                break;
        }
    }
    return 0;
}
