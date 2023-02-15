import time
import math
def FindPrimes(b):
    primes = []
    prime_buff = [True] * b
    for i in range(2,math.ceil(math.sqrt(b)) + 1):
        for j in range(i * i, b, i):
            prime_buff[j] = False

    for i in range(0, b):
        if prime_buff[i]:
            primes.append(i)
    return primes
            

if __name__ == "__main__":
    start = time.time();
    result = FindPrimes(50000000);
    end = time.time();
    print(end - start);
