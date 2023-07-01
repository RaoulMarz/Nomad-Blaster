#include "particlephysics.h"

ParticlePhysics::ParticlePhysics() {
	calcNxNy();
	makeContainerNeighborhood();

	generateMatrix();
	setParticleCount(10000);
}

ParticlePhysics::ParticlePhysics(DefaultAccelerator paramAccelerator,
		DefaultPositionSetter paramPositionSetter,
		DefaultMatrixGenerator paramMatrixGenerator,
		DefaultTypeSetter paramTypeSetter) {
	accelerator = paramAccelerator;
	positionSetter = paramPositionSetter;
	matrixGenerator = paramMatrixGenerator;
	typeSetter = paramTypeSetter;

	calcNxNy();
	makeContainerNeighborhood();

	generateMatrix();
	setParticleCount(10000); // uses current position setter to create particles
}

PhysicsSettings* ParticlePhysics::getPhysicsSettings() {
	return settings;
}

void ParticlePhysics::calcNxNy() {
	//        nx = (int) Math.ceil(2 * range.range.x / containerSize);
	//        ny = (int) Math.ceil(2 * range.range.y / containerSize);
	// currently, "floor" is needed (because containerSize = rmax), so that rmax lies inside "simple" neighborhood
	nx = (int)godot::Math::floor(2 / containerSize);
	ny = (int)godot::Math::floor(2 / containerSize);
}

void ParticlePhysics::makeContainerNeighborhood() {
	containerNeighborhood.push_back(std::make_pair(std::make_pair(-1, -1), 0));
	containerNeighborhood.push_back(std::make_pair(std::make_pair(0, -1), 1));
	containerNeighborhood.push_back(std::make_pair(std::make_pair(1, -1), 2));
	containerNeighborhood.push_back(std::make_pair(std::make_pair(-1, 0), 3));

	containerNeighborhood.push_back(std::make_pair(std::make_pair(0, 0), 4));

	containerNeighborhood.push_back(std::make_pair(std::make_pair(1, 0), 5));
	containerNeighborhood.push_back(std::make_pair(std::make_pair(-1, 1), 6));
	containerNeighborhood.push_back(std::make_pair(std::make_pair(0, 1), 7));
	containerNeighborhood.push_back(std::make_pair(std::make_pair(1, 1), 8));
	/* = new int[][]{
		new int[]{ -1, -1 },
		new int[]{ 0, -1 },
		new int[]{ 1, -1 },
		new int[]{ -1, 0 },
		new int[]{ 0, 0 },
		new int[]{ 1, 0 },
		new int[]{ -1, 1 },
		new int[]{ 0, 1 },
		new int[]{ 1, 1 }
	}; */
}

float ParticlePhysics::computeFrictionFactor(float halfLife, float dt) {
	if (halfLife == 0)
		return 0.0f; // avoid division by zero
	if (halfLife == std::numeric_limits<float>::max())
		return 1.0f;

	return godot::Math::pow(0.5f, dt / halfLife);
}

void ParticlePhysics::setPositions() {
	//Arrays.stream(particles).forEach(this::setPosition);
	if (particles.size() > 0) {
		for (Particle particleObj : particles) {
			//particleObj.SetPos
		}
	}
}

void ParticlePhysics::generateMatrix() {
	int prevSize = /*settings.matrix != null ? settings.matrix.Size() :*/ DEFAULT_MATRIX_SIZE;
	settings->physMatrix = matrixGenerator.makeMatrix(prevSize);

	//assert settings.matrix.size() == prevSize : "Matrix size should only change via setMatrixSize()";
}

void ParticlePhysics::setParticleCount(int n) {
	if (particles.size() <= 0) {
		//particles = new Particle[n];
		for (int i = 0; i < n; i++) {
			particles[i] = generateParticle();
		}
	} else if (n != particles.size()) {
		// strategy: if the array size changed, try to keep most of the particles
		std::vector<Particle> newParticles;

		if (n < particles.size()) { // array becomes shorter
			// randomly shuffle particles first
			// (otherwise, the container layout becomes visible)
			shuffleParticles();

			// copy previous array as far as possible
			//newParticles.assign(particles);
			newParticles = std::vector<Particle>(particles);
		} else { // array becomes longer
				 // copy old array and add particles to the end
			for (int i = 0; i < particles.size(); i++) {
				newParticles[i] = particles[i];
			}
			for (int i = particles.size(); i < n; i++) {
				newParticles[i] = generateParticle();
			}
		}
	}
}

