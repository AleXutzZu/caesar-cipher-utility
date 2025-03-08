#define ALPHABET_SIZE 26
#define TOP_N 3

/**
 * Computes the frequency array of the given text
 * @param text the text to analyze
 * @param histogram the array in which to store the data
 */
void compute_histogram(const char *text, double histogram[ALPHABET_SIZE]);

/**
 * Computes the Chi-Squared distance between 2 histograms of letter frequencies
 * @param hist1 the first histogram (used as expected)
 * @param hist2 the second histogram
 * @return the computed distance
 */
double chi_squared_distance(const double hist1[ALPHABET_SIZE], const double hist2[ALPHABET_SIZE]);

/**
 * Computes the Euclidean distance between 2 histograms of letter frequencies
 * @param hist1 the first histogram (used as expected)
 * @param hist2 the second histogram
 * @return the computed distance
 */
double euclidean_distance(const double hist1[ALPHABET_SIZE], const double hist2[ALPHABET_SIZE]);

/**
 * Computes the Cosine distance between 2 histograms of letter frequencies
 * @param hist1 the first histogram (used as expected)
 * @param hist2 the second histogram
 * @return the computed distance
 */
double cosine_distance(const double hist1[ALPHABET_SIZE], const double hist2[ALPHABET_SIZE]);

/**
 * Shifts the text with the specified shift
 * @param text the text to shift
 * @param shift the shift to use
 */
void shift_text(char *text, int shift);

/**
 * Uses frequency analysis to compute the top 3 shifts by lowest distance
 * @param text the text to decipher
 * @param top_shifts the array containing the best 3 shifts
 * @param top_distances the array containing the best 3 distances for their respective shifts
 * @param reference_distribution_histogram The histogram of the distribution used as reference
 * @param distance_function the function used to calculate distance
 */
void break_cipher(const char *text, int top_shifts[TOP_N], double top_distances[TOP_N],
                  const double reference_distribution_histogram[ALPHABET_SIZE],
                  double (*distance_function)(const double [], const double[]));