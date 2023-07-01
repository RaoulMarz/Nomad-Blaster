#include "nomaddisplay.h"

#include <godot_cpp/core/class_db.hpp>

#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/label.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

NomadDisplay::NomadDisplay() {
	//pixelData = std::make_unique<std::vector<uint>>();
}

NomadDisplay::~NomadDisplay() {
}

String NomadDisplay::_to_string() const {
	return "[ GDExtension::NomadDisplay <--> Instance ID:" + uitos(get_instance_id()) + " ]";
}

void NomadDisplay::set_ipc_path(String path) {
	UtilityFunctions::print("set_ipc_path called.");
    ipcPath = path.utf8().get_data();
}

//#define godot2stdstr(s) (const char *)(s).to_utf8_buffer().ptr()
void NomadDisplay::set_working_path(String path) {
	UtilityFunctions::print("set_working_path called.");
    workingPath = path.utf8().get_data();
}

void NomadDisplay::set_size(Vector2 imgSize) {
	UtilityFunctions::print("set_size called, size = " + imgSize);
	irSize = imgSize;
	//pixelData->resize(irSize.x * irSize.y);
}

void NomadDisplay::set_platform_colors(PackedStringArray &platformEntitiesColors) {
    if (!platformEntitiesColors.is_empty()) {

    }
}

void NomadDisplay::set_dimensions(String layer, Vector2 topLeft, Vector2 extent) {
  mapLayers[layer.utf8().get_data()] = structDrawExtent{topLeft, extent};
}

void NomadDisplay::start_game(bool start) {
    /*
    int countMeUp = 0;

	Timer t1([&](){
		countMeUp++;
		std::cout << countMeUp << std::endl;
	}, 1000);

	t1.start();

	//cin.get();
	t1.stop();
    */
    Timer* timerGamePtr = new Timer();
    timerGameLoop = std::make_optional<Timer *>(timerGamePtr);
    timerGamePtr->setFunc(
        ([&](){
		run_gameloop();
	}));
    timerGamePtr->setInterval(1000);
    if (start)
        timerGamePtr->start();
    //timerGameLoop = std::make_optional<Timer>
}

void NomadDisplay::run_gameloop() {
    pathScannerAgent = directoryscanner(true);
    int iLevel = 1;
    int listLimit = 200;
    std::string gameStatePath = ExtraHelper::combineFilePath(workingPath, "gamestate");
    pathScannerAgent.printdir("", gameStatePath.c_str(), 1, iLevel, listLimit);
    std::optional<std::vector<std::string>> foundFilesList = pathScannerAgent.results();
    if (foundFilesList)
    {
      for (std::string fileItem : *foundFilesList)
      {
        if (ExtraHelper::StringEndsWith(fileItem, ".json"))
        {
          std::string jsonText = ExtraHelper::readFileAsString(fileItem);
          std::filesystem::remove(fileItem);
        }
      }
    }
}

void NomadDisplay::_bind_methods() {
	// Methods.
	ClassDB::bind_method(D_METHOD("set_ipc_path"), &NomadDisplay::set_ipc_path);
	ClassDB::bind_method(D_METHOD("set_working_path"), &NomadDisplay::set_working_path);
	ClassDB::bind_method(D_METHOD("set_size"), &NomadDisplay::set_size);
	//ClassDB::bind_method(D_METHOD("set_platform_colors"), &NomadDisplay::set_platform_colors);
    ClassDB::bind_method(D_METHOD("start_game"), &NomadDisplay::start_game);
}
