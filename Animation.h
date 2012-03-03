#include <SFML\Graphics.hpp>

class Animation
{
	private:
		sf::Texture* m_tex;
		sf::Sprite m_sprite;

		sf::Clock m_clock;

		int m_frames;
		int m_frame;

		float m_frameTime;

		bool m_animate;
	public:
		Animation(sf::Texture* nTex, int nFrames, float nFTime);
		void Update();

		sf::Sprite GetSprite(){return m_sprite;}

		void Stop(){m_animate = false;}
		void Play(){m_animate = true;}
};