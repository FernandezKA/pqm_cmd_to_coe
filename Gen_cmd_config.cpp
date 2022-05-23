#include "main.h"
#include "file_parser.h"
#include "cmd_parser.h"

void print_vector(std::vector<std::string> vData) {
	for (const auto& s : vData) {
		cout << s << "\n\r";
	}
}

void print_vector(std::vector<std::pair<std::string, std::string>> vData) {
	for (const auto& s : vData) {
		cout << "Cmd: " << s.first << " Arg: " << s.second << "\n\r";
	}
}

void print_vector(std::vector<std::pair<uint32_t, uint32_t>> vData) {
	for (const auto& s : vData) {
		cout << std::hex;
		cout << "\n\rParsed cmd: " << s.first << " Parsed arg: " << s.second << "\n\r";
	}
}

file_parser parser;
cmd_parser cmd;


int main() {
	cout << "Readed file: \n\r";
	print_vector(parser.get_result());
	cout << "Parsed file: \n\r";
	print_vector(cmd.get_parse_label(parser.get_result()));
	cout << "Readed command: \n\r";
	print_vector(cmd.get_parse_string(cmd.get_parse_label(parser.get_result())));
	cout << "Replaced command\n\r";
	cmd.get_replace(cmd.get_string_result());
	print_vector(cmd.get_result());
	parser.get_write(cmd.get_result());
}