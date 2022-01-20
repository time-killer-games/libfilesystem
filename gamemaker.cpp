/*

 MIT License
 
 Copyright © 2020-2021 Samuel Venable
 
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

#include <algorithm>
#include <random>

#include "filesystem.h"

#if defined(_WIN32)
#include <windows.h>
#endif

using std::string;
using std::vector;

#if defined(_WIN32)
#define EXPORTED_FUNCTION extern "C" __declspec(dllexport)
#else /* macOS, Linux, and BSD */
#define EXPORTED_FUNCTION extern "C" __attribute__((visibility("default")))
#endif

enum {
  DC_ATOZ,  // Alphabetical Order
  DC_ZTOA,  // Reverse Alphabetical Order
  DC_AOTON, // Date Accessed Ordered Old to New
  DC_ANTOO, // Date Accessed Ordered New to Old
  DC_MOTON, // Date Modified Ordered Old to New
  DC_MNTOO, // Date Modified Ordered New to Old
  DC_COTON, // Date Created Ordered Old to New
  DC_CNTOO, // Date Created Ordered New to Old
  DC_RAND   // Random Order
};

static vector<string> directory_contents;
static unsigned directory_contents_index = 0;
static unsigned directory_contents_order = DC_ATOZ;
#if defined(_WIN32) 
static std::wstring widen(string str) {
  size_t wchar_count = str.size() + 1; vector<wchar_t> buf(wchar_count);
  return std::wstring{ buf.data(), (size_t)MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, buf.data(), (int)wchar_count) };
}
#endif
static time_t file_datetime_helper(std::string fname, int timestamp) {
  int result = -1;
  #if defined(_WIN32)
  std::wstring wfname = widen(fname);
  struct _stat info = { 0 }; 
  result = _wstat(wfname.c_str(), &info);
  #else
  struct stat info = { 0 }; 
  result = stat(fname.c_str(), &info);
  #endif
  if (result == -1) return 0;
  time_t time = 0;
  if (timestamp == 0) time = info.st_atime;
  if (timestamp == 1) time = info.st_mtime;
  if (timestamp == 2) time = info.st_ctime;
  return time;
}

EXPORTED_FUNCTION char *directory_get_current_working() {
  static string result;
  result = ngs::fs::directory_get_current_working();
  return (char *)result.c_str();
}

EXPORTED_FUNCTION double directory_set_current_working(char *dname) {
  return ngs::fs::directory_set_current_working(dname);
}

EXPORTED_FUNCTION char *directory_get_temporary_path() {
  static string result;
  result = ngs::fs::directory_get_temporary_path();
  return (char *)result.c_str();
}

EXPORTED_FUNCTION char *executable_get_directory() {
  static string result;
  result = ngs::fs::executable_get_directory();
  return (char *)result.c_str();
}

EXPORTED_FUNCTION char *executable_get_filename() {
  static string result;
  result = ngs::fs::executable_get_filename();
  return (char *)result.c_str();
}

EXPORTED_FUNCTION char *executable_get_pathname() {
  static string result;
  result = ngs::fs::executable_get_pathname();
  return (char *)result.c_str();
}

EXPORTED_FUNCTION char *file_bin_pathname(double fd) {
  static string result;
  result = ngs::fs::file_bin_pathname((int)fd);
  return (char *)result.c_str();
}

EXPORTED_FUNCTION char *filename_absolute(char *fname) {
  static string result;
  result = ngs::fs::filename_absolute(fname);
  return (char *)result.c_str();
}

EXPORTED_FUNCTION char *filename_canonical(char *fname) {
  static string result;
  result = ngs::fs::filename_canonical(fname);
  return (char *)result.c_str();
}

EXPORTED_FUNCTION double file_exists(char *fname) {
  return ngs::fs::file_exists(fname);
}

EXPORTED_FUNCTION double file_delete(char *fname) {
  return ngs::fs::file_delete(fname);
}

EXPORTED_FUNCTION double file_rename(char *oldname, char *newname) {
  return ngs::fs::file_rename(oldname, newname);
}

EXPORTED_FUNCTION double file_copy(char *fname, char *newname) {
  return ngs::fs::file_copy(fname, newname);
}

EXPORTED_FUNCTION double file_size(char *fname) {
  return (double)ngs::fs::file_size(fname);
}

EXPORTED_FUNCTION double directory_exists(char *dname) {
  return ngs::fs::directory_exists(dname);
}

