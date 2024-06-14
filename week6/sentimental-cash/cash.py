from cs50 import get_float

count = 0

while True:
    change = get_float("Change owed: ")
    if change > 0:
        break
# round up change to compare for coin values 25,10,5,1
cent = round(change * 100)

# add up count of coins
while cent >= 25:
    cent = cent - 25
    count += 1

while cent >= 10:
    cent = cent - 10
    count += 1

while cent >= 5:
    cent = cent - 5
    count += 1

while cent >= 1:
    cent = cent - 1
    count += 1

print(count)