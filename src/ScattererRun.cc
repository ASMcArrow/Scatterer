#include "ScattererRun.hh"
#include "G4SDManager.hh"

ScattererRun::ScattererRun(const G4String detectorName, G4bool verbose) : G4Run()
{
    G4SDManager* SDman = G4SDManager::GetSDMpointer();
    G4VSensitiveDetector* detector = SDman->FindSensitiveDetector(detectorName);

    CollName = detector->GetCollectionName(0);
    CollectionID = SDman->GetCollectionID(CollName);
    Verbose = verbose;
}

ScattererRun::~ScattererRun()
{
    HitVector.clear();
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
            for (G4int j = 0; j < HC->entries(); j++)
            {
                ScattererDetectorHit *hit = (ScattererDetectorHit*)(HC->GetHit(j));
                if (Verbose)
                {
                    G4cout << "HitsVector Initial: " << "j = "<< j << " Energy deposition is " << hit->GetEdep()
                           << " Position is" << hit->GetPos()[0] << G4endl;
                }
                ScattererDetectorHit *copyHit = new ScattererDetectorHit(*hit);
                HitVector.push_back((ScattererDetectorHit*)(copyHit));
            }

            if (HC->entries() != 0)
            {
                if(Verbose)
                {
                    for (G4int l = 0; l < HitVector.size(); l++)
                    {
                        G4cout << "HitsVector Recorded: " << "l=" << l << " Energy deposition is " << HitVector[l]->GetEdep()
                               <<  " Position is " << HitVector[l]->GetPos()[0] << G4endl;
                    }
                }
            }
        }
    }
}

void ScattererRun::Merge(const G4Run * aRun)
{
    const ScattererRun *localRun = static_cast<const ScattererRun*>(aRun);
    for (G4int i = 0; i < localRun -> HitVector.size(); i++)
        HitVector.push_back(localRun -> HitVector[i]);

    G4Run::Merge(aRun);
}


