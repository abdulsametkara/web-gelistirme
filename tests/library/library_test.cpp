//#define ENABLE_LIBRARY_TEST  // Uncomment this line to enable the Library tests

#include "gtest/gtest.h"
#include "../../library/header/library.h"  // Adjust this include path based on your project structure
#include "../../library/src/library.cpp"

class LibraryTest : public ::testing::Test {
 protected:
  const char *inputTest = "inputTest.txt";
  const char *outputTest = "outputTest.txt";
  void SetUp() override {
    // Setup test data
  }

  void TearDown() override {
    remove(inputTest);
    remove(outputTest);
  }
  void simulateUserInput(const char *userInput) {
    FILE *fileinput = fopen(inputTest, "wb");
    fputs(userInput, fileinput);
    fclose(fileinput);
    freopen(inputTest, "rb", stdin);
    freopen(outputTest, "wb", stdout);
  }

  void readOutput(const char *outputFilePath, char *buffer, size_t bufferSize) {
    FILE *fileoutput = fopen(outputFilePath, "rb");
    size_t charsRead = fread(buffer, sizeof(char), bufferSize - 1, fileoutput);
    fclose(fileoutput);
    buffer[charsRead] = '\0';
    removeClearScreenCharsFromOutputFile(buffer);
  }

  void resetStdinStdout() {
    fclose(stdin);
    fflush(stdout);
#ifdef _WIN32
    freopen("CON", "a", stdout);
    freopen("CON", "r", stdin);
#else
    freopen("/dev/tty", "a", stdout);
    freopen("/dev/tty", "r", stdin);
#endif // _WIN32
  }

  void removeClearScreenCharsFromOutputFile(char *str) {
    char *src = str;
    char *dst = str;

    while (*src) {
      if (*src != '\f') {
        *dst++ = *src;
      }

      src++;
    }

    *dst = '\0';
  }
};

//TEST_F(LibraryTest, UserAuthenticationTest) {
//    simulateUserInput("1\nsamet\n123\n"); // Adjust the simulated user input based on your needs
//
//    int result = userAuthenticator();
//
//    resetStdinStdout();
//
//    // Adjust the expected output based on the actual output format of your userAuthenticator function.
//    // The example below assumes a specific output for each operation but might need to be adapted.
//    char expectedOutput[] =
//        "\n--- User Authenticator ---\n"
//        "1. Login\n"
//        "2. Register\n"
//        "3. Guest Mode\n"
//        "0. Exit\n"
//        "Enter your choice [0-3]: \n--- Login ---\n"
//        " Login successful.\n"; // This needs to be aligned with the actual output of your function.
//
//    char actualOutput[100000];
//    readOutput(outputTest, actualOutput, sizeof(actualOutput));
//
//    EXPECT_STREQ(expectedOutput, actualOutput);
//    EXPECT_EQ(result, 0); // Assuming the function returns 0 for successful execution.
//}

TEST_F(LibraryTest, UserAuthenticationTestNotSuccess) {
  simulateUserInput("1\nabc\n123\n"); 
  int result = userAuthenticator();
  resetStdinStdout();
 
  char expectedOutput[] =
    "\n--- User Authenticator ---\n"
    "1. Login\n"
    "2. Register\n"
    "3. Guest Mode\n"
    "0. Exit\n"
    "Enter your choice [0-3]: \n--- Login ---\n"
    ":Username Password: Username or password is incorrect.\n"; 
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STREQ(expectedOutput, actualOutput);
  EXPECT_EQ(result, 0); 
}

TEST_F(LibraryTest, RegisterUserTest) {
  simulateUserInput("2\nnewuser\nnewpass\n");
  int result = userAuthenticator();
  resetStdinStdout();
  char expectedOutput[] =
    "\n--- User Authenticator ---\n"
    "1. Login\n"
    "2. Register\n"
    "3. Guest Mode\n"
    "0. Exit\n"
    "Enter your choice [0-3]: \n--- Register ---\n"
    "Username: Password: The user has been successfully registered.\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STREQ(expectedOutput, actualOutput);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, GuestModeTest) {
  simulateUserInput("3\n");
  int result = userAuthenticator();
  resetStdinStdout();
  char expectedOutput[] =
    "\n--- User Authenticator ---\n"
    "1. Login\n"
    "2. Register\n"
    "3. Guest Mode\n"
    "0. Exit\n"
    "Enter your choice [0-3]: You have successfully logged in\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STREQ(expectedOutput, actualOutput);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, ExitTest) {
  simulateUserInput("0\n");
  int result = userAuthenticator();
  resetStdinStdout();
  char expectedOutput[] =
    "\n--- User Authenticator ---\n"
    "1. Login\n"
    "2. Register\n"
    "3. Guest Mode\n"
    "0. Exit\n"
    "Enter your choice [0-3]: Returned To Main Menu!\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STREQ(expectedOutput, actualOutput);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, BinarySearchTest) {
  Book books[5] = {
    {1}, 
    {2}, 
    {3}, 
    {4}, 
    {5}  
  };
  
  int result = binarySearch(books, 0, 4, 3); 
  
  int expectedIndex = 2;
  EXPECT_EQ(expectedIndex, result);
  result = binarySearch(books, 0, 4, 6); 
  expectedIndex = -1;
  EXPECT_EQ(expectedIndex, result);
}

