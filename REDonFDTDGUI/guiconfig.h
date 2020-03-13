#ifndef GUICONFIG_H
#define GUICONFIG_H

#include "REDonFDTD/config.hpp"
#include "REDonFDTD/source.hpp"
namespace config {

    enum Component: int { Ex=0, Ey=1, Ez=2, Hx=3, Hy=4, Hz=5, EMag=6, HMag=7, E=EMag, H=HMag};
    enum Plane: int {XY=0, XZ=1, YZ=2 };
    enum PlotType: int { HeatMap=0 };

    class guiConfig : public REDonFDTD::config
    {
    public:
        guiConfig() = default;
        ~guiConfig() = default;

        REDonFDTD::source * getSource(REDonFDTD::Mesh *g);

        std::string getComponent();
        std::string getPlotType();
        std::string getPlane();

        REDonFDTD::sourceType source = REDonFDTD::src_Particle;
        Component component = Ex;
        Plane plane = XY;
        PlotType plot = HeatMap;
        bool interpolate = true;
    };


}
#endif // GUICONFIG_H
