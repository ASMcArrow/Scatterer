#include "ScattererDetectorHit.hh"

#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4ThreadLocal G4Allocator<ScattererDetectorHit>* ScattererDetectorHitAllocator = 0;

ScattererDetectorHit::ScattererDetectorHit()
{
    EnergyDeposit = 0;
    Position.set(0,0,0);
    Area = 0;
}

ScattererDetectorHit::~ScattererDetectorHit()
{}

ScattererDetectorHit::ScattererDetectorHit(const ScattererDetectorHit &right)
    :G4VHit()
{
   Position = right.Position;
   EnergyDeposit = right.EnergyDeposit;
   Area = right.Area;
}

const ScattererDetectorHit&
ScattererDetectorHit::operator=(const ScattererDetectorHit &right)
{
    Position = right.Position;
    EnergyDeposit = right.EnergyDeposit;
    Area = right.Area;

    return *this;
}

void ScattererDetectorHit::Draw()
{
    G4Circle circle(Position);
    circle.SetScreenDiameter(10.0);
    circle.SetFillStyle (G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
}

int ScattererDetectorHit::operator==(const ScattererDetectorHit &right) const
{
    return((Position==right.Position)&&(EnergyDeposit==right.EnergyDeposit))&&(Area==right.Area);
}


