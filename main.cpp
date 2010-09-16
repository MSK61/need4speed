/************************************************************
 *
 * Copyright 2010 Mohammed El-Afifi
 *
 * need4speed is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * need4speed is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with need4speed.  If not, see <http://www.gnu.org/licenses/>.
 *
 * file:         main.cpp
 *
 * function:     main (complete program listing in this file)
 *
 * description:  chooses the exact parts that would provide the maximum
 *               acceleration gain
 *
 * author:       Mohammed Safwat (MS)
 *
 * environment:  KDevelope 3.5.4, Fedora release 10 (Cambridge)
 *
 * notes:        This is a private program.
 *
 ************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <fstream>
#include <numeric>
#include <stdlib.h>
#include <vector>

namespace
{
    /**
     * @brief Performance part characteristics
     */
    struct PartInfo
    {
        /**
         * @brief Force provided by the part
         */
        unsigned long force;
        /**
         * @brief Mass of the part
         */
        unsigned short int mass;
    };
}

int main(int argc, char *argv[])
{
    using std::accumulate;
    using std::logical_or;
    using std::vector;
    float curA;
    unsigned short int curPart = 0;
    // problem parameters
    unsigned long f;// intrinsic force
    unsigned short int m;// intrinisc mass
    unsigned short int n;// number of parts
    vector< PartInfo > parts;
    // I/O files
    static const char inFileName[] = "boost.in";
    std::ifstream inFile(inFileName);
    static const char outFileName[] = "boost.out";
    std::ofstream outFile(outFileName);
    // maximum acceleration conditions
    float maxA;
    vector< bool > maxAParts;
    // accumulated characteristics for the car and parts
    unsigned long totalForce;
    unsigned short int totalMass;
    // part utilization
    vector< bool > used;
    vector< bool >::const_iterator firstUsed;
    vector< bool >::const_iterator lastUsed;

    /// Read the problem parameters.
    inFile >> f >> m >> n;
    parts.resize(n);

    for (; curPart < n; curPart++)
        inFile >> parts[curPart].force >> parts[curPart].mass;

    inFile.close();
    used.resize(n, false);
    firstUsed = used.begin();
    lastUsed = used.end();
    maxA = float(f) / m;
    maxAParts = used;
    used[0] = true;

    /// Calculate the acceleration for different part combinations.
    do
    {

        /// Calculate the acceleration for the current part combination.
        totalForce = f;
        totalMass = m;

        for (curPart = 0; curPart < n; curPart++) if (used[curPart])
            {

                totalForce += parts[curPart].force;
                totalMass += parts[curPart].mass;

            }

        /// Update the maximum acceleration if necessary.
        curA = float(totalForce) / totalMass;

        if (curA > maxA)
        {

            maxA = curA;
            maxAParts = used;

        }

        /// Prepare the next part combination.
        for (curPart = 0; curPart < n && used[curPart]; curPart++)
            used[curPart] = false;

        if (curPart < n) used[curPart] = true;

    }
    while (accumulate(firstUsed, lastUsed, false, logical_or< bool >()));

    /// Save the result.
    if (accumulate(maxAParts.begin(), maxAParts.end(), false,
                   logical_or< bool >()))
        for (curPart = 0; curPart < n; curPart++)
        {

            if (maxAParts[curPart]) outFile << curPart + 1 << std::endl;

        }
    else outFile << "NONE";

    outFile.close();
    return EXIT_SUCCESS;
}
