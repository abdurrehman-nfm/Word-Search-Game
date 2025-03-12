#include <iostream>
#include <fstream>

using namespace std;

//FUNCTION VARIABLES

void intro();
void exitGame();
void table_read_display(char[][20], int, int);
void word_search(char[20], int&, int&, int&, int&);
void fetching_word(char[20], char[][20], int, int, int, int, int, int&);
void word_check(char[20], char[20], int, bool&);
void lowercase(char*);
void high_score_view();

int main() {

    //MATRIX VARIABLES

    const int row = 20, col = 20;
    char board[row][col];
    char choice = '\0';
    char name[20];

    //WORD FETCH FROM TABLE VARIABLES

    int word_start_row = 0;
    int word_start_col = 0;
    int word_end_row = 0;
    int word_end_col = 0;
    char word[20] = { '\0' };
    bool word_dict_check = true;

    //WORD CHECKING VARIABLES

    char word_read[20];
    int choice2 = 0;
    int index = 0;

    bool check1 = true;

    //SCORING VARIABLES

    int score = 0;
    int lives = 3;

    intro();
    cin >> choice;
    cin.ignore();
    cout << "ENTER YOUR NAME TO PLAY:" << endl;
    cin.getline(name, 20);

    do {



        if (choice == 'E') {
            break;
        }
        else if (choice == 'H') {
            high_score_view();
            cout << "1) PRESS N FOR NEW GAME\n2) PRESS H FOR HIGH SCORES\n3) PRESS E TO EXIT" << endl;
            cin >> choice;
        }
        else if (choice != 'N' && choice != 'H' && choice != 'E') {
            cout << "Did not enter correct option" << endl;
            break;
        }

        table_read_display(board, row, col);

        cout << "Enter The word you want to search in the Board:" << endl;
        word_search(word, word_start_row, word_start_col, word_end_row, word_end_col);

        cout << "Enter The Option for type of pattern:" << endl;
        cout << "1) Forward row wise word :\n2) Backward row wise word :\n3) Forward column wise word :\n4) Backward column wise word :\n5) Forward diagonal wise word :\n6) Backward diagonal wise word :\n7) Forward reverse diagonal wise word :\n8) Backward reverse diagonal wise word :" << endl;
        cin >> choice2;

        fetching_word(word_read, board, choice2, word_start_row, word_start_col, word_end_row, word_end_col, index);

        lowercase(word_read);
        lowercase(word);

        word_check(word_read, word, index, check1);


        // WORD CHECK IN DICTIONARY

        ifstream fin;
        fin.open("dictionary.txt");

        char arr[30] = { '\0' };
        bool found_in_dict = false;

        while (fin >> arr) {
            // Check if the words match
            bool match = true;
            int i = 0;

           
         
            while (word[i] != '\0' && arr[i] != '\0') {
                if (word[i] != arr[i]) {
                    match = false;
                    break;
                }
                i++;
            }

           
            if (match && word[i] == '\0' && arr[i] == '\0') {
                found_in_dict = true;
                break;
            }
        }

        fin.close();

     
        if (found_in_dict) {
            cout << "Word is Present in Dictionary." << endl;
        }
        else {
            cout << "Word is NOT Present in Dictionary." << endl;
        }

        // SCORE SETTING OF USERS

        if (check1 && found_in_dict) {
            cout << "Points Increased: ";
            score += 5;
            cout << score << endl;
        }
        else {
            lives--;
            cout << lives << " lives left" << endl;
        }


        if (score == 25)
        {
            cout << "YOU HAVE REACHED THE HIGHEST SCORE." << endl;
           
            break;
        }

        cout<<"1) PRESS 'N' TO CONTINUE\n2) PRESS H FOR HIGH SCORES\n3) PRESS E TO EXIT" << endl;
        cin >> choice;
        cin.ignore();

        if (choice == 'H') {
            high_score_view();
        }

    } while (choice != 'E' && lives > 0);

    exitGame();

    ofstream write;
    write.open("Scores.txt", ios::app);

    write << score << "," << name << endl;

    write.close();

    return 0;
}

