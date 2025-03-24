#include <vector>
#include <fstream>
#include <iostream>



std::vector<std::vector<std::string>> read_file(std::string filename) {

    std::vector<std::vector<std::string>> out;
    std:: ifstream file(filename);
    std::string line;
    while(std::getline(file,line)){
        int i=0;
        while(line[i]!=':'){i++;}
        i++;
        while(line[i]==' '){i++;}
        std::string code;
        while(line[i]!=' '){code+=line[i];i++;}
        std::vector<std::string> temp;
        temp.push_back(code);
        while(line[i]==' '){i++;}
        std::string operation;
        
        while(line[i]!='\r' && line[i]!='\0'){operation+=line[i];i++;}
        temp.push_back(operation);
        out.push_back(temp);
       
    }
    return out;

}
