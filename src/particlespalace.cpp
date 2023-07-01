#include "particlespalace.h"
#include <optional>

ParticlesPalace::ParticlesPalace() {
}

ParticlesPalace::~ParticlesPalace() {
}

void ParticlesPalace::_ready() {
	UtilityFunctions::print("ParticlesPalace - _ready() called");
	setup();
}

void ParticlesPalace::set_physical_parameters(int numTypes, int particleCount) {
	//PhysicsSettings* phySettings = extPhysics.getPhysicsSettings();
	//if (phySettings != nullptr) {
	//	phySettings->setIntParameter(enumConfigurationParameter::CONFIG_PARAM_NTYPES, numTypes);
	//	phySettings->setIntParameter(enumConfigurationParameter::CONFIG_PARAM_PARTICLE_COUNT, particleCount);
	//}
}

String ParticlesPalace::_to_string() const {
	return "[ GDExtension::ParticlesPlayground <--> Instance ID:" + uitos(get_instance_id()) + " ]";
}

bool ParticlesPalace::is_timesync_enabled() {
	return timeSyncFlag;
}

void ParticlesPalace::set_timesync_enabled(bool syncEnabled) {
	timeSyncFlag = syncEnabled;
}

bool ParticlesPalace::is_extended_draw() {
	return extDrawFlag;
}

void ParticlesPalace::set_extended_draw(bool drawEnabled) {
	extDrawFlag = drawEnabled;
}

void ParticlesPalace::_process(float delta) {
	try {
		if (procTick == 0) {
			Vector2 valueDebug(delta, procTick);
			UtilityFunctions::print("ParticlesPalace - _process, delta,tick = ", UtilityFunctions::var_to_str(valueDebug));
		}
		procTick += 1;
		time_passed += delta;
		Vector2 new_position = Vector2(posOffset.x + (200.0 * sin(time_passed * 2.0)), posOffset.y + (250.0 * cos(time_passed * 1.5)));
		set_position(new_position);

		if (is_timesync_enabled() && is_extended_draw()) {
			jed_utils::datetime instantNow;

			jed_utils::timespan diffTime = instantNow - drawRefreshTime;
			if (diffTime.get_total_milliseconds() >= 25) {
				//extPhysics.Update();
				queue_redraw();
				drawRefreshTime = instantNow;
			}
		}
	} catch (std::exception ex) {
		UtilityFunctions::print("[ParticlesPalace], _process(), exception = ", godot::String(ex.what()));
	}
}

void ParticlesPalace::drawCircleArc(godot::Vector2 center, float radius, float angleFrom, float angleTo, float thickness, Color drawColor) {
	const int plotPoints = 32;
	std::vector<Vector2> arcVertices;
	for (int ix = 0; ix < plotPoints; ix++) {
		float angle_point = angleFrom + ix * (angleTo - angleFrom) / plotPoints;
		arcVertices.push_back(center + godot::Vector2(godot::Math::cos(angle_point), godot::Math::sin(angle_point)) * radius);
	}
	int idx = 0;
	godot::Vector2 prevPoint;
	for (godot::Vector2 point : arcVertices) {
		if (idx >= 1) {
			draw_line(prevPoint, point, drawColor, thickness);
		}
		prevPoint = point;
		idx += 1;
	}
}

void ParticlesPalace::experiment_draw_polys1() {
	PackedColorArray demoExpColorsList;
	PackedVector2Array demoExpVerticesList;
	demoExpColorsList.append(Color::named("GREEN"));
	demoExpColorsList.append(Color::named("RED"));
	demoExpColorsList.append(Color::named("BLUE"));
	demoExpColorsList.append(Color::named("CHOCOLATE"));
	demoExpVerticesList.append(Vector2(42.0f, 48.0f));
	demoExpVerticesList.append(Vector2(55.0f, 52.0f));
	demoExpVerticesList.append(Vector2(88.0f, 30.0f));
	demoExpVerticesList.append(Vector2(61.0f, 58.0f));
	draw_polyline_colors(demoExpVerticesList, demoExpColorsList, 4.0f, true);

	PackedVector2Array demoExpPolyVerticesList;
	demoExpPolyVerticesList.append(Vector2(42.0f, 48.0f));
	demoExpPolyVerticesList.append(Vector2(42.0f, 48.0f));
	demoExpPolyVerticesList.append(Vector2(42.0f, 48.0f));
	demoExpPolyVerticesList.append(Vector2(42.0f, 48.0f));
	demoExpPolyVerticesList.append(Vector2(42.0f, 48.0f));
	//const PackedVector2Array &uvs = PackedVector2Array()
	PackedVector2Array demoExpUvsList;
	draw_colored_polygon(demoExpPolyVerticesList, Color::named("CHOCOLATE"), demoExpUvsList);
}

void ParticlesPalace::_draw() {
	draw_rect(Rect2(80.0f, 120.0f, 150.0f, 160.0f), Color::named("DARK_SLATE_BLUE"), true, 2.0f);
	draw_circle(Vector2(55, 45), 90.0f, Color::named("GOLDENROD"));
	draw_line(Vector2(1.5f, 1.0f), Vector2(11.5f, 4.0f), Color::named("GREEN"), 1.0f);
	draw_line(Vector2(4.0f, 4.0f), Vector2(34.0f, 4.0f), Color::named("BLUE"), 2.0f);
	draw_line(Vector2(7.5f, 15.0f), Vector2(27.5f, 15.0f), Color::named("GREEN"), 3.0f);

	draw_rect(Rect2(0.0f, 10.0f, 40.0f, 40.0f), Color::named("RED"));
	draw_rect(Rect2(45.0f, 55.0f, 80.0f, 90.0f), Color::named("MISTY_ROSE"), false, 1.0f);
	//void draw_rect(const Rect2 &rect, const Color &color, bool filled = true, double width = -1.0);
	//void draw_circle(const Vector2 &position, double radius, const Color &color);
	drawCircleArc(Vector2(125, 95), 55.0f, 0.0f, Math_PI, 3.0f, Color::named("CHOCOLATE"));
	drawCircleArc(Vector2(128, 99), 55.0f, 0.0f, Math_PI * 2, 4.0f, Color::named("CHOCOLATE"));
	experiment_draw_polys1();
}

