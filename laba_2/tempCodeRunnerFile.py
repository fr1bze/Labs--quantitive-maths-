def mnk(arr1 = [], arr2 = []):
    arr1_mean = sum(arr1)/len(arr1)
    arr2_mean = sum(arr1)/len(arr1)
    sum1 = 0
    sum2 = 0
    for i in range(len(arr1)):
        sum1 += (arr1[i] - arr1_mean)*(arr2[i] - arr2_mean)
        sum2 += (arr1[i] - arr1_mean)*(arr1[i] - arr1_mean)
    return sum1/sum2