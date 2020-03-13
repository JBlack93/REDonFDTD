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

    config::guiConfig meshConfig;

public slots:
     void runFDTDSim();
     void updateConfig(config::guiConfig tempConfig);

signals:
     void newPlotAvailable(int step);
     void FDTDSimCompleted();
     void signalSlider(int steps);

private:
     void Plot(REDonFDTD::Mesh * g, std::string filename, int step);
};

#endif // FDTDCALC_H