void ParticlesPalace::enable_debug(bool debug) {
	debugFlag = debug;
}

void ParticlesPalace::position_offset(Vector2 offset) {
	posOffset = offset;
}

void ParticlesPalace::create_physics() {
	try {
		std::optional<DefaultPositionSetter> physicsCompartmentPosition;
		std::optional<DefaultMatrixGenerator> physicsCompartmentMatrix;
		std::optional<DefaultTypeSetter> physicsCompartmentTypes;
		std::optional<DefaultAccelerator> physicsCompartmentAccelerator;
		std::optional<InfoWrapper<DefaultPositionSetter>> activeContainerPosition = positionSetters.getActive();
		std::optional<InfoWrapper<DefaultMatrixGenerator>> activeContainerMatrixGen = matrixGenerators.getActive();
		std::optional<InfoWrapper<DefaultTypeSetter>> activeContainerTypes = typeSetters.getActive();
		std::optional<InfoWrapper<DefaultAccelerator>> activeContainerAccelerator = accelerateMgr.getActive();

		if (activeContainerPosition)
			physicsCompartmentPosition = activeContainerPosition->objectWrap;
		else
			physicsCompartmentPosition = std::nullopt;
		Diagnostics::printNullValueMessage(&physicsCompartmentPosition.value(), "physicsCompartmentPosition");

		if (activeContainerMatrixGen)
			physicsCompartmentMatrix = activeContainerMatrixGen->objectWrap;
		else
			physicsCompartmentMatrix = std::nullopt;
		Diagnostics::printNullValueMessage(&physicsCompartmentMatrix.value(), "physicsCompartmentMatrix");

		if (activeContainerTypes)
			physicsCompartmentTypes = activeContainerTypes->objectWrap;
		else
			physicsCompartmentTypes = std::nullopt;
		Diagnostics::printNullValueMessage(&physicsCompartmentTypes.value(), "physicsCompartmentTypes");

		if (activeContainerAccelerator)
			physicsCompartmentAccelerator = activeContainerAccelerator->objectWrap;
		else
			physicsCompartmentAccelerator = std::nullopt;
		//Accelerator physicsCompartmentAccelerator = accelerateMgr.getActive().objectWrap.AcceleratorDevice;
		Diagnostics::printNullValueMessage(&physicsCompartmentAccelerator.value(), "physicsCompartmentAccelerator");

	} catch (std::exception ex) {
		UtilityFunctions::print("[ParticlesPalace], create_physics(), exception = ", godot::String(ex.what()));
	}
}

void ParticlesPalace::setup() {
	try {
		Rect2 rectAppWindow = SceneUtilities::getApplicationWindowExtent(this);
		Vector2 screenExtent = rectAppWindow.get_size();
		UtilityFunctions::print("ParticlesPalace - setup() <0>, screenExtent = ", UtilityFunctions::var_to_str(screenExtent));
		accelerateMgr.addAll(AcceleratorProvider::create());
		UtilityFunctions::print("ParticlesPalace - setup() <1> : ", godot::String("accelerateMgr.addAll"));
		positionSetters.addAll(PositionSetterProvider::create());
		UtilityFunctions::print("ParticlesPalace - setup() <2> : ", godot::String("positionSetters.addAll"));

		std::vector<InfoWrapper<DefaultMatrixGenerator>> defaultMatriclesList = MatrixGeneratorProvider::create();
		UtilityFunctions::print("ParticlesPalace - setup() <3-1> : ", godot::String("MatrixGeneratorProvider::create() test"));
		//matrixGenerators.addAll(MatrixGeneratorProvider::create());
		//UtilityFunctions::print("ParticlesPalace - setup() <3> : ", godot::String("matrixGenerators.addAll"));
		typeSetters.addAll(TypeSetterProvider::create());
		UtilityFunctions::print("ParticlesPalace - setup() -- end : ", godot::String(/*std::to_string(typeSetters)*/ "typeSetters"));

		//create_physics();
	} catch (std::exception ex) {
		UtilityFunctions::print("[ParticlesPalace], setup(), exception = ", godot::String(ex.what()));
	}
}

void ParticlesPalace::_bind_methods() {
	// Methods.
	ClassDB::bind_method(D_METHOD("set_physical_parameters"), &ParticlesPalace::set_physical_parameters);
	ClassDB::bind_method(D_METHOD("enable_debug"), &ParticlesPalace::enable_debug);
	ClassDB::bind_method(D_METHOD("create_physics"), &ParticlesPalace::create_physics);
	ClassDB::bind_method(D_METHOD("position_offset"), &ParticlesPalace::position_offset);
	ClassDB::bind_method(D_METHOD("is_timesync_enabled"), &ParticlesPalace::is_timesync_enabled);
	ClassDB::bind_method(D_METHOD("set_timesync_enabled"), &ParticlesPalace::set_timesync_enabled);
	ClassDB::bind_method(D_METHOD("is_extended_draw"), &ParticlesPalace::is_extended_draw);
	ClassDB::bind_method(D_METHOD("set_extended_draw"), &ParticlesPalace::set_extended_draw);
	ClassDB::bind_method(D_METHOD("setup"), &ParticlesPalace::setup);
}