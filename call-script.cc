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
#include <chrono>
#include <ctime>

using namespace std;
using namespace cgicc;


string exec(const char* cmd);
string uniqueid();

template <typename Duration>
string print_time(tm t, Duration fraction);

string unquote(string query);

string command;

static string logFileLocation = "/home/vamsidhar/logging/logs.txt" ;

static string db = "/home/vamsidhar/db";

static string modelFileLocation = "/home/vamsidhar/happy.txt";

int main(int argc, char *argv[])
{
	  Cgicc formData;

	  const char* c_str();

	  char *hostName = getenv("SERVER_NAME"); 


	  string url = "http://";
	  url += hostName;
	  url += "/cgi-bin/click-record.cgi";
	  //string url = "http://";
	  string cmdGeneration = "xapian-rank --db=";
          cmdGeneration += db;
	  cmdGeneration += " ";
	  cmdGeneration += modelFileLocation;
	  cmdGeneration += " ";

   	  form_iterator fi = formData.getElement("query");  
	
	  string query;

	  if( !fi->isEmpty() && fi != (*formData).end()) {
		query = "'";
		string str = **fi;
	        query +=unquote(str);
		//query +=(**fi);
      		query += "'";
   	  }

	   else{
	   	query += "'all'";
	   }
	
	
	   cout << "Content-type:text/html\r\n\r\n";
	   cout << "<html>\n";
	   cout << "<head>\n";
	   cout << "<title>Using GET and POST Methods</title>\n";
	   cout << "</head>\n";
	   cout << "<body>\n";
           //sprintf(command, "%s %s", cmdGeneration.c_str(), query.c_str());
	   command += cmdGeneration;
	   command += query;
           string result = exec(command.c_str());
	   string id = uniqueid();


	   //checking if the logs are empty


	   char ch;
	   bool empty=false;
	   FILE *file = fopen(logFileLocation.c_str(), "r");
	   if(fscanf(file,"%c",&ch)==EOF)
       	    {
		empty = true;
	    }
	   fclose(file);

	  // logging

 	  ofstream myfile;
  	  myfile.open (logFileLocation.c_str(), std::ios_base::app);

	  if(!empty){
		myfile << "\n";
	   }
	   
	   myfile << '<';
  	   myfile << "letor:: ";
	   myfile << "qid:";
	   myfile << id;
           myfile << " query:";
	   myfile << query;
  	   

	   std::istringstream f(result);
           std::string line;    
    	   while (std::getline(f, line)) {
		myfile << " ";
	   	myfile << "docid:";
	   	myfile << line;
		cout << "<a href="<<url<< "?did=" << line << "&qid="<< id <<""<<">"<< line << "</a>";
		cout << "<br/>\n";
    	   }

	   myfile << '>';
	   myfile.close();
	   //cout << result << endl;
	   //cout << query.c_str() << endl; 
	   
	   cout << "</body>\n";
	   cout << "</html>\n";
}

string unquote(string query){
	string pre;
	string post;
	std::size_t found = query.find("'");
	while(found!=std::string::npos){
		pre = query.substr(0,found);
		post = query.substr(found+1);
		query = pre;
		query +=post;
		found = query.find("'");
	}
	return query;	

}

std::string exec(const char* cmd) {
    char buffer[128];
    std::string result = "";
    FILE* pipe = popen(cmd, "r");
    if (!pipe) throw std::runtime_error("popen() failed!");
    try {
        while (!feof(pipe)) {
            if (fgets(buffer, 128, pipe) != NULL)
                result += buffer;
        }
    } catch (...) {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    return result;
}


std::string uniqueid() {
    using namespace std;
    using namespace std::chrono;

    system_clock::time_point now = system_clock::now();
    system_clock::duration tp = now.time_since_epoch();

    tp -= duration_cast<seconds>(tp);

    time_t tt = system_clock::to_time_t(now);

    return print_time(*gmtime(&tt), tp);
}

template <typename Duration>
std::string print_time(tm t, Duration fraction) {
    using namespace std::chrono;
    /*std::printf("[%04u-%02u-%02u %02u:%02u:%02u.%03u]\n", t.tm_year + 1900,
                t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec,
                static_cast<unsigned>(fraction / milliseconds(1)));*/
	
    string id = std::to_string(t.tm_year+1900);
    id += std::to_string( t.tm_mon + 1);
    id += std::to_string( t.tm_mday);
    id += std::to_string( t.tm_hour);
    id += std::to_string( t.tm_min);
    id += std::to_string( t.tm_sec);
    id += std::to_string( static_cast<unsigned>(fraction / milliseconds(1)));
    return id;
    // VS2013's library has a bug which may require you to replace
    // "fraction / milliseconds(1)" with
    // "duration_cast<milliseconds>(fraction).count()"
}
