#ifndef BeamAnalysisManager_h
#define BeamAnalysisManager_h 1

#include "TFile.h"
#include "TList.h"
#include "TH1.h"
#include "TH2.h"
#include "TNtuple.h"
#include "globals.hh"

class BeamAnalysisManager
{
public:
	BeamAnalysisManager();
	virtual ~BeamAnalysisManager();

	static BeamAnalysisManager* Instance();
	virtual void OpenFile(G4String& fileName, const G4String& option="RECREATE");
	void CreateH1(const G4String &name, const G4String &title, G4int nbins, G4double xmin, G4double xmax, const G4String &unitName="none", const G4String &fcnName="none");
	void CreateH2(const G4String &name, const G4String &title, G4int nxbins, G4double xmin, G4double xmax, G4int nybins, G4double ymin, G4double ymax, const G4String &unitName="none", const G4String &fcnName="none");
	void FillH1(G4int id, G4double value, G4double weight=1.0);
	void FillH1(G4int id, G4String xname, G4double weight=1.0);
	void FillH2(G4int id, G4double xvalue, G4double yvalue, G4double weight=1.0);
	void FillH2(G4int id, G4String xname, G4double yvalue, G4double weight=1.0);
	void FillH2(G4int id, G4double xvalue, G4String yname, G4double weight=1.0);
	void CreateNtuple(const G4String &name, const G4String &title, const G4String &varlist);
	void FillNtuple(G4int id, G4double x0, G4double x1 = 0, G4double x2 = 0, G4double x3 = 0, G4double x4 = 0, G4double x5 = 0, G4double x6 = 0, G4double x7 = 0, G4double x8 = 0, G4double x9 = 0, G4double x10 = 0, G4double x11 = 0, G4double x12 = 0, G4double x13 = 0, G4double x14 = 0);
	void FillNtuple(G4int id, const G4double *x);
	void Write();
	void CloseFile();

private:
	static BeamAnalysisManager* fgInstance;
	TFile *fFile;
	TList *H1List;
	TList *H2List;
	TList *NtList;
};

#endif
