#pragma once
#include "Org.h"
class Ground : public Org {
public:
	Ground();
	Ground(World*, const CORDS);
	void action() override;
	const void draw() override;
	const char get_sign() override;
	~Ground();
};
