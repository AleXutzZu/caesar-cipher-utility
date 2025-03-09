import random
import sys
import os


# Function to read the dictionary from a file
def read_dictionary(file_path):
    with open(file_path, 'r') as file:
        words = [line.strip() for line in file.readlines()]
    return words


# Function to generate random text with controlled letter probabilities
def generate_random_text(dictionary, max_length, letter_probs, target_letters):
    text = []
    current_length = 0
    while current_length < max_length:
        word = random.choice(dictionary)
        if all(check_letter(word, target_letters[i], letter_probs[i]) for i in range(len(target_letters))):
            text.append(word)
            current_length += len(word) + 1
    return " ".join(text)


# Function to check the probability condition for a specific letter in a word
def check_letter(word, letter, prob):
    count = word.lower().count(letter.lower())
    return random.random() < (prob if count > 0 else 1)


# Main function
def main():
    if len(sys.argv) != 5:
        print(
            "Usage: python generate_random_texts_with_probs.py <dictionary_file> <max_length> <letters> <probabilities>")
        sys.exit(1)

    dictionary_file = sys.argv[1]
    max_length = int(sys.argv[2])
    letters = sys.argv[3].split(",")  # Letters provided as comma-separated values
    probabilities = list(map(float, sys.argv[4].split(",")))  # Probabilities as floats between 0 and 1

    if len(letters) != len(probabilities):
        print("Error: Number of letters and probabilities must match.")
        sys.exit(1)

    if not os.path.exists(dictionary_file):
        print(f"Error: {dictionary_file} does not exist.")
        sys.exit(1)

    dictionary = read_dictionary(dictionary_file)

    output_folder = "output"
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    output_file = os.path.join(output_folder, "random_texts_with_probs.txt")
    with open(output_file, "w") as file:
        for _ in range(1000):
            random_text = generate_random_text(dictionary, max_length, probabilities, letters)
            file.write(random_text + "\n")

    print(f"Random texts with controlled letter probabilities saved to {output_file}")


if __name__ == "__main__":
    main()
