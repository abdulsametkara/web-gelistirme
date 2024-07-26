#include "../header/library.h"
#include <stdexcept>
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#define NUM_BOOKS 5
#define MATRIX_CHAIN_LENGTH 6

#ifdef _WIN32
  #define CLEAR_SCREEN "cls"
#else
  #define CLEAR_SCREEN "clear"
#endif

typedef struct {
  char username[50];
  char password[50];
} User;


typedef struct {
  int id;
  const char *title;
  const char *author;
  const char *genre;
  float price;

} Book;

typedef struct {
  int id;
  const char *name;
  const char *director;
  const char *genre;
} Movie;

typedef struct {
  int id;
  const char *title;
  const char *artist;
  const char *genre;
} Music;

typedef struct {
  int id;
  char title[100];
  char author[100];
  bool reserved;
} Books;

typedef struct {
  int id;
  const char *title;
  const char *date;
  const char *time;
  const char *location;
  const char *description;
} Event;

typedef struct {
  char name[50];
  char eventName[60];
  int eventNumber;
} UserRegistration;

typedef struct {
  const char *name;
  const char *city;
  const char *address;
  const char *hours;
  const char *contact;
} Librarys;

typedef struct {
  int id;
  int weight;
  int value;
} Item;

typedef struct {
  int matrixSize[NUM_BOOKS + 1]; 
} MatrixChain;


Librarys libraries[] = {
  {
    "Uskudar Library", "Istanbul", "123 Library St, Istanbul, TR 34122",
    "Mon-Fri 9:00 AM to 7:00 PM, Sat-Sun 10:00 AM to 4:00 PM",
    "+90 212 123 45 67"
  },
  {
    "Camlıca Library", "Istanbul", "975 Library St, Istanbul, TR 34172",
    "Mon-Fri 9:00 AM to 7:00 PM, Sat-Sun 10:00 AM to 4:00 PM",
    "+90 212 123 45 67"
  },
  {
    "Rize Library", "Rize", "456 Library Ave, Rize, TR 53430",
    "Mon-Fri 8:00 AM to 6:00 PM, Sat 9:00 AM to 5:00 PM",
    "+90 232 234 56 78"
  },
  {
    "Izmır Library", "Izmir", "886 Library St, Izmir, TR 35430",
    "Mon-Fri 8:00 AM to 6:00 PM, Sat 9:00 AM to 5:00 PM",
    "+90 232 234 56 78"
  },
  {
    "Kordon Library", "Izmir", "106 Library St, Izmir, TR 35930",
    "Mon-Fri 8:00 AM to 6:00 PM, Sat 9:00 AM to 5:00 PM",
    "+90 232 234 56 78"
  },
  {
    "Fatih Library", "Trabzon", "789 Library Rd, Trabzon, TR 61000",
    "Mon-Fri 8:00 AM to 5:00 PM, Closed on Weekends",
    "+90 462 321 65 43"
  },
  {
    "Cukurova Library", "Adana", "101 Library Blvd, Adana, TR 01120",
    "Mon-Fri 9:00 AM to 5:00 PM, Sat 10:00 AM to 2:00 PM",
    "+90 322 456 78 90"
  },
  {
    "Hevsel Library", "Diyarbakir", "202 Library Ln, Diyarbakir, TR 21000",
    "Mon-Fri 9:00 AM to 7:00 PM, Sat 11:00 AM to 3:00 PM",
    "+90 412 567 89 01"
  }
};



