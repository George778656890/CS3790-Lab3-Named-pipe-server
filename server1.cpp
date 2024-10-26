//CS3790 Lab assignment3---Named pipe-worker server
//Zhihong  Liu(5088806)
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cmath> 
#include <iostream>
#include <vector>

using namespace std;

bool isPrime(int num) {  
    if (num <= 1) return false;  // 0 and 1 are not prime numbers  
    if (num <= 3) return true;   // 2 and 3 are prime numbers  

    // Check for factors from 2 to sqrt(num)  
    for (int i = 2; i <= sqrt(num); ++i) {  
        if (num % i == 0) {  
            return false;  // Found a factor, num is not prime  
        }  
    }  
    return true;  // No factors found, num is prime  
} 

//Check whether the 2nd and 3rd parts of the request are number
bool NotNumber(string s){

	const char *a=s.c_str();

	for(int i=0;i<s.size();++i){
		if(!isdigit(a[i])){
			return true;
		}
	}

	return false;
}

int main()
{
	int fd1;

	// FIFO file path
	char * myfifo = "/tmp/myfifo";

	// Creating the named file(FIFO)
	// mkfifo(<pathname>,<permission>)
	mkfifo(myfifo, 0666);

	char str2[80]="Malformed request!!!";
	while (1)
	{
		char str1[80]={};

		// First open in read only and read
		fd1 = open(myfifo,O_RDONLY);
		read(fd1, str1, 80);

		//Ignore the empty user request
        if(*str1!='\0'){

		// Print the read string and close
		printf("User Request : %s\n", str1);

		// Returns first token
		char* token = {strtok(str1, " ")};

		vector<string> request;
		
	    // Keep printing tokens while one of the delimiters present in str[].
	    while (token != nullptr) {
			request.push_back(string(token));
			token = strtok(NULL, " ");
			
		}
	   
	   //User request length
	   int requestLength=request.size();

       //Get the first part of user request message
	   string rangeLiteral=request[0];

	   //Convert to upper case
	   for(auto &c:rangeLiteral){
			c=toupper(c);
	   }


	//Check the validity of the user request
	if(requestLength!=3|| (rangeLiteral!="RANGE") || NotNumber(request[1]) || NotNumber(request[2]) )
	{
		close(fd1);

		// Now open in write mode and inform the client that it is malformed request
		fd1 = open(myfifo,O_WRONLY);
		write(fd1, str2, strlen(str2)+1);
		close(fd1);

	}else{

	   //Get the 2nd and 3rd part of user request message
	   int range1=atoi(request[1].c_str());
	   int range2=atoi(request[2].c_str());

		//Make sure the correct range
	   if(range1<range2){

	   string primeSequence="";

	   //Calculating  the prime number within the given range and generating the corresponding string
	    for(int i=range1;i<=range2;++i){
    	if(isPrime(i)){
    	    primeSequence=primeSequence+" "+string(to_string(i));
    	}
		
		}

		const char *primeSequenceC_stype=primeSequence.c_str(); 

		close(fd1);

		//Now open in write mode and write the primeSequence to the pipe
		fd1 = open(myfifo,O_WRONLY);
		write(fd1, primeSequenceC_stype, strlen(primeSequenceC_stype)+1);
		close(fd1);
	   }else{

		close(fd1);

		// Now open in write mode and inform the client that it is malformed request
		fd1 = open(myfifo,O_WRONLY);
		write(fd1, str2, strlen(str2)+1);
		close(fd1);
	   }



	  }

	}
	
}
     return 0;
}