void ParticlePhysics::update() {
	updateParticles();
}

void ParticlePhysics::updateParticles() {
	//updateThreadsShouldRun.set(true);
	makeContainers();

	for (int i = 0; i < particles.size(); i++) {
		updateVelocity(i);
		updatePosition(i);
	}
	/*
	loadDistributor.distributeLoadEvenly(particles.length, preferredNumberOfThreads, i-> {
		if (!updateThreadsShouldRun.get()) return false;
		updateVelocity(i);
		return true;
	});
	updateThreadsShouldRun.set(false);
	*/
}

void ParticlePhysics::setMatrixSize(int newSize) {
	DefaultMatrix prevMatrix = settings->physMatrix;
	int prevSize = prevMatrix.size();
	if (newSize == prevSize)
		return; // keep previous matrix

	settings->physMatrix = matrixGenerator.makeMatrix(newSize);

	//assert settings.matrix.size() == newSize;

	// copy as much as possible from previous matrix
	int commonSize = godot::Math::min(prevSize, newSize);
	for (int i = 0; i < commonSize; i++) {
		for (int j = 0; j < commonSize; j++) {
			settings->physMatrix.set(i, j, prevMatrix.get(i, j));
		}
	}

	if (newSize < prevSize) {
		// need to change types of particles that are not in the new matrix
		for (Particle p : particles) {
			if (p.type >= newSize) {
				setType(p);
			}
		}
	}
}

int ParticlePhysics::determineContainerValue(std::pair<std::pair<int, int>, int> value, int index) {
	int res = 0;
	std::pair<int, int> containerZone = value.first;
	if (index == 0)
		res = containerZone.first;
	if (index == 1)
		res = containerZone.second;
	return res;
}

void ParticlePhysics::updateVelocity(int i) {
	Particle p = particles[i];

	// apply friction before adding new velocity
	//p.velocity.mul(computeFrictionFactor(settings.velocityHalfLife, settings.dt));
	p.velocity = p.velocity * (float)computeFrictionFactor(settings->getParameter(enumPhysicsParameter::PHYSICS_PARAM_VELOCITY_HL), settings->getParameter(enumPhysicsParameter::PHYSICS_PARAM_DT));

	int cx0 = (int)godot::Math::floor((p.position.x + 1) / containerSize);
	int cy0 = (int)godot::Math::floor((p.position.y + 1) / containerSize);

	for (std::pair<std::pair<int, int>, int> containerNeighbor : containerNeighborhood) {
		int cx = wrapContainerAxis(enumCoordComponent::COORD_COMPONENT_X, cx0 + determineContainerValue(containerNeighbor, 0));
		int cy = wrapContainerAxis(enumCoordComponent::COORD_COMPONENT_Y, cy0 + determineContainerValue(containerNeighbor, 1));
		if (settings->isWrap()) {
			cx = wrapContainerAxis(enumCoordComponent::COORD_COMPONENT_X, cx);
			cy = wrapContainerAxis(enumCoordComponent::COORD_COMPONENT_Y, cy);
		} else {
			if (cx < 0 || cx >= nx || cy < 0 || cy >= ny) {
				continue;
			}
		}
		int ci = cx + cy * nx;

		int start = ci == 0 ? 0 : containers[ci - 1];
		int stop = containers[ci];

		for (int j = start; j < stop; j++) {
			if (i == j)
				continue;

			Particle q = particles[j];

			godot::Vector3 relativePosition = doConnection(p.position, q.position);
			float distanceSquared = relativePosition.length_squared();
			// only check particles that are closer than or at rmax
			float rmax = settings->getParameter(enumPhysicsParameter::PHYSICS_PARAM_RMAX);
			if (distanceSquared != 0 && distanceSquared <= rmax * rmax) {
				relativePosition = relativePosition / (float)rmax;
				godot::Vector3 deltaV = accelerator.accelerate(settings->physMatrix.get(p.type, q.type), relativePosition);
				// apply force as acceleration
				p.velocity += (deltaV * (float)(rmax * settings->getParameter(enumPhysicsParameter::PHYSICS_PARAM_FORCE) * 
				settings->getParameter(enumPhysicsParameter::PHYSICS_PARAM_DT)));
			}
		}
	}
}

