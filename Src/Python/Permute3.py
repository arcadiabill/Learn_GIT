# 
# Computes the next lexicographical permutation of the specified
# list in place, returning whether a next permutation existed.
# (Returns False when the argument is already the last possible
# permutation.)
# 
def next_permutation(arr):
    # Find non-increasing suffix
    i = len(arr) - 1
    while i > 0 and arr[i - 1] >= arr[i]:
        i -= 1
    if i <= 0:
        return False
    
    # Find successor to pivot
    j = len(arr) - 1
    while arr[j] <= arr[i - 1]:
        j -= 1
    arr[i - 1], arr[j] = arr[j], arr[i - 1]
    
    # Reverse suffix
    arr[i : ] = arr[len(arr) - 1 : i - 1 : -1]
    return True

# Example:
isNext = True
arr = [1,2,3,4,5,6,7,8,9]
while isNext:
	sum = arr[0] + arr[1] + arr[2]
	# see if all the lines add to sum 
	if (arr[3] + arr[4] + arr[5] == sum) and \
	   (arr[6] + arr[7] + arr[8] == sum) and \
	   (arr[0] + arr[3] + arr[6] == sum) and \
	   (arr[1] + arr[4] + arr[7] == sum) and \
	   (arr[2] + arr[5] + arr[8] == sum) and \
	   (arr[0] + arr[4] + arr[8] == sum) and \
	   (arr[2] + arr[4] + arr[6] == sum):
	   print(arr, sum)
	isNext = next_permutation(arr)
