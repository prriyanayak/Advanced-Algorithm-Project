#define FREQ 2.60e9

unsigned long long rdtsc()
{
  unsigned a, d;

  __asm__ volatile("rdtsc" : "=a" (a), "=d" (d));

  return ((unsigned long long)a) | (((unsigned long long)d) << 32);
}

void print()
{
	cout << "Project Done By - " << endl;
	cout << "Abhiram Bellur" << endl;
	cout << "Nakul Srivathsa" << endl;
	cout << "Priya S Nayak" << endl;
	cout << "******Implementation of Probablistic Data Structures******" << endl;
}

