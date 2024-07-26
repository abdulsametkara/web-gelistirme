/**
 * @file library.h
 *
 * @brief Provides functions for math. utilities
 */

#ifndef LIBRARY_H
#define LIBRARY_H
#include <iostream>
#define NUM_BOOKS 5


#include "../../utility/header/commonTypes.h"

int showMainMenu();
int userAuthenticator();
int searchCatalog();
int reservationAndRenewal();
int showEventsAndWorkshops();
int showLibraryInfo();
int mainMenu();
int searchBook();
int searchMovie();
int searchMusic();
int registerUser();
int loginPanel(const char *userFilePath);
int showEvents();
int registerForEvent(const char *userName);
int listMusic();
int listBook();
int listMovie();
int listLibraries();
int searchLibrary();
int reserveBook();
int renewBook();
int viewReservation();
int recommendBooksWithinBudget();
int searchAndRecommendMovies();
void matrix_multiply(float prices[1][NUM_BOOKS], int quantities[NUM_BOOKS][1], float result[1][1]);
int analyze(float result[1][1]);
int matrixChainOrder(int *p, int n);



#endif // LIBRARY_H
