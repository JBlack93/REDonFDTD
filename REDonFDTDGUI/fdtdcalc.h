#ifndef FDTDCALC_H
#define FDTDCALC_H

#include <QObject>
#include "REDonFDTD/mesh.hpp"
#include "REDonFDTD/particle.hpp"
#include "REDonFDTD/config.hpp"

#include <memory>

class FDTDCalc : public QObject
{
    Q_OBJECT
public:
    explicit FDTDCalc(QObject *parent);

    REDonFDTD::config meshConfig;

public slots:
     void runFDTDSim();
     void updateConfig(REDonFDTD::config tempConfig);

signals:
     void newPlotAvailable(int step);
     void FDTDSimCompleted();
     void signalSlider(int steps);

private:
     void Plot(REDonFDTD::Mesh * g, std::string filename, int step);
};

#endif // FDTDCALC_H
