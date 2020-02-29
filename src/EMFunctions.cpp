/* This Header File contains all the functions which call for global values
 * which therefore includes all the Electromagnetic effects
 */

#include <cmath>
#include "REDonFDTD/prototypes.hpp"
#include "REDonFDTD/macroSetUp.hpp"

void newPositionTaylor(Particle *p, Mesh *g)
{
    xFutPos = xPosition + xVelocity*TimeStep + pow(TimeStep,2)*xAcceleration/2;
    yFutPos = yPosition + yVelocity*TimeStep + pow(TimeStep,2)*yAcceleration/2;
    zFutPos = zPosition + zVelocity*TimeStep + pow(TimeStep,2)*zAcceleration/2;
}

void newVelocityTaylor(Particle *p, Mesh *g)
{

    xFutVel = xVelocity + TimeStep*xAcceleration;
    yFutVel = yVelocity + TimeStep*yAcceleration;
    zFutVel = zVelocity + TimeStep*zAcceleration;
    FutGamma = 1/(sqrt(1-pow(sqrt(pow(xFutVel,2)+pow(yFutVel,2)+pow(zFutVel,2))/c,2)));

}

void findAcceleration(Particle *p, std::vector<double> force)
{
    xFutAcc = force[0]/(Mass*FutGamma);
    yFutAcc = force[1]/(Mass*FutGamma);
    zFutAcc = force[2]/(Mass*FutGamma);
}

double findGamma(std::vector<double> velocity)
{
    double velMag = magnitude(velocity);
    double gamma = 1/(sqrt(1-pow(velMag/c,2)));
    return gamma;
}

/* ELECTROMAGNETIC EFFECTS */

std::vector<double> lorentzForce(Particle *p, Mesh *g)
{
    std::vector<double> velocity(3);
    std::vector<double> bField(3);
    velocity[0] = xFutVel;
    velocity[1] = yFutVel;
    velocity[2] = zFutVel;
    bField[0] = Hx((int) xFutPos, (int) yFutPos, (int) zFutPos)+5;
    bField[1] = Hy((int) xFutPos, (int) yFutPos, (int) zFutPos);
    bField[2] = Hz((int) xFutPos, (int) yFutPos, (int) zFutPos);

    std::vector<double> crossProduct = cross(velocity, bField);
    std::for_each(crossProduct.begin(), crossProduct.end(), [& p](double & a){a*=(Charge)*(Mu_0);});
    return crossProduct;
}

double powerRadiated(Particle *p)
{
    std::vector<double> velocity(3);
    std::vector<double> acceleration(3);

    velocity[0]     = xFutVel;    velocity[1]     = yFutVel;      velocity[2]     = zFutVel;
    acceleration[0] = xFutAcc;    acceleration[1] = yFutAcc;      acceleration[2] = zFutAcc;

    double coefficient = (Mu_0*pow(Charge,2)*pow(FutGamma,6))/(6*M_PI*c);
    std::vector<double> crossProd(3);
    crossProd = cross(velocity,acceleration);
    double crossProdMag = magnitude(crossProd);
    double magTerm = pow(crossProdMag/c,2);
    double accSquared = dot(acceleration, acceleration);
    double powerRad = coefficient*(accSquared - magTerm);
    return powerRad;
}

void velocityAfterRad(Particle *p, double powerRad)
{
    std::vector<double> velocity(3);
    std::vector<double> acceleration(3);

    velocity[0]     = xFutVel;     velocity[1]     = yFutVel;       velocity[2]     = zFutVel;
    acceleration[0] = xFutAcc;     acceleration[1] = yFutAcc;       acceleration[2] = zFutAcc;


    double velMag = magnitude(velocity);
    double iniEnergy = Mass*pow(c,2)*FutGamma;
    double finalEnergy = iniEnergy - powerRad;//*TimeStep;
    double finalVelMag = c*(sqrt(1-pow(((Mass*pow(c,2))/finalEnergy),2)));

    std::for_each(velocity.begin(), velocity.end(), [&velMag, &finalVelMag](double & vel){vel*=finalVelMag/velMag;});

    xFutVel = velocity[0];
    yFutVel = velocity[1];
    zFutVel = velocity[2];
    FutGamma = 1/(sqrt(1-pow(sqrt(pow(xFutVel,2)+pow(yFutVel,2)+pow(zFutVel,2))/c,2)));
    }


void timeAdvanceValues(Particle *p)
{
    xPrevPos  = xPosition;      yPrevPos  = yPosition;     zPrevPos  = zPosition;
    xPosition = xFutPos;        yPosition = yFutPos;       zPosition = zFutPos;

    xPrevVel  = xVelocity;      yPrevVel  = yVelocity;     zPrevVel  = zVelocity;
    xVelocity = xFutVel;        yVelocity = yFutVel;       zVelocity = zFutVel;

    xPrevAcc      = xAcceleration;    yPrevAcc      = yAcceleration;     zPrevAcc      = zAcceleration;
    xAcceleration = xFutAcc;          yAcceleration = yFutAcc;           zAcceleration = zFutAcc;

    PrevGamma = Gamma;
    Gamma = FutGamma;
}

void halfTimeStep(Particle *p, Mesh *g)
{
    Time += TimeStep/2;
    newPositionTaylor(p, g);
    newVelocityTaylor(p, g);
    std::vector<double> force(3);
    force = lorentzForce(p, g);
    findAcceleration(p, force);
    double powerRad = powerRadiated(p);
    if (powerRad !=0)
    {
        velocityAfterRad(p, powerRad);
    }
    timeAdvanceValues(p);
}
