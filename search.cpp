#include <conio.h>
#include <iostream>
#include <Windows.h>
#include <vector>
#include <algorithm>

#include "./libs/trie/trie.hpp"

void
printStringVector
(std::vector<std::pair<int, std::string>> v, std::string end = " ")
{
    std::cout << "Printing a vector" << std::endl;
    for(const auto& s : v) std::cout << s.first << " " << s.second << end;
    std::cout << std::endl;
}

using namespace std;

#define clrscr() printf("\033[H\033[J")
#define gotoxy(x,y) printf("\033[%d;%dH", (y), (x))

int cursor = 1;

int CONSOLE_WIDTH, CONSOLE_HEIGHT;
bool running = false;

void init();
void getScreenInfo();
void header();
void render(); // Pressing Enter
void update();
void showLine();

void hint(const std::vector<std::pair<int, std::string>>& suggestions);

std::vector<std::string> tokens;
std::string token;
trie db;
bool space = false;

int main()
{
//    db.insert("t");
//    db.insert("thet");
//    db.insert("theT");
//    db.insert("theT");
//    db.insert("theSe");
//    db.insert("theSS");
//
//
//
//    for(int i = 0; i < 26 * 2; i++) {
//        if (db.root->next[i] != nullptr) {
//            std::cout << "YES" << std::endl;
//            std::cout << (char)((i < 26 ? 'a' : 'A')+i % 26) << endl;
//        }
//    }
//
//    std::cout << "Before" << std::endl;
//    auto v = db.search("the");
//    std::cout << "After" << std::endl;
//
//    std::cout << v.size() << std::endl;
//    printStringVector(v);
//
//    return 0;

//    system("COLOR B5");
    clrscr();
    
    init();

    // std::cout << CONSOLE_WIDTH << endl;
    // std::cout << CONSOLE_HEIGHT << endl;

    while(running) {
        std::string input;
        std::cin >> input;

        if (input[0] == '+') {
            db.root->insert(input.substr(1));
        }

        if (input[0] == '?') {
            auto suggestions = db.root->getSimilar(input.substr(1), "");

            std::sort(suggestions.begin(), suggestions.end());

            printf("[\n");
            for(const auto& suggestion : suggestions)
                std::cout << '\t' << suggestion.second << std::endl;
            printf("]\n");
        }

        if (input[0] == '.') {
            running = false;
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
    clrscr();
    cout << "Search Master Interactive terminal. (Press 0 to exit)" << endl;
}

void render() {
    if (token.length() == 0) return;

    auto similar = db.root->getSimilar(token, "");

    std::sort(similar.begin(), similar.end());

    hint(similar);
}

void
hint
(const std::vector<std::pair<int, std::string>>& suggestions)
{
    clrscr();
    header();
    showLine();
    gotoxy(1, 3);
    for(const auto& suggest : suggestions) {
        std::cout << suggest.second << " ";
    }

    int n = 0;
    for(const auto& tkn : tokens)
        n += tkn.size();

    n += tokens.size();
    gotoxy(n, 2);
}

void update()
{
    for(const auto& tkn : tokens)
        db.root->insert(tkn);

    tokens.clear();
}

void showLine()
{
    for(const auto& tkn : tokens)
        cout << tkn << " ";
    cout << '\b';
    if (space) cout << ' ';
}