Books library[] = {
  {0, "To Kill a Mockingbird", "Harper Lee", true},
  {1, "1984", "George Orwell", false},
  {2, "The Great Gatsby", "F. Scott Fitzgerald", true},
  {3, "Pride and Prejudice", "Jane Austen", false},
  {4, "The Catcher in the Rye", "J.D. Salinger", true},
  {5, "Animal Farm", "George Orwell", false},
  {6, "The Lord of the Rings", "J.R.R. Tolkien", false},
  {7, "The Hobbit", "J.R.R. Tolkien", false},
  {8, "Brave New World", "Aldous Huxley", false},
  {9, "Harry Potter and the Sorcerer's Stone", "J.K. Rowling", false},
  {10, "The Chronicles of Narnia", "C.S. Lewis", false},
  {11, "The Hunger Games", "Suzanne Collins", true},
  {12, "The Da Vinci Code", "Dan Brown", false},
  {13, "The Hitchhiker's Guide to the Galaxy", "Douglas Adams", false}
};
int viewReservation() {
  printf("Books not on reservation:\n");

  for (int i = 0; i < sizeof(library) / sizeof(library[0]); i++) {
    if (!library[i].reserved) {
      printf("ID: %d, Title: %s, Author: %s\n", library[i].id, library[i].title, library[i].author);
    }
  }

  printf("\n");
  return 0;
}

int renewBook() {
  int bookId;
  printf("Enter the ID number of the book to renew: ");
  scanf("%d", &bookId);

  if (bookId < 0 || bookId >= sizeof(library) / sizeof(library[0])) {
    printf("Invalid book number!\n");
    return -1;
  }

  if (!library[bookId].reserved) {
    printf("This book is already available!\n");
    return 0;
  } else {
    library[bookId].reserved = false;
    printf("Book returned: %s\n", library[bookId].title);
    return 1;
  }
}

int reserveBook() {
  int id;
  printf("Enter the ID number of the book to reserve: ");
  scanf("%d", &id);

  if (id < 0 || id >= sizeof(library) / sizeof(library[0])) {
    printf("Invalid book number!\n");
    return -1;
  }

  if (library[id].reserved) {
    printf("This book is already reserved!\n");
    return 0;
  }

  library[id].reserved = true;
  printf("Book reserved: %s\n", library[id].title);
  return 1;
}

int loginPanel(const char *userFilePath) {
  User user;
  FILE *file;
  char username[50];
  char password[50];
  printf(":Username ");
  scanf("%49s", username);
  printf("Password: ");
  scanf("%49s", password);

  if ((file = fopen(userFilePath, "rb")) == NULL) {
    printf("The file could not be opened.\n");
    return 0;
  }

  while (fread(&user, sizeof(User), 1, file) == 1) {
    if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
      fclose(file);
      return 1;
    }
  }

  fclose(file);
  return 0;
}

int registerUser() {
  User user;
  printf("Username: ");
  scanf("%s", user.username);
  printf("Password: ");
  scanf("%s", user.password);
  FILE *file;

  if ((file = fopen("user.bin", "ab")) == NULL) {
    printf("File could not be opened.\n");
    return 1;
  }

  fwrite(&user, sizeof(User), 1, file);
  fclose(file);
  printf("The user has been successfully registered.\n");
  return 0;
}

int showMainMenu() {
  printf("******* LIBRARY MANAGEMENT SYSTEM *******\n");
  printf("1. User Authenticator\n");
  printf("2. Catalog Search\n");
  printf("3. Reservation and Renewal\n");
  printf("4. Event and Workshop\n");
  printf("5. Library Information\n");
  printf("6. Algorithms\n");
  printf("0. Exit\n\n");
  printf("Enter your choice [0-6]: ");
  return 0;
}

int userAuthenticator() {
  int choice;
  printf("\n--- User Authenticator ---\n");
  printf("1. Login\n");
  printf("2. Register\n");
  printf("3. Guest Mode\n");
  printf("0. Exit\n");
  printf("Enter your choice [0-3]: ");
  scanf("%d", &choice);

  if (choice == 1) {
    printf("\n--- Login ---\n");

    if (loginPanel("user.bin"))
      printf(" Login successful.\n");
    else
      printf("Username or password is incorrect.\n");
  } else if (choice == 2) {
    printf("\n--- Register ---\n");
    registerUser();
  } else if (choice == 3) {
    printf("You have successfully logged in\n");
  } else if (choice == 0) {
    printf("Returned To Main Menu!\n");
  } else {
    printf("Invalid choice. Please enter a valid option.\n");
  }

  return 0;
}

