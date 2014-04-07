#include "G4UserRunAction.hh"
#include "G4Run.hh"

class GEMRunAction : public G4UserRunAction
{
  public:
    GEMRunAction();
    virtual ~GEMRunAction();

  private:

  public:
    G4Run* GenerateRun();
    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);
};
