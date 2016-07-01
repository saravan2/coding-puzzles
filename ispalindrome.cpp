Credit : https://github.com/haoel/leetcode/
#include <stdio.h>

class Solution {
public:

    bool isPalindrome(int x) {
// Negative numbers are not considered to be palindromes.
        if (x<0) {
            return false;
        }
        
        int len=1;
        for (len=1; (x/len) >= 10; len*=10 );
        
        while (x != 0 ) {
            int left = x / len;
            int right = x % 10;
            
            if(left!=right){
                return false;
            }
           
            // x % len gives all digits minus most significant
            // x / 10 takes away the least significant.
            // Cheeky way of doing it.
            x = (x%len) / 10;
            len /= 100;
        }
        return true;
    }
    
    bool isPalindrome2(int x) {
        return (x>=0 && x == reverse(x));
    }

private:   
    // Reverse string method 
    // Has problem with overflow and underflow cases.
    int reverse(int x) {
        int y=0;

        int n;
        while( x!=0 ){
            n = x%10;
//Checking the over/underflow.
//Actually, it should be y>(INT_MAX-n)/10, but n/10 is 0, so omit it.
//if (y > INT_MAX/10 || y < INT_MIN/10)
//return 0
            y = y*10 + n;
            x /= 10;
        }
        return y;
    }
};



int main()
{
    Solution s;
    printf("%d is %d\n", 5, s.isPalindrome(5) );
    printf("%d is %d\n", 12000001, s.isPalindrome(12000021) );
}
