#include "extendedparticlephysics.h";

ExtendedParticlePhysics::ExtendedParticlePhysics() :
		ParticlePhysics() {
}

ExtendedParticlePhysics::ExtendedParticlePhysics(DefaultAccelerator &accelerator, DefaultPositionSetter &positionSetter,
		DefaultMatrixGenerator &matrixGenerator, DefaultTypeSetter &typeSetter) :
		ParticlePhysics(accelerator, positionSetter, matrixGenerator, typeSetter) {
	//
}

std::vector<int> ExtendedParticlePhysics::getTypeCount() {
	//int[] typeCount = new int[settings.matrix.size()];
	//Arrays.fill(typeCount, 0);
	std::vector<int> typeCount;
	for (Particle p : particles) {
		typeCount[p.type]++;
	}
	return typeCount;
}

void ExtendedParticlePhysics::setTypeCountEqual() {
	PhysicsSettings *phySettings = getPhysicsSettings();
	int nTypes = phySettings->physMatrix.size();
	if (nTypes < 2)
		return;

	//int[] idealTypeCount = new int[nTypes];
	std::vector<int> idealTypeCount;
	int count = (int)godot::Math::ceil(particles.size() / (float)nTypes);
	//Arrays.fill(idealTypeCount, 0, nTypes - 1, count);
	idealTypeCount[nTypes - 1] = particles.size() - (nTypes - 1) * (count);

	setTypeCount(idealTypeCount);
}

void ExtendedParticlePhysics::swapIntVector(std::vector<int> &array, int i, int j) {
        int h = array[i];
        array[i] = array[j];
        array[j] = h;
    }

void ExtendedParticlePhysics::setTypeCount(std::vector<int> &typeCount) {
	PhysicsSettings *phySettings = getPhysicsSettings();
	int nTypes = phySettings->physMatrix.size();
	if (nTypes < 2)
		return;

	if (typeCount.size() != nTypes) {
		//throw new IllegalArgumentException(String.format(
		//        "Got array of length %d, but current matrix size is %d. Maybe you should change the matrix size before doing this.",
		//        typeCount.length, nTypes));
	}

	// randomly shuffle particles first
	// (otherwise, the container layout becomes visible)
	shuffleParticles();

	int newCount = 0; //Arrays.stream(typeCount).sum();

	if (newCount != particles.size()) {
		//Particle[] newParticles = new Particle[newCount];
		std::vector<Particle> newParticles;

		//int[] actualTypeCount = new int[nTypes];
		//Arrays.fill(actualTypeCount, 0);
		std::vector<int> actualTypeCount;

		// sort all unusable particles to the end
		int i = 0;
		int j = particles.size() - 1;
		while (i < j) {
			int type = particles[i].type;
			if (actualTypeCount[type] < typeCount[type]) {
				// need more of this type -> leave it in front
				actualTypeCount[type]++;
				i++;
			} else {
				ArrayUtils::swap<Particle>(particles, i, j);
				//swapIntVector(particles, i, j);
				j--;
			}
		}
		// now i points at the end (exclusive) of the reusable particles

		// copy as much as possible
		int copyLength = godot::Math::min(newCount, (int)particles.size());
		int k = 0;
		while (k < copyLength) {
			newParticles[k] = particles[k];
			k++;
		}

		// if necessary, fill up rest with new particles
		while (k < newCount) {
			//newParticles[k] = new Particle();
			newParticles.push_back(Particle());
			k++;
		}

		// change types of all particles that couldn't be reused
		while (i < newCount) {
			// find type that has too few particles
			int type = ArrayUtils::findFirstIndexWithLess(actualTypeCount, typeCount);

			Particle p = newParticles[i];
			p.type = type;
			setPosition(p);
			actualTypeCount[type]++;

			i++;
		}
		particles = newParticles;
	} else {
		std::vector<int> actualTypeCount = getTypeCount();

		for (Particle p : particles) {
			if (actualTypeCount[p.type] > typeCount[p.type]) {
				// find type that has too few particles
				int type = 0; // FIX -> ArrayUtils.findFirstIndexWithLess(actualTypeCount, typeCount);  // need more of this type

				// change type
				actualTypeCount[p.type]--;
				p.type = type;
				actualTypeCount[type]++;
			}
		}
	}
}

void ExtendedParticlePhysics::shuffleParticles() {
	//Collections.shuffle(Arrays.asList(particles));
}