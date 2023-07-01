#include "particlesplayground.h"
#include <optional>

ParticlesPlayground::ParticlesPlayground() {
}

ParticlesPlayground::~ParticlesPlayground() {
}

void ParticlesPlayground::message(std::string messageValue) {
}

//void ParticlesPlayground::_ready() {
	//UtilityFunctions::print("ParticlesPlayground - _ready() called");
	//setup();
//}

void ParticlesPlayground::set_physical_parameters(int numTypes, int particleCount) {
	PhysicsSettings* phySettings = extPhysics.getPhysicsSettings();
	if (phySettings != nullptr) {
		phySettings->setIntParameter(enumConfigurationParameter::CONFIG_PARAM_NTYPES, numTypes);
		phySettings->setIntParameter(enumConfigurationParameter::CONFIG_PARAM_PARTICLE_COUNT, particleCount);
	}
}

void ParticlesPlayground::set_physical_extras(float velocityHalfLife, float force, float dt) {
	PhysicsSettings* phySettings = extPhysics.getPhysicsSettings();
	if (phySettings != nullptr) {
		phySettings->setParameter(enumPhysicsParameter::PHYSICS_PARAM_VELOCITY_HL, velocityHalfLife);
		phySettings->setParameter(enumPhysicsParameter::PHYSICS_PARAM_FORCE, force);
		phySettings->setParameter(enumPhysicsParameter::PHYSICS_PARAM_DT, dt);
	}
}

String ParticlesPlayground::_to_string() const {
	return "[ GDExtension::ParticlesPlayground <--> Instance ID:" + uitos(get_instance_id()) + " ]";
}

void ParticlesPlayground::_process(float delta) {
	time_passed += delta;
	Vector2 new_position = Vector2(10.0 + (200.0 * sin(time_passed * 2.0)), 10.0 + (250.0 * cos(time_passed * 1.5)));
	set_position(new_position);
	/*
	DateTime instantTime = DateTime.Now;
			TimeSpan diffTime = instantTime - drawRefreshTime;
			if (diffTime.TotalMilliseconds >= 25)
			{
				extPhysics.Update();
				QueueRedraw();
				drawRefreshTime = instantTime;
			}
	*/
}

void ParticlesPlayground::drawCircleArc(Vector2 center, float radius, float angleFrom, float angleTo, Color drawColor) {
	const int plotPoints = 32;
	std::vector<Vector2> arcVertices;
	for (int ix = 0; ix < plotPoints; ix++) {
		float angle_point = angleFrom + ix * (angleTo - angleFrom) / plotPoints;
		arcVertices.push_back(center + Vector2(godot::Math::cos(angle_point), godot::Math::sin(angle_point)) * radius);
	}
	int idx = 0;
	for (Vector2 point : arcVertices) {
		if (idx >= 1) {

		}
		idx += 1;
	}
}

void ParticlesPlayground::_draw() {
	draw_line(Vector2(1.5f, 1.0f), Vector2(11.5f, 4.0f), Color::named("GREEN"), 1.0f);
    draw_line(Vector2(4.0f, 4.0f), Vector2(34.0f, 4.0f), Color::named("BLUE"), 2.0f);
    draw_line(Vector2(7.5f, 15.0f), Vector2(27.5f, 15.0f), Color::named("GREEN"), 3.0f);

	draw_rect(Rect2(10.0f, 10.0f, 30.0f, 30.0f), Color::named("RED"));
    draw_rect(Rect2(45.0f, 55.0f, 80.0f, 90.0f), Color::named("MISTY_ROSE"), false, 1.0f);
}

void ParticlesPlayground::enable_debug(bool debug) {
	debugFlag = debug;
}

void ParticlesPlayground::create_physics() {
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
		
		extPhysics = ExtendedParticlePhysics(
				*physicsCompartmentAccelerator,
				*physicsCompartmentPosition,
				*physicsCompartmentMatrix,
				*physicsCompartmentTypes);
		//extPhysics.settings.dt = //autoDt ? dt : 
		//		fallbackDt;
	} catch (std::exception ex) {
		//GD.Print($ "[ParticlesZoo], CreatePhysics(), exception = {ex.Message}");
		UtilityFunctions::print("[ParticlesPlayground], create_physics(), exception = ", godot::String(ex.what()));
	}
}

void ParticlesPlayground::setup() {
	Rect2 rectAppWindow = SceneUtilities::getApplicationWindowExtent(this);
	Vector2 screenExtent = rectAppWindow.get_size();
	UtilityFunctions::print("ParticlesPlayground - setup(), screenExtent = ", UtilityFunctions::var_to_str(screenExtent));
	accelerateMgr.addAll(AcceleratorProvider::create());
	positionSetters.addAll(PositionSetterProvider::create());
	matrixGenerators.addAll(MatrixGeneratorProvider::create());
	typeSetters.addAll(TypeSetterProvider::create());

	create_physics();
}

void ParticlesPlayground::_bind_methods() {
	// Methods.
	ClassDB::bind_method(D_METHOD("set_physical_parameters"), &ParticlesPlayground::set_physical_parameters);
	ClassDB::bind_method(D_METHOD("set_physical_extras"), &ParticlesPlayground::set_physical_extras);
	ClassDB::bind_method(D_METHOD("enable_debug"), &ParticlesPlayground::enable_debug);
	ClassDB::bind_method(D_METHOD("create_physics"), &ParticlesPlayground::create_physics);
	ClassDB::bind_method(D_METHOD("setup"), &ParticlesPlayground::setup);
}