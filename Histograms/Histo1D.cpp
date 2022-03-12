#include "TH1F.h"
#include "TCanvas.h"
#include <fstream>
#include <iostream>
#include <cstring>
#include "TF1.h"
#include "TMath.h"

double FindMax(std::string& name){

    std::fstream arq;

    double temp, xmax;
    
    arq.open(name, std::ios::in);
    arq >> xmax;
    
    while(!arq.eof()){
        
        arq >> temp;
        
        if(temp > xmax){
            
            xmax = temp;
        }
    }

    arq.close();

    return xmax;
}

int FindN(std::string& name){
    
    std::fstream arq;

    double temp;
    int i=0;

    arq.open(name, std::ios::in);

    while(!arq.eof()){
        
        arq >> temp;
        i++;
    }
    
    arq.close();
    
    return i;
}

char* Addpdf(char*& nArq){

    std::string temp = nArq;

    int n = temp.size();

    temp.erase(n-3,3);

    temp= temp+"pdf";

    char *name = &temp[0];

    return name;
}

void PrintUsage(){

    std::cout << "Usage:\n\n./[Compile_name] [Data_file] [Xmax] [nBin] [XTitle] [Title]\n\n";
}

void Histo1D(char* nArq, double xmax = 50000, int nDiv = 100, char* xtitle = "#bf{[u.a.]}", 
    char* title = ""){

    TH1F *Histo1D = new TH1F("h1", title, nDiv, 0, xmax);

    TCanvas *c1 = new TCanvas();

    std::fstream file;

    file.open(nArq, std::ios::in);

    if(!file.is_open()){PrintUsage(); return;}

    float x;

    while(!file.eof()){

        file >> x;
        Histo1D->Fill(x);

    }

    file.close();
    
    Histo1D->SetXTitle(xtitle);
    Histo1D->SetYTitle("");
    Histo1D->GetYaxis()->SetMaxDigits(2);
    Histo1D->GetXaxis()->SetMaxDigits(3);
    Histo1D->SetLineColor(kBlack);
    Histo1D->SetFillColor(kBlack);
    Histo1D->SetFillStyle(3003);
    Histo1D->SetStats(0);
    Histo1D->Draw();

    c1->Print(Addpdf(nArq));

}

int main(int argc,char** argv){

    std::string arquivo, nomearquivo, maximo, divisao, parametro;

    switch (argc){
        case 2:
            nomearquivo = argv[1];
            Histo1D(argv[1], TMath::Ceil(FindMax(nomearquivo)/500)*500, TMath::CeilNint(TMath::Sqrt(FindN(nomearquivo))));
            break;
        case 3:
            nomearquivo = argv[1];
            maximo = argv[2];
            Histo1D(argv[1], std::stod(maximo), TMath::CeilNint(TMath::Sqrt(FindN(nomearquivo))));
            break;
        case 4:
            maximo = argv[2];
            divisao = argv[3];
            Histo1D(argv[1], std::stod(maximo), std::stoi(divisao));
            break;
        case 5:
            maximo = argv[2];
            divisao = argv[3];
            Histo1D(argv[1], std::stod(maximo), std::stoi(divisao), argv[4]);
            break;
        default:
            PrintUsage();
            break;
    }
    return 0;
}