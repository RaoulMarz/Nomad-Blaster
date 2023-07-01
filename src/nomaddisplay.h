#ifndef NOMADDISPLAY_CLASS_H
#define NOMADDISPLAY_CLASS_H

// We don't need windows.h in this example plugin but many others do, and it can
// lead to annoying situations due to the ton of macros it defines.
// So we include it and make sure CI warns us if we use something that conflicts
// with a Windows define.
#ifdef WIN32
#include <windows.h>
#endif

#include <thread>
#include <godot_cpp/classes/canvas_layer.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/viewport.hpp>

#include <godot_cpp/core/binder_common.hpp>
#include <godot_cpp/variant/packed_byte_array.hpp>
#include <godot_cpp/variant/packed_string_array.hpp>
#include <vector>
#include <memory>
#include <map>
#include <optional>
#include "directoryscanner.h"
#include "timer.h"

using namespace godot;

struct structDrawExtent {
  Vector2 drawTopLeft;
  Vector2 drawExtent;
};

//------------------------------------------------

class NomadDisplay : public CanvasLayer {
	GDCLASS(NomadDisplay, CanvasLayer);

protected:
	static void _bind_methods();
	String _to_string() const;

public:
	NomadDisplay();
	~NomadDisplay();

	void set_working_path(String path);
	void set_ipc_path(String path);
	void set_size(Vector2 imgSize);
	void set_platform_colors(PackedStringArray &platformEntitiesColors);
        void set_dimensions(String layer, Vector2 topLeft, Vector2 extent);
	void start_game(bool start);
private:
	Vector2 custom_position;
	Vector2 irSize;
	std::string ipcPath;
	std::string workingPath;

	directoryscanner pathScannerAgent;//(true);
	std::optional<Timer *> timerGameLoop = std::nullopt;
        std::map<std::string, structDrawExtent> mapLayers;

	void run_gameloop();
};

#endif
