#include "guiconfig.h"

std::string config::guiConfig::getComponent(){
    std::string comp;
    switch(component){
    case 0:
        comp = "Ex";
        break;
    case 1:
        comp = "Ey";
        break;
    case 2:
        comp = "Ez";
        break;
    case 3:
        comp = "Hx";
        break;
    case 4:
        comp = "Hy";
        break;
    case 5:
        comp = "Hz";
        break;
    case 6:
        comp = "EMag";
        break;
    case 7:
        comp = "HMag";
        break;
    }
    return comp;
}

REDonFDTD::source * config::guiConfig::getSource(REDonFDTD::Mesh *g){
    REDonFDTD::source * s;
    return s->Create(g, *this, this->source);
}

std::string config::guiConfig::getPlotType(){
    std::string plotType;
    switch(plot){
    case 0:
        plotType = "HeatMap";
        break;
     }
    return plotType;
}

std::string config::guiConfig::getPlane(){
    std::string plotPlane;
    switch(plane){
    case 0:
        plotPlane = "XY";
        break;
    case 1:
        plotPlane = "XZ";
        break;
    case 2:
        plotPlane = "YZ";
        break;
    }
    return plotPlane;
}
