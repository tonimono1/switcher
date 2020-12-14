#ifndef ASTROCALCULATOR_H
#define ASTROCALCULATOR_H


class AstroCalculator
{
public:
    AstroCalculator() = delete;
    static double calculateSunrise(double latitude, double longitude, int dayOfYear, double timeshift);
    static double calculateSunset(double latitude, double longitude, int dayOfYear, double timeshift);
private:
    static double calculateDeclination(int dayOfYear);
    static double calculateTimeApproximation(int dayOfYear);
    static double calculateTimeDifference(double latitude, double declination, double horrizonHeight);
    static double calculateTimeShift(double longitude, double timeshift);
    static double calculateTimeEquation(int dayOfYear);
};

#endif // ASTROCALCULATOR_H
