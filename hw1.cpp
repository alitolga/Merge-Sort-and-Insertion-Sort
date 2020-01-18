#include <iostream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <sstream>
#include <utility>
#include <ctime>

using namespace std;

bool checkErrors(int argnum, char* args[7]);
string readFile(vector<pair<string, string>> &array, int &size, int number_of_columns, char &feature);
void mergeSort(vector<pair<string, string>> &array, int l, int r, char &feature);
void merge(vector<pair<string, string>> &array, int l, int middle, int r, char &feature);
void insertionSort(vector<pair<string, string>> &array, int size, char &feature);
string split(string &s, char delimiter, int &n);
void writeFile(vector<pair<string, string>> &array, int size, string beginning);
void writeCalcTime(float &seconds, char &algo, char &feature, int &size);

int main(int argnum, char* args[7])
{

	// Checking if the program is run with the correct arguments
	if(checkErrors(argnum, args))
		return 0;

	char algo = args[2][0];
	char feature = args[4][0];
	int size = atoi(args[6]);
	clock_t t;

	int number_of_columns = 42;

	// Vector to read the data.
	vector<pair<string, string>> array;

	// Reading the file and returning the first line.
	string beginning = readFile(array, size, number_of_columns, feature);

	// Time start for the selected sort.
	t = clock();
	if (algo == 'i'){
		insertionSort(array, size, feature);
	}
	else if(algo == 'm'){
		mergeSort(array, 0, array.size()-1, feature);
	}
	t = clock() - t;
	// Time end

	float seconds = ((float)t) / CLOCKS_PER_SEC;

	writeFile(array, size, beginning);
	writeCalcTime(seconds, algo, feature, size);

    return 0;
}

// Writing the time taken to a text file.
void writeCalcTime(float &seconds, char &algo, char &feature, int &size)
{
	fstream myfile;
	myfile.open("calcTimes.csv", ios::out | ios::app);
	string alg, ftr;
	if(algo == 'i') alg = "Insertion Sort";
	else alg = "Merge Sort";
	if(feature == 'p') ftr = "last_price";
	else ftr = "timestamp";
	myfile << alg << "," << ftr << ",";
	myfile << size << "," << seconds << endl;
	myfile.close();
}

// Writing the sorted output to sorted.csv file.
void writeFile(vector<pair<string, string>> &array, int size, string beginning)
{
	fstream myfile;
	myfile.open("sorted.csv", ios::out);
	if (!myfile.is_open()){
		cout << "sorted.csv file cannot be opened for write mode" << endl;
	}

	myfile << beginning << endl;
	for (int i = 0; i < size; ++i){
		myfile << array[i].first << endl;
	}
	myfile.close();
}

// Checking if the program is run with the correct arguments
bool checkErrors(int argnum, char* args[7])
{
	if(argnum != 7){
		cout << "The program takes 6 arguments not: " << argnum-1 << endl;
		return 1;
	}
    if(strcmp(args[1], "-algo") != 0){
    	cout << "First argument " << args[1] << " must be -algo" << endl;
    	return 1;
    }
    char algo = args[2][0];
    if(algo != 'i' && algo != 'm'){
    	cout << "There is no sorting algorithm for the specified input: " << args[2] << endl;
		return 1;
    }
    if(strcmp(args[3], "-feature") != 0){
    	cout << "Third argument " << args[3] << " must be -feature" << endl;
    	return 1;
    }
	char feature = args[4][0];
    if(feature != 'p' && feature != 't'){
    	cout << "There is no available sorting feature for the specified input: " << args[4] << endl;
		return 1;
    }
    if(strcmp(args[5], "-size") != 0){
    	cout << "Fifth argument " << args[5] << " must be -size" << endl;
    	return 1;
    }
    int size = atoi(args[6]);
    if(size <= 0){
    	cout << "Please enter a valid number for size" << endl;
    	return 1;
    }
    return 0;
}

// Reads file and returns the first line.
string readFile(vector<pair<string,string>> &array, int &size, int number_of_columns, char &feature)
{
	fstream myfile;
	myfile.open ("log_inf.csv", ios::in);
	if (!myfile.is_open()){
		cout << "log_inf.csv file cannot be opened for read mode" << endl;
	}
	
	int n = 1;
	if(feature == 'p') n=3;

	string beginning;
	getline(myfile, beginning);
	string temp, temp2;
	for (int i = 0; i < size; ++i)
	{
		getline(myfile, temp);
		temp2 = split(temp, ',', n);
		array.push_back(make_pair(temp, temp2));
	}
	myfile.close();
	return beginning;
}

// Returns the value in the specified column.
string split(string &s, char delimiter, int &n)
{
	istringstream tokenStream(s);
	string token;
	for (int i = 0; i < n; ++i){
		getline(tokenStream, token, delimiter);
	}
	return token;
}

void insertionSort(vector<pair<string, string>> &array, int size, char &feature)
{
	vector<pair<string, string>> array2;
	array2.push_back(array[0]);
	pair<string, string> element;
	int n;
	float val1, val2;
	int length = array.size();
	float prices[length];
	for (int i = 1; i < length; ++i){
		prices[i] = stof(array[i].second);
	}

	for (int i = 1; i < size; ++i)
	{
		element = array[i];
		n = array2.size()-1;
		array2.push_back(element);
		if(feature == 'p'){
			val1 = prices[i];
			val2 = stof(array2[n].second);
			//cout << val1 << "\t" << val2 << endl;
			while(val1 < val2){
				array2[n+1] = array2[n];
				array2[n] = element;
				n--;
				if(n<0) break;
				val2 = stof(array2[n].second);
			}
		}
		else{
			while(n >= 0 && element.second < array2[n].second){
				array2[n+1] = array2[n];
				array2[n] = element;
				n--;
			}
		}
	}

	for (int i = 0; i < size; ++i){
		array[i] = array2[i];
	}
}

void mergeSort(vector<pair<string, string>> &array, int l, int r, char &feature)
{
	if(l >= r) return;
	int m = l + ((r-l)/2);
	mergeSort(array, l, m, feature);
	mergeSort(array, m+1, r, feature);
	merge(array, l, m, r, feature);
}

void merge(vector<pair<string, string>> &array, int l, int m, int r, char &feature)
{
	vector<pair<string, string>> L;
	L.resize(m-l+1);
	vector<pair<string, string>> R;
	R.resize(r-m);
	
	int Lsize = L.size();
	int Rsize = R.size();
	for (int i = 0; i < Lsize; ++i) {
		L[i] = array[l+i];
	}
	for (int j = 0; j < Rsize; ++j) {
		R[j] = array[m+j+1];
	}

	int index = l, i=0, j=0;
	while(i < Lsize && j < Rsize){
		if(feature == 'p'){
			if(stof(L[i].second) < stof(R[j].second)){
				array[index] = L[i];
				i++;
			}
			else{
				array[index] = R[j];
				j++;
			}
		}
		else{
			if(L[i].second < R[j].second){
				array[index] = L[i];
				i++;
			}
			else{
				array[index] = R[j];
				j++;
			}
		}
		index++;
	}

	while(i < Lsize){
		array[index] = L[i];
		i++;
		index++;
	}
	while(j < Rsize){
		array[index] = R[j];
		j++;
		index++;
	}
}

