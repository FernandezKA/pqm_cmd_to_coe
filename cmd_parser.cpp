#include "cmd_parser.h"

cmd_parser::cmd_parser() {}

std::vector<std::string> cmd_parser::get_parse_label(const std::vector<std::string> iString) {
	std::pair<std::string, uint32_t> temp_label;
	std::vector<std::string> returned_value;
	uint32_t label_index = 0;
	for (const auto& s : iString) {
		static std::string without_label;
		for (const char ch : s) {
			if (ch == ':') {//We recognize labels
				temp_label = make_pair(get_naming(without_label), label_index);
				without_label.erase();
			}
			else {
				without_label += ch;
			}
		}
		++label_index;
		returned_value.push_back(without_label);
		without_label.erase();
	}
		return returned_value;
}

std::vector<std::pair<std::string, std::string>> cmd_parser::get_parse_string(std::vector<std::string> iString) {
	std::vector<std::pair<std::string, std::string>> temp_result;
	for (const auto& s : iString) {
		std::string command, arg;
		for (const char ch : s) {
			if (ch == ',') {
				command = arg;
				arg.erase();
			}
			else {
				arg += ch;
			}
		}
		command = get_naming(command);
		arg = get_naming(arg);
		temp_result.push_back({ command, arg });
	}
	parsed_labels = temp_result;
	return temp_result;
}

std::vector<std::pair<uint32_t, uint32_t>> cmd_parser::get_replace(std::vector<std::pair<std::string, std::string>> iPString) {
	uint32_t _cmd, _arg;
	std::vector<std::pair<uint32_t, uint32_t>> replaced_value;
	try {
		for (const auto& s : iPString) {
			if (cmd_interpret.find(s.first) == cmd_interpret.end()) { //Cmd can't be finded
				std::cout << "\n\r Command " << s.first << "can't be founded\n\r";
			}
			else {
				_cmd = cmd_interpret.at(s.first);
				_arg = get_hex_from_string(s.second);
				replaced_value.push_back({ _cmd, _arg });
			}
		}
	}
	catch (...) {
		std::cout << "\n\r Replaced value not handled\n\r";
	}
	parsed_result = replaced_value;
	return replaced_value;
}

std::vector<std::pair<uint32_t, uint32_t>> cmd_parser::get_result(void) const 
{
	return parsed_result;
}

std::string cmd_parser::get_naming(const std::string& cmd_name) const
{
	std::string upper_name;
	upper_name.erase();
	for (const char& s : cmd_name) {
		if (islower(s)) {
			upper_name += toupper(s);
		}
		else {
			upper_name += s;
		}
	}
	return upper_name;
}

uint32_t cmd_parser::get_hex_from_string(const std::string& hex_string) const 
{
	std::string rev_hex_val = hex_string;
	uint32_t arg_val = 0x00U;
	std::stringstream ss;
	ss << std::hex << hex_string;
	ss >> arg_val;
	return arg_val;
}

std::vector<std::pair<std::string, std::string>> cmd_parser::get_string_result(void) const 
{
	return parsed_labels;
}

cmd_parser::~cmd_parser() {

}