void intro() {
    cout << "--------WELCOME TO WORD SEARCH GAME--------" << endl;
    cout << "1) PRESS N FOR NEW GAME\n2) PRESS H FOR HIGH SCORES\n3) PRESS E TO EXIT" << endl;
}

void exitGame() {
    cout << "--------THANK YOU FOR PLAYING--------" << endl;
    cout << "--------SEE YOU SOON--------" << endl;
}

void table_read_display(char board[][20], int row, int col) {
    ifstream fin("board.txt");
    char alpha;

    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            fin >> alpha;
            board[r][c] = alpha;
        }
    }

    fin.close();

    for (int r = 0; r < row; r++) {
        for (int c = 0; c < col; c++) {
            cout << board[r][c] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void word_search(char word[20], int& word_start_row, int& word_start_col, int& word_end_row, int& word_end_col) {
    cout << "Enter word to search: ";
    cin.getline(word, 20);

    cout << "Enter Co-Ordinates of the word:" << endl;
    cout << "Enter Starting Row:";
    cin >> word_start_row;
    cout << "Enter Starting Col:";
    cin >> word_start_col;
    cout << "Enter Ending Row:";
    cin >> word_end_row;
    cout << "Enter Ending Col:";
    cin >> word_end_col;
}

void fetching_word(char word[20], char arr[][20], int choice, int word_start_row, int word_start_col, int word_end_row, int word_end_col, int& array_index) {
    array_index = 0;

    if (choice == 1) {

        for (int i = word_start_col; i <= word_end_col; i++) {
           
            word[array_index++] = arr[word_start_row][i];
        
        }
    }
    else if (choice == 2) {

        for (int i = word_start_col; i >= word_end_col; i--) {
            
            word[array_index++] = arr[word_start_row][i];
        
        }
    }
    else if (choice == 3) {

        for (int i = word_start_row; i <= word_end_row; i++) {
            
            word[array_index++] = arr[i][word_start_col];
        
        }
    }
    else if (choice == 4) {
        
        for (int i = word_start_row; i >= word_end_row; i--) {
        
            word[array_index++] = arr[i][word_start_col];
        
        }
    }
    else if (choice == 5) {
        
        int col = word_start_col;
        
        for (int i = word_start_row; i <= word_end_row; i++) {
        
            word[array_index++] = arr[i][col++];
        
        }
    }
    else if (choice == 6) {
        
        int col = word_start_col;
        
        for (int i = word_start_row; i >= word_end_row; i--) {
        
            word[array_index++] = arr[i][col--];
        
        }
    }
    else if (choice == 7) {
        
        int col = word_start_col;
        
        for (int i = word_start_row; i >= word_end_row; i--) {
        
            word[array_index++] = arr[i][col++];
        
        }
    }
    else if (choice == 8) {
        
        int col = word_start_col;
        
        for (int i = word_start_row; i <= word_end_row; i++) {
        
            word[array_index++] = arr[i][col--];
        
        }
    }

    cout << "The word from board is: ";
    for (int i = 0; i < array_index; i++) {
        cout << word[i];
    }
    cout << endl;
}

void word_check(char word_read[20], char word[20], int index, bool& check1) {
    check1 = true;

   

    for (int i = 0; i < index; i++) {
       
        if (word_read[i] == word[i]) {
            check1 = true;
            continue;
        }
        
        if (word_read[i] != word[i]) {
            check1 = false;
            break;
        }
    }

    if (check1) {
        cout << "Word is Present In Table." << endl;
    }
    else {
        cout << "Word is not Present in Table." << endl;
    }
}

void lowercase(char* str) {
  
    //TO CONVERT CAPITAL LETTERS TO LOWERCASE FOR COMP[ARISON WITH DICTIONARY:

    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            str[i] = str[i] + (32);
        }
    }
}

void high_score_view() {
   
    //READING TOP 5 SCORES FROM SCORES FILE:

    ifstream fin("Scores.txt");
    int num;
    char comma;
    char name[20];

    cout << "Top 5 Players are:" << endl;
    while (!fin.eof())
    {
        for (int i = 0; i < 5 && fin >> num >> comma; ++i) {
            fin.getline(name, 20);
            cout << name << " : " << num << endl;
        }
    }
   

    fin.close();
}