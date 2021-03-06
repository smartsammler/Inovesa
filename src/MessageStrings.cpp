/******************************************************************************
 * Inovesa - Inovesa Numerical Optimized Vlesov-Equation Solver Application   *
 * Copyright (c) 2014-2017: Patrik Schönfeldt                                 *
 *                                                                            *
 * This file is part of Inovesa.                                              *
 * Inovesa is free software: you can redistribute it and/or modify            *
 * it under the terms of the GNU General Public License as published by       *
 * the Free Software Foundation, either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * Inovesa is distributed in the hope that it will be useful,                 *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with Inovesa.  If not, see <http://www.gnu.org/licenses/>.           *
 ******************************************************************************/

#include "MessageStrings.hpp"

const std::string vfps::copyright_notice() noexcept {
    std::string rv (
        "Inovesa Numerical Optimized Vlasov-Equation Solver Application\n"
        "\n");
    if (
            #if FXP_FRACPART < 31
            std::is_same<vfps::meshdata_t,fixp32>::value ||
            #endif
            std::is_same<vfps::meshdata_t,fixp64>::value)
    {
        rv += "Copyright (c) 2007-2009 Peter Schregle (FPML)\n";
    }
    rv+="Copyright (c) 2012-2017 Patrik Schönfeldt\n"
        "Copyright (c) 2014-2017 Karlsruhe Institute of Technology\n"
        "Copyright (c) 2017 Patrick Schreiber\n"
        "Copyright (c) 1997-2016 John C. Bowman,\n"
        "\tUniversity of Alberta (Array class)\n"
        "\n"
        "Inovesa is free software: you can redistribute it and/or modify\n"
        "it under the terms of the GNU General Public License as published by\n"
        "the Free Software Foundation, either version 3 of the License, or\n"
        "(at your option) any later version.\n"
        "\n"
        "Inovesa is distributed in the hope that it will be useful,\n"
        "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
        "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the\n"
        "GNU General Public License for more details.\n"
        "\n"
        "You should have received a copy of the GNU General Public License"
        "along with Inovesa. If not, see <http://www.gnu.org/licenses/>.";
    return rv;
}

const std::string vfps::inovesa_version() {
    std::stringstream sstream;
    sstream << 'v' << INOVESA_VERSION_RELEASE << '.'
            << INOVESA_VERSION_MINOR;
    std::string version(sstream.str());
    if ( INOVESA_VERSION_FIX >= 0 ) {
        sstream << '.' << INOVESA_VERSION_FIX;
    } else if ( INOVESA_VERSION_FIX == -1 ) {
        sstream << " alpha";
    } else if ( INOVESA_VERSION_FIX == -2 ) {
        sstream << " beta";
    } else {
        sstream << " RC" << std::abs(INOVESA_VERSION_FIX)-2;
    }
    if (std::string(GIT_BRANCH) != version) {
        sstream << ", Branch: "<< GIT_BRANCH;
    }
    if (std::string(GIT_BRANCH) != version
            && (INOVESA_VERSION_FIX == -1 || INOVESA_VERSION_FIX == -2)) {
        sstream << ", Commit: "<< GIT_COMMIT;
    }
    #ifdef DEBUG
    sstream << " (Debug Build)";
    #endif
    return sstream.str();
}



const std::string vfps::status_string(std::shared_ptr<PhaseSpace> ps,
                                      float roatation,
                                      float total_rotations)
{
    std::stringstream status;
    status.precision(5);
    status << std::setw(6) << roatation << '/' << total_rotations;
    status << "\t1-Q/Q_0=" << 1.0 - ps->getIntegral()
           << "\ts_p=" << ps->getEnergySpread();

    return status.str();
}

#ifdef INOVESA_ENABLE_CLPROFILING
const std::string vfps::printProfilingInfo(const cl::vector<cl::Event> &events)
{
    double predevicewait = 0;
    double atdevicewait = 0;
    double exectime = 0;
    for (auto ev : events) {
        predevicewait += ev.getProfilingInfo<CL_PROFILING_COMMAND_SUBMIT>()
                       - ev.getProfilingInfo<CL_PROFILING_COMMAND_QUEUED>();
        atdevicewait += ev.getProfilingInfo<CL_PROFILING_COMMAND_START>()
                      - ev.getProfilingInfo<CL_PROFILING_COMMAND_QUEUED>();
        exectime += ev.getProfilingInfo<CL_PROFILING_COMMAND_END>()
                  - ev.getProfilingInfo<CL_PROFILING_COMMAND_QUEUED>();
    }
    double nEvents = events.size();
    predevicewait /= nEvents;
    atdevicewait /= nEvents;
    exectime /= nEvents;


    std::stringstream timings;
    timings << std::setiosflags(std::ios::fixed)
              << std::setprecision(6)
              << std::setw(12)
              << predevicewait/1e6
              << std::setw(12)
              << atdevicewait/1e6
              << std::setw(12)
              << exectime/1e6 << std::endl;

    return timings.str();
}
#endif