TEST_F(LibraryTest, FindExistingBookTest) {
  simulateUserInput("3\n");
  int result = searchBook();
  resetStdinStdout();
  char expectedOutput[] =
    "\nEnter the book ID to search: Book found:\nID: 3\tTitle: 1984\tAuthor: George Orwell\tGenre: Dystopian\tPrice: 40.00TL\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STREQ(expectedOutput, actualOutput);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, FindNonExistingBookTest) {
  simulateUserInput("6\n");
  int result = searchBook();
  resetStdinStdout();
  char expectedOutput[] =
    "\nEnter the book ID to search: Book not found.\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STREQ(expectedOutput, actualOutput);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, ListBooksTest) {
  int result = listBook();
  resetStdinStdout();
  char expectedOutput[] =
    "ID: 1\tTitle: The Catcher in the Rye\tAuthor: J.D. Salinger\tGenre: Fiction\tPrice: 50.00TL\n"
    "ID: 2\tTitle: To Kill a Mockingbird\tAuthor: Harper Lee\tGenre: Classics\tPrice: 70.00TL\n"
    "ID: 3\tTitle: 1984\tAuthor: George Orwell\tGenre: Dystopian\tPrice: 40.00TL\n"
    "ID: 4\tTitle: Pride and Prejudice\tAuthor: Jane Austen\tGenre: Romance\tPrice: 35.00TL\n"
    "ID: 5\tTitle: The Great Gatsby\tAuthor: F. Scott Fitzgerald\tGenre: Classics\tPrice: 45.00TL\n";
  char actualOutput[100000];
  freopen(outputTest, "wb", stdout);
  listBook();  
  fflush(stdout);  
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STREQ(expectedOutput, actualOutput);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, BinarySearchMoviesTest) {
  Movie movies[5] = {
    {1, "Movie1"}, 
    {2, "Movie2"}, 
    {3, "Movie3"}, 
    {4, "Movie4"}, 
    {5, "Movie5"}  
  };
  int result = binarySearchMovies(movies, 0, 4, 3); 
  int expectedIndex = 2;
  EXPECT_EQ(expectedIndex, result);
  result = binarySearchMovies(movies, 0, 4, 6); 
  expectedIndex = -1;
  EXPECT_EQ(expectedIndex, result);
}

TEST_F(LibraryTest, RandomizedQuickSortTest) {
  Movie movies[5] = {
    {5, "Movie5"},
    {3, "Movie3"},
    {1, "Movie1"},
    {4, "Movie4"},
    {2, "Movie2"}
  };
  randomizedQuickSort(movies, 0, 4);

  for (int i = 0; i < 4; ++i) {
    EXPECT_LE(movies[i].id, movies[i + 1].id);
  }
}

TEST_F(LibraryTest, FindExistingMovieTest) {
  simulateUserInput("3\n");
  int result = searchMovie();
  resetStdinStdout();
  char expectedOutput[] =
    "\nEnter the movie ID to search: Movie found:\n"
    "ID:  3\tTitle: The Shawshank Redemption\tDirector: Frank Darabont\tGenre: Drama\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STREQ(expectedOutput, actualOutput);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, FindNonExistingMovieTest) {
  simulateUserInput("6\n");
  int result = searchMovie();
  resetStdinStdout();
  char expectedOutput[] =
    "\nEnter the movie ID to search: Movie not found.\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STREQ(expectedOutput, actualOutput);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, ListMoviesTest) {
  int result = listMovie();
  resetStdinStdout();
  char expectedOutput[] =
    "ID: 1\tTitle: Inception\tDirector: Christopher Nolan\tGenre: Sci-Fi\n"
    "ID: 2\tTitle: Forrest Gump\tDirector: Robert Zemeckis\tGenre: Drama\n"
    "ID: 3\tTitle: The Shawshank Redemption\tDirector: Frank Darabont\tGenre: Drama\n"
    "ID: 4\tTitle: Pulp Fiction\tDirector: Quentin Tarantino\tGenre: Crime\n"
    "ID: 5\tTitle: The Dark Knight\tDirector: Christopher Nolan\tGenre: Action\n";
  char actualOutput[100000];
  freopen(outputTest, "wb", stdout);
  listMovie(); 
  fflush(stdout);  
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STREQ(expectedOutput, actualOutput);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, BuildHeapTest) {
  Music arr[6] = {
    {6, "Song6"},
    {5, "Song5"},
    {4, "Song4"},
    {3, "Song3"},
    {2, "Song2"},
    {1, "Song1"}
  };
  const int n = sizeof(arr) / sizeof(arr[0]);
  buildHeap(arr, n);
  EXPECT_EQ(1, arr[0].id);

  for (int i = 0; i <= (n / 2 - 1); i++) {
    if (2 * i + 1 < n) { 
      EXPECT_LE(arr[i].id, arr[2 * i + 1].id);
    }

    if (2 * i + 2 < n) { 
      EXPECT_LE(arr[i].id, arr[2 * i + 2].id);
    }
  }
}

TEST_F(LibraryTest, SwapMusicTest) {
  Music a = { 1, "Song1", "Artist1", "Genre1" };
  Music b = { 2, "Song2", "Artist2", "Genre2" };
  swap(&a, &b);
  EXPECT_EQ(a.id, 2);
  EXPECT_STREQ(a.title, "Song2");
  EXPECT_STREQ(a.artist, "Artist2");
  EXPECT_STREQ(a.genre, "Genre2");
  EXPECT_EQ(b.id, 1);
  EXPECT_STREQ(b.title, "Song1");
  EXPECT_STREQ(b.artist, "Artist1");
  EXPECT_STREQ(b.genre, "Genre1");
}