EXPORTED_FUNCTION double directory_create(char *dname) {
  return ngs::fs::directory_create(dname);
}

EXPORTED_FUNCTION double directory_destroy(char *dname) {
  return ngs::fs::directory_destroy(dname);
}

EXPORTED_FUNCTION double directory_rename(char *oldname, char *newname) {
  return ngs::fs::directory_rename(oldname, newname);
}

EXPORTED_FUNCTION double directory_copy(char *dname, char *newname) {
  return ngs::fs::directory_copy(dname, newname);
}

EXPORTED_FUNCTION double directory_size(char *dname) {
  return (double)ngs::fs::directory_size(dname);
}

EXPORTED_FUNCTION double directory_contents_close() {
  directory_contents.clear(); 
  directory_contents_index = 0;
  return 0;
}

EXPORTED_FUNCTION double directory_contents_get_order() {
  return directory_contents_order;
}

EXPORTED_FUNCTION double directory_contents_set_order(double order) {
  directory_contents_order = (unsigned)order;
  return 0;
}

EXPORTED_FUNCTION char *directory_contents_first(char *dname, char *pattern, double includedirs, double recursive) {
  directory_contents_close();
  if (!recursive) directory_contents = ngs::fs::directory_contents(dname, pattern, includedirs);
  else directory_contents = ngs::fs::directory_contents_recursive(dname, pattern, includedirs);
  if (directory_contents_index < directory_contents.size()) {
    if (directory_contents_order == DC_ZTOA) {
      std::reverse(directory_contents.begin(), directory_contents.end());
    } else if (directory_contents_order == DC_AOTON) {
      std::sort(directory_contents.begin(), directory_contents.end(),
      [](const std::string& l, const std::string& r) {
      return (file_datetime_helper(l, 0) < file_datetime_helper(r, 0));
      });
    } else if (directory_contents_order == DC_ANTOO) {
      std::sort(directory_contents.begin(), directory_contents.end(),
      [](const std::string& l, const std::string& r) {
      return (file_datetime_helper(l, 0) > file_datetime_helper(r, 0));
      });
    } else if (directory_contents_order == DC_MOTON) {
      std::sort(directory_contents.begin(), directory_contents.end(),
      [](const std::string& l, const std::string& r) {
      return (file_datetime_helper(l, 1) < file_datetime_helper(r, 1));
      });
    } else if (directory_contents_order == DC_MNTOO) {
      std::sort(directory_contents.begin(), directory_contents.end(),
      [](const std::string& l, const std::string& r) {
      return (file_datetime_helper(l, 1) > file_datetime_helper(r, 1));
      });
    } else if (directory_contents_order == DC_COTON) {
      std::sort(directory_contents.begin(), directory_contents.end(),
      [](const std::string& l, const std::string& r) {
      return (file_datetime_helper(l, 2) < file_datetime_helper(r, 2));
      });
    } else if (directory_contents_order == DC_CNTOO) {
      std::sort(directory_contents.begin(), directory_contents.end(),
      [](const std::string& l, const std::string& r) {
      return (file_datetime_helper(l, 2) > file_datetime_helper(r, 2));
      });
    } else if (directory_contents_order == DC_RAND) {
      std::random_device rd; std::mt19937 g(rd());
      std::shuffle(directory_contents.begin(), directory_contents.end(), g);
    }
  return (char*)directory_contents[directory_contents_index].c_str();
  } 
  return (char *)"";
}

EXPORTED_FUNCTION char *directory_contents_next() {
  directory_contents_index++;
  if (directory_contents_index < directory_contents.size())
  return (char *)directory_contents[directory_contents_index].c_str();
  else return (char *)"";
}

EXPORTED_FUNCTION char *environment_get_variable(char *name) {
  static string result;
  result = ngs::fs::environment_get_variable(name);
  return (char *)result.c_str();
}

EXPORTED_FUNCTION double environment_set_variable(char *name, char *value) {
  return ngs::fs::environment_set_variable(name, value);
}

EXPORTED_FUNCTION double environment_unset_variable(char *name) {
  return ngs::fs::environment_unset_variable(name);
}

EXPORTED_FUNCTION char *environment_expand_variables(char *str) {
  static string result;
  result = ngs::fs::environment_expand_variables(str);
  return (char *)result.c_str();
}

