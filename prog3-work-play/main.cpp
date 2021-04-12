/* ------------------------------------------------
 *
 * Class: Program #3 for CS 141, Fall 2019
 * System: Codio
 * Author: Vince Weaver, Farbod Amiry
 *
 */
#include <iostream>/***** Use new line to divide section, all #include should be in the same section - Clark *****/

#include <string>

#include <fstream>      // For file input

#include <vector> // For dictionary vector

#include <iomanip> // For setw()

#include <cctype>       // For tolower()

#include <stdlib.h>     // srand, rand

#include <algorithm>

using namespace std;

//---------------------------------------------------------------
// Display ID info
//
void displayIdInfo() {
  cout << " \n" <<
    "Program #3: Work Play  \n" <<
    "Author: Dale Reed      \n" <<
    "Lab: Tues 8am          \n" <<
    "System:  Codio         \n" <<
    " \n";
  /*cout << " \n"
       << "Program #3: Work Play    \n"
       << "Author: Farbod Amiry,Vince Weaver   \n"/***** Commented out code shouldn't be in the final submission - Clark *****/
       << "Lab: Tues 11am         \n"
       << "System:  Codio         \n"
       << " \n";*/
} //end displayIDInfo()

//-----------------------------------------------------------------------------------------
//  You should use parameters for the dictionary, the word lengths array,/***** This is insruction on how to write this function, not how the function works. - Clark *****/
//  the length of words to use, and the total number of words.
void readInWordsFromFile(int userInput, vector < string > & dictionary, int & totalWords, int & sameLengthWords, vector < string > & newDictionary) // userInput = word length
{

  totalWords = 0; // set to 0 to read all the words within the file, the +250k words
  sameLengthWords = 0; // set the same words equal to 0 after it hits the total
  dictionary.clear();
  newDictionary.clear();

  ifstream inputFileStream;

  string fileName = "dictionary.txt"; // C string (array of char) to store filename
  string inputWord; // stores each word as it is read

  // Open input file
  inputFileStream.open(fileName.c_str());

  // Verify that the open worked
  if (!inputFileStream.is_open()) {
    cout << "Could not find input file " << fileName << "  Exiting..." << endl;
    exit(-1);
  }

  // Read all the words from the file, and display them
  while (inputFileStream >> inputWord) {
    totalWords++; // increment words to pass through to the next words

    if (inputWord.size() == userInput) {
      sameLengthWords++; // increment words with this same size length

      for (int i = 0; i < userInput; i++) {
        inputWord.at(i) = tolower(inputWord.at(i)); // sets the word to all lower case letters
      }
      newDictionary.push_back(inputWord); // create new dictionary for same length words
    }
    dictionary.push_back(inputWord);

  }

  inputFileStream.close(); // Close the input file.
} // end of readInWordsFromFile()

//--------------------------------------------------------------------------------------
// Use binary search to look up the search word in the dictionary vector, returning
// the word's index if found, -1 otherwise.
//
long binarySearch(
  string searchWord, //word to be looked up
  vector < string > dictionary) //the dictionary of words
{
  long low, mid, high; // array indices for binary search
  long searchResult = -1; // Stores index of word if search succeeded, else -1

  // Binary search for word
  low = 0;
  high = dictionary.size() - 1;
  while (low <= high) {
    mid = (low + high) / 2;
    // SearchResult negative value means word is to the left, positive value means
    // word is to the right, value of 0 means word was found
    searchResult = searchWord.compare(dictionary[mid]);
    if (searchResult == 0) {
      // Word IS in dictionary, so return the index where the word was found
      return mid;
    } else if (searchResult < 0) {
      high = mid - 1; // word should be located before the mid location
    } else {
      low = mid + 1; // word should be located after the mid location
    }
  }

  // Word was not found
  return -1;
} //end binarySearch()

