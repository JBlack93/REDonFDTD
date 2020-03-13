#ifndef FDTDCALC_H
#define FDTDCALC_H

#include <QObject>
#include <memory>

#include "REDonFDTD/mesh.hpp"
#include "REDonFDTD/particle.hpp"

#include "guiconfig.h"


class FDTDCalc : public QObject
{
    Q_OBJECT
public:
    explicit FDTDCalc(QObject *parent);

    config::guiConfig calcConfig;
    void output(REDonFDTD::Mesh * g);

public slots:
     void runFDTDSim();
     void updateConfig(config::guiConfig tempConfig);
     void cancel();


signals:
     void newPlotAvailable(int step);
     void FDTDSimCompleted();
     void FDTDSimCancelled();
     void signalSlider(int steps);

private:
     void Plot(REDonFDTD::Mesh * g, config::guiConfig calcConfig, std::string filename);
     bool cancelled = false;
};

#endif // FDTDCALC_H