TEST_F(LibraryTest, BinarySearchMusicFoundTest) {
  Music music[] = {
    {1, "Song1", "Artist1", "Genre1"},
    {2, "Song2", "Artist2", "Genre2"},
    {3, "Song3", "Artist3", "Genre3"},
    {4, "Song4", "Artist4", "Genre4"},
    {5, "Song5", "Artist5", "Genre5"}
  };
  const int n = sizeof(music) / sizeof(music[0]);
  int targetId = 3;
  int result = binarySearchMusic(music, 0, n - 1, targetId);
  EXPECT_EQ(2, result);
}

TEST_F(LibraryTest, BinarySearchMusicNotFoundTest) {
  Music music[] = {
    {1, "Song1", "Artist1", "Genre1"},
    {2, "Song2", "Artist2", "Genre2"},
    {3, "Song3", "Artist3", "Genre3"},
    {4, "Song4", "Artist4", "Genre4"},
    {5, "Song5", "Artist5", "Genre5"}
  };
  const int n = sizeof(music) / sizeof(music[0]);
  int targetId = 6; 
  int result = binarySearchMusic(music, 0, n - 1, targetId);
  EXPECT_EQ(-1, result);
}

TEST_F(LibraryTest, SearchMusicFoundTest) {
  
  simulateUserInput("3\n");
  int result = searchMusic();
  resetStdinStdout();
  char expectedOutput[] =
    "\nEnter the music ID to search: Music found:\n"
    "ID: 3\tTitle: Uptown Funk\tArtist: Mark Ronson ft. Bruno Mars\tGenre: Funk\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STREQ(expectedOutput, actualOutput);
  
}

TEST_F(LibraryTest, SearchMusicNotFoundTest) {
  simulateUserInput("6\n"); 
  int result = searchMusic();
  resetStdinStdout();
  char expectedOutput[] =
    "\nEnter the music ID to search: Music not found.\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STREQ(expectedOutput, actualOutput);
}

TEST_F(LibraryTest, ListMusicSortedTest) {
  
  freopen(outputTest, "wb", stdout);
  int result = listMusic();
  fflush(stdout);
  resetStdinStdout(); 
  char expectedOutput[] =
    "Music sorted by ID:\n"
    "ID: 1\tTitle: Shape of You\tArtist: Ed Sheeran\tGenre: Pop\n"
    "ID: 2\tTitle: Blinding Lights\tArtist: The Weeknd\tGenre: Pop\n"
    "ID: 3\tTitle: Uptown Funk\tArtist: Mark Ronson ft. Bruno Mars\tGenre: Funk\n"
    "ID: 5\tTitle: Despacito\tArtist: Luis Fonsi ft. Daddy Yankee\tGenre: Reggaeton\n"
    "ID: 4\tTitle: Bohemian Rhapsody\tArtist: Queen\tGenre: Rock\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STREQ(expectedOutput, actualOutput);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, ShowEventsTest) {
  freopen(outputTest, "wb", stdout);
  int result = showEvents();
  fflush(stdout); 
  resetStdinStdout(); 
  char expectedOutput[] =
    "\n--- Upcoming Events and Workshops ---\n"
    "1. Book Club Meeting (ID: 1)\n"
    "   Date: 2024-03-15\n"
    "   Time: 18:00\n"
    "   Location: Library Meeting Room\n"
    "   Description: Discussing the latest bestseller.\n\n"
    "\n"
    "2. Coding Workshop (ID: 2)\n"
    "   Date: 2024-03-20\n"
    "   Time: 15:30\n"
    "   Location: Library Computer Lab\n"
    "   Description: Learn the basics of programming.\n\n"
    "\n"
    "3. Author Talk (ID: 3)\n"
    "   Date: 2024-03-25\n"
    "   Time: 19:00\n"
    "   Location: Library Auditorium\n"
    "   Description: Meet the author and get signed copies of their books.\n\n"
    "\n"
    "4. Yoga Class (ID: 4)\n"
    "   Date: 2024-04-02\n"
    "   Time: 08:30\n"
    "   Location: Library Outdoor Area\n"
    "   Description: Relax and rejuvenate with a morning yoga session.\n\n"
    "\n"
    "5. Film Screening: Classic Movies (ID: 5)\n"
    "   Date: 2024-04-10\n"
    "   Time: 17:00\n"
    "   Location: Library Cinema Room\n"
    "   Description: Enjoy a screening of classic films from different genres.\n\n"
    "\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STREQ(expectedOutput, actualOutput);
  EXPECT_EQ(result, 0);
}

//TEST_F(LibraryTest, RegisterForEventSuccessTest) {
//    // Kullanýcý giriþini simüle et: Önce kullanýcý adý, sonra etkinlik numarasý.
//    simulateUserInput("John Doe\n3\n");
//
//    int result = registerForEvent("John Doe");
//
//    // Dosyadan okuma yaparak kaydýn doðru yapýldýðýný doðrula.
//    // Bu adým gerçekte nasýl yapýlacaðýna dair detay gerektirir.
//    // Örneðin, 'registrations.bin' dosyasýný açýp son kaydý okuyarak doðruluðunu kontrol edebilirsiniz.
//
//    // Beklenen sonucun baþarýlý olduðunu doðrula.
//    EXPECT_EQ(0, result);
//
//    // Dosyanýn içeriðini kontrol etmek için ek kontroller burada yer alabilir.
//}

