#include <iostream>
#include <vector>

using namespace std;


class Person{
	protected:
		string firstName;
		string lastName;
		int id;
	public:
		Person(string firstName, string lastName, int identification){
			this->firstName = firstName;
			this->lastName = lastName;
			this->id = identification;
		}
		void printPerson(){
			cout<< "Name: "<< lastName << ", "<< firstName <<"\nID: "<< id << "\n"; 
		}
	
};

class Student :  public Person{
	private:
		vector<int> testScores;
	public:
        /*
        *   Class Constructor
        *
        *   Parameters:
        *   firstName - A string denoting the Person's first name.
        *   lastName - A string denoting the Person's last name.
        *   id - An integer denoting the Person's ID number.
        *   scores - An array of integers denoting the Person's test scores.
        */
        Student(string firstName, string lastName, int identification, vector<int>& scores) : Person(firstName, lastName, identification) {
            //super(firstName, lastName, identification);
            this->testScores.assign(scores.begin(), scores.end());
        }
        /*
        *   Function Name: calculate
        *   Return: A character denoting the grade.
        */
        string calculate() {
            double sum = 0;
            for (int i = 0; i < testScores.size(); i++) {
                sum += testScores[i];
            }
            double average = (sum / testScores.size());
            if (average >= 90.0 && average <= 100.0) {
                return "O";
            } else if (average >= 80.0 && average < 90.0) {
                return "E";
            } else if (average >= 70.0 && average < 80.0) {
                return "A";
            } else if (average >= 55.0 && average < 70.0) {
                return "P";
            } else if (average >= 40.0 && average < 55.0) {
                return "D";
            } else {
                return "T";
            }
        }
};

int main() {
	string firstName;
  	string lastName;
	int id;
  	int numScores;
	cin >> firstName >> lastName >> id >> numScores;
  	vector<int> scores;
  	for(int i = 0; i < numScores; i++){
	  	int tmpScore;
	  	cin >> tmpScore;
		scores.push_back(tmpScore);
	}
	Student* s = new Student(firstName, lastName, id, scores);
	s->printPerson();
	cout << "Grade: " << s->calculate() << "\n";
	return 0;
}
