#ifndef HLL_CLASS
#define HLL_CLASS


class hyperLogLog{

	// class variables
		
	int *m_stream;
	int b; //number of bits
	int m; //number of streams = 2^b 
	double am;


	// private functions
	//32bit hash Function
	unsigned int hashFN(char * ch);
	unsigned int hashFN(int x);
	int add(int hashVal);

	int getStream(int hashVal); // process the first b bits and determine the which stream it belongs to.
	int leadingZeroes(int hashVal);// Compute the number of leading zeroes following the first b bits.
	double J0(int no_stream); //Some math thing.

	public:

		hyperLogLog(int bits=4); //Constructor
		~hyperLogLog(){ // Destructor
			delete []m_stream; 
		}

		int add_HLL(int newData); // 1 on success, 0 on fail
		int add_HLL(char * newData); // 1 on success, 0 on fail
		int getCardinality(); //Return the cardinality estimate
		int trimmedCardinality(); //Returns the cardinality estimate after discounting the smaller x% of streams
		int store_toFile(char * fileName);
		int load_fromFile(char * fileName);
		void printStream();
		void printAM();
		unsigned int MurmurHash2 (const void * key, int len, unsigned int seed );
};



static double harmonicMean(int * arr, int len);
double getAM(int m);


#endif