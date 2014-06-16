#include "BeamAnalysisManager.hh"

BeamAnalysisManager* BeamAnalysisManager::fgInstance = 0;

BeamAnalysisManager* BeamAnalysisManager::Instance()
{
	if(fgInstance==0){
		fgInstance = new BeamAnalysisManager();
	}

	return fgInstance;
}

BeamAnalysisManager::BeamAnalysisManager()
{
	H1List = new TList();
	H2List = new TList();
	NtList = new TList();
  if ( fgInstance ) {
    G4ExceptionDescription description;
    description << " "
                << "BeamAnalysisManager already exists."
                << "Cannot create another instance.";
    G4Exception("BeamAnalysisManager::BeamAnalysisManager()",
                "Analysis_F001", FatalException, description);
  } 	
}

BeamAnalysisManager::~BeamAnalysisManager()
{
	fgInstance=0;
}

void BeamAnalysisManager::OpenFile(G4String& fileName, const G4String& option)
{
	fFile = new TFile(fileName,option);
}

void BeamAnalysisManager::CreateH1(const G4String &name, const G4String &title, G4int nbins, G4double xmin, G4double xmax, const G4String &unitName, const G4String &fcnName)
{
	TH1F *htemp = new TH1F(name,title,nbins,xmin,xmax);
	H1List->Add(htemp);
}

void BeamAnalysisManager::CreateH2(const G4String &name, const G4String &title, G4int nxbins, G4double xmin, G4double xmax, G4int nybins, G4double ymin, G4double ymax, const G4String &unitName, const G4String &fcnName)
{
	TH2F *htemp = new TH2F(name,title,nxbins,xmin,xmax,nybins,ymin,ymax);
	H2List->Add(htemp);
}

void BeamAnalysisManager::FillH1(G4int id, G4double value, G4double weight)
{
	if(TH1F *hout = (TH1F*)H1List->At(id)){
		hout->Fill(value, weight);
	}

	else{
   	 	G4ExceptionDescription description;
   		 description << " "
              		  << "H1 id is wrong."
        		        << "Cannot fill "<<value<<" to the H1.";
		    G4Exception("BeamAnalysisManager::BeamAnalysisManager()",
              		  "Analysis_W001", JustWarning, description);
	}
}

void BeamAnalysisManager::FillH1(G4int id, G4String xname, G4double weight)
{
	if(TH1F *hout = (TH1F*)H1List->At(id)){
		hout->Fill(xname, weight);
	}

	else{
   	 	G4ExceptionDescription description;
   		 description << " "
              		  << "H1 id is wrong."
        		        << "Cannot fill "<<xname<<" to the H1.";
		    G4Exception("BeamAnalysisManager::BeamAnalysisManager()",
              		  "Analysis_W001", JustWarning, description);
	}
}

void BeamAnalysisManager::FillH2(G4int id, G4double xvalue, G4double yvalue, G4double weight)
{
	if(TH2F *hout = (TH2F*)H2List->At(id)){
		hout->Fill(xvalue, yvalue, weight);
	}

	else{
   	 	G4ExceptionDescription description;
     		 description << " "
                		  << "H1 id is wrong."
          		        << "Cannot fill "<<xvalue<<", "
          			<< yvalue <<" to the H1.";
          	    G4Exception("BeamAnalysisManager::BeamAnalysisManager()",
              		  "Analysis_W001", JustWarning, description);
 	}
}

void BeamAnalysisManager::FillH2(G4int id, G4String xname, G4double yvalue, G4double weight)
{
	if(TH2F *hout = (TH2F*)H2List->At(id)){
		hout->Fill(xname, yvalue, weight);
	}

	else{
   	 	G4ExceptionDescription description;
     		 description << " "
                		  << "H2 id is wrong."
          		        << "Cannot fill "<<xname
          			<<", "<<yvalue<<" to the H2.";
          	    G4Exception("BeamAnalysisManager::BeamAnalysisManager()",
                		  "Analysis_W001", JustWarning, description);
        }
}

void BeamAnalysisManager::FillH2(G4int id, G4double xvalue, G4String yname, G4double weight)
{
	if(TH2F *hout = (TH2F*)H2List->At(id)){
		hout->Fill(xvalue, yname, weight);
	}

	else{
   	 	G4ExceptionDescription description;
     		 description << " "
                		  << "H2 id is wrong."
          		        << "Cannot fill "<<xvalue
          			<<", "<<yname<<" to the H2.";
          	    G4Exception("BeamAnalysisManager::BeamAnalysisManager()",
                		  "Analysis_W001", JustWarning, description);
        }
}

void BeamAnalysisManager::CreateNtuple(const G4String &name, const G4String &title, const G4String &varlist)
{
	TNtuple *ntemp = new TNtuple(name,title,varlist);
	NtList->Add(ntemp); 
}

void BeamAnalysisManager::FillNtuple(G4int id, G4double x0, G4double x1, G4double x2, G4double x3, G4double x4, G4double x5, G4double x6, G4double x7, G4double x8, G4double x9, G4double x10, G4double x11, G4double x12, G4double x13, G4double x14)
{
	if(TNtuple *ntout = (TNtuple*)NtList->At(id)){
		ntout->Fill( x0,  x1,  x2,  x3,  x4,  x5,  x6,  x7,  x8,  x9,  x10,  x11,  x12,  x13,  x14);
	}

	else{
   	 	G4ExceptionDescription description;
     		 description << " "
                		  << "Ntuple id is wrong."
          		        << "Cannot fill the Ntuple.";
          	    G4Exception("BeamAnalysisManager::BeamAnalysisManager()",
                		  "Analysis_W001", JustWarning, description);
          }
}

void BeamAnalysisManager::FillNtuple(G4int id, const G4double *x)
{
	if(TNtuple *ntout = (TNtuple*)NtList->At(id)){
		ntout->Fill(*x);
	}

	else{
   	 	G4ExceptionDescription description;
     		 description << " "
                		  << "Ntuple id is wrong."
          		        << "Cannot fill the Ntuple.";
          	    G4Exception("BeamAnalysisManager::BeamAnalysisManager()",
                		  "Analysis_W001", JustWarning, description);
        }
}

void BeamAnalysisManager::Write()
{
	TDirectory *h1dir;// = new TDirectory("h1dir","1d histogram directory");
	h1dir=fFile->mkdir("h1dir");
	for(G4int i=0;i<H1List->GetEntries();i++){
		h1dir->Add(H1List->At(i));
	}

	TDirectory *h2dir;// = new TDirectory("h2dir","2d histogram directory");
	h2dir=fFile->mkdir("h2dir");
	for(G4int i=0;i<H2List->GetEntries();i++){
		h2dir->Add(H2List->At(i));
	}

	TDirectory *ndir;// = new TDirectory("ndir","ntuple histogram directory");
	ndir=fFile->mkdir("ndir");
	for(G4int i=0;i<NtList->GetEntries();i++){
		ndir->Add(NtList->At(i));
	}

	h1dir->Write();
	h2dir->Write();
	ndir->Write();
}

void BeamAnalysisManager::CloseFile()
{
	fFile->Close();
}
