#include "hyperLogLog.h"
// #include <bits/stdc++.h>
// using namespace std;
#define hashlen 32

int hyperLogLog::add(int hashval){
	// j = get the first b bits
	// k = read the number of zeroes following the first b-bits
	// append 'that number' to m_stream[j] = k
	
	
	// for(int i = 0;i<(hashlen-b)){
	// 	h = h>>1;
	// }

	int j = getStream(hashval);
	int leading = leadingZeroes(hashval);
	m_stream[j] = m_stream[j]>leading?m_stream[j]:leading;

	return 1;
}

int hyperLogLog::add_HLL(int newData){
	return add(hashFN(newData));
} // 1 on success, 0 on fail
int hyperLogLog::add_HLL(char * newData){
	return add(hashFN(newData));
	// return add(MurmurHash2((void*)newData, strlen(newData),1));
} // 1 on success, 0 on fail
		



int hyperLogLog::getCardinality(){

	// compute harmonic mean of m_stream[0...m]
	// return it

	int *power2 = new int[m];

	// double am = 0;
	// am = 
	for(int i = 0;i<m;i++){
		if(m_stream[i]==INT_MIN){
			power2[i] = 0;
			continue;
		}
		power2[i] = pow(2,m_stream[i]);
	}
	// cout<<endl<<"2 power:";
	// for(int i =0;i<m;i++)
	// 	cout<<power2[i]<<" ";
	// cout<<endl;

	double harmonicM = harmonicMean(power2 , m);

	// cout<<"Harmonic mean= "<<harmonicM<<endl;
	harmonicM *= (m*am);
	// cout<<"Harmonic mean= "<<harmonicM<<endl;
	

	delete []power2;

	return (int)harmonicM;



	/*Arithmatic mean*/
	// int sum = 0, count = 0;
	// for(int i =0;i<m;i++){
	// 	if(m_stream[i]==INT_MIN)
	// 		continue;
	// 	sum+=pow(2,m_stream[i]);
	// 	count++;
	// }

	// return sum/count;

}


int hyperLogLog::leadingZeroes(int x){

	int count = 0;

	for(int i = 0;i<b;i++) //Skipping b bits
		x = x<<1;


	while(!(x&0x80000000) && count < (hashlen - b)){
		x = x<<1;
		count++;
	}

	return count;
}


static double harmonicMean(int * arr, int len){
	// cout<<"hm";
	double sum = 0;
	int l = 0;

	for(int i = 0; i< len; i++){
		double d = arr[i];
		if(arr[i]==0){
			continue;
		}

		sum+= (double)(1/d);
		// cout<<(double)(1/d)<<" ";
		l++;
	}

	// cout<<endl;
	// cout<<"++\n";
	return ((double)l)/sum;

}



int hyperLogLog::getStream(int hashval){

	int j = 0;
	for(int i = 0;i<b;i++){
		j*=2;
		if(hashval&0x80000000)
			j+=1;
		hashval = hashval<<1;
	}

	return j;

}

double getAM(int m){
	if(m==16)
		return 0.673;
	else if(m==32)
		return 0.697;
	else if(m==64)
		return 0.709;
	else
		return 0.7213/(1 + 1.079/m); 

}


double hyperLogLog::J0(int no_stream){



	// double log2 = log(2);
	double log2 = 0.6931471805599453;


	return (2*log2/no_stream)*(1+((3*log2 - 1)/no_stream));
}

unsigned int hyperLogLog:: hashFN(char * str){


//Simple hash

	// unsigned int hashval = 1;
	// int i = 0;
	// while(str[i]!='\0'){
	// 	hashval *= str[i]*(i+1); 
	// 	i++;
	// }

	// return hashval;



	// Jenkins One
	unsigned int hash = 0;
	int i;
	for(hash = i = 0; str[i]!='\0'; ++i){
		hash += str[i];
		hash += (hash << 10);
		hash ^= (hash >> 6);
    }
	hash += (hash << 3);
	hash ^= (hash >> 11);
	hash += (hash << 15);
	return hash;

}
unsigned int hyperLogLog::hashFN(int x){
	unsigned int y = x*x*x;
	return y;
}


