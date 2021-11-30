// Jakob McCloskey - 11.29.21
// Banker's Algorithm

#include <fstream>
#include <string>
#include <iostream>

bool compareArraysLEQ(int[], int[]);
bool isAllTrue(bool[]);
bool contains(int[], int);

int main() {

	// Create file stream for the input file.
	std::string filename("input.txt");
	std::ifstream fin(filename);

	// Matrix for data in table
	int table[5][9];

	int row = 0, col = 0;
	while (!fin.eof()) {
		int num;
		fin >> num;
		table[row][col] = num;
		col++;
		if (col == 9) {
			col = 0;
			row++;
		}
	}

	// Data arrays
	int alloc[5][3], max[5][3], need[5][3], safeseq[5], safecount = 0;
	int avail[3] = { table[0][6], table[0][7], table[0][8] };
	bool bools[5] = { false, false, false, false, false };

	// Fill data arrays with corresponding data from table
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 9; j++) {
			if (j == 0 || j == 1 || j == 2) alloc[i][j] = table[i][j];
			if (j == 3 || j == 4 || j == 5) max[i][j % 3] = table[i][j];
		}
	}

	// Fill need array (need = max - allocation)
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 3; j++) {
			need[i][j] = max[i][j] - alloc[i][j];
		}
	}

	while (!isAllTrue(bools)) {
		for (int i = 0; i < 5; i++) {
			if (compareArraysLEQ(need[i], avail)) {
				bools[i] = true;
				if (!contains(safeseq, i)) {
					safeseq[safecount] = i;
					safecount++;
				}
				avail[0] = avail[0] + alloc[i][0];
				avail[1] = avail[1] + alloc[i][1];
				avail[2] = avail[2] + alloc[i][2];
			}
		}
	}

	std::cout << "Safe sequence: ";
	for (int i = 0; i < 5; i++) std::cout << "P" << safeseq[i] << " ";

}

bool compareArraysLEQ(int x[], int y[]) {
	// Assumes x and y are the same length
	for (int i = 0; i < sizeof(x)-1; i++) if (x[i] > y[i]) return false;
	return true;
}

bool isAllTrue(bool arr[]) {
	for (int i = 0; i < sizeof(arr)-1; i++) if (arr[i] == false) return false;
	return true;
}

bool contains(int arr[], int x) {
	for (int i = 0; i < sizeof(arr)-1; i++) if (arr[i] == x) return true;
	return false;
}