#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <Windows.h>
#include <vector>

#include "./libs/trie/trie.hpp"

void
printStringVector
(std::vector<std::string> v, std::string end = "")
{
    std::cout << "Printing a vector" << std::endl;
    for(auto s : v) std::cout << s << " ";
    std::cout << std::endl;
}

using namespace std;

#define clear() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

const int N = 10000;

int CONSOLE_WIDTH, CONSOLE_HEIGHT;
bool running = false;

void init();
void getScreenInfo();
void header();
void render(); // Pressing Enter
void hint();
void update();
void showLine();

std::vector<std::string> tokens;
std::string token;

int main()
{
    trie db;
    db.insert("t");
    db.insert("thet");
    db.insert("theT");
    db.insert("theSe");
    db.insert("theSS");



    for(int i = 0; i < 26 * 2; i++) {
        if (db.root->next[i] != nullptr) {
            std::cout << "YES" << std::endl;
            std::cout << (char)((i < 26 ? 'a' : 'A')+i % 26) << endl;
        }
    }

    std::cout << "Before" << std::endl;
    auto v = db.search("the");
    std::cout << "After" << std::endl;

    std::cout << v.size() << std::endl;
    printStringVector(v);

    return 0;
    system("COLOR B5"); 

    clear();
    
    init();

    // std::cout << CONSOLE_WIDTH << endl;
    // std::cout << CONSOLE_HEIGHT << endl;
    
    header();

    while(running) {
        char c = getch();
        if (c == '\r') {
            update();
            header();
            gotoxy(1, 2);
        } else if (c == '0') {
            clear();
            break;
        } else if (c == ' ') {
            tokens.push_back(token);
            token = "";
            header();
            showLine();
        } else if (c == '\b') {
            if (token.length() > 0) {
                token.pop_back();
            } else {
                token = tokens[tokens.size() - 1];
                tokens.pop_back();
            }
            printf("\b \b");
            render();
        } else {
            token += c;
            render();
            printf("%c", c);
        }
    }

}

void init() {
    getScreenInfo();
    running = true;
}

void getScreenInfo() {
    CONSOLE_SCREEN_BUFFER_INFO screenInfo;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &screenInfo);
    CONSOLE_HEIGHT = screenInfo.srWindow.Right - screenInfo.srWindow.Left + 1;
    CONSOLE_WIDTH = screenInfo.srWindow.Bottom - screenInfo.srWindow.Top + 1;
}

void header() {
    clear();
    cout << "Enter your word. Press 0 key to exit." << endl;
}

void render() {
    if (token.length() == 0) return;

    std::vector<std::string> similar;
    
    
}

void hint() {

}

void update() {

}

void showLine() {
    for(auto t : tokens) {
        cout << t << " ";
    }
}