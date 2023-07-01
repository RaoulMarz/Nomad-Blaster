#ifndef PARTICLES_PALACE_CLASS_H
#define PARTICLES_PALACE_CLASS_H

#include <string>
#include <vector>
#include <memory>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/global_constants.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/viewport.hpp>
#include <godot_cpp/core/math.hpp>
#include <godot_cpp/variant/color.hpp>
#include <godot_cpp/variant/packed_vector2_array.hpp>
#include <godot_cpp/variant/packed_color_array.hpp>

#include <godot_cpp/core/binder_common.hpp>
#include "datetime.h"
#include "timespan.h"
#include "diagnostics.h"
#include "pathutilities.h"
#include "sceneutilities.h"
#include "selectionmanager.h"
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

class ParticlesPalace : public Node2D {
    GDCLASS(ParticlesPalace, Node2D);

    protected:
	    static void _bind_methods();
	    String _to_string() const;        
    public:
        ParticlesPalace();
        ~ParticlesPalace();

        void set_physical_parameters(int numTypes, int particleCount);
        void _ready();
        void _process(float delta);
        void _draw();
        void enable_debug(bool debug);
        void create_physics();
        void setup();
        void position_offset(Vector2 offset);
        bool is_timesync_enabled();        
        void set_timesync_enabled(bool syncEnabled);
        bool is_extended_draw();
        void set_extended_draw(bool drawEnabled);
    private:
        float time_passed;
        bool debugFlag = true;
        bool autoDt = true;
        bool timeSyncFlag = false;
        bool extDrawFlag = false;
		float fallbackDt = 0.02f;
        int procTick = 0;
        Vector2 posOffset;
        jed_utils::datetime drawRefreshTime;
 
        SelectionManager<DefaultAccelerator> accelerateMgr;
        SelectionManager<DefaultMatrixGenerator> matrixGenerators;
        SelectionManager<DefaultPositionSetter> positionSetters;
        SelectionManager<DefaultTypeSetter> typeSetters;

        void drawCircleArc(godot::Vector2 center, float radius, float angleFrom, float angleTo, float thickness, Color drawColor);
        void experiment_draw_polys1();
};

#endif