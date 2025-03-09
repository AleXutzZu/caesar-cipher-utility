import random
import sys
import os

# Function to apply Caesar cipher
def caesar_cipher(text, shift):
    encrypted_text = []
    for char in text:
        if char == ' ':  # Preserve spaces
            encrypted_text.append(char)
        elif char.isalpha():  # Only encrypt alphabetic characters
            start = ord('a') if char.islower() else ord('A')
            encrypted_text.append(chr((ord(char) - start + shift) % 26 + start))
        else:
            encrypted_text.append(char)  # Non-alphabetic characters remain unchanged
    return ''.join(encrypted_text)

# Main function
def main():
    if len(sys.argv) != 4:
        print("Usage: python apply_caesar_cipher.py <input_file> <output_file> <shift>")
        sys.exit(1)

    input_file = sys.argv[1]
    output_file = sys.argv[2]
    shift = int(sys.argv[3])

    if not os.path.exists(input_file):
        print(f"Error: {input_file} does not exist.")
        sys.exit(1)

    # Read the generated text from the input file
    with open(input_file, 'r') as file:
        lines = file.readlines()

    # Write the encrypted text to the output file
    with open(output_file, 'w') as file:
        for line in lines:
            line = line.strip()
            chosen_shift = shift if shift != -1 else random.randint(0, 25)
            encrypted_line = caesar_cipher(line, chosen_shift)
            file.write(f"{chosen_shift} {encrypted_line}\n")

    print(f"Encrypted text saved to {output_file}")

if __name__ == "__main__":
    main()
