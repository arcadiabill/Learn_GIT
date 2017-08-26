def list_minimum(numbers):
    """
    Compute the minimum of a list of numbers
    """
    
    min_num = numbers[0]
    for num in numbers:
        if num < min_num:
            min_num = num  # Set breakpoint on this line
    return min_num

example_list = [4, 5, 2, 5, 1, 8]
print("\nAn example list is %s" % example_list)
print()
minimum_number = list_minimum(example_list)
print("The minimum of this example list is %s\n" % minimum_number)
