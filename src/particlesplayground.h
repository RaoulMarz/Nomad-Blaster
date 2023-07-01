#ifndef PARTICLES_PLAYGROUND_CLASS_H
#define PARTICLES_PLAYGROUND_CLASS_H

#include <string>
#include <vector>
#include <memory>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/color.hpp>

#include <godot_cpp/core/binder_common.hpp>
#include "diagnostics.h"
#include "sceneutilities.h"
#include "selectionmanager.h"
#include "pathutilities.h"
#include "particle.h"
#include "physicssettings.h"
#include "defaultaccelerator.h"
#include "defaultmatrixgenerator.h"
#include "defaulttypesetter.h"
#include "defaultpositionsetter.h"
#include "acceleratorprovider.h"
#include "matrixgeneratorprovider.h"
#include "positionsetterprovider.h"
#include "typesetterprovider.h"
#include "particlephysics.h"
#include "extendedparticlephysics.h"

using namespace godot;

class ParticlesPlayground : public Node2D {
    GDCLASS(ParticlesPlayground, Node2D);

    protected:
	    static void _bind_methods();
	    String _to_string() const;        
    public:
        ParticlesPlayground();
        ~ParticlesPlayground();

        void message(std::string messageValue);
        void set_physical_parameters(int numTypes, int particleCount);
        void set_physical_extras(float velocityHalfLife, float force = 1.0f, float dt = 0.02f);
        //void _ready();
        void _process(float delta);
        void _draw();
        void enable_debug(bool debug);
        void create_physics();
        void setup();
    private:
        float time_passed;
        bool debugFlag = true;
        bool autoDt = true;
		float fallbackDt = 0.02f;
        ExtendedParticlePhysics extPhysics;
 
        SelectionManager<DefaultAccelerator> accelerateMgr;
        SelectionManager<DefaultMatrixGenerator> matrixGenerators;
        SelectionManager<DefaultPositionSetter> positionSetters;
        SelectionManager<DefaultTypeSetter> typeSetters;

        void drawCircleArc(Vector2 center, float radius, float angleFrom, float angleTo, Color drawColor);
};

#endif