#include "cmd_parser.h"

cmd_parser::cmd_parser() {}


//This function detect labels into readed file, delete its, and get list of pair <label - abs_addr>
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
		labels_library.insert(temp_label);
		returned_value.push_back(without_label);
		without_label.erase();
	}
		return returned_value;
}

//This funct. parse input string to pair of string (cmd + arg)
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

//This function get pair of nums for initialization mem. in view cmd + arg
std::vector<std::pair<uint32_t, uint32_t>> cmd_parser::get_replace(std::vector<std::pair<std::string, std::string>> iPString) {
	uint32_t _cmd, _arg;
	std::vector<std::pair<uint32_t, uint32_t>> replaced_value;
	try {
		for (const auto& s : iPString) {
			if (cmd_interpret.find(s.first) == cmd_interpret.end()) { //Cmd can't be finded
				std::cout << "\n\r Command " << s.first << "can't be founded\n\r";
				std::cerr << "Cmd "<<s.first << " not exist\n\r";
				//TODO:: add string number
			}
			else {//Cmd is exist
				_cmd = cmd_interpret.at(s.first);
				if (s.first == "JMP") {//Check arg. value for jmp cmd (may be abs. val or label)
					if (find_label(s.second, labels_library, _arg)) {
						std::cout << "Label " << s.second << " with addr. " << _arg << " finded\n\r";
					}
					else {//Try to interpret as absolute value 
						std::cerr << "Label " << s.second << " not finded\n\r";
					}
				}
				else {
				_arg = get_hex_from_string(s.second);
				}
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

//This function return parsed vector of result
std::vector<std::pair<uint32_t, uint32_t>> cmd_parser::get_result(void) const 
{
	return parsed_result;
}

//This funct. convert all of symbols to upper case
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

//Get uint32_t nums from input hex string
uint32_t cmd_parser::get_hex_from_string(const std::string& hex_string) const 
{
	std::string rev_hex_val = hex_string;
	uint32_t arg_val = 0x00U;
	std::stringstream ss;
	ss << std::hex << hex_string;
	ss >> arg_val;
	return arg_val;
}

//Return list of labels
std::vector<std::pair<std::string, std::string>> cmd_parser::get_string_result(void) const 
{
	return parsed_labels;
}

std::vector<std::pair<std::string, std::string>> cmd_parser::get_labels_replace(const std::vector<std::pair<std::string, std::string>>& pFile)
{
	std::vector<std::pair<std::string, std::string>> tmp;
	for (const auto& s : pFile) {
		
	}
	return tmp;
}

bool cmd_parser::find_label(const std::string& _label, std::map<std::string, uint32_t>& _lib_lbl, uint32_t& arg) {
	if (_lib_lbl.find(_label) == _lib_lbl.end()) {//Label not exist
		return false;
	}
	else {
		arg = _lib_lbl.at(_label);
		return true;
	}
}

cmd_parser::~cmd_parser() {

}
