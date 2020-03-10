#ifndef FDTDCALC_H
#define FDTDCALC_H

#include <QObject>
#include "REDonFDTD/mesh.hpp"
#include "REDonFDTD/particle.hpp"
#include <memory>

class FDTDCalc : public QObject
{
    Q_OBJECT
public:
    explicit FDTDCalc(QObject *parent);

public slots:
     void runFDTDSim();

signals:
     void newPlotAvailable(int step);
     void FDTDSimCompleted();

private:
     void Plot(REDonFDTD::Mesh * g, std::string filename);
};

#endif // FDTDCALC_H
