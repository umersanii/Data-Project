#pragma warning(disable : 4996)
#include <iostream>
#include <iomanip>
#include <sstream>
#include <openssl/sha.h>

long long calculateHashAndMod(const std::string& input, int n) {
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
    long long hashValue;
    numericalString >> hashValue;

    // Add ASCII value of the last alphabet character in the original hash
    hashValue += static_cast<long long>(lastAlphabet);

    // Take the modulus with the given number
    hashValue = hashValue % n;

    // Ensure the result is not negative
    if (hashValue < 0) {
        hashValue += n;
    }

    return hashValue;
}

int main() {
    std::string inputString = "your_input_string_here is";
    int divisor = 5;

    // Calculate hash and modulus
    long long result = calculateHashAndMod(inputString, divisor);

    // Output the result
    std::cout << "Result: " << result << std::endl;

    return 0;
}
