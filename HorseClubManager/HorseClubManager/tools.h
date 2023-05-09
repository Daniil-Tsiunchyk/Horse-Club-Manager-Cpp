#pragma once
// Включает стандартные библиотеки, используемые в программе
#include <iostream>     // для работы с потоками ввода-вывода
#include <iomanip>      // для работы с манипуляторами потоков
#include <vector>       // для работы с векторами
#include <cstdint>      // для работы с целочисленными типами фиксированного размера
#include <sstream>      // для работы с потоками строк
#include <conio.h>      // для работы с функцией _getch()

using namespace std;

// Объявления функций
int inputInt(int a, int b);
string inputPassword();

#ifndef HASHSHA_256_H
#define HASHSHA_256_H

// Функция смещения на определенное количество битов
uint32_t rightRotate(uint32_t value, size_t bits);

// Функция для хеширования строки с использованием алгоритма SHA-256
std::string doHash(const std::string& input);
#endif 
