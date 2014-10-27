#include <TFile.h>
#include <TH2F.h>
#include <TCanvas.h>
//#include <TPaletteAxis.h>
#include <TPaveStats.h>
#include <TText.h>
#include <TColor.h>
#include <TString.h>
#include <iostream>

int main(int argc, char** argv){
//=========Macro generated from canvas: Canvas_1/Canvas_1
//=========  (Wed Aug 27 23:28:50 2014) by ROOT version5.34/04
   TCanvas *Canvas_1 = new TCanvas("Canvas_1", "Canvas_1",258,73,1243,811);
   Canvas_1->Range(-0.0625,-0.0625,0.0625,0.0625);
   Canvas_1->SetFillColor(0);
   Canvas_1->SetBorderMode(0);
   Canvas_1->SetBorderSize(2);
   Canvas_1->SetFrameBorderMode(0);
   Canvas_1->SetFrameBorderMode(0);
   
   TFile f(argv[1],"r");
   TH2F *h1 = (TH2F*)f.Get("h2dir/h4");
/*  
   TPaletteAxis *palette = new TPaletteAxis(0.050625,-0.05,0.05625,0.05,h1);
palette->SetLabelColor(1);
palette->SetLabelFont(42);
palette->SetLabelOffset(0.005);
palette->SetLabelSize(0.035);
palette->SetTitleOffset(1);
palette->SetTitleSize(0.035);
   palette->SetFillColor(100);
   palette->SetFillStyle(1001);
   h1->GetListOfFunctions()->Add(palette,"br");
*/
   
   TPaveStats *ptstats = new TPaveStats(0.700565,0.6608696,0.9007264,0.9006211,"brNDC");
   ptstats->SetName("stats");
   ptstats->SetBorderSize(1);
   ptstats->SetFillColor(0);
   ptstats->SetTextAlign(12);
   ptstats->SetTextFont(42);
   TText *text = ptstats->AddText("h1");
   text->SetTextSize(0.03676191);
   text = ptstats->AddText("Entries = 101    ");
   text = ptstats->AddText("Mean x = -0.0003512");
   text = ptstats->AddText("Mean y = -0.0003318");
   text = ptstats->AddText("RMS x = 0.01432");
   text = ptstats->AddText("RMS y = 0.01428");
   ptstats->SetOptStat(1111);
   ptstats->SetOptFit(0);
   ptstats->Draw();
   h1->GetListOfFunctions()->Add(ptstats);
   ptstats->SetParent(h1);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#000099");
   h1->SetLineColor(ci);
   h1->GetXaxis()->SetTitle("mm");
   h1->GetXaxis()->SetLabelFont(42);
   h1->GetXaxis()->SetLabelSize(0.035);
   h1->GetXaxis()->SetTitleSize(0.035);
   h1->GetXaxis()->SetTitleFont(42);
   h1->GetYaxis()->SetTitle("mm");
   h1->GetYaxis()->SetLabelFont(42);
   h1->GetYaxis()->SetLabelSize(0.035);
   h1->GetYaxis()->SetTitleSize(0.035);
   h1->GetYaxis()->SetTitleFont(42);
   h1->GetZaxis()->SetLabelFont(42);
   h1->GetZaxis()->SetLabelSize(0.035);
   h1->GetZaxis()->SetTitleSize(0.035);
   h1->GetZaxis()->SetTitleFont(42);
   h1->Draw("COLZ ");
   
   TPaveText *pt = new TPaveText(0.1594915,0.9368634,0.8405085,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetFillStyle(0);
   pt->SetTextFont(42);
   text = pt->AddText("2D Energy deposit distribution at z=-25um");
   pt->Draw();
   Canvas_1->Modified();
   Canvas_1->cd();
   Canvas_1->SetSelected(Canvas_1);
   std::cout<<argv[1]<<std::endl;
   Canvas_1->SaveAs(TString(argv[1])+"35#.png");
}