//-----------------------------------------------------------------------------------------
/***** Missing comment - Clark *****/
void wordChangeGame(string startWord, string endWord, int lengthOfWordsToUse, vector < string > & newDictionary) {
  string nextWord = "";
  int numAttempts = 1;
  string userPick = "";
  nextWord = startWord;
  int counter = 0;
  // make an algorithm to check all possible words that
  // are one letter away from the start word regardless
  // of position of the letter
  do { //start of do-while loop for the word change game.
    counter = 0;
    if ((startWord == "") && (endWord == "")) {
      for (int i = 0; i < lengthOfWordsToUse; i++) {
        cout << "*";
      }
      cout << " You must first set start and end words.  Please retry. " << endl;
      break;
    } // if set words are blank, give error message and go back to menu.

    cout << numAttempts << ". Previous word is '" << nextWord << "'.  Next word: ";
    cin >> userPick;

    if (userPick == "exit") { // exit program
      break;
    } // program goes back to main menu if exit is inputed

    for (int letterCheck = 0; letterCheck < lengthOfWordsToUse; letterCheck++) { // check if the word is 1 letter difference
      if (userPick[letterCheck] != nextWord[letterCheck]) {
        counter++;
      }
    } // this for loop goes through each letter of every word and if each letter of input is different than the last one, it
    // increments the counter by 1.

    if (userPick == nextWord) { // check if the word is the same word
      for (int i = 0; i < lengthOfWordsToUse; i++) {
        cout << "*";
      }
      cout << " " << "'" << userPick << "'" << " must be exactly 1 character different.  Please retry. " << endl;
      cout << endl;
      continue;
    }
    if (userPick.size() != lengthOfWordsToUse) { // checks the length of the word
      for (int i = 0; i < lengthOfWordsToUse; i++) {
        cout << "*";
      }
      cout << " " << "'" << userPick << "'" << " is not of length " << lengthOfWordsToUse << ". Please retry." << endl;
      cout << endl;
      continue;
    }

    if (binarySearch(userPick, newDictionary) == -1) { // check if user word is in new dictionary for same length words
      for (int i = 0; i < lengthOfWordsToUse; i++) {
        cout << "*";
      }
      cout << " " << "'" << userPick << "'" << " is not in the dictionary. Please retry. " << endl;
      cout << endl;
      continue;
    } else if (counter > 1) { // if our counter from above is more than, it will give an error becaue more than 1 letter was changed.
      for (int i = 0; i < lengthOfWordsToUse; i++) {
        cout << "*";
      }
      cout << " " << "'" << userPick << "'" << " must be exactly 1 character different.  Please retry. " << endl;
      cout << endl;
      continue;
    } else {
      nextWord = userPick;
    }
    numAttempts++; // only increments if user input meets all conditions above.
    if (nextWord == endWord) {
      cout << endl;
      cout << "Congratulations, you did it!" << endl;
      break; // breaks out of the do while loop and goes back to main menu.
    }
  } while (true); // end of do- while loop.
} // end of word change game function
//-----------------------------------------------------------------------------------------
void debug(string startWord, string endWord, int lengthOfWordsToUse, vector < string > & newDictionary, int Case) { //start of the debug function.
  vector < string > startVector; //Vector for the words inserted.
  vector < int > sizeVector; // Vector for words index numbers.

  int l = 0;/***** Identifier not meaningful - Clark *****//***** Missing comment - Clark *****/
  int sub = 0; //sub is for each letter loop.

  int index = 1; //All index
  int wCounter = 0; //Parent index
  startVector.push_back(startWord); // Our startvector starts with out startword.

  sizeVector.push_back(-1);
  bool found = false;

  do {

    if ((startWord == "") && (endWord == "")) {
      for (int i = 0; i < lengthOfWordsToUse; i++) {
        cout << "*";
      }
      cout << " You must first set start and end words.  Please retry. " << endl;
      break;
    } // if set words are blank, give error message and go back to menu.

    if (Case == 5) { //we only want this to be outputed if case 5 was entered.
      cout << wCounter << ". " << startVector.at(wCounter) << ":  ";
    }
    for (l = 0; l < lengthOfWordsToUse; l++) { // goes through each letter.

      for (sub = 0; sub < 26; sub++) { // goes through the alphabet.
        string Word = startVector.at(wCounter);

        Word[l] = 97 + sub; //increments each letter.

        if ((binarySearch(Word, newDictionary) != -1) //checks if the word is in our new dictionary
          &&
          (find(startVector.begin(), startVector.end(), Word) == startVector.end())) { //find algorithm that locates the word
                                                                                      // and does not use duplicates.
          startVector.push_back(Word); // input Words into the vector
          sizeVector.push_back(wCounter); //inputs index of parent into size vector.

          if (Case == 5) { //we only want this to be outputed if case 5 was entered.
            cout << index << ":" << Word << " ";
          }
          if (startVector.at(index) == endWord) { // when our startword has reached the end word, debug ends.
            found = true; //bool variable that when endWord is found, sets to true
            cout << endl;
            cout << endl;
            if (Case == 5 || Case == 6) { //we only want this to be outputed if case 5 or case 6 was entered.
              cout << "Winning Sequence was found!";
            }
            break; // if conditions have been met, then break out of the loop.
          }
          index++; // increment index.

        }

      }

      if (found) {/***** Missing comment - Clark *****/
        break;
      }

    }
    wCounter++; //parent index incremented.

    if (Case == 5)
      cout << endl;
  } while (!found); // end of do-while loop.
  if (Case == 7) { //we only want this to be outputed if case 7 was entered.
    cout << endl;
    cout << "Winning sequence in reverse order is: " << endl;
    while (index != -1) {

      cout << setw(4) << index << ". " << startVector.at(index) << endl;
      index = sizeVector.at(index);
    } //outputs a debug short cut by finiding its parent indexs in a loop until reach start word.
  }
}
//-----------------------------------------------------------------------------------------

