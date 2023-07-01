#include "sceneutilities.h"

void SceneUtilities::cleanPreviousScenes(Node referenceScene, String callSource) {
	int numChildren = referenceScene.get_tree()->get_root()->get_child_count();
	//GD.Print($"CleanPreviousScenes() - scenes count = {numChildren}, called from {callSource} \n");
	Node* previousScene = referenceScene.get_tree()->get_root()->get_child(0, false);
	/*
	var props = Diagnostics.GetProperties(previousScene);
	if (props.Count > 0)
	{
		PrintObjectProperties("previousScene", introTimer);
	}
	*/
	referenceScene.get_tree()->get_root()->remove_child(previousScene);
}

void SceneUtilities::changeSceneToFile(Node referenceScene, String scenePath, bool deferCall) {
	//ResourceLoader resLoader;
	ResourceLoader* resLoader = ResourceLoader::get_singleton();
	Ref<PackedScene> resPckScene = resLoader->load(scenePath);
	Node* newScene = resPckScene->instantiate();
	//PackedScene newScene = (PackedScene)resLoader.load(scenePath);
	if (newScene != nullptr) {
		if (deferCall) {
			//referenceScene.get_tree()->get_root()->CallDeferred("add_child", newScene.Instantiate());
		}
		else
			referenceScene.get_tree()->get_root()->add_child(newScene/*newScene.instantiate()*/);
	}
}

void SceneUtilities::exitApplication(Node* referenceScene) {
	referenceScene->get_tree()->quit();
}

Rect2 SceneUtilities::getApplicationWindowExtent(Node* referenceScene) {
	Rect2 res;
	res = referenceScene->get_tree()->get_root()->get_visible_rect();
	return res;
}