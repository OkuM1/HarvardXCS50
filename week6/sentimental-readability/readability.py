letters = 0
words = 1
sentences = 0

# input text
text = input("Text: ")

text_length = len(text)

# letters in the text
for i in range(text_length):
    if (text[i].isalpha()):
        letters += 1

# words in text
    if (text[i].isspace()):
        words += 1

# count the number of sentence
    if (text[i] == '.' or text[i] == '?' or text[i] == '!'):
        sentences += 1

calculation = (0.0588 * letters / words * 100) - (0.296 * sentences / words * 100) - 15.8
# to calculate Index

index = round(calculation)

if index < 1:
    print("Before Grade 1")
elif index > 16:
    print("Grade 16+")
else:
    print(f"Grade {index}")