int main() {
  vector < string > dictionary; // Vector of dictionary words read in from file
  int lengthOfWordsToUse = 3; // Default length of word to use in word transformation
  string startWord = "dog"; // The start word for transformation
  string endWord = "cat"; // The end word for transformation
  int menuOption = -1; // User menu option selection
  int startIndex = 0; // Case 2: start index
  int endIndex = 0; // Case 2: end index
  int sameLengthWords = 0; // Words of the same length
  int totalWords = 0; // Total number of words in the vector
  int indexCase2 = 0; // Case 2: Index for the dictionary
  int counterCase2 = 0; // Case 2: counter for elements in case
  int randIndexStart = 0; // Case 3: random number Index
  int randIndexEnd = 0; // Case 3: random number Index
  int wordCheck = 0; // Case 3: check if word exits in dictionary
  bool done = false;
  vector < string > newDictionary;

  // Display ID info
  displayIdInfo();

  // Seed the random number generator
  srand(1); // Change 1 to time(0) for non-predictable results, but leave as 1 for testing

  // Menu display and handling infinite loop
  readInWordsFromFile(lengthOfWordsToUse, dictionary, totalWords, sameLengthWords, newDictionary); //only added for dictionary.size() to work below.
  cout << "Total number of words in dictionary file: " << dictionary.size() << endl;
  cout << endl;
  cout << "Word lengths where there are more than 1400 words: \n" <</***** This section can be its own function - Clark *****/
    "Length  How Many" << endl <<
    "------  --------" << endl;

  for (int wordElement = 0; wordElement < 18; wordElement++) { //begenning display with the number of words based on their length
    readInWordsFromFile(wordElement, dictionary, totalWords, sameLengthWords, newDictionary);
    if (sameLengthWords > 1400) {
      cout << setw(5) << wordElement < " ";
      cout << setw(10) << sameLengthWords << endl;
    }
  }
  readInWordsFromFile(lengthOfWordsToUse, dictionary, totalWords, sameLengthWords, newDictionary);
  do {

    cout << endl;
    cout << "Currently we have " << sameLengthWords << " words of length " <<
      lengthOfWordsToUse << " in the dictionary.  \n" <<
      "Changing from '" << startWord << "' to '" << endWord << "'" << endl <<
      endl;

    cout << "Choose from the following options:  \n" <<
      "   1. Change the word length        \n" <<
      "   2. Display some dictionary words \n" <<
      "   3. Get start and end words       \n" <<
      "   4. Play the word change game     \n" <<
      "   5. Find the end word with debug  \n" <<
      "   6. Find the end word             \n" <<
      "   7. Display an answer sequence    \n" <<
      "   8. Exit the program              \n" <<
      "Your choice -> ";

    cin >> menuOption;

    // Menu option handling should go here
    // Handle menu options
  switch (menuOption) {/***** Incorrect level of indentation - Clark *****/
         /***** Longer section should be group into its own function, espeically case 3 - Clark *****/
    case 1: //setting of word length.
      cout << endl;
      cout << "What length words do you want to use? ";
      cin >> lengthOfWordsToUse;

      dictionary.clear(); // Delete all the contents of vector dictionary
      startWord = "";
      endWord = "";

      readInWordsFromFile(lengthOfWordsToUse, dictionary, totalWords, sameLengthWords, newDictionary);
      break;
         
    case 2: //displaying dictionary based on index and the length set.
      cout << endl;
      cout << "Enter the start and end index values of words to display: ";

      cin >> startIndex; // skip words and start at this words index
      counterCase2 = startIndex;
      indexCase2 = startIndex;
      cin >> endIndex; // end the word at this index
      cout << "About to display dictionary words from 1 to 10" << endl;
      while (startIndex <= endIndex) {
        if (newDictionary[indexCase2].length() == lengthOfWordsToUse) {

          cout << setw(4) << counterCase2 << " " << newDictionary[indexCase2] << endl;
          startIndex++;
          counterCase2++;
          indexCase2++;
        } else {
          indexCase2++;
        }

      }

      break;
         
    case 3: // setting startword and endword
      cout << endl;
      do { //start of do-while loop
        cout << "Enter starting word, or 'r' for a random word: ";
        cin >> startWord;
        cout << endl;

        binarySearch(startWord, newDictionary);

        if (startWord == "exit") {
          cout << "Exiting program." << endl; // exit program
          exit(-1);
        }
        if (startWord == "r") { // random word for start word
          randIndexStart = rand() % newDictionary.size();
          //while( newDictionary[ randIndexStart].length() != lengthOfWordsToUse) {
          //    randIndexStart++;
          //}
          startWord = newDictionary[randIndexStart]; // get random start word from dictionary
        } else if (startWord.size() != lengthOfWordsToUse) {
          //while (startWord.size() != lengthOfWordsToUse) { // check start word length
          for (int i = 0; i < lengthOfWordsToUse; i++) {
            cout << "*";
          }
          cout << " " << "'" << startWord << "'" << " is not of length " << lengthOfWordsToUse << ". Please retry." << endl;
          //cout << "Enter starting word, or 'r' for a random word: ";      
          //cin >> startWord;
          cout << endl;
          continue;

          //}
        } else if (binarySearch(startWord, newDictionary) == -1) {
          //while (binarySearch(startWord, dictionary) == -1){
          for (int i = 0; i < lengthOfWordsToUse; i++) {
            cout << "*";
          }
          cout << " " << "'" << startWord << "'" << " is not in the dictionary. Please retry." << endl;
          cout << endl;
          continue;
        }
        break;

      } while (true); // startWord

      do {
        cout << "Enter ending word, or 'r' for a random word: ";
        cin >> endWord;

        binarySearch(endWord, newDictionary);

        if (endWord == "exit") { // exit the program
          exit(-1);
        }
        if (endWord == "r") { // get random end word not equal to start word
          randIndexEnd = rand() % newDictionary.size();
         
          endWord = newDictionary[randIndexEnd]; // get random end word from dictionary
          if (endWord == startWord) {
            randIndexEnd++;
            endWord = newDictionary[randIndexEnd];
          }
          //}

        } else if (endWord.size() != lengthOfWordsToUse) {
         
          for (int i = 0; i < lengthOfWordsToUse; i++) {
            cout << "*";
          }
          cout << " '" << endWord << "' is not of length " << lengthOfWordsToUse << ". Please retry." << endl;
          continue;

        } else if (binarySearch(endWord, newDictionary) == -1) {
         
          for (int i = 0; i < lengthOfWordsToUse; i++) {
            cout << "*";
          }
          cout << " " << endWord << " is not in the dictionary. Please retry." << endl;
          cout << endl;
          continue;
 

        }
        break;
      } while (true); // end of do while loop.

      break;
         
    case 4: // word change game
      wordChangeGame(startWord, endWord, lengthOfWordsToUse, newDictionary);
      break;
         
    case 5: //debug
      debug(startWord, endWord, lengthOfWordsToUse, newDictionary, 5);
      done = true;
      break;
         
    case 6: //debug without display
      debug(startWord, endWord, lengthOfWordsToUse, newDictionary, 6);
      done = true;
      break;
         
    case 7: //winning sequence in reverse
      if (done == true) {
        debug(startWord, endWord, lengthOfWordsToUse, newDictionary, 7);
        break;
      } else {
        for (int i = 0; i < lengthOfWordsToUse; i++) {
          cout << "*";
        }

        cout << "You must first find the winning sequence!";
        cout << endl;
        break;
      }
         
    case 8: // exit program
      cout << endl;
      cout << "Exiting the program" << endl;
      exit(-1);

      break;
    default: //Invalid menu option prompt.
      cout << "Invalid menu response.  Please retry. " << endl;
      continue;
      break;/***** Unreachable code - Clark *****/
    } //end switch( menuOption)

  } while (true); //end of loop.

  return 0;
} //end main()
