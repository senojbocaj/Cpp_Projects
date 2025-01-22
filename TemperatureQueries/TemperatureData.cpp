# include "TemperatureData.h"
using std::string;

TemperatureData::TemperatureData() : id(""), year(0), month(0), temperature(0.0) {} // Default Constructor

TemperatureData::TemperatureData(string id, int year, int month, double temperature) : id(id), year(year), month(month), temperature(temperature) {} // Copy Constructor

TemperatureData::~TemperatureData() {} // Destructor 

bool TemperatureData::operator<(const TemperatureData& b) { // < Operator

	if (id != b.id) { // If the inputted values don't match current values, return less than bool value
		return id < b.id;
	} else if(year != b.year) { 
		return year < b.year;
	} else if (month != b.month) {
		return month < b.month;
	} else {
		return temperature < b.temperature;
	}
}

