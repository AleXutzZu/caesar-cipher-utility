import random
import sys
import os


# Function to read the dictionary from a file
def read_dictionary(file_path):
    with open(file_path, 'r') as file:
        words = [line.strip() for line in file.readlines()]
    return words


# Function to generate a random text
def generate_random_text(dictionary, max_length):
    text = []
    current_length = 0
    while current_length < max_length:
        word = random.choice(dictionary)
        text.append(word)
        current_length += len(word) + 1
    return " ".join(text)


# Main function
def main():
    # Command line arguments: max length
    if len(sys.argv) != 3:
        print("Usage: python generate_random_texts.py <dictionary_file> <max_length>")
        sys.exit(1)

    dictionary_file = sys.argv[1]
    max_length = int(sys.argv[2])

    # Read dictionary
    if not os.path.exists(dictionary_file):
        print(f"Error: {dictionary_file} does not exist.")
        sys.exit(1)

    dictionary = read_dictionary(dictionary_file)

    # Output folder
    output_folder = "output"
    if not os.path.exists(output_folder):
        os.makedirs(output_folder)

    # Generate random texts and save them to a file
    output_file = os.path.join(output_folder, "random_texts.txt")
    with open(output_file, "w") as file:
        for _ in range(1000):  # Generating 1000 random texts
            random_text = generate_random_text(dictionary, max_length)
            file.write(random_text + "\n")

    print(f"Random texts generated and saved to {output_file}")


if __name__ == "__main__":
    main()
