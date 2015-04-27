#include "ScattererRun.hh"
#include "G4SDManager.hh"

ScattererRun::ScattererRun(const G4String detectorName, G4bool verbose) : G4Run()
{
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    G4VSensitiveDetector* detector = SDman->FindSensitiveDetector(detectorName);

    CollName = detector->GetCollectionName(0);
    CollectionID = SDman->GetCollectionID(CollName);
    Verbose = verbose;
    Cells = new G4double*[200];
    for (int i = 0; i < 200; i++)
    {
        Cells[i] = new G4double[200];
        for (int j = 0; j < 200; j++)
            Cells[i][j] = 0;
    }
}

ScattererRun::~ScattererRun() {
    for (int i = 0; i < 200; i++) {
        delete[] Cells[i];
    }
    delete[] Cells;
}

void ScattererRun::RecordEvent(const G4Event* aEvent)
{
    numberOfEvent++;

    G4HCofThisEvent* HCE = aEvent->GetHCofThisEvent();
    if(HCE!=NULL)
    {
        ScattererDetectorHitsCollection* HC = (ScattererDetectorHitsCollection*)(HCE -> GetHC(CollectionID));
        if(HC!=NULL)
        {
            //ScattererDetectorHit *hit = 0;
            for (G4int i = 0; i < HC->entries(); i++)
            {
                ScattererDetectorHit *hit = (ScattererDetectorHit*)(HC->GetHit(i));
                if (Verbose)
                {
                    G4cout << "HitsVector Initial: " << "i = "<< i << " Energy deposition is " << hit->GetEdep()
                           << " Position is" << hit->GetPos()[0] << G4endl;
                }
                G4int j = hit->GetPos()[0];
                G4int k = hit->GetPos()[1];

                Cells[j][k] += hit->GetEdep()/hit->GetArea();
            }
        }
    }
}

void ScattererRun::Merge(const G4Run * aRun)
{
    const ScattererRun *localRun = static_cast<const ScattererRun*>(aRun);
    for (int i = 0; i < 200; i++)
    {
        for (int j = 0; j < 200; j++)
            Cells[i][j] += localRun->Cells[i][j];
    }

    G4Run::Merge(aRun);
}


