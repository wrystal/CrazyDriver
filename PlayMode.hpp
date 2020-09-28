#include "Mode.hpp"

#include "Scene.hpp"
#include "Sound.hpp"
#include "Mesh.hpp"

#include <glm/glm.hpp>

#include <vector>
#include <deque>

struct PlayMode : Mode {
	PlayMode();
	virtual ~PlayMode();

	//functions called by main loop:
	virtual bool handle_event(SDL_Event const &, glm::uvec2 const &window_size) override;
	virtual void update(float elapsed) override;
	virtual void draw(glm::uvec2 const &drawable_size) override;

	static constexpr float LANE_WIDTH = 1.0;

	struct RoadTiles {
		RoadTiles(PlayMode *p, int num_tiles);
		void attachToDrawable();
		void detachFromDrawable();
		void update(float elapsed);
		PlayMode *p;
		int num_tiles;
		std::list<Scene::Transform> transforms;
		std::vector<decltype(Scene::drawables)::iterator> drawable_iterators;
		const Mesh *mesh;
	} road_tiles{this, 100};

	struct Player {
		Player(Scene *s);
		void goLeft() { target_lane_ = std::max(-1, target_lane_ - 1); }
		void goRight() { target_lane_ = std::min(1, target_lane_ + 1); };
		void attachToDrawable();
		void detachFromDrawable(); // TODO(xiaoqiao): not implemented -- is this really needed?
		void update(float elapsed);
		float position_ = 0;
		int target_lane_ = 0;
		const Mesh *mesh_;
		Scene *scene_;
		Scene::Transform transform_;
		static constexpr int PLAYER_SPEED = 10;
	} player{&this->scene};

	//----- game state -----

	//input tracking:
	struct Button {
		uint8_t downs = 0;
		uint8_t pressed = 0;
	} left, right, down, up;

	//local copy of the game scene (so code can change it during gameplay):
	Scene scene;

	//hexapod leg to wobble:
//	Scene::Transform *hip = nullptr;
//	Scene::Transform *upper_leg = nullptr;
//	Scene::Transform *lower_leg = nullptr;
//	glm::quat hip_base_rotation;
//	glm::quat upper_leg_base_rotation;
//	glm::quat lower_leg_base_rotation;
//	float wobble = 0.0f;

//	glm::vec3 get_leg_tip_position();

	//music coming from the tip of the leg (as a demonstration):
//	std::shared_ptr< Sound::PlayingSample > leg_tip_loop;
	
	//camera:
	Scene::Camera *camera = nullptr;

};
