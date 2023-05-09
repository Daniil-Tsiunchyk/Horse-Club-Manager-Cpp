#pragma once
// �������� ����������� ����������, ������������ � ���������
#include <iostream>     // ��� ������ � �������� �����-������
#include <iomanip>      // ��� ������ � �������������� �������
#include <vector>       // ��� ������ � ���������
#include <cstdint>      // ��� ������ � �������������� ������ �������������� �������
#include <sstream>      // ��� ������ � �������� �����
#include <conio.h>      // ��� ������ � �������� _getch()

using namespace std;

// ���������� �������
int inputInt(int a, int b);
string inputPassword();

#ifndef HASHSHA_256_H
#define HASHSHA_256_H

// ������� �������� �� ������������ ���������� �����
uint32_t rightRotate(uint32_t value, size_t bits);

// ������� ��� ����������� ������ � �������������� ��������� SHA-256
std::string doHash(const std::string& input);
#endif 
