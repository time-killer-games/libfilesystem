/*

 MIT License
 
 Copyright © 2020-2022 Samuel Venable
 
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

#include "gamemaker.h"
#include "filesystem.h"

using std::string;

char *directory_get_current_working() {
  static string result;
  result = ngs::fs::directory_get_current_working();
  return (char *)result.c_str();
}

double directory_set_current_working(char *dname) {
  return ngs::fs::directory_set_current_working(dname);
}

char *directory_get_temporary_path() {
  static string result;
  result = ngs::fs::directory_get_temporary_path();
  return (char *)result.c_str();
}

char *executable_get_directory() {
  static string result;
  result = ngs::fs::executable_get_directory();
  return (char *)result.c_str();
}

char *executable_get_filename() {
  static string result;
  result = ngs::fs::executable_get_filename();
  return (char *)result.c_str();
}

char *executable_get_pathname() {
  static string result;
  result = ngs::fs::executable_get_pathname();
  return (char *)result.c_str();
}

double symlink_create(char *fname, char *newname) {
  return ngs::fs::symlink_create(fname, newname);
}

double symlink_copy(char *fname, char *newname) {
  return ngs::fs::symlink_copy(fname, newname);
}

double symlink_exists(char *fname) {
  return ngs::fs::symlink_exists(fname);
}

double hardlink_create(char *fname, char *newname) {
  return ngs::fs::hardlink_create(fname, newname);
}

double file_numblinks(char *fname) {
  return (double)ngs::fs::file_numblinks(fname);
}

double file_bin_numblinks(double fd) {
  return (double)ngs::fs::file_bin_numblinks((int)fd);
}

char *file_bin_hardlinks(double fd, char *dnames, double recursive) {
  static string result;
  result = ngs::fs::file_bin_hardlinks((int)fd, dnames, (bool)recursive);
  return (char *)result.c_str();
}

char *filename_absolute(char *fname) {
  static string result;
  result = ngs::fs::filename_absolute(fname);
  return (char *)result.c_str();
}

char *filename_canonical(char *fname) {
  static string result;
  result = ngs::fs::filename_canonical(fname);
  return (char *)result.c_str();
}

double filename_equivalent(char *fname1, char *fname2) {
  return ngs::fs::filename_equivalent(fname1, fname2);
}

double file_exists(char *fname) {
  return ngs::fs::file_exists(fname);
}

double file_delete(char *fname) {
  return ngs::fs::file_delete(fname);
}

double file_rename(char *oldname, char *newname) {
  return ngs::fs::file_rename(oldname, newname);
}

double file_copy(char *fname, char *newname) {
  return ngs::fs::file_copy(fname, newname);
}

double file_size(char *fname) {
  return (double)ngs::fs::file_size(fname);
}

double directory_exists(char *dname) {
  return ngs::fs::directory_exists(dname);
}

double directory_create(char *dname) {
  return ngs::fs::directory_create(dname);
}

double directory_destroy(char *dname) {
  return ngs::fs::directory_destroy(dname);
}

double directory_rename(char *oldname, char *newname) {
  return ngs::fs::directory_rename(oldname, newname);
}

double directory_copy(char *dname, char *newname) {
  return ngs::fs::directory_copy(dname, newname);
}

double directory_size(char *dname) {
  return (double)ngs::fs::directory_size(dname);
}

double directory_contents_close() {
  ngs::fs::directory_contents_close();
  return 0;
}

double directory_contents_get_order() {
  return ngs::fs::directory_contents_get_order();
}

double directory_contents_set_order(double order) {
  ngs::fs::directory_contents_set_order((unsigned)order);
  return 0;
}

double directory_contents_get_cntfiles() {
  return ngs::fs::directory_contents_get_cntfiles();
}

double directory_contents_get_maxfiles() {
  return ngs::fs::directory_contents_get_maxfiles();
}

double directory_contents_set_maxfiles(double order) {
  ngs::fs::directory_contents_set_maxfiles((unsigned)order);
  return 0;
}

char *directory_contents_first(char *dname, char *pattern, double includedirs, double recursive) {
  static string result;
  result = ngs::fs::directory_contents_first(dname, pattern, includedirs, recursive);
  return (char *)result.c_str();
}

char *directory_contents_next() {
  static string result;
  result = ngs::fs::directory_contents_next();
  return (char *)result.c_str();
}

char *environment_get_variable(char *name) {
  static string result;
  result = ngs::fs::environment_get_variable(name);
  return (char *)result.c_str();
}

double environment_get_variable_exists(char *name) {
  return ngs::fs::environment_get_variable_exists(name);
}

double environment_set_variable(char *name, char *value) {
  return ngs::fs::environment_set_variable(name, value);
}

double environment_unset_variable(char *name) {
  return ngs::fs::environment_unset_variable(name);
}

char *environment_expand_variables(char *str) {
  static string result;
  result = ngs::fs::environment_expand_variables(str);
  return (char *)result.c_str();
}

double file_datetime_accessed_year(char *fname) {
  return ngs::fs::file_datetime_accessed_year(fname);
}

double file_datetime_accessed_month(char *fname) {
  return ngs::fs::file_datetime_accessed_month(fname);
}

double file_datetime_accessed_day(char *fname) {
  return ngs::fs::file_datetime_accessed_day(fname);
}

double file_datetime_accessed_hour(char *fname) {
  return ngs::fs::file_datetime_accessed_hour(fname);
}

double file_datetime_accessed_minute(char *fname) {
  return ngs::fs::file_datetime_accessed_minute(fname);
}

double file_datetime_accessed_second(char *fname) {
  return ngs::fs::file_datetime_accessed_second(fname);
}

double file_datetime_modified_year(char *fname) {
  return ngs::fs::file_datetime_modified_year(fname);
}

double file_datetime_modified_month(char *fname) {
  return ngs::fs::file_datetime_modified_month(fname);
}

double file_datetime_modified_day(char *fname) {
  return ngs::fs::file_datetime_modified_day(fname);
}

double file_datetime_modified_hour(char *fname) {
  return ngs::fs::file_datetime_modified_hour(fname);
}

double file_datetime_modified_minute(char *fname) {
  return ngs::fs::file_datetime_modified_minute(fname);
}

double file_datetime_modified_second(char *fname) {
  return ngs::fs::file_datetime_modified_second(fname);
}

double file_datetime_created_year(char *fname) {
  return ngs::fs::file_datetime_created_year(fname);
}

double file_datetime_created_month(char *fname) {
  return ngs::fs::file_datetime_created_month(fname);
}

double file_datetime_created_day(char *fname) {
  return ngs::fs::file_datetime_created_day(fname);
}

double file_datetime_created_hour(char *fname) {
  return ngs::fs::file_datetime_created_hour(fname);
}

double file_datetime_created_minute(char *fname) {
  return ngs::fs::file_datetime_created_minute(fname);
}

double file_datetime_created_second(char *fname) {
  return ngs::fs::file_datetime_created_second(fname);
}

double file_bin_datetime_accessed_year(double fd) {
  return ngs::fs::file_bin_datetime_accessed_year((int)fd);
}

double file_bin_datetime_accessed_month(double fd) {
  return ngs::fs::file_bin_datetime_accessed_month((int)fd);
}

double file_bin_datetime_accessed_day(double fd) {
  return ngs::fs::file_bin_datetime_accessed_day((int)fd);
}

double file_bin_datetime_accessed_hour(double fd) {
  return ngs::fs::file_bin_datetime_accessed_hour((int)fd);
}

double file_bin_datetime_accessed_minute(double fd) {
  return ngs::fs::file_bin_datetime_accessed_minute((int)fd);
}

double file_bin_datetime_accessed_second(double fd) {
  return ngs::fs::file_bin_datetime_accessed_second((int)fd);
}

double file_bin_datetime_modified_year(double fd) {
  return ngs::fs::file_bin_datetime_modified_year((int)fd);
}

double file_bin_datetime_modified_month(double fd) {
  return ngs::fs::file_bin_datetime_modified_month((int)fd);
}

double file_bin_datetime_modified_day(double fd) {
  return ngs::fs::file_bin_datetime_modified_day((int)fd);
}

double file_bin_datetime_modified_hour(double fd) {
  return ngs::fs::file_bin_datetime_modified_hour((int)fd);
}

double file_bin_datetime_modified_minute(double fd) {
  return ngs::fs::file_bin_datetime_modified_minute((int)fd);
}

double file_bin_datetime_modified_second(double fd) {
  return ngs::fs::file_bin_datetime_modified_second((int)fd);
}

double file_bin_datetime_created_year(double fd) {
  return ngs::fs::file_bin_datetime_created_year((int)fd);
}

double file_bin_datetime_created_month(double fd) {
  return ngs::fs::file_bin_datetime_created_month((int)fd);
}

double file_bin_datetime_created_day(double fd) {
  return ngs::fs::file_bin_datetime_created_day((int)fd);
}

double file_bin_datetime_created_hour(double fd) {
  return ngs::fs::file_bin_datetime_created_hour((int)fd);
}

double file_bin_datetime_created_minute(double fd) {
  return ngs::fs::file_bin_datetime_created_minute((int)fd);
}

double file_bin_datetime_created_second(double fd) {
  return ngs::fs::file_bin_datetime_created_second((int)fd);
}

double file_bin_open(char *fname, double mode) {
  return ngs::fs::file_bin_open(fname, (int)mode);
}

double file_bin_rewrite(double fd) {
  return ngs::fs::file_bin_rewrite((int)fd);
}

double file_bin_close(double fd) {
  return ngs::fs::file_bin_close((int)fd);
}

double file_bin_size(double fd) {
  return ngs::fs::file_bin_size((int)fd);
}

double file_bin_position(double fd) {
  return ngs::fs::file_bin_position((int)fd);
}

double file_bin_seek(double fd, double pos) {
  return ngs::fs::file_bin_seek((int)fd, (long)pos);
}

double file_bin_read_byte(double fd) {
  return ngs::fs::file_bin_read_byte((int)fd);
}

double file_bin_write_byte(double fd, double byte) {
  return ngs::fs::file_bin_write_byte((int)fd, (int)byte);
}

double file_text_open_read(char *fname) {
  return ngs::fs::file_text_open_read(fname);
}

double file_text_open_write(char *fname) {
  return ngs::fs::file_text_open_write(fname);
}

double file_text_open_append(char *fname) {
  return ngs::fs::file_text_open_append(fname);
}

double file_text_write_real(double fd, double val) {
  return ngs::fs::file_text_write_real((int)fd, val);
}
  
double file_text_write_string(double fd, char *str) {
  return ngs::fs::file_text_write_string((int)fd, str);
}

double file_text_writeln(double fd) {
  return ngs::fs::file_text_writeln((int)fd);
}

double file_text_eoln(double fd) {
  return ngs::fs::file_text_eoln((int)fd);
}

double file_text_eof(double fd) {
  return ngs::fs::file_text_eof((int)fd);
}

double file_text_read_real(double fd) {
  return ngs::fs::file_text_read_real((int)fd);
}

char *file_text_read_string(double fd) {
  static string result;
  result = ngs::fs::file_text_read_string((int)fd);
  return (char *)result.c_str();
}

char *file_text_readln(double fd) {
  static string result;
  result = ngs::fs::file_text_readln((int)fd);
  return (char *)result.c_str();
}

char *file_text_read_all(double fd) {
  static string result;
  result = ngs::fs::file_text_read_all((int)fd);
  return (char *)result.c_str();
}
  
double file_text_open_from_string(char *str) {
  return ngs::fs::file_text_open_from_string(str);
}

double file_text_close(double fd) {
  return ngs::fs::file_text_close((int)fd);
}