EXPORTED_FUNCTION double file_datetime_accessed_year(char *fname) {
  return ngs::fs::file_datetime_accessed_year(fname);
}

EXPORTED_FUNCTION double file_datetime_accessed_month(char *fname) {
  return ngs::fs::file_datetime_accessed_month(fname);
}

EXPORTED_FUNCTION double file_datetime_accessed_day(char *fname) {
  return ngs::fs::file_datetime_accessed_day(fname);
}

EXPORTED_FUNCTION double file_datetime_accessed_hour(char *fname) {
  return ngs::fs::file_datetime_accessed_hour(fname);
}

EXPORTED_FUNCTION double file_datetime_accessed_minute(char *fname) {
  return ngs::fs::file_datetime_accessed_minute(fname);
}

EXPORTED_FUNCTION double file_datetime_accessed_second(char *fname) {
  return ngs::fs::file_datetime_accessed_second(fname);
}

EXPORTED_FUNCTION double file_datetime_modified_year(char *fname) {
  return ngs::fs::file_datetime_modified_year(fname);
}

EXPORTED_FUNCTION double file_datetime_modified_month(char *fname) {
  return ngs::fs::file_datetime_modified_month(fname);
}

EXPORTED_FUNCTION double file_datetime_modified_day(char *fname) {
  return ngs::fs::file_datetime_modified_day(fname);
}

EXPORTED_FUNCTION double file_datetime_modified_hour(char *fname) {
  return ngs::fs::file_datetime_modified_hour(fname);
}

EXPORTED_FUNCTION double file_datetime_modified_minute(char *fname) {
  return ngs::fs::file_datetime_modified_minute(fname);
}

EXPORTED_FUNCTION double file_datetime_modified_second(char *fname) {
  return ngs::fs::file_datetime_modified_second(fname);
}

EXPORTED_FUNCTION double file_datetime_created_year(char *fname) {
  return ngs::fs::file_datetime_created_year(fname);
}

EXPORTED_FUNCTION double file_datetime_created_month(char *fname) {
  return ngs::fs::file_datetime_created_month(fname);
}

EXPORTED_FUNCTION double file_datetime_created_day(char *fname) {
  return ngs::fs::file_datetime_created_day(fname);
}

EXPORTED_FUNCTION double file_datetime_created_hour(char *fname) {
  return ngs::fs::file_datetime_created_hour(fname);
}

EXPORTED_FUNCTION double file_datetime_created_minute(char *fname) {
  return ngs::fs::file_datetime_created_minute(fname);
}

EXPORTED_FUNCTION double file_datetime_created_second(char *fname) {
  return ngs::fs::file_datetime_created_second(fname);
}

EXPORTED_FUNCTION double file_bin_datetime_accessed_year(double fd) {
  return ngs::fs::file_bin_datetime_accessed_year((int)fd);
}

EXPORTED_FUNCTION double file_bin_datetime_accessed_month(double fd) {
  return ngs::fs::file_bin_datetime_accessed_month((int)fd);
}

EXPORTED_FUNCTION double file_bin_datetime_accessed_day(double fd) {
  return ngs::fs::file_bin_datetime_accessed_day((int)fd);
}

EXPORTED_FUNCTION double file_bin_datetime_accessed_hour(double fd) {
  return ngs::fs::file_bin_datetime_accessed_hour((int)fd);
}

EXPORTED_FUNCTION double file_bin_datetime_accessed_minute(double fd) {
  return ngs::fs::file_bin_datetime_accessed_minute((int)fd);
}

EXPORTED_FUNCTION double file_bin_datetime_accessed_second(double fd) {
  return ngs::fs::file_bin_datetime_accessed_second((int)fd);
}

EXPORTED_FUNCTION double file_bin_datetime_modified_year(double fd) {
  return ngs::fs::file_bin_datetime_modified_year((int)fd);
}

EXPORTED_FUNCTION double file_bin_datetime_modified_month(double fd) {
  return ngs::fs::file_bin_datetime_modified_month((int)fd);
}

EXPORTED_FUNCTION double file_bin_datetime_modified_day(double fd) {
  return ngs::fs::file_bin_datetime_modified_day((int)fd);
}

EXPORTED_FUNCTION double file_bin_datetime_modified_hour(double fd) {
  return ngs::fs::file_bin_datetime_modified_hour((int)fd);
}

EXPORTED_FUNCTION double file_bin_datetime_modified_minute(double fd) {
  return ngs::fs::file_bin_datetime_modified_minute((int)fd);
}

