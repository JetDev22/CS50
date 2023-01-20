import csv
import sys


def main():

    # Check for command-line usage
    if len(sys.argv) != 3:
        print("Useage: csv file and text file")
    elif "csv" not in sys.argv[1]:
        print("Please specify csv file as first argument")
    elif "txt" not in sys.argv[2]:
        print("Please specify txt file as second argument")

    # Read database file into a variable
    # {'name': 'Albus', 'AGATC': '15', 'TTTTTTCT': '49', 'AATG': '38', 'TCTAG': '5', 'GATA': '14', 'TATC': '44', 'GAAA': '14', 'TCTG': '12'}
    databaseList = []
    with open(sys.argv[1], 'r') as database:
        reader = csv.DictReader(database)
        for row in reader:
            databaseList.append(row)

    # Read DNA sequence file into a variable
    sequenceList = []
    with open(sys.argv[2], 'r') as sequence:
        reader = csv.reader(sequence)
        for row in reader:
            sequenceList = row

    # Find longest match of each STR in DNA sequence
    if sys.argv[1] == "databases/large.csv":
        resultDict = {"AGATC": 0, "TTTTTTCT": 0, "AATG": 0, "TCTAG": 0, "GATA": 0, "TATC": 0, "GAAA": 0, "TCTG": 0}
    elif sys.argv[1] == "databases/small.csv":
        resultDict = {"AGATC": 0, "AATG": 0, "TATC": 0}
    for key in resultDict:
        resultDict[key] = str(resultDict[key] + longest_match(sequenceList[0], key))

    # Check database for matching profiles
    found = False
    for i in range(len(databaseList)):
        person = databaseList[i]
        personName = databaseList[i]["name"]
        del person["name"]
        if person == resultDict:
            print(personName)
            found = True
    if found == False:
        print("No match")

    return


def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
