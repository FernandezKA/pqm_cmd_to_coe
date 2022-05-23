#pragma once

#include "main.h"
using namespace std;
class file_parser {
public:
	file_parser();
	void set_path(enum class stream_direction dir);
	vector<string> get_read(void);
	void get_write(vector<pair<uint32_t, uint32_t>>);
	vector<string> get_result(void) const;
	void clear_read(void);
	void print_readed(void) const;
private:
	string path_input; 
	string path_output;
	ifstream read_stream;
	ofstream write_stream;
	vector<string> read_result;
};