int searchCatalog() {
  int choice;
  printf( "\n--- Catalog Search ---\n");
  printf( "1. Book List\n");
  printf( "2. Book Search\n");
  printf( "3. Movie List\n");
  printf( "4. Movie Search\n");
  printf( "5. Music List\n");
  printf( "6. Music Search\n");
  printf( "0. Exit\n");
  printf( "Enter your choice [0-6]: ");
  scanf("%d", &choice);

  if (choice == 1) {
    printf( "\n--- Book List ---\n");
    listBook();
  } else if (choice == 2) {
    printf( "\n--- Book Search ---\n");
    searchBook();
  } else if (choice == 3) {
    printf( "\n--- Movie List ---\n");
    listMovie();
  } else if (choice == 4) {
    printf( "\n--- Movie Search ---\n");
    searchMovie();
  } else if (choice == 5) {
    printf( "\n--- Music List ---\n");
    listMusic();
  } else if (choice == 6) {
    printf( "\n--- Music Search ---\n");
    searchMusic();
  } else if (choice == 0) {
    printf( "Returned To Main Menu!\n");
  } else {
    printf( "Invalid choice. Please enter a valid option.\n");
  }

  return 0;
}

int reservationAndRenewal() {
  int choice;
  printf( "\n--- Reservation and Renewal System ---\n");
  printf( "1. Reserve Items\n");
  printf( "2. Renew Items\n");
  printf( "3. View Reservation\n");
  printf( "0. Exit\n");
  printf( "Enter your choice [0-3]: ");
  scanf( "%d", &choice);

  if (choice == 1) {
    printf( "\n--- Reserve Items ---\n");
    reserveBook();
  } else if (choice == 2) {
    printf( "\n--- Renew Items ---\n");
    renewBook();
  } else if (choice == 3) {
    printf( "\n--- View Reservation ---\n");
    viewReservation();
  } else if (choice == 0) {
    printf( "Returned To Main Menu!\n");
  } else {
    printf( "Invalid choice. Please enter a valid option.\n");
  }

  return 0;
}

int showEventsAndWorkshops() {
  int choice;
  printf( "\n--- Event And Workshop Schedule ---\n");
  printf( "1. View Events\n");
  printf( "2. Register for Events\n");
  printf( "0. Exit\n");
  printf( "Enter your choice [0-2]: ");
  scanf( "%d", &choice);

  if (choice == 1) {
    printf( "Displaying events...\n");
    showEvents();
    // Burada etkinlikleri listeleme işlevini çağırın
  } else if (choice == 2) {
    printf( "\n--- Register for Events ---\n");
    registerForEvent("Username");
  } else if (choice == 0) {
    printf( "Returned To Main Menu!\n");
  } else {
    printf( "Invalid choice. Please enter a valid option.\n");
  }

  return 0;
}


int showLibraryInfo() {
  int choice;
  printf( "\n--- Library Location And Hours ---\n");
  printf( "1. List Library\n");
  printf( "2. View Locations\n");
  printf( "0. Exit\n");
  printf( "Enter your choice [0-2]: ");
  scanf( "%d", &choice);

  if (choice == 1) {
    printf( "\n--- List Library ---\n");
    listLibraries();
  } else if (choice == 2) {
    printf( "\n--- View Locations ---\n");
    searchLibrary();
  } else if (choice == 0) {
    printf( "Returned To Main Menu!\n");
  } else {
    printf( "Invalid choice. Please enter a valid option.\n");
  }

  return 0;
}

