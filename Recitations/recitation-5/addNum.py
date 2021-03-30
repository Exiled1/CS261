file = open("numbers.txt", "r")
sum = 0
for lines in file:
	sum += int(lines)
print(sum)