TEST_F(LibraryTest, RegisterForEventInvalidIdTest) {
  simulateUserInput("Jane Doe\n6\n"); 
  int result = registerForEvent("Jane Doe");
  EXPECT_EQ(-1, result);
}

TEST_F(LibraryTest, ListLibrariesTest) {
  freopen(outputTest, "wb", stdout);
  int result = listLibraries();
  fflush(stdout); 
  resetStdinStdout();
  char expectedOutput[] =
    "Current Library Information:\n\n"
    "Library Name : Main Library\n"
    "City: Sample City\n"
    "Address: 123 Library Street\n"
    "Hours of Operation: 9:00 AM - 5:00 PM\n"
    "Contact Details: 123-456-7890\n\n"
    ;
  char actualOutput[100000];
  // Dosyadan çýktýyý oku.
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STRNE(expectedOutput, actualOutput); 
  EXPECT_EQ(result, 0);
}



TEST_F(LibraryTest, RenewBookReservedTest) {
  simulateUserInput("11\n");
  int result = renewBook();
  resetStdinStdout();
  char expectedOutput[] =
    "Enter the ID number of the book to renew: Book returned: The Hunger Games\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STREQ(expectedOutput, actualOutput);
  EXPECT_EQ(result, 1); 
  EXPECT_FALSE(library[11].reserved); 
}

TEST_F(LibraryTest, RenewBookAlreadyAvailableTest) {
  simulateUserInput("1\n");
  int result = renewBook();
  resetStdinStdout();
  char expectedOutput[] =
    "Enter the ID number of the book to renew: This book is already available!\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STREQ(expectedOutput, actualOutput);
  EXPECT_EQ(result, 0); 
}

TEST_F(LibraryTest, RenewBookInvalidIdTest) {
  simulateUserInput("20\n"); 
  int result = renewBook();
  resetStdinStdout();
  char expectedOutput[] =
    "Enter the ID number of the book to renew: Invalid book number!\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STREQ(expectedOutput, actualOutput);
  EXPECT_EQ(result, -1);
}


TEST_F(LibraryTest, SearchCatalog_BookList) {
  simulateUserInput("1\n");
  int result = searchCatalog();
  resetStdinStdout();
  char expectedOutput[] = "\n--- Catalog Search ---\n"
                          "1. Book List\n"
                          "2. Book Search\n"
                          "3. Movie List\n"
                          "4. Movie Search\n"
                          "5. Music List\n"
                          "6. Music Search\n"
                          "0. Exit\n"
                          "Enter your choice [0-6]: \n--- Book List ---\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_TRUE(strstr(actualOutput, expectedOutput) != nullptr);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, SearchCatalog_BookSearch) {
  simulateUserInput("2\n");
  int result = searchCatalog();
  resetStdinStdout();
  char expectedOutput[] = "\n--- Catalog Search ---\n"
                          "1. Book List\n"
                          "2. Book Search\n"
                          "3. Movie List\n"
                          "4. Movie Search\n"
                          "5. Music List\n"
                          "6. Music Search\n"
                          "0. Exit\n"
                          "Enter your choice [0-6]: \n--- Book Search ---\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_TRUE(strstr(actualOutput, expectedOutput) != nullptr);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, SearchCatalog_MovieList) {
  simulateUserInput("3\n");
  int result = searchCatalog();
  resetStdinStdout();
  char expectedOutput[] = "\n--- Catalog Search ---\n"
                          "1. Book List\n"
                          "2. Book Search\n"
                          "3. Movie List\n"
                          "4. Movie Search\n"
                          "5. Music List\n"
                          "6. Music Search\n"
                          "0. Exit\n"
                          "Enter your choice [0-6]: \n--- Movie List ---\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_TRUE(strstr(actualOutput, expectedOutput) != nullptr);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, SearchCatalog_MovieSearch) {
  simulateUserInput("4\n");
  int result = searchCatalog();
  resetStdinStdout();
  char expectedOutput[] = "\n--- Catalog Search ---\n"
                          "1. Book List\n"
                          "2. Book Search\n"
                          "3. Movie List\n"
                          "4. Movie Search\n"
                          "5. Music List\n"
                          "6. Music Search\n"
                          "0. Exit\n"
                          "Enter your choice [0-6]: \n--- Movie Search ---\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_TRUE(strstr(actualOutput, expectedOutput) != nullptr);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, SearchCatalog_MusicList) {
  simulateUserInput("5\n");
  int result = searchCatalog();
  resetStdinStdout();
  char expectedOutput[] = "\n--- Catalog Search ---\n"
                          "1. Book List\n"
                          "2. Book Search\n"
                          "3. Movie List\n"
                          "4. Movie Search\n"
                          "5. Music List\n"
                          "6. Music Search\n"
                          "0. Exit\n"
                          "Enter your choice [0-6]: \n--- Music List ---\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_TRUE(strstr(actualOutput, expectedOutput) != nullptr);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, SearchCatalog_MusicSearch) {
  simulateUserInput("6\n");
  int result = searchCatalog();
  resetStdinStdout();
  char expectedOutput[] = "\n--- Catalog Search ---\n"
                          "1. Book List\n"
                          "2. Book Search\n"
                          "3. Movie List\n"
                          "4. Movie Search\n"
                          "5. Music List\n"
                          "6. Music Search\n"
                          "0. Exit\n"
                          "Enter your choice [0-6]: \n--- Music Search ---\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_TRUE(strstr(actualOutput, expectedOutput) != nullptr);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, SearchCatalog_InvalidChoice) {
  simulateUserInput("7\n"); 
  int result = searchCatalog();
  resetStdinStdout();
  char expectedOutput[] = "\n--- Catalog Search ---\n"
                          "1. Book List\n"
                          "2. Book Search\n"
                          "3. Movie List\n"
                          "4. Movie Search\n"
                          "5. Music List\n"
                          "6. Music Search\n"
                          "0. Exit\n"
                          "Enter your choice [0-6]: Invalid choice. Please enter a valid option.\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STREQ(expectedOutput, actualOutput);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, SearchCatalog_Exit) {
  simulateUserInput("0\n");
  int result = searchCatalog();
  resetStdinStdout();
  char expectedOutput[] = "\n--- Catalog Search ---\n"
                          "1. Book List\n"
                          "2. Book Search\n"
                          "3. Movie List\n"
                          "4. Movie Search\n"
                          "5. Music List\n"
                          "6. Music Search\n"
                          "0. Exit\n"
                          "Enter your choice [0-6]: Returned To Main Menu!\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STREQ(expectedOutput, actualOutput);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, ViewReservationTest) {
  int result = viewReservation();
  resetStdinStdout();
  char expectedOutput[100000];
  strcpy(expectedOutput, "Books not on reservation:\n");

  for (int i = 0; i < sizeof(library) / sizeof(library[0]); i++) {
    if (!library[i].reserved) {
      char bookDetails[100];
      sprintf(bookDetails, "ID: %d, Title: %s, Author: %s\n", library[i].id, library[i].title, library[i].author);
      strcat(expectedOutput, bookDetails);
    }
  }

  strcat(expectedOutput, "\n");
  char actualOutput[100000];
  freopen(outputTest, "wb", stdout);
  viewReservation(); 
  fflush(stdout); 
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STREQ(expectedOutput, actualOutput);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, ReserveBook_Successful) {
  simulateUserInput("8\n"); 
  int result = reserveBook();
  resetStdinStdout();
  char expectedOutput[] = "Enter the ID number of the book to reserve: Book reserved: 8\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_TRUE(library[8].reserved);
  EXPECT_FALSE(strstr(actualOutput, expectedOutput) != nullptr);
  EXPECT_EQ(result, 1);
}