int showAlgorithmsMenu() {
  int choice;
  printf("\n--- Algorithms ---\n");
  printf("1. Knapsack\n");
  printf("2. LCS Recommend\n");
  printf("3. Recursive Matrix\n");
  printf("4. Matrix Chain Multiplication Order\n");
  printf("0. Exit\n");
  printf("Enter your choice [0-4]: ");
  scanf("%d", &choice);
  int matrix_sizes[NUM_BOOKS + 1] = { 5, 10, 3, 12, 5, 50 }; // Örnek boyutlar

  if (choice == 1) {
    printf("\n--- Knapsack ---\n");
    recommendBooksWithinBudget();
  } else if (choice == 2) {
    printf("\n--- LCS Recommend ---\n");
    searchAndRecommendMovies();
  } else if (choice == 3) {
    printf("\n--- Recursive Matrix ---\n");
    float prices[1][NUM_BOOKS] = { {50.0, 70.0, 40.0, 35.0, 45.0} };
    int quantities[NUM_BOOKS][1] = { {1}, {2}, {3}, {4}, {5} };
    float result[1][1];
    matrix_multiply(prices, quantities, result);
    analyze(result);
  } else if (choice == 4) {
    printf("\n--- Matrix Chain Multiplication Order ---\n");
    int size = sizeof(matrix_sizes) / sizeof(matrix_sizes[0]);
    int cost = matrixChainOrder(matrix_sizes, size);
    printf("Minimum number of multiplications is %d\n", cost);
  } else if (choice == 0) {
    printf("Returned To Main Menu!\n");
  } else {
    printf("Invalid choice. Please enter a valid option.\n");
  }

  return 0;
}

int mainMenu() {
  int choice;

  while (true) {
    showMainMenu();
    scanf( "%d", &choice);
    system(CLEAR_SCREEN);

    if (choice == 1) {
      userAuthenticator();
    } else if (choice == 2) {
      searchCatalog();
    } else if (choice == 3) {
      reservationAndRenewal();
    } else if (choice == 4) {
      showEventsAndWorkshops();
    } else if (choice == 5) {
      showLibraryInfo();
    } else if (choice == 6) {
      showAlgorithmsMenu();
    } else if (choice == 0) {
      printf( "Exiting the program...\n");
      return 0;
    } else {
      printf( "Invalid choice. Please enter a valid option.\n");
    }
  }

  return 0;
}


int binarySearch(Book books[], int left, int right, int targetId) {
  if (right >= left) {
    int mid = left + (right - left) / 2;

    if (books[mid].id == targetId) {
      return mid;
    }

    if (books[mid].id > targetId) {
      return binarySearch(books, left, mid - 1, targetId);
    }

    return binarySearch(books, mid + 1, right, targetId);
  }

  return -1;
}

int searchBook() {
  const int numBooks = 5;
  Book books[numBooks] = {
    {1, "The Catcher in the Rye", "J.D. Salinger", "Fiction", 50.0},
    {2, "To Kill a Mockingbird", "Harper Lee", "Classics", 70.0},
    {3, "1984", "George Orwell", "Dystopian", 40.0},
    {4, "Pride and Prejudice", "Jane Austen", "Romance", 35.0},
    {5, "The Great Gatsby", "F. Scott Fitzgerald", "Classics", 45.0}
  };
  int targetId;
  printf("\nEnter the book ID to search: ");
  scanf("%d", &targetId);
  int result = binarySearch(books, 0, numBooks - 1, targetId);

  if (result != -1) {
    printf("Book found:\n");
    printf("ID: %d\tTitle: %s\tAuthor: %s\tGenre: %s\tPrice: %.2fTL\n", books[result].id, books[result].title, books[result].author, books[result].genre, books[result].price);
  } else {
    printf("Book not found.\n");
  }

  return 0;
}

int listBook() {
  const int numBooks = 5;
  Book books[numBooks] = {
    {1, "The Catcher in the Rye", "J.D. Salinger", "Fiction", 50.0},
    {2, "To Kill a Mockingbird", "Harper Lee", "Classics", 70.0},
    {3, "1984", "George Orwell", "Dystopian", 40.0},
    {4, "Pride and Prejudice", "Jane Austen", "Romance", 35.0},
    {5, "The Great Gatsby", "F. Scott Fitzgerald", "Classics", 45.0}
  };

  for (int i = 0; i < numBooks; i++) {
    printf("ID: %d\tTitle: %s\tAuthor: %s\tGenre: %s\tPrice: %.2fTL\n", books[i].id, books[i].title, books[i].author, books[i].genre, books[i].price);
  }

  return 0;
}

