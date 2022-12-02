#pragma once
#include <iostream>
#include <cstring>
#include <cctype>
#include "website.h"
#include "BST.h"

using namespace std;

int main();
void menu();
void menuOperations(BST &, int &);
void getInput(char *&);
void generateWebsite(website &);
void generateSearchSite(website &);
int getInteger();