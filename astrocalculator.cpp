#include "astrocalculator.h"
#include "math.h"
/*!
Die Bewegung der Erde um die Sonne ist genau betrachtet eine komplizierte
Angelegenheit. Selbst wenn die Erde der einzige Planet wäre, hätte es mit einer
nur numerisch (d.h. nur durch spezielle Näherungsverfahren) lösbaren Gleichung
zu tun. Die Erdbahn erfährt zudem noch kleine Störungen durch die anderen
Planeten. Dies alles zu berücksichtigen, würde die eingangs gestellte Forderung
nach Einfachheit verletzen.

Wir müssen deshalb einen anderen Weg gehen. Dieser besteht darin, dass wir durch
die genauen Werte der Zeitgleichung eine Näherungskurve legen. Wenn man sich die
in Fig. 1 als Funktion der Tagnummer dargestellte Zeitgleichung ansieht, so kann
man sich zwei sich überlagernde harmonische Schwingungen vorstellen. In der Tat
lässt sich damit mit der folgenden, aus zwei harmonischen Schwingungen
zusammengesetzten Formel die Differenz zwischen Wahrer Ortszeit (WOZ, Sonnenuhr)
und mittlerer Ortszeit (MOZ) auf besser als eine Minute genau annähern:

*/
double AstroCalculator::calculateTimeApproximation(int dayOfYear)
{
    return  -0.171*sin(0.0337 * dayOfYear + 0.465) - 0.1299*sin(0.01787 * dayOfYear - 0.168);

}

/* Die Höhe über dem Horizont eines Gestirns beim Passieren der Südrichtung
 * (Meridian) bestimmt, wie lange es über dem Horizont bleibt. Mit der
 * Zeitgleichung kennen wir den Zeitpunkt, zu dem die Sonne im Süden steht
 * (Mittag). Wenn wir noch wissen, wie lange die Sonne über dem Horizont bleibt,
 * können wir die Aufgangs- und Untergangszeit berechnen. Dazu brauchen wir die
 * Deklination der Sonne. Vereinfacht gesprochen ist die Deklination eines
 * Gestirns der Breitengrad über dem das Gestirn im Zenit steht (dies stimmt
 * nicht exakt, weil die Erde keine Kugel ist). Die Deklination der Sonne
 * stellen wir als einfache harmonische Schwingung dar. Im Gegensatz zur
 * Zeitgleichung nehmen wir hier also die Näherung einer kreisförmigen Erdbahn
 * an:
 */
double AstroCalculator::calculateDeclination(int dayOfYear)
{
  return 0.4095 * sin(0.016906 * (dayOfYear - 80.086));
}
/*!
 * \brief AstroCalculator::calculateTimeDifference
 * Das Licht der Sonne wird in der Atmosphäre gebeugt. Es läuft besonders in
 * Horizontnähe auf einer leicht zum Boden hin gekrümmten Bahn. Deshalb kann man
 * die Sonne auch noch sehen, wenn sie rein geometrisch schon untergegangen ist.
 * Deshalb wird der Untergang und auch der Aufgang der Sonne für eine
 * geometrische Horizonthöhe h von -50 Bogenminuten berechnet (-50 Bogenminuten
 * sind -50/60°=-0.833° und -50/60/57.29578 rad=-0.0145 rad). Von bürgerlicher
 * Dämmerung spricht man, wenn h= -6° ist, nautische Dämmerung entspricht h =
 * -12° und schliesslich astronomische Dämmerung entspricht h = -18°.
 * \return
 */
double AstroCalculator::calculateTimeDifference(double latitude, double declination, double horrizonHeight)
{
    // in rad
    double b = M_PI * latitude / 180.0;
    double h = M_PI * horrizonHeight / 60.0 / 180.0;

    return  12 * acos((sin(h) - sin(b)*sin(declination)) / (cos(b)*cos(declination)))/M_PI;
}

double AstroCalculator::calculateTimeEquation(int dayOfYear)
{
    return -0.171 * sin(0.0337 * dayOfYear + 0.465) - 0.1299 * sin(0.01787 * dayOfYear - 0.168);
}

double AstroCalculator::calculateTimeShift(double longitude, double timeshift)
{
    return  longitude / 15.0 + timeshift;
}

double AstroCalculator::calculateSunrise(double latitude, double longitude, int dayOfYear, double timeshift)
{
    double declination = calculateDeclination(dayOfYear);
    double timeDifference = calculateTimeDifference(latitude, declination, -50.0);
    double realLocalTime = 12.0 - timeDifference;
    double timeEquation = calculateTimeEquation(dayOfYear);
    double averageLocalTime = realLocalTime - timeEquation;
    double timeDiff = calculateTimeShift(longitude, timeshift);
    return averageLocalTime - timeDiff;
}

double AstroCalculator::calculateSunset(double latitude, double longitude, int dayOfYear, double timeshift)
{
    double declination = calculateDeclination(dayOfYear);
    double timeDifference = calculateTimeDifference(latitude, declination, -6.0);
    double realLocalTime = 12.0 + timeDifference;
    double timeEquation = calculateTimeEquation(dayOfYear);
    double averageLocalTime = realLocalTime - timeEquation;
    double timeDiff = calculateTimeShift(longitude, timeshift);
    return averageLocalTime - timeDiff;
}