int hoarePartition(Movie arr[], int low, int high) {
  int pivotIndex = low + rand() % (high - low + 1);
  Movie pivot = arr[pivotIndex];
  int i = low - 1, j = high + 1;

  while (1) {
    do {
      i++;
    } while (arr[i].id < pivot.id);

    do {
      j--;
    } while (arr[j].id > pivot.id);

    if (i >= j) return j;

    Movie temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
  }
}

int randomizedQuickSort(Movie arr[], int low, int high) {
  if (low < high) {
    int pi = hoarePartition(arr, low, high);
    randomizedQuickSort(arr, low, pi);
    randomizedQuickSort(arr, pi + 1, high);
  }

  return 0;
}
int binarySearchMovies(Movie movies[], int left, int right, int targetId) {
  while (left <= right) {
    int mid = left + (right - left) / 2;

    if (movies[mid].id == targetId) return mid;

    if (movies[mid].id < targetId) left = mid + 1;
    else right = mid - 1;
  }

  return -1;
}

int searchMovie() {
  const int numMovies = 5;
  Movie movies[numMovies] = {
    {1, "Inception", "Christopher Nolan", "Sci-Fi"},
    {2, "Forrest Gump", "Robert Zemeckis", "Drama"},
    {3, "The Shawshank Redemption", "Frank Darabont", "Drama"},
    {4, "Pulp Fiction", "Quentin Tarantino", "Crime"},
    {5, "The Dark Knight", "Christopher Nolan", "Action"}
  };
  int targetId;
  printf("\nEnter the movie ID to search: ");
  scanf("%d", &targetId);
  int result = binarySearchMovies(movies, 0, numMovies - 1, targetId);

  if (result != -1) {
    printf("Movie found:\n");
    printf("ID: % d\tTitle: % s\tDirector: % s\tGenre: % s\n", movies[result].id, movies[result].name, movies[result].director, movies[result].genre);
  } else {
    printf("Movie not found.\n");
  }

  return 0;
}

int listMovie() {
  const int numFilms = 5;
  Movie films[numFilms] = {
    {1,"Inception", "Christopher Nolan", "Sci-Fi"},
    {3,"The Shawshank Redemption", "Frank Darabont", "Drama"},
    {5,"The Dark Knight", "Christopher Nolan", "Action"},
    {4,"Pulp Fiction", "Quentin Tarantino", "Crime"},
    {2,"Forrest Gump", "Robert Zemeckis", "Drama"}
  };
  randomizedQuickSort(films, 0, numFilms - 1);

  for (int i = 0; i < numFilms; i++) {
    printf("ID: %d\tTitle: %s\tDirector: %s\tGenre: %s\n", films[i].id, films[i].name, films[i].director, films[i].genre);
  }

  return 0;
}

int swap(Music *a, Music *b) {
  Music temp = *a;
  *a = *b;
  *b = temp;
  return 0;
}

int heapify(Music arr[], int n, int i) {
  int smallest = i;
  int left = 2 * i + 1;
  int right = 2 * i + 2;

  if (left < n && arr[left].id < arr[smallest].id)
    smallest = left;

  if (right < n && arr[right].id < arr[smallest].id)
    smallest = right;

  if (smallest != i) {
    swap(&arr[i], &arr[smallest]);
    heapify(arr, n, smallest);
  }

  return 0;
}

int buildHeap(Music arr[], int n) {
  for (int i = n / 2 - 1; i >= 0; i--)
    heapify(arr, n, i);

  return 0;
}

int printMusic(Music arr[], int n) {
  for (int i = 0; i < n; ++i) {
    printf("ID: %d\tTitle: %s\tArtist: %s\tGenre: %s\n", arr[i].id, arr[i].title, arr[i].artist, arr[i].genre);
  }

  return 0;
}

