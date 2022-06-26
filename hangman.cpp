#include <iostream>
#include <string>
#include <time.h>
#include <SDL2/SDL.h>

// Hangman Words
#include "hangman.hpp"

int random_word()
{
    //Initialize Random Seed
    srand(time(NULL));

    int word_index = rand() % sizeof(words)/sizeof(std::string);

    return word_index;
}

void print_guess(std::string guess, int length) {
    std::cout << std::endl;
    std::cout << "Here's Your Guess: " << std::endl;
    for (int i = 0; i < length; i++) {
        if (i == length - 1) {
            std::cout << guess[i] << std::endl; 
        } else {
            std::cout << guess[i] << ",";
        }
    }
}

std::string check_letter(std::string word, std::string guess, int length, char letter) {
    for (int i = 0; i < length; i++) {
        if (word[i] == letter) {
            guess[i] = letter;
        }
    }

    return guess;
}

std::string check_wguess(std::string word, std::string wguess, int length) {
    for (int i = 0; i < length; i++) {
        char letter = wguess[i];
        if (word[i] == letter) {
            wguess[i] = letter;
        } else {
            wguess[i] = '_';
        }
    }

    return wguess;
}

int check_guess(std::string word, std::string guess, int length) {
    int correct = 0;
    for (int i = 0; i < length; i++) {
        if (guess[i] == word[i]) {
            correct++;
        }
    }

    return correct;
}

int main() 
{
    std::string word = words[random_word()];

    int guess_length = word.length();
    std::string guess;

    std::cout << "Welcome To Hangman!" << std::endl;

    for (int i = 0; i < guess_length; i++) {
        guess[i] = '_';
    }

    bool playing = true;
    int turns = guess_length + 5;
    while (playing) {
        print_guess(guess, guess_length);
        std::cout << turns << " Turns Left!" << std::endl;
        std::cout << "Guess Letter (l) or Word (w)" << std::endl;

        char response;
        std::cin >> response;

        if (response == 'l') {
            std::cout << "Enter A Letter (lowercase only)" << std::endl;

            char letter;
            std::cin >> letter;
            guess = check_letter(word, guess, guess_length, letter);
            int correct = check_guess(word, guess, guess_length);

            turns--;
            
            if (correct == guess_length) {
                std::cout << "Congrats! You're Correct! The Word Was: " << word << std::endl;
                playing = false;
            } else if (turns == 0) {
                std::cout << "Sorry, You Ran Out Of Turns. The Correct Answer Was: " << word << std::endl;
                playing = false;
            }

        } else if (response == 'w') {
            std::cout << "Enter a word (lowercase only)" << std::endl;

            std::string wguess;
            std::cin >> wguess;

            if (wguess.length() != guess_length) {
                std::cout << "Error: Guess is not the same length as Word" << std::endl;
            } else {
                guess = check_wguess(word, wguess, guess_length);
                int correct = check_guess(word, guess, guess_length);

                turns--;
                
                if (correct == guess_length) {
                    std::cout << "Congrats! You're Correct! The Word Was: " << word << std::endl;
                    playing = false;
                } else if (turns == 0) {
                    std::cout << "Sorry, You Ran Out Of Turns. The Correct Answer Was: " << word << std::endl;
                    playing = false;
                }
            }
        }
    }

    return 0;
}