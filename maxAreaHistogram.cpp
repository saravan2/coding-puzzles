#include<iostream>
#include<vector>
#include<stack>
#include<sstream>
using namespace std;
long int maxRectangle(vector<int>& histogram) {
	long int maxArea = 0;
	long int topRectangleArea = 0;
	long int index = 0;
	long int topRectangle;
	stack<int> pendingRectangles;
	while (index < histogram.size()) {
		if (pendingRectangles.empty() || (histogram[index] >= histogram[pendingRectangles.top()])) {
			pendingRectangles.push(index++);
		} else {
			topRectangle = pendingRectangles.top();
			pendingRectangles.pop();
			topRectangleArea = histogram[topRectangle] * (pendingRectangles.empty()?index:(index - pendingRectangles.top() - 1));
			if (topRectangleArea > maxArea)
				maxArea = topRectangleArea;
		}
	}
	while (pendingRectangles.empty()) {
			topRectangle = pendingRectangles.top();
			pendingRectangles.pop();
			topRectangleArea = histogram[topRectangle] * (pendingRectangles.empty()?index:(index - pendingRectangles.top() - 1));
			if (topRectangleArea > maxArea)
				maxArea = topRectangleArea;
	}
	return maxArea;
}

int main(int argc, char* argv[]) {
	vector<int> histogram;
	if (argc > 1) {
		int values = argc - 1;
		int index = 1;
		while (index < argc) {
			istringstream ss(argv[index]);
			int value;
			if (ss >> value) {
				histogram.push_back(value);
			} else {
				cout << "Invalid parameter ! " << argv[index] << endl;
			}
			index++;
		}
	} else {
		histogram.push_back(4);
		histogram.push_back(4);
		histogram.push_back(2);
		histogram.push_back(1);
	}
	cout << "Max rectangle area in given histogram is " << maxRectangle(histogram) << endl;
	return 0;
}
