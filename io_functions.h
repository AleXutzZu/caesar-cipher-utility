#include "caesar.h"
#include <stdbool.h>

#define MAX_SIZE 1000

/**
 * Reads the distribution of letters in the English alphabet from the specified filename. The file should
 * contain a line with a floating point number for each of the letters representing its frequency
 * @param filename The filename
 * @param distribution an array in which the read data is to be stored
 */
void read_distribution(const char *filename, double distribution[ALPHABET_SIZE]);

/**
 * Encrypts or decrypts some text using Caesar's cipher. This function is responsible for IO
 * @param reverse_operation whether or not to apply the reverse shift
 */
void run_caesar_known_shift(bool reverse_operation);

/**
 * Call this function to read the text required to apply different operations on it
 * @param dest the array to store the text in
 * @return true if the read succeeded, false otherwise
 */
bool read_text(char dest[MAX_SIZE + 1]);

/**
 * Prints the frequencies of letters in the alphabet for a read text. This function is responsible for IO.
 */
void print_frequencies();

/**
 * Attempts to decrypt a text encrypted using Caesar's cipher with an unknown shift. The best matches will be
 * printed. This function is responsible for IO.
 * @param reference_distribution The reference histogram used for distance calculation
 */
void run_caesar_brute_force(const double reference_distribution[ALPHABET_SIZE]);