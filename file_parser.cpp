#include "file_parser.h"

enum class stream_direction{
	input_stream,
	out_stream, 
	all
};

file_parser::file_parser() {
	set_path(stream_direction::all);
	if (get_read().size() != 0) {
		cout << "Read success. \n\r";
		print_readed();
		//get_write(get_result());
	}
}

//For path config for in|out files
void file_parser::set_path(enum class stream_direction dir){
	switch (dir) {
	case stream_direction::all:
		cout << "Enter path to input file\n\r";
		cin >> path_input;
		cout << "Enter path to output file\n\r";
		cin >> path_output;
		break;

	case stream_direction::input_stream:
		cout << "Enter path to input file\n\r";
		cin >> path_input;
		break;

	case stream_direction::out_stream:
		cout << "Enter path to output file\n\r";
		cin >> path_output;
		break;
	}
}

//Only read input file at path in_path
vector<string> file_parser::get_read(void) {
	static string curr_line;
	static vector<string> temp_vector;
	if (read_stream.is_open()) {
		while (getline(read_stream, curr_line)) {
			read_result.push_back(curr_line);
		}
		return read_result;
	}
	else {
		read_stream.open(path_input);
		if (read_stream.is_open()) {
			while (getline(read_stream, curr_line)) {
				read_result.push_back(curr_line);
			}
		}
		else {
			cout << "Can't open file\n\r";
		}
		return read_result;
	}
}

//Write to the out COE file with current coe syntax rules
void file_parser::get_write(vector<pair<uint32_t, uint32_t>> dWrite) {
	if (write_stream.is_open()) {
		bool is_first = true;
		write_stream << "memory_initialization_radix=16;\n";
		write_stream << "memory_initialization_vector=";
		for (const auto& s : dWrite) {
			if (!is_first) {
				write_stream << ' ';
			}
			else {
				is_first = false;
			}
			write_stream << std::hex << setw(8) << setfill('0') << s.first;
			write_stream << ' ';
			write_stream << std::hex << setw(8) << setfill('0') << s.second;
		}
		write_stream << ';';
	}
	else {
		write_stream.open(path_output);
		if (write_stream.is_open()) {
			bool is_first = true;
			write_stream << "memory_initialization_radix=16;\n";
			write_stream << "memory_initialization_vector=";
			for (const auto& s : dWrite) {
				if (!is_first) {
					write_stream << ' ';
				}
				else {
					is_first = false;
				}
				write_stream << std::hex << setw(8) << setfill('0') << s.first;
				write_stream << ' ';
				write_stream << std::hex << setw(8) << setfill('0') << s.second;
			}
			write_stream << ';';
		}
		else {
			cout << "Can't open file for write\n\r";
		}
	}
}

//Return readed vector of strings
vector<string> file_parser::get_result(void) const {
	return read_result;
}

//Clear internal with readed files
void file_parser::clear_read(void) {
	read_result.clear();
}

//Print readed file
void file_parser::print_readed(void) const {
	for (const auto& s : read_result) {
		cout << s << endl;
	}
}