#include <algorithm>
#include <cstdlib>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

#include "timing.h"
#include "Hash.h"
// typedef to save typing for the following object	
typedef std::vector< std::vector<std::string> > txtVector;

int compare (const void * a, const void * b)
{
	return ( *(int*)a - *(int*)b );
}

class sorters
{
public:

	int values[10000];
	std::vector<int> vec; 
	sorters()
	{
		values[0] = 40;
		values[1] = 10;
		values[2] = 100;
		values[3] = 90;
		values[4] = 20;
		values[5] = 25;
		for(int i = 0; i < 10000; ++i)
		{
			values[i] = rand()%10000;
			vec.push_back(values[i]);
		}
		Hashing trial;
		//trial.length(values);
	};
	~sorters(){};

	int qsorting()
	{
		CTiming timer;
		int n;
		qsort(values, 10000, sizeof(int), compare);
		return 0;
	}
	
	int std_sorting()
	{
		CTiming timer;
		int elements = sizeof(values) / sizeof(values[0]); 
		std::sort(values, values + elements);
		return 0;
	}
	int stdvector_sorting()
	{
		CTiming timer;
		std::sort(vec.begin(), vec.end());
		return 0;
	}

	void quickSort() 	//void quickSort(int array[]) 
	{
		CTiming timer;
		quickSort(0, sizeof(values) / sizeof(values[0]));
	}


	void quickSort(int start, int end)//void quickSort(int array[], int start, int end)
	{
			int i = start;                         
			int k = end;                           

			if (end - start >= 1)                   
			{
					int pivot = values[start];       

					while (k > i)                   
					{
							while (values[i] <= pivot && i <= end && k > i)  
									i++;                                   
							while (values[k] > pivot && k >= start && k >= i) 
								k--;                                        
							if (k > i)                                      
									swap( i, k);                     
					}
					swap( start, k);          
													
					quickSort( start, k - 1); 
					quickSort( k + 1, end);  
			}
			else    
			{
					return;                     
			}
	}

	void swap(int index1, int index2) 
	{
		int temp = values[index1];           
		values[index1] = values[index2];      
		values[index2] = temp;               
	}
};

class TXT 
{
public:
	TXT(){};
	void readTXT(std::istream &input, std::vector< std::vector<std::string> > &output)
	{
		CTiming timer;
		output.clear();
		txtData.clear();
		std::string txtLine;
		// read every line from the stream
		while( std::getline(input, txtLine) )
		{
			std::istringstream txtStream(txtLine);
			std::vector<std::string> txtColumn;
			std::string txtElement;
			// read every element from the line that is seperated by space
			// and put it into the vector or strings
			while( std::getline(txtStream, txtElement, ' ') )
			{
				txtColumn.push_back(txtElement);
				words++;
			}		
			output.push_back(txtColumn);
		}
		txtData = output;
	}

	void printTXT()
	{
		for(txtVector::iterator i = txtData.begin(); i != txtData.end(); ++i)
		{
			for(std::vector<std::string>::iterator j = i->begin(); j != i->end(); ++j)
			{
				std::cout << *j << ",";
			}
			std::cout << "\n";
		}
	}

	void Unique()
	{
		//CTiming timer;
		for(txtVector::iterator i = txtData.begin(); i != txtData.end(); ++i)
		{
			for(std::vector<std::string>::iterator j = i->begin(); j != i->end(); ++j)
			{
				unique_words.push_back(*j);
				std::string word;
				word = *j;
				Hash(word);
				//std::cout << *j << "\n";
			}

			std::sort(unique_words.begin(), unique_words.end());

			std::vector<string>::iterator p = unique_words.begin();
			while( p != unique_words.end() )
			{
				int i = 0;
				i = count(unique_words.begin(),unique_words.end(),*p++);
				
				//cout << *p++ << "=" << i << endl;
			}

			std::cout << "\n";
		}
	}

	void Hash(std::string key)
	{
		CTiming timer;
		int prime = 271;
		int bucket = 0;

		int length = strlen(key.c_str());
		unsigned int val = 0;

		unsigned long hash = 5381;
		int c = 0;
		for(int i=0; i < strlen(key.c_str()); ++i)
		{
			c = key.at(i);
			hash = ((hash<<5) + hash) + c;
		}

		bucket = hash % prime;

		if(hash_table[bucket].keyfield == 0)
		{
			hash_table[bucket].keyfield = hash;
			hash_table[bucket].datafield = key;
			hash_table[bucket].counter++;
		}
		else
		{
			if(hash_table[bucket].keyfield == hash)
			{
				hash_table[bucket].counter++;
			}
			else
			{
				bucket = (hash + 1) % prime;
			}
		}
	}

	void qsorting()
	{
		sorters sorter;
		sorter.qsorting();
	}

	void std_sorting()
	{
		sorters sorter;
		sorter.std_sorting();
	}

	void stdvector_sorting()
	{
		sorters sorter;
		sorter.stdvector_sorting();
	}

	void own_quicksort()
	{
		sorters sorter;
		sorter.quickSort();
	}

	txtVector GetData()
	{
		return txtData;
	}

private:

	txtVector txtData;
	RECT UIObject;
	std::vector<string> unique_words;
	struct hash_node
	{
		int keyfield;
		std::string datafield;
		int counter;
	};

	hash_node hash_table[271];
	unsigned int words;
};

// http://technet.microsoft.com/en-us/library/2dzy4k6e(VS.80).aspx