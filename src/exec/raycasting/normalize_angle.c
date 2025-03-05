#include "../../../include/exec.h"

float normalize_angle(float angle)
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

// mets l'angle entre 0 et 2 * pi