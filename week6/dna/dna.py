import csv
import sys


def main():

    # TODO: Check for command-line usage
    # Ensure correct usage
    if len(sys.argv) != 3:
        sys.exit("Usage: python dna.py database sequences")

    database = []

    # Read data csv into list with dicts
    data = sys.argv[1]
    with open(data) as file:

        reader_database = csv.DictReader(file)
        for row in reader_database:
            database.append(row)

    # load sequence.txt into memory
    seq = sys.argv[2]
    with open(seq) as file:
        sequences = file.readline()

    # split into a list of subsequences without names

    STRs = list(database[0].keys())[1:]
    hit = {}
    # creates a dictionary with subs and count of them
    for i in STRs:
        hit[i] = longest_match(sequences, i)

    # compare new dict hit with people in database one by one to find match
    for person in database:
        match = 0
        for i in STRs:
            if int(person[i]) == hit[i]:
                match += 1
    # if STRs matching
        if match == len(STRs):
            print(person["name"])
            return

    print("no match")

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