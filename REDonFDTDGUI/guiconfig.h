#ifndef GUICONFIG_H
#define GUICONFIG_H

#include "REDonFDTD/config.hpp"

    namespace config {

    enum SourceType: int { Particle=0, ricker=1 };
    enum Component: int { Ex=0, Ey=1, Ez=2, Hx=3, Hy=4, Hz=5, EMag=6, HMag=7, E=EMag, H=HMag};
    enum Plane: int {XY=0, XZ=1, YZ=2 };
    enum PlotType: int { HeatMap=0 };

    struct guiConfig : public REDonFDTD::config
    {
        SourceType source = Particle;
        Component component = Ex;
        Plane plane = XY;
        PlotType plot = HeatMap;
    };

    }
#endif // GUICONFIG_H
