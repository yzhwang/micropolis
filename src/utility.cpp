/******************************************************************************\
 * This file is part of Micropolis.                                           *
 *                                                                            *
 * Micropolis is free software: you can redistribute it and/or modify         *
 * it under the terms of the GNU General Public License as published by       *
 * the Free Software Foundation, either version 3 of the License, or          *
 * (at your option) any later version.                                        *
 *                                                                            *
 * Micropolis is distributed in the hope that it will be useful,              *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of             *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              *
 * GNU General Public License for more details.                               *
 *                                                                            *
 * You should have received a copy of the GNU General Public License          *
 * along with Micropolis.  If not, see <http://www.gnu.org/licenses/>.        *
\******************************************************************************/


#include "utility.h"

#include <fstream>

#include <time.h>

uint64_t nanotime()
{
#ifdef linux
	struct timespec tp;
	clock_gettime(CLOCK_MONOTONIC, &tp);
	return (unsigned long long) tp.tv_sec * BILLION + (unsigned long long) tp.tv_nsec;
#else
	LARGE_INTEGER current;
	LARGE_INTEGER m_ticksPerSec;
	QueryPerformanceFrequency(&m_ticksPerSec);
	QueryPerformanceCounter(&current);
	return (unsigned long long)((double)current.QuadPart / m_ticksPerSec.QuadPart * BILLION);
#endif
}

string with_commas(long n)
{
    std::stringstream ss;

    int i = 0;
    do {
        
        int d = n % 10;
        n = n / 10;

        ss << d;

        ++i;
        if (n > 0 && i == 3) {
            i = 0;
            ss << ',';
        }
    } while (n > 0);

    return reverse(ss.str());
}

string reverse (const string& s)
{
    return string(s.rbegin(), s.rend());
}

bool file_exists(const string &filename)
{
    std::ifstream ifile(filename.c_str());
    return ifile.good();
}

string read_file(const string &filename)
{
    std::ifstream ifile(filename.c_str());

    return string(std::istreambuf_iterator<char>(ifile),
        std::istreambuf_iterator<char>());
}


void get_errors(void)
{
    static int call_count = 0;

    // We don't need get_errors if we use ARB_debug_output
    if (true) {
        GLenum error = glGetError();

        if (error != GL_NO_ERROR) {
            if (call_count == 16) return;

            switch (error) {
            case GL_INVALID_ENUM:
                cerr << "GL: enum argument out of range." << endl;
                break;
            case GL_INVALID_VALUE:
                cerr << "GL: Numeric argument out of range." << endl;
                break;
            case GL_INVALID_OPERATION:
                cerr << "GL: Operation illegal in current state." << endl;
                break;
            case GL_INVALID_FRAMEBUFFER_OPERATION:
                cerr << "GL: Framebuffer object is not complete." << endl;
                break;
            case GL_OUT_OF_MEMORY:
                cerr << "GL: Not enough memory left to execute command." << endl;
                break;
            default:
                cerr << "GL: Unknown error." << endl;
            }

            ++call_count;
        }
    }
}
