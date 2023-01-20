# Get User Text
userText = input("Text: ")

# Set variables
letterCount = 0
wordCount = 0
sentenceCount = 0
newWord = True

# Count letters and sentences
for char in userText:
    if ord(char) in range(65, 91) or ord(char) in range(97, 123):
        letterCount += 1
    elif ord(char) == 33 or ord(char) == 46 or ord(char) == 63:
        sentenceCount += 1

# Count words
wordCount = len(userText.split())

# Coleman-Liau index
averageLetters = (letterCount / wordCount) * 100
averageSentences = (sentenceCount / wordCount) * 100
index = (0.0588 * averageLetters) - (0.296 * averageSentences) - 15.8

# Give Result
if round(index) < 1:
    print("Before Grade 1...")
elif round(index) >= 16:
    print("Grade 16+")
else:
    print(f"Grade {round(index)}")