from cs50 import get_int

while True:
    height = get_int("Height 1-8: ")
    if height > 0 and height < 9:
        break
# iterate height times for each line of pyramid
for i in range(height):
    # print spaces
    for space in range(height - i - 1):
        print(" ", end="")
    # print hashes after space print
    for hashes in range(i + 1):
        print("#", end="")
    # go to new line
    print("")