void ParticlePhysics::updatePosition(int i) {
	Particle p = particles[i];

	// pos += vel * dt
	//p.velocity.mulAdd(settings.dt, p.position, p.position);
	p.position = p.velocity * settings->getParameter(enumPhysicsParameter::PHYSICS_PARAM_DT);

	ensurePosition(p.position);
}

void ParticlePhysics::ensurePosition(godot::Vector3 position) {
	if (settings->isWrap()) {
		MathRange::wrap(position);
	} else {
		MathRange::clamp(position);
	}
}

void ParticlePhysics::shuffleParticles() {
	std::vector<Particle> listParts(particles);
	//listParts. //list.AddRange(particles);
	godot::RandomNumberGenerator randNumGen;
	unsigned seed = std::chrono::system_clock::now()
							.time_since_epoch()
							.count();
	std::shuffle(std::begin(listParts), std::end(listParts), std::default_random_engine(seed));
	particles = listParts; //  list.ToArray();
}

Particle ParticlePhysics::generateParticle() {
	Particle p; // = new Particle();
	setType(p);
	setPosition(p);
	return p;
}

void ParticlePhysics::setPosition(Particle p) {
	positionSetter.set(p.position, p.type, settings->physMatrix.size());
	//Range.wrap(p.position);
	p.velocity.x = 0;
	p.velocity.y = 0;
	p.velocity.z = 0;
}

void ParticlePhysics::setType(Particle p) {
	p.type = typeSetter.getType(p.position, p.velocity, p.type, settings->physMatrix.size());
}

void ParticlePhysics::makeContainers() {
	// ensure that nx and ny are still OK
	containerSize = settings->getParameter(enumPhysicsParameter::PHYSICS_PARAM_RMAX); // settings->rmax; //todo: in the future, containerSize should be independent of rmax
	calcNxNy(); //todo: only change if containerSize (or range) changed
				//todo: (future) containerNeighborhood depends on rmax and containerSize.
				// if (rmax changed or containerSize changed) {
				//     makeContainerNeighborhood();
				// }

	// init arrays
	if (containers.size() != nx * ny) {
		//containers = new int[nx * ny];
		containers.resize(nx * ny);
	}
	//Array.Fill(containers, 0);
	if (particlesBuffer.size() != particles.size()) {
		//particlesBuffer = new Particle[particles.Length];
		particlesBuffer.resize(particles.size());
	}

	// calculate container capacity
	for (Particle p : particles) {
		int ci = getContainerIndex(p.position);
		containers[ci]++;
	}

	// capacity -> index
	int offset = 0;
	for (int i = 0; i < containers.size(); i++) {
		int cap = containers[i];
		containers[i] = offset;
		offset += cap;
	}

	// fill particles into containers
	for (Particle p : particles) {
		int ci = getContainerIndex(p.position);
		int i = containers[ci];
		particlesBuffer[i] = p;
		//containers[ci]++;  // for next access
	}

	// swap buffers
	std::vector<Particle> swapList(particles);
	particles = particlesBuffer;
	particlesBuffer = swapList;
}

int ParticlePhysics::getContainerIndex(godot::Vector3 position) {
	int cx = (int)((position.x + 1) / containerSize);
	int cy = (int)((position.y + 1) / containerSize);

	// for solid borders
	if (cx == nx) {
		cx = nx - 1;
	}
	if (cy == ny) {
		cy = ny - 1;
	}
	return cx + cy * nx;
}

int ParticlePhysics::wrapContainerAxis(enumCoordComponent compAxis, int cValue) {
	int changeValue = 0;
	switch (compAxis) {
		case enumCoordComponent::COORD_COMPONENT_X:
			changeValue = nx;
			break;
		case enumCoordComponent::COORD_COMPONENT_Y:
			changeValue = ny;
			break;
	}
	if (cValue < 0) {
		return cValue + changeValue;
	} else if (cValue >= nx) {
		return cValue - changeValue;
	} else {
		return cValue;
	}
}

godot::Vector3 ParticlePhysics::doConnection(godot::Vector3 pos1, godot::Vector3 pos2) {
	godot::Vector3 delta = pos2 - pos1;

	if (settings->isWrap()) {
		// wrapping the connection gives us the shortest possible distance
		MathRange::wrap(delta);
	}

	return delta;
}