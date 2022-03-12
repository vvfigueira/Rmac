#include "TH2F.h"
#include "TCanvas.h"
#include <fstream>
#include <iostream>
#include <cstring>

char* Addpdf(char*& nArq){

    std::string temp = nArq;

    int n = temp.size();

    temp.erase(n-3,3);

    temp= temp+"pdf";

    char *name = &temp[0];

    return name;
}

void PrintUsage(){

    std::cout << "Usage:\n\n./[Compile_name] [Data_file] [BinX] [BinY] [Xmax] [Ymax] [Title]" 
        << " [xTitle] [yTitle]\n\n";
}

void Histo2D(char* nArq, int nDivx = 100, int nDivy = 5, double xmax = 50000, 
    double ymax = 13000,char* title = "", char* xtitle = "#bf{[u.a.]}", 
    char* ytitle = "#bf{[u.a.]}"){

    TH2F *Histo2D = new TH2F("h2", title, nDivx, 0, xmax, nDivy, 0, ymax);

    TCanvas *c1 = new TCanvas();

    std::fstream file;

    file.open(nArq, std::ios::in);

    if(!file.is_open()){PrintUsage(); return;}

    float x, y;

    while(!file.eof()){

        file >> x >> y;
        Histo2D->Fill(x,y);

    }
    Histo2D->SetXTitle(xtitle);
    Histo2D->SetYTitle(ytitle);
    Histo2D->GetYaxis()->SetMaxDigits(3);
    Histo2D->GetXaxis()->SetMaxDigits(3);
    Histo2D->SetMarkerColor(1);
    Histo2D->SetLineColor(1);
    Histo2D->SetStats(0);
    Histo2D->Draw("COLZ");

    c1->Print(Addpdf(nArq));

}

int main(int argc,char** argv){

    switch (argc){
        case 2:
            Histo2D(argv[1]);
            break;
        case 3:
            Histo2D(argv[1], std::stoi(argv[2]));
            break;
        case 4:
            Histo2D(argv[1], std::stoi(argv[2]), std::stoi(argv[3]));
            break;
        case 5:
            Histo2D(argv[1], std::stoi(argv[2]), std::stoi(argv[3]), std::stod(argv[4]));
            break;
        case 6:
            Histo2D(argv[1], std::stoi(argv[2]), std::stoi(argv[3]), std::stod(argv[4]), 
                std::stod(argv[5]));
            break;
        case 7:
            Histo2D(argv[1], std::stoi(argv[2]), std::stoi(argv[3]), std::stod(argv[4]), 
                std::stod(argv[5]), argv[6]);
            break;
        case 8:
            Histo2D(argv[1], std::stoi(argv[2]), std::stoi(argv[3]), std::stod(argv[4]), 
                std::stod(argv[5]), argv[6], argv[7]);
            break;
        case 9:
            Histo2D(argv[1], std::stoi(argv[2]), std::stoi(argv[3]), std::stod(argv[4]), 
                std::stod(argv[5]), argv[6], argv[7], argv[8]);
            break;
        default:
            PrintUsage();
            break;
    }
    return 0;
}