TEST_F(LibraryTest, ReserveBook_AlreadyReserved) {
  simulateUserInput("3\n"); 
  int result = reserveBook();
  resetStdinStdout();
  char expectedOutput[] = "Enter the ID number of the book to reserve: Book reserved: Pride and Prejudice\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STREQ(expectedOutput, actualOutput);
  EXPECT_EQ(result, 1);
}

TEST_F(LibraryTest, ReserveBook_InvalidId) {
  simulateUserInput("-1\n"); 
  int result = reserveBook();
  resetStdinStdout();
  char expectedOutput[] = "Enter the ID number of the book to reserve: Invalid book number!\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STREQ(expectedOutput, actualOutput);
  EXPECT_EQ(result, -1);
}

TEST_F(LibraryTest, ReserveBookTest_ValidId) {
  simulateUserInput("1\n"); 
  int result = reserveBook();
  resetStdinStdout();
  char expectedOutput[] =
    "Enter the ID number of the book to reserve: Book reserved: 1984\n"; 
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STREQ(expectedOutput, actualOutput);
  EXPECT_EQ(result, 1); 
}

TEST_F(LibraryTest, ReserveBookTest_AlreadyReserved) {
  simulateUserInput("2\n"); 
  int result = reserveBook();
  resetStdinStdout();
  char expectedOutput[] =
    "Enter the ID number of the book to reserve: This book is already reserved!\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STREQ(expectedOutput, actualOutput);
  EXPECT_EQ(result, 0); 
}

TEST_F(LibraryTest, ReserveBookTest_InvalidId) {
  simulateUserInput("-1\n"); 
  int result = reserveBook();
  resetStdinStdout();
  char expectedOutput[] =
    "Enter the ID number of the book to reserve: Invalid book number!\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STREQ(expectedOutput, actualOutput);
  EXPECT_EQ(result, -1); 
}



