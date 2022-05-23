#pragma once

#include "main.h"

class cmd_parser {
public:
	cmd_parser();
	std::vector<std::string> get_parse_label(const std::vector<std::string>);
	std::vector<std::pair<std::string, std::string>> get_parse_string(std::vector<std::string>);
	std::vector<std::pair<uint32_t, uint32_t>> get_replace(std::vector<std::pair<std::string, std::string>>);
	std::vector<std::pair<uint32_t, uint32_t>> get_result(void) const;
	std::vector<std::pair<std::string, std::string>> get_string_result(void) const;
	~cmd_parser();
private:
	std::map<std::string, uint32_t> cmd_interpret = {
		{"GEW", 0x01},
		{"GES", 0x02},
		{"GER", 0x03},
		{"GIW", 0x04},
		{"GIS", 0x05},
		{"GIR", 0x06},
		{"SAMP", 0x07},
		{"SFZC", 0x08},
		{"SFZR", 0x09},
		{"SFIC", 0x0A},
		{"SFIR", 0x0B},
		{"SPC", 0x0C},
		{"SPR", 0x0D},
		{"JMP", 0x0E},
		{"NOP", 0x0F},
		{"SMOD", 0x10}
	};
	std::vector<std::pair<uint32_t, uint32_t>> parsed_result;
	std::map<std::string, uint32_t> labels_library;
	std::vector<std::pair<std::string, std::string>> parsed_labels;
	std::string get_naming(const std::string& cmd_name) const;
	uint32_t get_hex_from_string(const std::string& hex_string) const;

};
