#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include "console.h"
#include "filelib.h"
#include "simpio.h"
#include "strlib.h"
using namespace std;

void welcomeMessages();
void fillInAStory(string line, string& words);
unsigned int findPlaceholders(string filename);
void replace(string& buffer, string words, unsigned int pos1, unsigned int pos2);
void outputLibStory();
void storyStatus(unsigned int num_Placeholders);

//find the placeholders, count the total number of them
unsigned int findPlaceholders(string filename){
    ifstream input;
    // words are the input from users
    string line, prompt, reprompt, placeholders, words, buffer, output;
    unsigned int pos1, pos2, num_Placeholders = 0;
    filename = promptUserForFile(input, prompt="Mad Lib input file? ", reprompt);
    cout << " " << endl;
    while(getline(input, line)){
        pos1=0; pos2=0;
        string buffer = line;
            while(buffer.find_first_of("<") != string::npos &&
                    buffer.find_first_of(">") != string::npos){
                pos1=buffer.find_first_of("<");
                pos2=buffer.find_first_of(">");
                if (pos2 > pos1) // the specical case: torture1.txt, the 7th row
                placeholders=buffer.substr((pos1+1),(pos2-pos1-1));
                num_Placeholders++; // count placeholders
                fillInAStory(placeholders, words);
                replace(buffer, words, pos1, pos2);
            }
        output = output.append(buffer) + '\n';
        }
    outputLibStory();
    cout << output << endl;
    cout << " " << endl;
    cout << num_Placeholders << " placeholder(s) replaced." << endl;
    input.close();
    return num_Placeholders; // return the value to be used for calculating the average of placeholders
}

// output the general messages
void outputLibStory(){
    cout << " " << endl;
    cout << "Your Mad Lib story: " << endl;
}

// check how many Mad Libs users input and calculate average placeholders per story
void storyStatus(){
    string prompt, reprompt, filename;
    // call findPlaceholders to start the game
    unsigned int num_Libs = 1, total_Placeholders = findPlaceholders(filename);
    double num_Placeholders;
    while (getYesOrNo(prompt = "Do another Mad Lib (Y/N)? ",
                   reprompt = "Please type a word that starts with 'Y of 'N'.")){
        cout << " " << endl;
        total_Placeholders += findPlaceholders(filename);
        num_Libs++;
    }
    // total_Placeholders is an integer, that's why 1.0 is multiplied by
    num_Placeholders =1.0*total_Placeholders / num_Libs;
    cout << " " << endl;
    cout << "Mad Lib stories you created: " << num_Libs << endl;
    cout << "Total placeholder(s) replaced: "
         << total_Placeholders << " (" <<fixed <<setprecision(1)
         << num_Placeholders << " per story)" << endl;
}

// output welcome messages
void welcomeMessages(){
    cout << "Welcome to CS 106B Mad Libs" << endl;
    cout << "I will ask you to provide various words" << endl;
    cout << "and phrases to fill in a story" << endl;
    cout << "At the end, I will display your story to you" << endl;
    cout << " " << endl;
}

// To ask users to input the corresponding placeholders
// reference &words should be used to pass the value to findPlaceholders() to handle placeholders
void fillInAStory(string line, string& words){
    string prompt;
    if (toUpperCase(line.substr(0,1))== "A" || toUpperCase(line.substr(0,1))== "E" ||
         toUpperCase(line.substr(0,1))== "I" || toUpperCase(line.substr(0,1))== "O" ||
            toUpperCase(line.substr(0,1))== "U"){
        prompt = "Please type an " + line + ": ";
        words = getLine(prompt);
        }
    else {
        prompt = "Please type a " + line + ": ";
        words = getLine(prompt);
    }
}

// To replace the placeholders with the input from users
// reference &buffer should be used to pass the value to output the story
void replace(string& buffer, string words, unsigned int pos1, unsigned int pos2){
    if ((pos2-pos1+1) >= words.length()){
       buffer.replace(pos1, pos2-pos1+1, words);
    }
    else {
        buffer.insert(pos2+1, words);
        buffer.erase(pos1, pos2-pos1+1);
    }
}

int main() {
    welcomeMessages();
    storyStatus();
    return 0;
}
