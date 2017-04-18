#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <vector>  
#include <string>  
#include <stdio.h>  
#include <stdlib.h> 


#include <cgicc/CgiDefs.h> 
#include <cgicc/Cgicc.h> 
#include <cgicc/HTTPHTMLHeader.h> 
#include <cgicc/HTMLClasses.h>  

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <fstream>


using namespace std;
using namespace cgicc;

static string logFileLocation = "/home/vamsidhar/logging/logs.txt" ;

int main(int argc, char *argv[])
{

	Cgicc formData;

   	form_iterator fi = formData.getElement("did");

	string docid;

	docid ="did:";

	const char* c_str();

	if( !fi->isEmpty() && fi != (*formData).end()) {  
      		docid += **fi;
   	}

	fi = formData.getElement("qid");

	string qid="qid:";

	if( !fi->isEmpty() && fi != (*formData).end()) {  
      		qid += **fi;
   	}

	//checking if file is empty or not
	char ch;
	bool empty=false;
	FILE *f = fopen(logFileLocation.c_str(), "r");
	if(fscanf(f,"%c",&ch)==EOF)
	{
	   empty = true;
	}
	fclose(f);

	
 	ofstream myfile;
  	myfile.open (logFileLocation.c_str(), std::ios_base::app);

	if(!empty){
		myfile << "\n";
	}

	myfile << '<';
  	myfile << "uclick:: ";
	myfile << qid;
        myfile << " ";
	myfile << docid;
	myfile << '>';
  	myfile.close();

 	cout << "Content-type:text/html\r\n\r\n";
        cout << "<html>\n";
	cout << "<head>\n";
	cout << "<title>Doc</title>\n";
	cout << "</head>\n";
	cout << "<body>\n";
	cout << "Thanks for clicking";
	cout << "</body>\n";
	cout << "</html>\n";


}

bool is_empty(std::ifstream& pFile)
{
    return pFile.peek() == std::ifstream::traits_type::eof();
}