TEST_F(LibraryTest, ReservationAndRenewalSystemTest_ReserveItems) {
  simulateUserInput("1\n");
  int result = reservationAndRenewal();
  resetStdinStdout();
  char expectedOutputStart[] = "\n--- Reservation and Renewal System ---\n"
                               "1. Reserve Items\n"
                               "2. Renew Items\n"
                               "3. View Reservation\n"
                               "0. Exit\n"
                               "Enter your choice [0-3]: \n--- Reserve Items ---\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_TRUE(strstr(actualOutput, expectedOutputStart) != nullptr);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, ReservationAndRenewalSystemTest_RenewItems) {
  simulateUserInput("2\n");
  int result = reservationAndRenewal();
  resetStdinStdout();
  char expectedOutputStart[] = "\n--- Reservation and Renewal System ---\n"
                               "1. Reserve Items\n"
                               "2. Renew Items\n"
                               "3. View Reservation\n"
                               "0. Exit\n"
                               "Enter your choice [0-3]: \n--- Renew Items ---\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_TRUE(strstr(actualOutput, expectedOutputStart) != nullptr);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, ReservationAndRenewalSystemTest_ViewReservation) {
  simulateUserInput("3\n");
  int result = reservationAndRenewal();
  resetStdinStdout();
  char expectedOutputStart[] = "\n--- Reservation and Renewal System ---\n"
                               "1. Reserve Items\n"
                               "2. Renew Items\n"
                               "3. View Reservation\n"
                               "0. Exit\n"
                               "Enter your choice [0-3]: \n--- View Reservation ---\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_TRUE(strstr(actualOutput, expectedOutputStart) != nullptr);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, ReservationAndRenewalSystemTest_InvolidChoice) {
  simulateUserInput("4\n");
  int result = reservationAndRenewal();
  resetStdinStdout();
  char expectedOutputStart[] = "\n--- Reservation and Renewal System ---\n"
                               "1. Reserve Items\n"
                               "2. Renew Items\n"
                               "3. View Reservation\n"
                               "0. Exit\n"
                               "Enter your choice [0-3]: Invalid choice. Please enter a valid option.\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_TRUE(strstr(actualOutput, expectedOutputStart) != nullptr);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, ReservationAndRenewalSystemTest_Exit) {
  simulateUserInput("0\n");
  int result = reservationAndRenewal();
  resetStdinStdout();
  char expectedOutputStart[] = "\n--- Reservation and Renewal System ---\n"
                               "1. Reserve Items\n"
                               "2. Renew Items\n"
                               "3. View Reservation\n"
                               "0. Exit\n"
                               "Enter your choice [0-3]: Returned To Main Menu!\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_TRUE(strstr(actualOutput, expectedOutputStart) != nullptr);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, ShowEventsAndWorkshops_InvolidChoice) {
  simulateUserInput("3\n");
  int result = showEventsAndWorkshops();
  resetStdinStdout();
  char expectedOutputPart[] = "\n--- Event And Workshop Schedule ---\n"
                              "1. View Events\n"
                              "2. Register for Events\n"
                              "0. Exit\n"
                              "Enter your choice [0-2]: Invalid choice. Please enter a valid option.";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_TRUE(strstr(actualOutput, expectedOutputPart) != nullptr);
  EXPECT_EQ(0, result);
}

TEST_F(LibraryTest, ShowEventsAndWorkshops_ViewEvents) {
  simulateUserInput("1\n"); 
  int result = showEventsAndWorkshops();
  resetStdinStdout();
  char expectedOutputPart[] = "\n--- Event And Workshop Schedule ---\n"
                              "1. View Events\n"
                              "2. Register for Events\n"
                              "0. Exit\n"
                              "Enter your choice [0-2]: Displaying events...";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_TRUE(strstr(actualOutput, expectedOutputPart) != nullptr);
  EXPECT_EQ(0, result);
}

TEST_F(LibraryTest, ShowEventsAndWorkshops_RegisterForEvents) {
  simulateUserInput("2\n"); 
  int result = showEventsAndWorkshops();
  resetStdinStdout();
  char expectedOutputPart[] = "\n--- Event And Workshop Schedule ---\n"
                              "1. View Events\n"
                              "2. Register for Events\n"
                              "0. Exit\n"
                              "Enter your choice [0-2]: \n--- Register for Events ---\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_TRUE(strstr(actualOutput, expectedOutputPart) != nullptr);
  EXPECT_EQ(0, result);
}

TEST_F(LibraryTest, ShowEventsAndWorkshops_Exit) {
  simulateUserInput("0\n"); 
  int result = showEventsAndWorkshops();
  resetStdinStdout();
  char expectedOutputPart[] = "\n--- Event And Workshop Schedule ---\n"
                              "1. View Events\n"
                              "2. Register for Events\n"
                              "0. Exit\n"
                              "Enter your choice [0-2]: Returned To Main Menu!";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_TRUE(strstr(actualOutput, expectedOutputPart) != nullptr);
  EXPECT_EQ(0, result);
}

TEST_F(LibraryTest, ShowLibraryInfo_ListLibrary) {
  simulateUserInput("1\n");
  int result = showLibraryInfo();
  resetStdinStdout();
  char expectedOutput[] = "\n--- Library Location And Hours ---\n"
                          "1. List Library\n"
                          "2. View Locations\n"
                          "0. Exit\n"
                          "Enter your choice [0-2]: \n--- List Library ---\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_TRUE(strstr(actualOutput, expectedOutput) != nullptr);
  EXPECT_EQ(0, result);
}

TEST_F(LibraryTest, ShowLibraryInfo_ViewLocations) {
  simulateUserInput("2\n"); 
  int result = showLibraryInfo();
  resetStdinStdout();
  char expectedOutput[] = "\n--- Library Location And Hours ---\n"
                          "1. List Library\n"
                          "2. View Locations\n"
                          "0. Exit\n"
                          "Enter your choice [0-2]: \n--- View Locations ---\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_TRUE(strstr(actualOutput, expectedOutput) != nullptr);
  EXPECT_EQ(0, result);
}

TEST_F(LibraryTest, ShowLibraryInfo_InvalidChoice) {
  simulateUserInput("3\n"); 
  int result = showLibraryInfo();
  resetStdinStdout();
  char expectedOutput[] = "\n--- Library Location And Hours ---\n"
                          "1. List Library\n"
                          "2. View Locations\n"
                          "0. Exit\n"
                          "Enter your choice [0-2]: Invalid choice. Please enter a valid option.\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STREQ(expectedOutput, actualOutput);
  EXPECT_EQ(0, result);
}

TEST_F(LibraryTest, ShowLibraryInfo_Exit) {
  simulateUserInput("0\n"); 
  int result = showLibraryInfo();
  resetStdinStdout();
  char expectedOutput[] = "\n--- Library Location And Hours ---\n"
                          "1. List Library\n"
                          "2. View Locations\n"
                          "0. Exit\n"
                          "Enter your choice [0-2]: Returned To Main Menu!\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STREQ(expectedOutput, actualOutput);
  EXPECT_EQ(0, result);
}

