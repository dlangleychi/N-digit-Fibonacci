/*

This is a Project Euler problem that allows me to demonstrate
object oriented principles including method and operator
overloading; and also the principle of memorization.

Problem: Given natural number N <= 5000, whats is the first
term in the Fibonacci sequence with N digits?  Looking for index of
the term, not the Fibonacci number.  There will be multiple test cases.

Remarks:

1)  Since I know the test cases can't be for more than 5000 digits,
I can compute the Fibonacci numbers up to 5000 digits, recording each
time a new digit high is reached.  Then for each test case I'll just
refer to the memorized results.

2)  You can't store a 5000 digit number in an int or a long.

3)  I tried representing Fibonacci numbers as arrays of single digit
integers.  I would sum the numbers by adding the arrays element wise
and taking the carry to the next term.  This was too slow to pass.

4)  I used an array of multiple digit integers, made number of digits per
element a data member, and wrapped up the functionality in a class.

*/

#include <cmath>
#include <iostream>
using namespace std;

#define MAX_DIGITS 5000

// define BigNumber class to hold large numbers as an array of integers
class BigNumber {
    private:
        // capacity is size of array
        // bin_size is the number of digit per array element
        // div is 10^bin_size
        // len is the number of utilized elements
        // a is the array
        int capacity, bin_size, div, len, *a;

        // return the number of digits in an integer
        int digit_count (int x) {
            int ans = 0;
            while (x > 0) {
                ans++;
                x /= 10;
            }
            return ans;
        }

    public:

        // parameter constructor
        BigNumber(int init_val, int capacity, int bin_size){
            this->capacity = capacity;
            this->bin_size = bin_size;
            div = (int) pow(10,bin_size);
            a = new int[capacity];

            // put the initial value into the array
            int i = 0;
            while (init_val > 0){
                a[i++] = init_val % div;
                init_val /= div;
            }
            len = i;
        }

        // copy constructor
        BigNumber(const BigNumber& bn){
            capacity = bn.capacity;
            bin_size = bn.bin_size;
            div = bn.div;
            len = bn.len;
            a = new int[capacity];
            for (int i = 0; i < len; i++) a[i] = bn.a[i];
        }

        // return number of digits
        int get_digits() {
            return bin_size * (len - 1) + digit_count(a[len-1]);
        }

        // overload += operator for BigNumber
        BigNumber& operator+=(const BigNumber& bn){
            int max_len = max(len,bn.len);
            int i = 0, carry = 0;
            while ( i < max_len || carry) {
                int temp = a[i] + bn.a[i] + carry;
                a[i] = temp % div;
                carry = temp/div;
                i++;
            }
            len = i;
            return *this;
        }
};

int main() {
    // an array to hold the results
    int ans[MAX_DIGITS + 1];
    ans[1] = 1;

    // target_size is the number of digits we seek
    // term_number is the where we are in Fibonacci sequence
    // num_digits is number of digits per array element
    int target_size = 2, term_number = 2, num_digits = 3;

    // initialize two terms in Fibonacci sequence
    // x is current term, y is the previous
    BigNumber y(1,MAX_DIGITS/num_digits + 1, 3);
    BigNumber x(y);

    // compute Fibonacci sequence record new number of digits
    while (target_size <= MAX_DIGITS){
        while (x.get_digits() < target_size){
            // update Fibonacci sequence
            BigNumber temp(x);
            x += y;
            y = temp;
            term_number++;
        }
        ans[target_size++] = term_number;
    }

    // take in the test cases and output the answers
    int t, n;
    cin >> t;
    while (t--){
        cin >> n;
        cout << ans[n] << endl;
    }
    return 0;
}
