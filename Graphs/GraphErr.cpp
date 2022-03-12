#include "TCanvas.h"
#include "TGraphErrors.h"
#include <fstream>
#include <iostream>
#include "TF1.h"
#include "TMath.h"
#include "TAxis.h"

char* Addpdf(char*& nArq){

    std::string temp = nArq;

    int n = temp.size();

    temp.erase(n-3,3);

    temp= temp+"pdf";

    char *name = &temp[0];

    return name;
}

void PrintUsage(){

    std::cout << "Usage:\n\n./[Compile_name] [Data_file] [Xmin] [Xmax] [XTitle] [YTitle] [Title]" 
        << " [Xpos] [Ypos] [Expos] [Eypos]\n\n";
}

void GpWE(char* nArq, double xmin = 0, double xmax = 100, char* xtitle = "#bf{[u.a.]}", 
    char* ytitle = "#bf{[u.a.]}",char* title = "", int posx = 0, int posy = 1, 
    int posex = 2, int posey = 3){
    
    TCanvas *c1 = new TCanvas();    

    c1->SetTickx();
    c1->SetTicky();
    c1->SetGridx();
    c1->SetGridy();

    TGraphErrors *gr = new TGraphErrors();

    gr->GetXaxis()->SetTitle(xtitle);
    gr->GetYaxis()->SetTitle(ytitle);
    gr->GetXaxis()->SetLabelFont(132);
    gr->GetXaxis()->SetTitleFont(132);
    gr->GetYaxis()->SetLabelFont(132);
    gr->GetYaxis()->SetTitleFont(132);
    gr->GetYaxis()->SetLabelSize(0.035);
    gr->GetYaxis()->SetTitleSize(0.035);
    gr->GetXaxis()->SetLabelSize(0.035);
    gr->GetXaxis()->SetTitleSize(0.035);
    gr->GetYaxis()->SetTitleOffset(1.5);
    gr->GetXaxis()->SetMaxDigits(2);
    gr->SetMarkerStyle(kFullCircle);
    gr->SetMarkerSize(0.7);

    std::fstream file;
    file.open(nArq, std::ios::in);

    if(!file.is_open()){PrintUsage(); return;}

    double x1[4];

    int n = 0;

    while(!file.eof()){
        file >> x1[0] >> x1[1] >> x1[2] >> x1[3];
    
        n = gr->GetN();

        gr->SetPoint(n, x1[posx], x1[posy]);
        gr->SetPointError(n, x1[posex], x1[posey]);
    
    }

    file.close();

    gr->GetXaxis()->SetLimits(xmin, xmax);
    c1->cd();
    gr->Draw("AP");

    c1->Print(Addpdf(nArq));
}

int main(int argc, char** argv){

    switch (argc){
        case 2:
            GpWE(argv[1]);
            break;
        case 3:
            GpWE(argv[1], std::stod(argv[2]));
            break;
        case 4:
            GpWE(argv[1], std::stod(argv[2]), std::stod(argv[3]));
            break;
        case 5:
            GpWE(argv[1], std::stod(argv[2]), std::stod(argv[3]), argv[4]);
            break;
        case 6:
            GpWE(argv[1], std::stod(argv[2]), std::stod(argv[3]), argv[4], argv[5]);
            break;
        case 7:
            GpWE(argv[1], std::stod(argv[2]), std::stod(argv[3]), argv[4], argv[5], argv[6]);
            break;
        case 8:
            GpWE(argv[1], std::stod(argv[2]), std::stod(argv[3]), argv[4], argv[5], argv[6], 
                std::stoi(argv[7]));
            break;
        case 9:
            GpWE(argv[1], std::stod(argv[2]), std::stod(argv[3]), argv[4], argv[5], argv[6], 
                std::stoi(argv[7]), std::stoi(argv[8]));
            break;
        case 10:
            GpWE(argv[1], std::stod(argv[2]), std::stod(argv[3]), argv[4], argv[5], argv[6], 
                std::stoi(argv[7]), std::stoi(argv[8]), std::stoi(argv[9]));
            break;
        case 11:
            GpWE(argv[1], std::stod(argv[2]), std::stod(argv[3]), argv[4], argv[5], argv[6], 
                std::stoi(argv[7]), std::stoi(argv[8]), std::stoi(argv[9]), std::stoi(argv[10]));
            break;
        default:
            PrintUsage();
            break;
    }

    return 0;
}