int binarySearchMusic(Music music[], int left, int right, int targetId) {
  while (left <= right) {
    int mid = left + (right - left) / 2;

    if (music[mid].id == targetId) return mid;

    if (music[mid].id < targetId) left = mid + 1;
    else right = mid - 1;
  }

  return -1;
}

int searchMusic() {
  const int numMusic = 5;
  Music music[numMusic] = {
    {1,"Shape of You", "Ed Sheeran", "Pop"},
    {4,"Bohemian Rhapsody", "Queen", "Rock"},
    {3,"Uptown Funk", "Mark Ronson ft. Bruno Mars", "Funk"},
    {5,"Despacito", "Luis Fonsi ft. Daddy Yankee", "Reggaeton"},
    {2,"Blinding Lights", "The Weeknd", "Pop"}
  };
  int targetId;
  printf("\nEnter the music ID to search: ");
  scanf("%d", &targetId);
  int result = binarySearchMusic(music, 0, numMusic - 1, targetId);

  if (result != -1) {
    printf("Music found:\n");
    printf("ID: %d\tTitle: %s\tArtist: %s\tGenre: %s\n", music[result].id, music[result].title, music[result].artist, music[result].genre);
  } else {
    printf("Music not found.\n");
  }

  return 0;
}

int listMusic() {
  const int numMusic = 5;
  Music music[numMusic] = {
    {1,"Shape of You", "Ed Sheeran", "Pop"},
    {4,"Bohemian Rhapsody", "Queen", "Rock"},
    {3,"Uptown Funk", "Mark Ronson ft. Bruno Mars", "Funk"},
    {5,"Despacito", "Luis Fonsi ft. Daddy Yankee", "Reggaeton"},
    {2,"Blinding Lights", "The Weeknd", "Pop"}
  };
  buildHeap(music, numMusic);
  printf("Music sorted by ID:\n");
  printMusic(music, numMusic);
  return 0;
}

int showEvents() {
  const int numEvents = 5;
  Event events[numEvents] = {
    {1,"Book Club Meeting", "2024-03-15", "18:00", "Library Meeting Room", "Discussing the latest bestseller."},
    {2,"Coding Workshop", "2024-03-20", "15:30", "Library Computer Lab", "Learn the basics of programming."},
    {3,"Author Talk", "2024-03-25", "19:00", "Library Auditorium", "Meet the author and get signed copies of their books."},
    {4,"Yoga Class", "2024-04-02", "08:30", "Library Outdoor Area", "Relax and rejuvenate with a morning yoga session."},
    {5,"Film Screening: Classic Movies", "2024-04-10", "17:00", "Library Cinema Room", "Enjoy a screening of classic films from different genres."}
  };
  printf("\n--- Upcoming Events and Workshops ---\n");

  for (int i = 0; i < numEvents; ++i) {
    printf("%d. %s (ID: %d)\n", i + 1, events[i].title, events[i].id);
    printf("   Date: %s\n", events[i].date);
    printf("   Time: %s\n", events[i].time);
    printf("   Location: %s\n", events[i].location);
    printf("   Description: %s\n\n", events[i].description);
    printf("\n");
  }

  return 0;
}

int registerForEvent(const char *userName) {
  UserRegistration registration;
  FILE *file = fopen("registrations.bin", "ab");

  if (file == NULL) {
    printf("File was not open.\n\n");
    return -1;
  }

  printf("Enter your name: ");
  scanf("%99s", registration.name);
  printf("Enter the event ID you want to register for: ");
  scanf("%d", &registration.eventNumber);

  if (registration.eventNumber < 1 || registration.eventNumber > 5) {
    printf("Invalid event ID. Please enter a number between 1 and 5.\n\n");
    fclose(file);
    return -1;
  }

  fwrite(&registration, sizeof(UserRegistration), 1, file);
  fclose(file);
  printf("Your registration has been successfully received.\n\n");
  return 0;
}