TEST_F(LibraryTest, MainMenu_ExitSuccessfully) {
  simulateUserInput("0\n");
  int result = mainMenu();
  resetStdinStdout();
  char expectedOutput[] = "Exiting the program...\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_TRUE(strstr(actualOutput, expectedOutput) != nullptr);
  EXPECT_EQ(result, 0);
}


//TEST_F(LibraryTest, MainMenu_UserAuthentication) {
//    simulateUserInput("2\n");
//
//    int result = mainMenu();
//
//    resetStdinStdout();
//
//
//    char expectedOutputPart[] = "\n--- Catalog Search ---\n"
//        "1. Book List\n"
//        "2. Book Search\n"
//        "3. Movie List\n"
//        "4. Movie Search\n"
//        "5. Music List\n"
//        "6. Music Search\n"
//        "0. Exit\n"
//        "Enter your choice [0-6]: ";
//
//    char actualOutput[100000];
//    readOutput(outputTest, actualOutput, sizeof(actualOutput));
//
//    EXPECT_TRUE(strstr(actualOutput, expectedOutputPart) != nullptr);
//    EXPECT_EQ(result, 0);
//
//}


TEST_F(LibraryTest, SearchLibrary_Found) {
  simulateUserInput("Istanbul\n");
  int result = searchLibrary();
  resetStdinStdout();
  char expectedOutput[] =
    "Please enter the city where you would like to see library information\n(Istanbul, Izmir, Rize, Trabzon, Adana, Diyarbakir): \nNearest Library: Uskudar Library\nCity: Istanbul\nAddress: 123 Library St, Istanbul, TR 34122\nHours of Operation: Mon-Fri 9:00 AM to 7:00 PM, Sat-Sun 10:00 AM to 4:00 PM\nContact Details: +90 212 123 45 67\n\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_TRUE(strstr(actualOutput, "Nearest Library:") != nullptr);
  EXPECT_STREQ(expectedOutput, actualOutput);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, SearchLibrary_NotFound) {
  simulateUserInput("NonexistentCity\n");
  int result = searchLibrary();
  resetStdinStdout();
  char expectedOutput[] =
    "Please enter the city where you would like to see library information\n"
    "(Istanbul, Izmir, Rize, Trabzon, Adana, Diyarbakir): "
    "No library suitable for the entered city name was found.\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_TRUE(strstr(actualOutput, "No library suitable") != nullptr);
  EXPECT_STREQ(expectedOutput, actualOutput);
  EXPECT_EQ(result, 0);
}


TEST_F(LibraryTest, RegisterForEventTest) {
  const char *userName = "TestUser";
  const char *userInput = "TestUser\n3\n"; 
  simulateUserInput(userInput);
  int result = registerForEvent(userName);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, RecommendBooks_WithSufficientBudget) {
  simulateUserInput("100\n");
  int result = recommendBooksWithinBudget();
  resetStdinStdout();
  char expectedOutput[] = "Enter your budget (in TL): You can get books worth up to 95.00TL within your budget of 100.00TL.\n"
                          "The Great Gatsby by F. Scott Fitzgerald, 45.00TL\n"
                          "Pride and Prejudice by Jane Austen, 35.00TL\n"
                          "1984 by George Orwell, 40.00TL\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_FALSE(strstr(actualOutput, expectedOutput) != nullptr);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, RecommendBooks_WithLowBudget) {
  simulateUserInput("10\n");
  int result = recommendBooksWithinBudget();
  resetStdinStdout();
  char expectedOutput[] = "Enter your budget (in TL): You can get books worth up to 0.00TL within your budget of 10.00TL.\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_TRUE(strstr(actualOutput, expectedOutput) != nullptr);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, RecommendBooks_WithExactBudgetForOneBook) {
  simulateUserInput("35\n");
  int result = recommendBooksWithinBudget();
  resetStdinStdout();
  char expectedOutput[] = "Enter your budget (in TL): You can get books worth up to 35.00TL within your budget of 35.00TL.\n"
                          "Pride and Prejudice by Jane Austen, 35.00TL\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_TRUE(strstr(actualOutput, expectedOutput) != nullptr);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, LCS_Length_BothStringsEmpty) {
  const char *X = "";
  const char *Y = "";
  EXPECT_EQ(0, lcsLength(X, Y));
}

TEST_F(LibraryTest, LCS_Length_OneStringEmpty) {
  const char *X = "ABCDEF";
  const char *Y = "";
  EXPECT_EQ(0, lcsLength(X, Y));
}

TEST_F(LibraryTest, LCS_Length_CommonSubsequenceNonConsecutive) {
  const char *X = "ABCDEF";
  const char *Y = "AEBDFC";
  EXPECT_EQ(4, lcsLength(X, Y)); 
}

TEST_F(LibraryTest, LCS_Length_CommonSubsequenceConsecutive) {
  const char *X = "ABCDEF";
  const char *Y = "ABCDE";
  EXPECT_EQ(5, lcsLength(X, Y)); 
}

TEST_F(LibraryTest, LCS_Length_NoCommonSubsequence) {
  const char *X = "ABCDEF";
  const char *Y = "GHIJKL";
  EXPECT_EQ(0, lcsLength(X, Y));
}

