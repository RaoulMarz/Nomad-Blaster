#ifndef SCENE_UTILITIES_CLASS_H
#define SCENE_UTILITIES_CLASS_H

#include <string>
#include <map>
#include <godot_cpp/classes/control.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/scene_tree.hpp>
#include <godot_cpp/classes/packed_scene.hpp>
#include <godot_cpp/classes/window.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/utility_functions.hpp>

using namespace godot;

class SceneUtilities {
    public:
    void cleanPreviousScenes(Node referenceScene, String callSource = "");
    void changeSceneToFile(Node referenceScene, String scenePath, bool deferCall = false);
    static void exitApplication(Node* referenceScene);
    static Rect2 getApplicationWindowExtent(Node* referenceScene);
};

#endif