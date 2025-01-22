# ifndef NODE
# define NODE

# include "TemperatureData.h"

using std::string;

struct Node {
	public:
		// Member Variables
		TemperatureData data;
		Node* next;

		Node(); // Default Constructor
		Node(string id, int year, int month, double temperature); // Copy Constructor
		bool operator<(const Node& b); // < Operator
		virtual ~Node() {} // Destructor
};

# endif
