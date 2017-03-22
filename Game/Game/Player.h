#include "Game.h"
#include <vector>
#include <math.h>
#define M_PI 3.14
using namespace sf;
class Player : public Drawable,
	Transformable
{
public:
	Player(void);
	~Player(void);

	enum Status {
		IDZ,
		STOJ
	};

	Vector2f getPosition();
	Status getStatus();

	void update(Vector2f mysz);

	void stop();
	void idz(Vector2f mysz);

protected:
	int klatka_animacji;

private:
	Sprite sprite;
	Texture texture;

	Status status;

	float speed;
	size_t frame;

	Clock anim_clock;

	virtual void draw(RenderTarget &target, RenderStates states) const;
};