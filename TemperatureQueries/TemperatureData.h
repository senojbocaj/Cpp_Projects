# ifndef TEMPERATUREDATA
# define TEMPERATUREDATA

# include <string>

using std::string;

struct TemperatureData {
	public:
		// Member Variables
		string id = "";
		int year = 0;
		int month = 0;
		double temperature = 0.0;

		TemperatureData(); // Default Constructor
		TemperatureData(std::string id, int year, int month, double temperature); // Copy Constructor
		virtual ~TemperatureData(); // Destructor
		bool operator<(const TemperatureData& b); // < Operator
};

# endif
