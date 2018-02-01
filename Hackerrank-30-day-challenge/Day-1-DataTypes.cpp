#include <iostream>
#include <iomanip>
#include <limits>

using namespace std;

int main() {
    int i = 4;
    double d = 4.0;
    string s = "HackerRank ";
    // Declare second integer, double, and String variables.
    int is;
    double ds;
    string ss, line;

    // Read and save an integer, double, and String to your variables.
    getline(cin, line);
    is = stoi(line);

    getline(cin, line);
    ds = stod(line);
    d += ds;
    
    getline(cin, ss);

    // Print the sum of both integer variables on a new line.
    cout << (i + is) << endl;
    // Print the sum of the double variables on a new line.
    printf("%.1f\n", d);
    // Concatenate and print the String variables on a new line
    // The 's' variable above should be printed first.
    s = s + ss;
    cout << s << endl;
    return 0;
}
