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

const int N = 10000;

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
    
    header();

    while(running) {
        char c = getch();

        if (c == '0') {
            clrscr();
            std::cout << "Exited" << std::endl;
            running = false;
            continue;
        }

        if (
                ! isalpha(c)
                && c != '\r'
                && c != ' '
                && c != '\b'
        ) continue;

        if (c == '\r')
        {
            space = false;
            if (!token.empty()) tokens.push_back(token);
            token = "";
            update();
            header();
            gotoxy(1, 2);
        }
        else if (c == ' ' && !space)
        {
            space = true;
            tokens.push_back(token);
            token = "";
            header();
            showLine();
        }
        else if (c == '\b')
        {
            space = false;
            if (token.length() > 0)
            {
                token.pop_back();
            }
            else if (!tokens.empty())
            {
                token = tokens[tokens.size() - 1];
                tokens.pop_back();
            }

            if (!tokens.empty() || !token.empty()) render();
        }
        else if (!space)
        {
            token += c;
            showLine();
            render();
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