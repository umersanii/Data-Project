#pragma once
#pragma warning(disable : 4996)
#include<iostream>
#include<vector>
#include<algorithm>
#include <random>
#include <iomanip>
#include<unordered_set>
#include <sstream>
#include <openssl/sha.h>
#include <windows.h>
#include <chrono>
#include <ctime>

#include <locale>
#include <codecvt>
#include <fstream>
#include <stdlib.h>

using namespace std;
using std::string;
using std::wstring;
using std::chrono::system_clock;
using std::time_t;
using std::tm;
using std::chrono::system_clock;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::put_time;
using std::wstringstream;
using std::wcout;
using std::wcerr;
using std::cout;
using std::cin;
using std::endl;
using std::ofstream;
using std::ifstream;
using std::getline;
using std::stringstream;
extern string Dir;

long int CalculateHash(const std::string& input) {
    // Calculate SHA-1 hash
    SHA_CTX sha1Context;
    SHA1_Init(&sha1Context);
    SHA1_Update(&sha1Context, input.c_str(), input.length());

    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1_Final(hash, &sha1Context);

    // Find the last alphabet character in the hash
    char lastAlphabet = '\0';
    for (int i = SHA_DIGEST_LENGTH - 1; i >= 0; --i) {
        if (isalpha(hash[i])) {
            lastAlphabet = hash[i];
            break;
        }
    }

    // Extract numerical digits from the hash
    std::stringstream numericalString;
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i) {
        if (isdigit(hash[i])) {
            numericalString << hash[i];
        }
    }

    // Convert the numerical string to a long long variable
    long int hashValue;
    numericalString >> hashValue;

    // Add ASCII value of the last alphabet character in the original hash
    hashValue += static_cast<long int>(lastAlphabet);

    // Take the modulus with the given number
   /* hashValue = hashValue % n;*/

    // Ensure the result is not negative
    if (hashValue < 0) {
        hashValue = hashValue * (-1);
    }

    return hashValue;
}
void sortVectorAscending(std::vector<int>& vec) {
    std::sort(vec.begin(), vec.end());
}
//int CalculateHash(string file)
//{
//    int hash = 0;
//    for (int i = 0; i < file[i] != NULL; i++)
//    {
//        hash += file[i];
//        hash *= 'A';
//        hash *= 'S';
//        hash *= 'U';
//    }
//    if (hash < 0) {
//        hash = hash * (-1);
//    }
//    return hash;
//}
void convertStringVectorToIntVector(vector<int>& ids,vector<string>& idsS,int MaxMachines) {
	for (int i = 0; i < idsS.size(); i++)
	{
         long int temp = CalculateHash(idsS[i]);
		temp = temp % MaxMachines;
        int temp2 = temp;
		ids.push_back(temp2);
	}
}


void generateRandomNumbers(int N, int k, std::vector<int>& randomNumbers) {
    // Seed for the random number generator
    std::random_device rd;
    std::mt19937 gen(rd());

    // Distribution for the random numbers in the range [0, k]
    std::uniform_int_distribution<int> dis(0, k);

    // HashSet to store the unique generated random numbers
    std::unordered_set<int> uniqueNumbers;

    // Generate N unique random numbers and store them in the vector
    while (uniqueNumbers.size() < static_cast<std::size_t>(N)) {
        int randomNumber = dis(gen);

        // Insert the number into the set only if it's not already present
        if (uniqueNumbers.find(randomNumber) == uniqueNumbers.end()) {
            uniqueNumbers.insert(randomNumber);
            randomNumbers.push_back(randomNumber);
        }
    }
}
void printVector(const vector<int> &ids) {
    for (int i = 0; i < ids.size(); i++)
    {
        cout << " " << ids[i] << " ";
    }
    cout << endl;
}


















void createFolder(string name)
{

	wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	wstring folderName = converter.from_bytes(name);

	wstring wideFolderPath = converter.from_bytes(Dir + "\\" + name);
	string tDir = converter.to_bytes(wideFolderPath);
	if (CreateDirectory(wideFolderPath.c_str(), NULL) || ERROR_ALREADY_EXISTS == GetLastError())
	{
		wcout << L"Folder '" << folderName << L"' created successfully." << endl;
	}
	else
	{
		DWORD error = GetLastError();
		if (error == ERROR_PATH_NOT_FOUND)
		{
			wcerr << L"One or more intermediate directories do not exist." << endl;
		}
		else
		{
			wcerr << L"Failed to create folder. Error code: " << error << endl;
		}
	}
}




std::string insertFile(const string& dir, string fileName, const string& filecontent) {
    fileName = fileName + ".txt";
    std::string filePath = dir + "\\" + fileName;

    std::stringstream content(filecontent);
    std::ofstream outputFile(filePath);

    if (outputFile.is_open()) {
        outputFile << content.str() << std::endl;
        outputFile.close();

        std::cout << "File created successfully: " << fileName << std::endl;
        return filePath;
    }
    else {
        std::cerr << "Error opening file: " << fileName << std::endl;
        return ""; // Return an empty string to indicate failure
    }
}

void deleteFile(string Dir, string fileName)
{
	


	

	string filePath = Dir + "\\" + fileName + ".txt";
	if (remove(filePath.c_str()) != 0)
		perror("Error deleting file");
	else
		puts("File successfully deleted");
}

void relocateFile(string source, string destination)
{
	ifstream inputFile(source);
	string fileName;
	if (!inputFile.is_open()) {
		cerr << "Error opening file: " << source << std::endl;
		return;
	}

	stringstream contentStream;
	contentStream << inputFile.rdbuf();
	inputFile.close();

	int found = source.find_last_of("/\\");
	if (found != string::npos)
	{
		fileName = source.substr(found + 1);
	}
	else
	{
		fileName = source;
	}
	cout << fileName;
	if (remove(source.c_str()) != 0)
		perror("Error deleting file");
	else
		puts("File successfully deleted");
	destination = destination + "\\" + fileName;
	ofstream outputFile(destination);
	if (outputFile.is_open())
	{
		outputFile << contentStream.str() << endl;
		outputFile.close();

		cout << "File created successfully: " << fileName << std::endl;
	}
	else
	{
		cerr << "Error opening file: " << fileName << std::endl;

	}

}