EXPORTED_FUNCTION double file_bin_datetime_modified_second(double fd) {
  return ngs::fs::file_bin_datetime_modified_second((int)fd);
}

EXPORTED_FUNCTION double file_bin_datetime_created_year(double fd) {
  return ngs::fs::file_bin_datetime_created_year((int)fd);
}

EXPORTED_FUNCTION double file_bin_datetime_created_month(double fd) {
  return ngs::fs::file_bin_datetime_created_month((int)fd);
}

EXPORTED_FUNCTION double file_bin_datetime_created_day(double fd) {
  return ngs::fs::file_bin_datetime_created_day((int)fd);
}

EXPORTED_FUNCTION double file_bin_datetime_created_hour(double fd) {
  return ngs::fs::file_bin_datetime_created_hour((int)fd);
}

EXPORTED_FUNCTION double file_bin_datetime_created_minute(double fd) {
  return ngs::fs::file_bin_datetime_created_minute((int)fd);
}

EXPORTED_FUNCTION double file_bin_datetime_created_second(double fd) {
  return ngs::fs::file_bin_datetime_created_second((int)fd);
}

EXPORTED_FUNCTION double file_bin_open(char *fname, double mode) {
  return ngs::fs::file_bin_open(fname, (int)mode);
}

EXPORTED_FUNCTION double file_bin_rewrite(double fd) {
  return ngs::fs::file_bin_rewrite((int)fd);
}

EXPORTED_FUNCTION double file_bin_close(double fd) {
  return ngs::fs::file_bin_close((int)fd);
}

EXPORTED_FUNCTION double file_bin_size(double fd) {
  return ngs::fs::file_bin_size((int)fd);
}

EXPORTED_FUNCTION double file_bin_position(double fd) {
  return ngs::fs::file_bin_position((int)fd);
}

EXPORTED_FUNCTION double file_bin_seek(double fd, double pos) {
  return ngs::fs::file_bin_seek((int)fd, (long)pos);
}

EXPORTED_FUNCTION double file_bin_read_byte(double fd) {
  return ngs::fs::file_bin_read_byte((int)fd);
}

EXPORTED_FUNCTION double file_bin_write_byte(double fd, double byte) {
  return ngs::fs::file_bin_write_byte((int)fd, (int)byte);
}

EXPORTED_FUNCTION double file_text_open_read(char *fname) {
  return ngs::fs::file_text_open_read(fname);
}

EXPORTED_FUNCTION double file_text_open_write(char *fname) {
  return ngs::fs::file_text_open_write(fname);
}

EXPORTED_FUNCTION double file_text_open_append(char *fname) {
  return ngs::fs::file_text_open_append(fname);
}

EXPORTED_FUNCTION double file_text_write_real(double fd, double val) {
  return ngs::fs::file_text_write_real((int)fd, val);
}
  
EXPORTED_FUNCTION double file_text_write_string(double fd, char *str) {
  return ngs::fs::file_text_write_string((int)fd, str);
}

EXPORTED_FUNCTION double file_text_writeln(double fd) {
  return ngs::fs::file_text_writeln((int)fd);
}

EXPORTED_FUNCTION double file_text_eoln(double fd) {
  return ngs::fs::file_text_eoln((int)fd);
}

EXPORTED_FUNCTION double file_text_eof(double fd) {
  return ngs::fs::file_text_eof((int)fd);
}

EXPORTED_FUNCTION double file_text_read_real(double fd) {
  return ngs::fs::file_text_read_real((int)fd);
}

EXPORTED_FUNCTION char *file_text_read_string(double fd) {
  static string result;
  result = ngs::fs::file_text_read_string((int)fd);
  return (char *)result.c_str();
}

EXPORTED_FUNCTION char *file_text_readln(double fd) {
  static string result;
  result = ngs::fs::file_text_readln((int)fd);
  return (char *)result.c_str();
}

EXPORTED_FUNCTION char *file_text_read_all(double fd) {
  static string result;
  result = ngs::fs::file_text_read_all((int)fd);
  return (char *)result.c_str();
}
  
EXPORTED_FUNCTION double file_text_open_from_string(char *str) {
  return ngs::fs::file_text_open_from_string(str);
}

EXPORTED_FUNCTION double file_text_close(double fd) {
  return ngs::fs::file_text_close((int)fd);
}