int listLibraries() {
  printf("Current Library Information:\n\n");

  for (int i = 0; i < sizeof(libraries) / sizeof(libraries[0]); i++) {
    printf("Library Name : %s\n", libraries[i].name);
    printf("City: %s\n", libraries[i].city);
    printf("Address: %s\n", libraries[i].address);
    printf("Hours of Operation: %s\n", libraries[i].hours);
    printf("Contact Details: %s\n\n", libraries[i].contact);
  }

  return 0;
}

int searchLibrary() {
  char user_city[50];
  int found = 0;
  printf("Please enter the city where you would like to see library information\n(Istanbul, Izmir, Rize, Trabzon, Adana, Diyarbakir): ");
  scanf("%49s", user_city);

  for (int i = 0; i < sizeof(libraries) / sizeof(libraries[0]); i++) {
    if (strcmp(libraries[i].city, user_city) == 0) {
      printf("\nNearest Library: %s\n", libraries[i].name);
      printf("City: %s\n", libraries[i].city);
      printf("Address: %s\n", libraries[i].address);
      printf("Hours of Operation: %s\n", libraries[i].hours);
      printf("Contact Details: %s\n\n", libraries[i].contact);
      found = 1;
      break;
    }
  }

  if (!found) {
    printf("No library suitable for the entered city name was found.\n");
  }

  return 0;
}

int recommendBooksWithinBudget() {
  const int numBooks = 5;
  Book books[numBooks] = {
    {1, "The Catcher in the Rye", "J.D. Salinger", "Fiction", 50.0},
    {2, "To Kill a Mockingbird", "Harper Lee", "Classics", 70.0},
    {3, "1984", "George Orwell", "Dystopian", 40.0},
    {4, "Pride and Prejudice", "Jane Austen", "Romance", 35.0},
    {5, "The Great Gatsby", "F. Scott Fitzgerald", "Classics", 45.0}
  };
  float budget;
  printf("\nEnter your budget (in TL): ");
  scanf("%f", &budget);
  float **dp = (float **)malloc((numBooks + 1) * sizeof(float *));

  for (int i = 0; i <= numBooks; i++) {
    dp[i] = (float *)malloc((int)(budget + 1) * sizeof(float));
  }

  for (int i = 0; i <= numBooks; i++) {
    for (int w = 0; w <= (int)budget; w++) {
      if (i == 0 || w == 0)
        dp[i][w] = 0;
      else if (books[i - 1].price <= w)
        dp[i][w] = fmax(dp[i - 1][w], dp[i - 1][(int)(w - books[i - 1].price)] + books[i - 1].price);
      else
        dp[i][w] = dp[i - 1][w];
    }
  }

  printf("You can get books worth up to %.2fTL within your budget of %.2fTL.\n", dp[numBooks][(int)budget], budget);
  int w = (int)budget;

  for (int i = numBooks; i > 0 && dp[i][w] > 0; i--) {
    if (dp[i][w] != dp[i - 1][w]) {
      printf("%s by %s, %.2fTL\n", books[i - 1].title, books[i - 1].author, books[i - 1].price);
      w -= (int)books[i - 1].price;
    }
  }

  for (int i = 0; i <= numBooks; i++) {
    free(dp[i]);
  }

  free(dp);
  return 0;
}


int lcsLength(const char *X, const char *Y) {
  int m = strlen(X), n = strlen(Y);
  int **L = (int **)malloc((m + 1) * sizeof(int *));

  for (int i = 0; i <= m; i++) {
    L[i] = (int *)malloc((n + 1) * sizeof(int));
  }

  for (int i = 0; i <= m; i++) {
    for (int j = 0; j <= n; j++) {
      if (i == 0 || j == 0)
        L[i][j] = 0;
      else if (X[i - 1] == Y[j - 1])
        L[i][j] = L[i - 1][j - 1] + 1;
      else
        L[i][j] = (L[i - 1][j] > L[i][j - 1]) ? L[i - 1][j] : L[i][j - 1];
    }
  }

  int result = L[m][n]; 

  for (int i = 0; i <= m; i++) {
    free(L[i]);
  }

  free(L);
  return result;
}

