#include "TH1F.h"
#include "TCanvas.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include "TF1.h"
#include "TMath.h"

char* Addmod(char* nArq){

    std::string temp = nArq, temp2 = nArq;

    int n = temp.size(), n2 = n;

    temp.erase(n - 4, 4);
    temp2.erase(0, n - 3);

    temp = temp + "_mod.";
    temp = temp + temp2;

    char *name = &temp[0];

    return name;

}

void PrintUsage(){

    std::cout << "Usage:\n\n./[Compile_name] [Data_file] [Cut_value]\n\n";
}

void Eli(char* nArq, double cut){
    std::fstream file;
    file.open(nArq,std::ios::in);

    if(!file.is_open()){ PrintUsage(); return;}

    float x;

    std::ofstream zFile (Addmod(nArq), std::ofstream::app);

    while(!file.eof()){
        
        file >> x;

        if(x > cut) zFile << x << "\n";
    }
}

int main(int argc,char** argv){

    switch (argc){
        case 3:
            Eli(argv[1],std::stod(argv[2]));
            break;
        default:
            PrintUsage();
            break;
    }
    return 0;
}