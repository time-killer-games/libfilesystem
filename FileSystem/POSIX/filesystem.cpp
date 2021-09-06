/*

 MIT License
 
 Copyright © 2020 Samuel Venable
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 
*/

#include <cstdlib>

#include "../filesystem.h"

#include <unistd.h>

using std::string;

namespace datetime {

  int file_get_date_accessed_modified(const char *fname, bool modified, int type) {
    int result = -1; // returns -1 on failure
    struct stat info = { 0 }; result = stat(fname, &info);
    time_t time = modified ? info.st_mtime : info.st_atime;
    if (result == -1) return result; // failure: stat errored
    struct tm *timeinfo = std::localtime(&time);
    if      (type == dt_year)   return timeinfo->tm_year + 1900;
    else if (type == dt_month)  return timeinfo->tm_mon  + 1;
    else if (type == dt_day)    return timeinfo->tm_mday;
    else if (type == dt_hour)   return timeinfo->tm_hour;
    else if (type == dt_minute) return timeinfo->tm_min;
    else if (type == dt_second) return timeinfo->tm_sec;
    else return result; // failure: enum value not found
  }

} // namespace datetime

namespace strings {

  string filename_remove_slash(string dname, bool canonical) {
    if (canonical) dname = filesystem::fs_filename_canonical(dname);
    while (dname.back() == '/') dname.pop_back();
    return dname;
  }

  string filename_add_slash(string dname, bool canonical) {
    if (canonical) dname = filesystem::fs_filename_canonical(dname);
    if (dname.back() != '/') dname += "/";
    return dname;
  }

} // namespace strings

namespace filesystem {

  string fs_environment_get_variable(string name) {
    char *value = getenv(name.c_str());
    return value ? value : "";
  }

  bool fs_environment_set_variable(string name, string value) {
    if (value == "") return (unsetenv(name.c_str()) == 0);
    return (setenv(name.c_str(), value.c_str(), 1) == 0);
  }

} // namespace filesystem
