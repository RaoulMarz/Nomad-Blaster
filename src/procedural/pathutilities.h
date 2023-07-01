#ifndef PATH_UTILITIES_CLASS_H
#define PATH_UTILITIES_CLASS_H

#include <filesystem>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/variant/string.hpp>
#include <string>
#include <vector>
namespace fs = std::filesystem;

class PathUtilities {
public:
	static godot::String getDirectoryName(godot::String inPath) {
		godot::String res = inPath;
		std::string dirInPath = std::string(inPath.utf8().get_data());
		std::string value = getDirectoryName(dirInPath);
		res = godot::String(value.c_str());
		return res;
	}

	static godot::String getFileName(godot::String inPath) {
		godot::String res = inPath;
		std::string dirInPath = std::string(inPath.utf8().get_data());
		std::string value = getFileName(dirInPath);
		res = godot::String(value.c_str());
		return res;
	}

	static godot::String getExtension(godot::String inPath) {
		godot::String res = inPath;
		std::string dirInPath = std::string(inPath.utf8().get_data());
		std::string value = getExtension(dirInPath);
		res = godot::String(value.c_str());
		return res;
	}

	static godot::String getFileWithoutExtension(godot::String inPath) {
		godot::String res = inPath;
		std::string dirInPath = std::string(inPath.utf8().get_data());
		std::string value = getFileWithoutExtension(dirInPath);
		res = godot::String(value.c_str());
		return res;
	}

	static godot::String directorySeparator() {
		return godot::String("/");
	}

	static std::string getDirectoryName(std::string inPath) {
		std::string res = inPath;
		res = fs::path(inPath).parent_path();
		return res;
	}

	static std::string getFileName(std::string inPath) {
		std::string res = inPath;
		res = fs::path(inPath).filename();
		return res;
	}

	static std::string getExtension(std::string inPath) {
		std::string res = inPath;
		res = fs::path(inPath).extension();
		return res;
	}

	static std::string getFileWithoutExtension(std::string inPath, bool justFile = false) {
		std::string res = inPath;
		std::string extValue = fs::path(inPath).extension();
		if (extValue.length() > 0)
			res.erase(inPath.length() - extValue.length(), extValue.length());
		return res;
	}

	//fs::path( "/foo/bar.txt" ).filename()
};

#endif