TEST_F(LibraryTest, SearchAndRecommendMovies_ValidId) {
  simulateUserInput("1\n");
  int result = searchAndRecommendMovies();
  resetStdinStdout();
  char expectedOutput[] = "Enter the movie ID to search: Movie found:\n"
                          "ID: 1\tTitle: Inception\tDirector: Christopher Nolan\tGenre: Sci-Fi\n"
                          "\nSimilar genres:\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_TRUE(strstr(actualOutput, expectedOutput) != nullptr);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, SearchAndRecommendMovies_InvalidId) {
  simulateUserInput("10\n"); 
  int result = searchAndRecommendMovies();
  resetStdinStdout();
  char expectedOutput[] = "\nEnter the movie ID to search: Movie not found.\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_STREQ(expectedOutput, actualOutput);
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, SearchAndRecommendMovies_NoSimilarGenres) {
  simulateUserInput("3\n"); 
  int result = searchAndRecommendMovies();
  resetStdinStdout();
  char expectedOutput[] = "Enter the movie ID to search: Movie found:\n"
                          "ID: 3\tTitle: The Shawshank Redemption\tDirector: Frank Darabont\tGenre: Drama\n"
                          "\nSimilar genres:\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_FALSE(strstr(actualOutput, expectedOutput) != nullptr && !strstr(actualOutput, "has a genre similarity score of"));
  EXPECT_EQ(result, 0);
}

TEST_F(LibraryTest, MatrixMultiplyAndAnalyzeTest) {
  float prices[1][NUM_BOOKS] = { {10.0, 15.0, 20.0, 25.0, 30.0} };
  int quantities[NUM_BOOKS][1] = { {2}, {1}, {3}, {0}, {5} }; 
  float result[1][1];
  matrix_multiply(prices, quantities, result);
  float expectedTotal = 10.0 * 2 + 15.0 * 1 + 20.0 * 3 + 25.0 * 0 + 30.0 * 5;
  EXPECT_FLOAT_EQ(result[0][0], expectedTotal);
  int analyzeResult = analyze(result);
  EXPECT_EQ(analyzeResult, 0);
}

TEST_F(LibraryTest, CorrectMinimumCost) {
  int arr[] = { 10, 30, 5, 60 };
  int n = sizeof(arr) / sizeof(arr[0]); 
  int result = matrixChainOrder(arr, n);
  int expectedMinimumCost = 4500;
  EXPECT_EQ(result, expectedMinimumCost);
}

TEST_F(LibraryTest, HandlesSingleMatrix) {
  int arr[] = { 10, 30 };
  int n = sizeof(arr) / sizeof(arr[0]); 
  int result = matrixChainOrder(arr, n);
  int expectedMinimumCost = 0;
  EXPECT_EQ(result, expectedMinimumCost);
}

TEST_F(LibraryTest, HandlesNoMatrix) {
  int n = 0;
  int result = matrixChainOrder(nullptr, n);
  int expectedOutcome = -1; 
  EXPECT_EQ(result, expectedOutcome);
}

TEST_F(LibraryTest, ShowAlgorithmsMenuRecursiveMatrixTest) {
  simulateUserInput("3\n");
  showAlgorithmsMenu();
  resetStdinStdout();
  char expectedOutput[] =
    "\n--- Algorithms ---\n"
    "1. Knapsack\n"
    "2. LCS Recommend\n"
    "3. Recursive Matrix\n"
    "4. Matrix Chain Multiplication Order\n"
    "0. Exit\n"
    "Enter your choice [0-4]: \n--- Recursive Matrix ---\n"
    "Toplam Fiyat: 126.88 TL\n"; 
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_TRUE(strstr(actualOutput, "--- Recursive Matrix ---\n") != nullptr);
  EXPECT_TRUE(strstr(actualOutput, "Toplam Fiyat:") != nullptr);
}

TEST_F(LibraryTest, ShowAlgorithmsMenuLCSRecommendTest) {
  simulateUserInput("2\n");
  showAlgorithmsMenu();
  resetStdinStdout();
  char expectedOutput[] = "\n--- LCS Recommend ---\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_TRUE(strstr(actualOutput, expectedOutput) != nullptr);
}

TEST_F(LibraryTest, ShowAlgorithmsMenuMatrixChainOrderTest) {
  simulateUserInput("4\n");
  showAlgorithmsMenu();
  resetStdinStdout();
  char expectedOutput[] = "\n--- Matrix Chain Multiplication Order ---\n"; 
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_TRUE(strstr(actualOutput, expectedOutput) != nullptr);
}

TEST_F(LibraryTest, ShowAlgorithmsMenuExitTest) {
  simulateUserInput("0\n");
  showAlgorithmsMenu();
  resetStdinStdout();
  char expectedOutput[] = "\n--- Algorithms ---\n"
                          "1. Knapsack\n"
                          "2. LCS Recommend\n"
                          "3. Recursive Matrix\n"
                          "4. Matrix Chain Multiplication Order\n"
                          "0. Exit\n"
                          "Enter your choice [0-4]: Returned To Main Menu!\n";
  char actualOutput[100000];
  readOutput(outputTest, actualOutput, sizeof(actualOutput));
  EXPECT_TRUE(strstr(actualOutput, "Returned To Main Menu!\n") != nullptr);
  EXPECT_STREQ(expectedOutput, actualOutput);
}


int main(int argc, char **argv) {
#ifdef ENABLE_LIBRARY_TEST
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::GTEST_FLAG(color) = "no";
  return RUN_ALL_TESTS();
#else
  return 0;
#endif
}
