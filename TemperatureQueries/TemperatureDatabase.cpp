# include "TemperatureDatabase.h"
# include <fstream>
# include <sstream>

using std::cout, std::endl, std::string, std::ofstream, std::ifstream;

TemperatureDatabase::TemperatureDatabase() : records() {}
TemperatureDatabase::~TemperatureDatabase() {}

void TemperatureDatabase::loadData(const string& filename) {
	// Variables
	string id = "";
	int year = 0;
	int month = 0;
	double temperature = 0.0;
	string data = "";

	ifstream ifs(filename); // Opens file

	if (!ifs.is_open()) { // If file fails to open output error message
		cout << "Error : Unable to open " << filename << endl;
	} else {
		while (getline(ifs, data)) { // While there is a line to read
			std::istringstream iss(data);

			// Extract variable values from file
			iss >> id;
			iss >> year;
			iss >> month;
			iss >> temperature;

			if (iss.fail()) { // If extraction fails output error message
				cout << "Error: Other invalid input" << endl;
			}

			if (year < 1800 || year > 2024) { // If year is invalid, output error message
				cout << "Error: Invalid year " << year << endl;
			}

			if (month < 1 || month > 12) { // If month is invalid, output error message
				cout << "Error: Invalid month " << month << endl;
			}

			if ((temperature < -50.0 && temperature != -99.99) || temperature > 50.0) { // If temperature is invalid, output error message
				cout << "Error: Invalid temperature " << temperature << endl;
			}
			records.insert(id, year, month, temperature); // Update records
		}
	}
	ifs.close(); // Close file
}



void TemperatureDatabase::outputData(const string& filename) {
	ofstream dataout("sorted." + filename);
	
	if (!dataout.is_open()) {
		cout << "Error: Unable to open " << filename << endl;
		exit(1);
	}
	
	dataout << records.print();
}

void TemperatureDatabase::performQuery(const string& filename) {
	// TODO: implement this function
}
