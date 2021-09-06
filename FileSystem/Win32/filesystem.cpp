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

#include <cstddef>
#include <cwchar>

#include "../filesystem.h"

#include <windows.h>

using std::string;
using std::wstring;
using std::vector;
using std::size_t;

namespace {

  wstring widen(string str) {
    size_t wchar_count = str.size() + 1;
    vector<wchar_t> buf(wchar_count);
    return wstring{ buf.data(), (size_t)MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, buf.data(), (int)wchar_count) };
  }

  string narrow(wstring wstr) {
    int nbytes = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.length(), NULL, 0, NULL, NULL);
    vector<char> buf(nbytes);
    return string{ buf.data(), (size_t)WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), (int)wstr.length(), buf.data(), nbytes, NULL, NULL) };
  }

} // anonymous namespace

namespace datetime {

  int file_get_date_accessed_modified(const char *fname, bool modified, int type) {
    int result = -1; // returns -1 on failure
    std::wstring wfname = widen(fname);
    struct _stat info = { 0 }; result = _wstat(wfname.c_str(), &info);
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
    while (dname.back() == '\\' || dname.back() == '/') dname.pop_back();
    return dname;
  }

  string filename_add_slash(string dname, bool canonical) {
    dname = filename_remove_slash(dname, canonical);
    if (dname.back() != '\\') dname += "\\";
    return dname;
  }

} // namespace strings

namespace filesystem {

  string fs_get_program_pathname() {
    string path;
    wchar_t buffer[MAX_PATH];
    if (GetModuleFileNameW(NULL, buffer, MAX_PATH) != 0) {
      path = narrow(buffer);
    }
    return path;
  }

  string fs_environment_get_variable(string name) {
    string value;
    wchar_t buffer[32767];
    wstring u8name = widen(name);
    if (GetEnvironmentVariableW(u8name.c_str(), buffer, 32767) != 0) {
      value = narrow(buffer);
    }
    return value;
  }

  bool fs_environment_set_variable(string name, string value) {
    wstring u8name = widen(name);
    wstring u8value = widen(value);
    if (value == "") return (SetEnvironmentVariableW(u8name.c_str(), NULL) != 0);
    return (SetEnvironmentVariableW(u8name.c_str(), u8value.c_str()) != 0);
  }

} // namespace filesystem
