#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

vector<vector<string>> readCSV(const string& filename) {
    ifstream input{filename};
    if (!input.is_open()) {
        cerr << "Couldn't read file: " << filename << "\n";
        return {};
    }

    vector<vector<string>> csvRows;
    string line;

    while (getline(input, line)) {
        istringstream ss(move(line));
        vector<string> row;
        string value;

        while (getline(ss, value, ',')) {
            row.push_back(move(value));
        }

        csvRows.push_back(move(row));
    }

    return csvRows;
}

vector<string> getColumnByName(const vector<vector<string>>& csvRows, const string& columnName) {
    if (csvRows.empty()) {
        cerr << "CSV data is empty!\n";
        return {};
    }

    const vector<string>& header = csvRows[0];
    auto it = find(header.begin(), header.end(), columnName);

    if (it == header.end()) {
        cerr << "Column not found: " << columnName << "\n";
        return {};
    }

    size_t columnIndex = distance(header.begin(), it);
    vector<string> columnData;

    for (size_t i = 1; i < csvRows.size(); ++i) {
        columnData.push_back(csvRows[i][columnIndex]);
    }

    return columnData;
}

int main() {
    string filename = "filename.csv";
    vector<vector<string>> csvData = readCSV(filename);
    vector<string> closeColumn = getColumnByName(csvData, "age");
    string nthElement = closeColumn[5];
  
    cout << closeColumn[5];

    return 0;
}
