#include "bloom.h"
#include "bloom.cpp"
#include "hyperLogLog.h"
#include "hyperLogLog.cpp"
#include "print.cpp"
#include "CountMinSketch.hpp"
#include "CountMinSketch.cpp"
countMinSketch myCMS;

int main(int argc, char** argv){
    //printing everything
    print();
    // Using murmurHash2 with 12 different seed values
    Bloom mybloom;
    string word;
    //ifstream infile("dictionary.txt");

    cout << "Enter the dictionary file: ";
   	string dictionary;
	cin >> dictionary;
    long int t1, t0;

	ifstream infile(dictionary.c_str());

    while (getline(infile,word)){
        mybloom.insert(word);
    }
    
    infile.close();
    // close dictionary
    
    //ifstream itfile("testWords.txt");
    string actual_file;
    cout << "Enter the file to be tested: ";
    cin >> actual_file;
    ifstream itfile(actual_file.c_str());
    // load test words and "check spelling"
    cout << endl << endl;
    cout << "\t\t******Bloom Filter by Priya Nayak******" << endl << endl;
    cout << "Dictionary Built.\n";
    
    int count_present = 0;
    int count_absent = 0;

    string test_word;
    t0 = rdtsc();     //start timer
    while (itfile >> test_word){
        if (mybloom.is_in(test_word)){
            // cout << test_word << " is in the dictionary." << endl;
            count_present += 1;
            // cout << test_word << endl;
            // outfile << test_word+"\n";
            // final.push_back(test_word);
        } else {
            // cout << test_word << " is NOT in the dictionary." << endl;
            count_absent += 1;
        }
    }
    t1 = rdtsc();
    itfile.close(); 
    cout << count_absent << " of " << count_absent + count_present<< " words are not present." << endl;
    printf("Number of Words found in: %lf\n", (t1-t0)/FREQ);
    // cout << count_present << " words are present." << endl;

    //End of Bloom Filter.

    //Hyper Log Log
    cout << endl << endl;
    cout << "\t\t******HyperLogLog by Abhiram Bellur******" << endl << endl;
    ifstream file(actual_file.c_str());
    hyperLogLog HLL(4);
    long int t2, t3;
    
    while(!file.eof()){
        char word[100];
        file>>word;
        // cin>>word;
        // cout<<word<<endl;
        HLL.add_HLL(word);
    }
    
    cout << "HyperLogLog Addition Done.\n";
    
    t2 = rdtsc();
    cout<<"Cardinality Estimate: "<<HLL.trimmedCardinality()<<endl;
    t3 = rdtsc();
    printf("Estimate done in: %lf\n", (t3-t2)/FREQ);
    HLL.store_toFile((char*)"hpHLL.txt");
    file.close();

    cout << endl << endl;
    cout << "\t\t******CountMinSketch by Nakul Srivathsa******" << endl << endl;
    ifstream ffile(actual_file.c_str());
    long int t4, t5;
    
    while(!ffile.eof()){
        char word[100];
        ffile>>word;
        // cin>>word;
        // cout<<word<<endl;
        // HLL.add_HLL(word);
        myCMS.inc(word);
    }
    
    ffile.close();
    cout << "CountMinSketch Inclusion Done.\n";
    
    int t;
    cout<<"Enter number of words to be tested for frequency: ";
    cin >> t;
    vector <int> times;
    vector <string> words;
    t4 = rdtsc();
    for(int i = 0;i<t;i++){
        char word[50];
        cout << "Enter the Word: ";
        cin >> word;
        words.push_back(word);
        // cout<<"Estimated frequency of '"<<word<<"': "<<myCMS.cnt(word)<<endl;
        times.push_back(myCMS.cnt(word));
    }
    t5 = rdtsc();

    for(int i = 0; i < times.size(); i++)
    {
        cout <<"Frequency of " << words[i] <<": " << times[i] << endl;
    }
    printf("Frequency found in: %lf\n", (t5-t4)/FREQ);
}