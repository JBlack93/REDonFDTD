#include "fdtdcalc.h"
#include <memory>
#include <QPixmap>
#include <QGraphicsPixmapItem>

#include "REDonFDTD/mesh.hpp"
#include "REDonFDTD/particle.hpp"
#include "REDonFDTD/EMfunctions.hpp"
#include "REDonFDTD/output.hpp"
#include "gnuplot/gnuplot.hpp"


FDTDCalc::FDTDCalc(QObject *parent) : QObject(parent)
{
    // Configuration of simulation to go here?
}

void FDTDCalc::runFDTDSim(){
    std::unique_ptr<REDonFDTD::Mesh> g = std::make_unique<REDonFDTD::Mesh>();
    std::unique_ptr<REDonFDTD::Particle> p = std::make_unique<REDonFDTD::Particle>(g.get());

    /* do time stepping */
    for (g->time = 0; g->time < g->maxTime;){
      g->updateH();                 // update magnetic fields in mesh
      halfTimeStep(p.get(), g.get());
      g->updateE();                 // update electric fields in mesh
      halfTimeStep(p.get(), g.get());
      p->sourceFunction(g.get());   // produce effects of source on local fields.

      g->updateABC();               // apply ABCs


      const int step = static_cast<int>(g->time/g->timeStep);
      std::string fileSt = "Ex";
      fileSt.append(std::to_string(step));
      fileSt.append(".png");
      this->Plot(g.get(), fileSt);
      emit newPlotAvailable(step);
   }                               // end of time-stepping
    emit FDTDSimCompleted();
}

void FDTDCalc::Plot(REDonFDTD::Mesh * g, std::string filename){
    REDonFDTD::writeEx(g,1);
    gnuplot::GnuplotPipe gp;
    gp.sendLine("set terminal pngcairo");
    gp.sendLine("set view map");
    gp.sendLine("set dgrid3d");
    gp.sendLine("set cbrange [0:1e-7]");
    gp.sendLine("set cblabel 'Ex'");
    gp.sendLine("set pm3d interpolate 15,15");
    std::string output = "set output '/home/black/projects/REDonFDTD/REDonFDTDGUI/";
    output.append(filename);
    gp.sendLine(output);
    gp.sendLine("splot 'Ex50.txt' using  1:2:3 with pm3");
    gp.sendLine("exit gnuplot");
}