hyperLogLog::hyperLogLog(int bits){ /*Number of bits to define the stream number*/
	// m = 2^b;
	m = pow(2,bits);
	m_stream = new int[m];
	b = bits;
	for(int i = 0;i<m;i++)
		m_stream[i] = INT_MIN;

	// am = (double)(1/(m*J0(m)));
	am = getAM(m);
}


void hyperLogLog::printStream(){
	for(int i = 0;i<m;i++)
		cout<<m_stream[i]<<" ";
	cout<<endl;
}

void hyperLogLog::printAM(){
	cout<<am<<endl;
}


int hyperLogLog::store_toFile(char * fileName){

	ofstream file;
	file.open(fileName);

	if(!file){
		cout<<"Error in opening file";
		return 0;
	}

	file<<b<<endl<<m<<endl<<am<<endl;
	for(int i = 0;i<m;i++)
		file<<m_stream[i]<<" ";

	file.close();
	return 1;

}

int hyperLogLog::load_fromFile(char * fileName){
	delete []m_stream;

	ifstream file;
	file.open(fileName);

	if(!file){
		cout<<"Error in opening file";
		return 0;
	}

	file>>b;
	file>>m;
	file>>am;

	m_stream = new int[m];
	for(int i = 0;i<m;i++){
		int x;
		file>>x;
		m_stream[i] = x;
	}

	file.close();
	return 1;

}


unsigned int hyperLogLog::MurmurHash2 (const void * key, int len, unsigned int seed ){
	const unsigned int m = 0x5bd1e995;
	const int r = 24;
	unsigned int h = seed ^ len;
	const unsigned char * data = (const unsigned char *)key;
	while(len >= 4)
	{
		unsigned int k = *(unsigned int *)data;
		k *= m; 
		k ^= k >> r; 
		k *= m; 
		h *= m; 
		h ^= k;
		data += 4;
		len -= 4;
	}
	switch(len)
	{
	case 3: h ^= data[2] << 16;
	case 2: h ^= data[1] << 8;
	case 1: h ^= data[0];
	        h *= m;
	};
	h ^= h >> 13;
	h *= m;
	h ^= h >> 15;
	return h ;
} 

int hyperLogLog::trimmedCardinality(){

	int cutoff = ceil((double)m * 0.2); //10%cutoff
	int rem = m - cutoff;
	// cout << rem<<cutoff<<endl;

	int *power2 = new int[rem];

	// double am = 0;
	// am = 

	for(int i = 0;i<cutoff;i++){
		int max = i;

		if(i<cutoff/2){
			for(int j = i;j<m;j++){
				if(m_stream[j]<m_stream[max])
					max = j;
			}
		}
		else{
			for(int j = i;j<m;j++){
				if(m_stream[j]<m_stream[max])
					max = j;
			}

		}

		int temp = m_stream[i];
		m_stream[i] = m_stream[max];
		m_stream[max] = temp;

	}

	for(int i = cutoff;i<m;i++){
		if(m_stream[i]==INT_MIN){
			power2[i - cutoff] = 0;
			// for(int k = i;k<rem-1;k++){
			// 	power2[k] = power2[k+1];
			// 	rem--;
			// 	cutoff++;
			// }
			continue;
		}
		power2[i - cutoff] = pow(2,m_stream[i]);
	}
	// cout<<endl<<"2 power:";
	// for(int i =0;i<rem;i++)
	// 	cout<<power2[i]<<" ";
	// cout<<endl;

	double harmonicM = harmonicMean(power2 , rem);
	// double a = (double)(1/(rem*J0(rem)));
	double a = getAM(rem);

	// return harmonicM;



	// cout<<"Harmonic mean= "<<harmonicM<<endl;
	harmonicM *= (rem*a);
	// cout<<"Harmonic mean= "<<harmonicM<<endl;
	

	delete []power2;

	return (int)harmonicM;



}
