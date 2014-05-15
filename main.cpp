#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

std::string scrub (const std::string& oldtoken, const std::string& chars) {
	std::string newtoken;
	unsigned oldlen = oldtoken.length();
	if(oldlen == 0)	return newtoken;
	if(chars.length() == 0)	return newtoken;
	
	char* str = (char*)oldtoken.c_str();
	
	for(str = strtok(str,(char*)chars.c_str()); str != NULL; str = strtok(NULL,(char*)chars.c_str())){
		newtoken += str;
	}
	return newtoken;
}

std::string trim(const std::string& oldstr){
	std::string newstr;
	if(oldstr.length()){
		unsigned int i	= oldstr.find_first_not_of(' ');
		unsigned int j	= oldstr.find_last_not_of(' ');
		newstr	= oldstr.substr(i,j-i+1);
	}
	return newstr;
}

void processLine (const std::string& line) {

	std::istringstream ss(line);
	std::string chars, result, str, token;

	std::getline(ss,str,',');
	std::getline(ss,chars);
	std::istringstream tokens(str);
	
	chars = trim(chars);
	str = trim(scrub(str,chars));
	std::cout << str << '\n';
	/****
	while(!tokens.eof()){
		tokens >> token;
		token = scrub(token,chars);
		if(token.length() > 0){
			if(result.length() > 0){
				result += ' ';
			}
			result += token;
		}
	}
	std::cout << result << '\n';****/
	return;
}


int main(int argc, char **argv)
{
	std::ifstream file;
	std::string line;
	file.open (argv[1]);

	if(file.good()){
		while(std::getline(file,line)){
			processLine(line);
		}
	}else{
		std::cout << strerror(errno) << "\n";
		std::cout << "Could not open " << argv[1] << "\n";
	}

	return 0;
}
