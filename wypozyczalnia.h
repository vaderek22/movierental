#ifndef WYPOZYCZALNIA_H_INCLUDED
#define WYPOZYCZALNIA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
/** \brief Struktura dynamiczna clients umożliwiająca operacje na klientach
 *
 * Struktura listy umożliwiająca operacje na klientach oraz plikach z danymi przechowującymi informacje o klientach.
 *
 */

struct clients
{
    char name[50];/**< Zmienna char przechowująca imię klienta */
    char surname[50];/**< Zmienna char przechowująca nazwisko klienta */
    char email[50];/**< Zmienna char przechowująca email klienta */
    char phone[50];/**< Zmienna char przechowująca numer telefonu klienta */
    int id;/**< Zmienna całkowita przechowująca identyfikator klienta */
    struct clients *next;/**< Wskaźnik na następne pole listy */
};
struct clients *first;/**< Wskaźnik umożliwiający poruszanie się po liście. Wskazujący na pierwszy element listy. */
struct clients *current;/**< Wskaźnik umożliwiający poruszanie się po liście. Wskazujący na aktualny element listy. */
struct clients *newclient;/**< Wskaźnik umożliwiający poruszanie się po liście. Wskazujący na nowy element listy. */
/** \brief Struktura dynamiczna movies umożliwiająca operacje na filmach
 *
 * Struktura listy umożliwiająca operacje na filmach oraz plikach z danymi przechowującymi informacje o filmach.
 *
 */

struct movies
{
    char title[50];/**< Zmienna char przechowująca tytuł filmu */
    int year;/**< Zmienna całkowita przechowująca rok produkcji filmu */
    char director[50];/**< Zmienna char przechowująca imię i nazwisko reżysera */
    char type[50];/**< Zmienna char przechowująca gatunek filmu */
    int copies;/**< Zmienna całkowita przechowująca ilość kopii filmu */
    int id;/**< Zmienna całkowita przechowująca identyfikator filmu */
    struct movies *next;/**< Wskaźnik na następne pole listy */
};
struct movies *firstm;/**< Wskaźnik umożliwiający poruszanie się po liście. Wskazujący na pierwszy element listy. */
struct movies *currentm;/**< Wskaźnik umożliwiający poruszanie się po liście. Wskazujący na aktualny element listy. */
struct movies *currentm2;/**< Pomocniczy wskaźnik umożliwiający poruszanie się po liście. Wskazujący na aktualny element listy. */
struct movies *newmovie;/**< Wskaźnik umożliwiający poruszanie się po liście. Wskazujący na nowy element listy. */

/** \brief Struktura date umożliwiająca operacje na dacie
 *
 * Strutkura date pomagająca w sprawdzaniu lat przestępnych oraz porównania dat.
 * Pomaga ona również w zapisie i odczycie daty z plików.
 *
 */

struct date
{
    int year;/**< Zmienna całkowita przechowująca rok */
    int month;/**< Zmienna całkowita przechowujaca miesiąc */
    int day;/**< Zmienna całkowita przechowująca dzieñ */
};
/** \brief Struktura dynamiczna rentals umożliwiająca operacje na wypożyczeniach filmów
 *
 * Struktura listy umożliwiająca operacje na wypożyczeniach oraz plikach z danymi przechowującymi informacje o wypożyczeniach.
 *
 */

struct rentals
{
    int id;/**< Zmienna całkowita przechowująca identyfikator wypożyczenia */
    int client_id;/**< Zmienna całkowita przechowująca identyfikator klienta, który wypożyczył film */
    int movie_id;/**< Zmienna całkowita przechowująca identyfikator filmu, który został wypożyczony */
    struct date rental_date;/**< Struktura przechowująca date wypożyczenia filmu */
    struct date return_date;/**< Struktura przechowująca date zwrotu filmu */
    struct rentals *next;/**< Wskaźnik na następne pole listy */
};
struct rentals *firstr;/**< Wskaźnik umożliwiający poruszanie się po liście. Wskazujący na pierwszy element listy. */
struct rentals *currentr;/**< Wskaźnik umożliwiający poruszanie się po liście. Wskazujący na aktualny element listy. */
struct rentals *newrental;/**< Wskaźnik umożliwiający poruszanie się po liście. Wskazujący na nowy element listy. */


extern void readclients();

extern void writeclients();

extern void add_clients();

extern int findnumberc(int);

extern void print_clients();

extern void delete_clients();

extern void clients_question();

extern void edit_clients();

extern void readmovies();

extern void writemovies();

extern void add_movies();

extern int findnumberm(int);

extern void print_movies();

extern void delete_movies();

extern void movies_question();

extern void edit_movies();

extern void find_movies();

extern void readrentals();

extern void writerentals();

extern int count_rentals_by_movies(int);

extern int count_rentals_by_clients(int);

extern int get_movie_copies(int);

extern int renting_question_1();

extern int renting_question_2();

extern void add_rentals();

extern int countLeapYears(struct date);

extern int getDifference(struct date ,struct date);

extern void print_rentals();

extern void delete_rentals();

extern void renting();

extern void wait();

extern int question_sort();

extern void sort_movies();

extern void swap_movies();

extern void sort_movies_by_director(int);

extern void sort_movies_by_title(int);

extern void sort_movies_by_type(int);

extern void sort_movies_by_year(int);

extern void sort_movies_by_id(int);

extern void sort_movies_by_copies(int);

#endif // WYPOZYCZALNIA_H_INCLUDED