int searchAndRecommendMovies() {
  const int numMovies = 5;
  Movie movies[numMovies] = {
    {1, "Inception", "Christopher Nolan", "Sci-Fi"},
    {2, "Forrest Gump", "Robert Zemeckis", "Drama"},
    {3, "The Shawshank Redemption", "Frank Darabont", "Drama"},
    {4, "Pulp Fiction", "Quentin Tarantino", "Crime"},
    {5, "The Dark Knight", "Christopher Nolan", "Action"}
  };
  int targetId;
  printf("\nEnter the movie ID to search: ");
  scanf("%d", &targetId);
  int foundIndex = -1;

  for (int i = 0; i < numMovies; i++) {
    if (movies[i].id == targetId) {
      foundIndex = i;
      break;
    }
  }

  if (foundIndex != -1) {
    printf("Movie found:\n");
    printf("ID: %d\tTitle: %s\tDirector: %s\tGenre: %s\n",
           movies[foundIndex].id, movies[foundIndex].name,
           movies[foundIndex].director, movies[foundIndex].genre);
    printf("\nSimilar genres:\n");

    for (int i = 0; i < numMovies; i++) {
      if (i != foundIndex) { 
        int commonLength = lcsLength(movies[foundIndex].genre, movies[i].genre);

        if (commonLength > 0) { 
          printf("%s (%s) has a genre similarity score of %d\n", movies[i].name, movies[i].genre, commonLength);
        }
      }
    }
  } else {
    printf("Movie not found.\n");
  }

  return 0;
}

void matrix_multiply(float prices[1][NUM_BOOKS], int quantities[NUM_BOOKS][1], float result[1][1]) {
  for (int i = 0; i < 1; i++) {
    for (int j = 0; j < 1; j++) {
      result[i][j] = 0;

      for (int k = 0; k < NUM_BOOKS; k++) {
        result[i][j] += prices[i][k] * quantities[k][j];
      }
    }
  }
}

int analyze(float result[1][1]) {
  printf("Toplam Fiyat: %.2f TL\n", result[0][0]);
  return 0;
}

int matrixChainOrder(int *p, int n) {
  if (n <= 1) {
    printf("Invalid matrix chain length\n");
    return -1; 
  }

  int **m = (int **)malloc(n * sizeof(int *));
  int **s = (int **)malloc((n - 1) * sizeof(int *));

  if (!m || !s) {
    printf("Memory allocation failed\n");
    free(m); 
    free(s); 
    return -1;
  }

  for (int i = 0; i < n; i++) {
    m[i] = (int *)malloc(n * sizeof(int));

    if (!m[i]) {
      printf("Memory allocation failed\n");

      while (--i >= 0) {
        free(m[i]); 
      }

      free(m);
      free(s);
      return -1;
    }
  }

  for (int i = 0; i < n - 1; i++) {
    s[i] = (int *)malloc((n - 1) * sizeof(int));

    if (!s[i]) { 
      printf("Memory allocation failed\n");

      while (--i >= 0) {
        free(s[i]); 
      }

      for (int j = 0; j < n; j++) {
        free(m[j]); 
      }

      free(m);
      free(s);
      return -1;
    }
  }

  for (int i = 1; i < n; i++) {
    m[i][i] = 0;
  }

  for (int l = 2; l < n; l++) {
    for (int i = 1; i < n - l + 1; i++) {
      int j = i + l - 1;
      m[i][j] = INT_MAX;

      for (int k = i; k <= j - 1; k++) {
        int q = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];

        if (q < m[i][j]) {
          m[i][j] = q;
          s[i][j - 1] = k; 
        }
      }
    }
  }

  int result = m[1][n - 1]; 

  for (int i = 0; i < n - 1; i++) {
    free(s[i]);
  }

  free(s);

  for (int i = 0; i < n; i++) {
    free(m[i]);
  }

  free(m);
  return result;
}
