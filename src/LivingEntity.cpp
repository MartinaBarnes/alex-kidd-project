#include "LivingEntity.h"

void LivingEntity::kill() {
	if (!alive) {
		return;
	}

	alive = false;
	onKilled();
}