#include <memory>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <filesystem>

#include "REDonFDTD/mesh.hpp"
#include "REDonFDTD/particle.hpp"
#include "REDonFDTD/EMfunctions.hpp"
#include "REDonFDTD/output.hpp"

#include "gnuplot/gnuplot.hpp"

#include "fdtdcalc.h"
#include "guiconfig.h"

FDTDCalc::FDTDCalc(QObject *parent) : QObject(parent)
{
    std::filesystem::create_directory("output");
}

void FDTDCalc::runFDTDSim(){
    std::unique_ptr<REDonFDTD::Mesh> g = std::make_unique<REDonFDTD::Mesh>(calcConfig);
    REDonFDTD::source * runSource = calcConfig.getSource(g.get());
    runSource->InitialiseMesh(g.get());
    emit signalSlider(g->steps);
    /* do time stepping */
    for (g->time = 0; g->time < g->maxTime;){
      runSource->sourceFunction(g.get(), calcConfig.analyticRange);   // produce effects of source on local fields.
      g->updateH();                         // update magnetic fields in mesh
      halfTimeStep(runSource, g.get());
      g->updateE();                         // update electric fields in mesh
      halfTimeStep(runSource, g.get());

      const int step = static_cast<int>(g->time/g->timeStep);
      std::string fileSt = calcConfig.getComponent()+calcConfig.getPlane()+std::to_string(step);
      output(g.get());
      this->Plot(g.get(), calcConfig, fileSt);
      emit newPlotAvailable(step);
      if (cancelled) {
        cancelled = false;
        emit FDTDSimCancelled();
        return;
      }
   }                               // end of time-stepping
   emit FDTDSimCompleted();
}

void FDTDCalc::cancel(){
    cancelled = true;
}

void FDTDCalc::updateConfig(config::guiConfig tempConfig){
    calcConfig = tempConfig;
}

void FDTDCalc::output(REDonFDTD::Mesh *g){
    switch (calcConfig.component){
    case 0:
        REDonFDTD::writeExXY(g,1);
        break;
    case 1:
        REDonFDTD::writeEyXY(g,1);
        break;
    case 2:
        REDonFDTD::writeEzXY(g,1);
        break;
    case 3:
        REDonFDTD::writeHxXY(g,1);
        break;
    case 4:
        REDonFDTD::writeHyXY(g,1);
        break;
    case 5:
        REDonFDTD::writeHzXY(g,1);
        break;
    case 6:
        REDonFDTD::writeEMagXY(g,1);
        break;
    case 7:
        REDonFDTD::writeHMagXY(g,1);
        break;
    }
}


void FDTDCalc::Plot(REDonFDTD::Mesh * g, config::guiConfig calcConfig, std::string filename){
    gnuplot::GnuplotPipe gp;
    gp.sendLine("set terminal pngcairo");
    gp.sendLine("set view map");
    std::string plotType = "set dgrid3d "+std::to_string(g->sizeX)+","+
            std::to_string(g->sizeY)+","+std::to_string(g->dS*g->sizeX);
    gp.sendLine(plotType);
    //gp.sendLine("set cbrange [-5e-11:5e-11]");
    gp.sendLine("set cblabel ''");
    std::string output = "set output 'output/"+filename+".png'";
    gp.sendLine(output);
    std::string plot = "splot 'output/"+filename+".txt' using  1:2:3 with pm3";
    if (calcConfig.interpolate)  gp.sendLine("set pm3d interpolate 15,15");
    gp.sendLine("set autoscale xfix; set autoscale yfix");
    gp.sendLine(plot);
    gp.sendLine("exit gnuplot");
}
