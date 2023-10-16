# Ask user height of pyramids and check to be between 1 and 8
height = 0
try:
    while height < 1 or height > 8 or isinstance(height, int) == False:
        height = int(input("Height: "))
except ValueError:
    while height < 1 or height > 8 or isinstance(height, int) == False:
        height = int(input("Height: "))


# Set value for whitespace for left side
whiteSpace = height - 1
centerSpace = "  "

# Draw Pyramid
for rows in range(height):
    print(whiteSpace * " " + (height - whiteSpace) * "#" + centerSpace + (height - whiteSpace) * "#")
    whiteSpace = whiteSpace - 1
