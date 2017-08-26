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
nFound = 0
arr = [1, 2, 3, 4, 5, 6, 7, 8, 9]
lst = []
# The only possible sums are 17, 19, 20, 21, 23
# See how many of each are present in the permutation
nList = []
while isNext:
	sum = arr[0] + arr[1] + arr[3] + arr[5]
	# see if all the lines add to sum 
	if (arr[0] + arr[2] + arr[4] + arr[8] == sum) and \
	   (arr[5] + arr[6] + arr[7] + arr[8] == sum):
		nFound += 1
		print(arr, sum)
		if sum not in lst:
			lst.append(sum)
			nList.append(0)
		nPos = lst.index(sum)		# We know sum is in the list
		nList[nPos] += 1			# Increment its occurance
	isNext = next_permutation(arr)
print("Number found: ", nFound)
print("Number unique  sums: ", lst)
print("Number of each sums: ", nList)
