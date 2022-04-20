#include <stdio.h>
#include <stdbool.h>
#include <conio.h>

#include <SFML/Audio.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/OpenGL.h>

#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

void window_display(sfSound* sound)
{
	//music
	int isPlaying = 0, isloop = 0;
	float volume = 100, speed = 1, current_soundPos, shift = 2;
	int isStop = 0, isPlay = 0, isLeftBtn = 0, isRightBtn = 0, isPause = 0, isMinusBtn = 0, isPlus = 0;

	//texture position
	struct buttons {
		sfVector2f posbtnleft;
		sfVector2f posbtnright;
		sfVector2f posbtnpause;
		sfVector2f posbtnreply;
		sfVector2f posbtnminus;
		sfVector2f posbtnstop;
		sfVector2f posbtnplus;
	}pos;
	pos.posbtnleft.x = 120; pos.posbtnleft.y = 150;
	pos.posbtnright.x = 240; pos.posbtnright.y = 150;
	pos.posbtnpause.x = 180; pos.posbtnpause.y = 150;
	pos.posbtnreply.x = 380; pos.posbtnreply.y = 154;
	pos.posbtnminus.x = 375; pos.posbtnminus.y = 100;
	pos.posbtnplus.x = 375; pos.posbtnplus.y = 10;
	pos.posbtnstop.x = 50; pos.posbtnstop.y = 150;

	//window creation
	sfVideoMode mode = { 432, 200, 32 };
	sfRenderWindow* main_window = sfRenderWindow_create(mode, "SoundPlayer", sfClose, NULL);
	sfColor bactgr = sfColor_fromRGB(41, 47, 54); //window color
	
	//creat textures
	sfFloatRect btn = { 0,0,0,0 };
	sfFloatRect btnRep = { 0,0,0,0 };

		//leftbtn
	sfTexture* btnleft = sfTexture_createFromFile("Texture\\btnleft.png", &btn);
	sfSprite* spritebtnleft = sfSprite_create();
	sfSprite_setTexture(spritebtnleft, btnleft, true);
	sfSprite_setPosition(spritebtnleft, pos.posbtnleft);
	sfTexture* btnlefteff = sfTexture_createFromFile("Texture\\btnlefteff.png", &btn);
	sfSprite* spritebtnlefteff = sfSprite_create();
	sfSprite_setTexture(spritebtnlefteff, btnlefteff, true);
	sfSprite_setPosition(spritebtnlefteff, pos.posbtnleft);
		//rightbtn
	sfTexture* btnright = sfTexture_createFromFile("Texture\\btnright.png", &btn);
	sfSprite* spritebtnright = sfSprite_create();
	sfSprite_setTexture(spritebtnright, btnright, true);
	sfSprite_setPosition(spritebtnright, pos.posbtnright);
	sfTexture* btnrighteff = sfTexture_createFromFile("Texture\\btnrighteff.png", &btn);
	sfSprite* spritebtnrighteff = sfSprite_create();
	sfSprite_setTexture(spritebtnrighteff, btnrighteff, true);
	sfSprite_setPosition(spritebtnrighteff, pos.posbtnright);
		//pausebtn
	sfTexture* btnpause = sfTexture_createFromFile("Texture\\pausebtn.png", &btn);
	sfSprite* spritebtnpause = sfSprite_create();
	sfSprite_setTexture(spritebtnpause, btnpause, true);
	sfSprite_setPosition(spritebtnpause, pos.posbtnpause);
	sfTexture* btnpauseeff = sfTexture_createFromFile("Texture\\pausebtneff.png", &btn);
	sfSprite* spritebtnpauseeff = sfSprite_create();
	sfSprite_setTexture(spritebtnpauseeff, btnpauseeff, true);
	sfSprite_setPosition(spritebtnpauseeff, pos.posbtnpause);
		//playbtn
	sfTexture* btnplay = sfTexture_createFromFile("Texture\\playbtn.png", &btn);
	sfSprite* spritebtnplay = sfSprite_create();
	sfSprite_setTexture(spritebtnplay, btnplay, true);
	sfSprite_setPosition(spritebtnplay, pos.posbtnpause);
	sfTexture* btnplayeff = sfTexture_createFromFile("Texture\\playbtneff.png", &btn);
	sfSprite* spritebtnplayeff = sfSprite_create();
	sfSprite_setTexture(spritebtnplayeff, btnplayeff, true);
	sfSprite_setPosition(spritebtnplayeff, pos.posbtnpause);
		//replybtn
	sfTexture* btnreply = sfTexture_createFromFile("Texture\\reply.png", &btnRep);
	sfSprite* spritebtnreply = sfSprite_create();
	sfSprite_setTexture(spritebtnreply, btnreply, true);
	sfSprite_setPosition(spritebtnreply, pos.posbtnreply);
	sfTexture* btnreplyeff = sfTexture_createFromFile("Texture\\replyeff.png", &btnRep);
	sfSprite* spritebtnreplyeff = sfSprite_create();
	sfSprite_setTexture(spritebtnreplyeff, btnreplyeff, true);
	sfSprite_setPosition(spritebtnreplyeff, pos.posbtnreply);
		//volumebtn-
	sfTexture* btnminus= sfTexture_createFromFile("Texture\\minus.png", &btnRep);
	sfSprite* spritebtnminus = sfSprite_create();
	sfSprite_setTexture(spritebtnminus, btnminus, true);
	sfSprite_setPosition(spritebtnminus, pos.posbtnminus);
	sfTexture* btnminuseff = sfTexture_createFromFile("Texture\\minuseff.png", &btnRep);
	sfSprite* spritebtnminuseff = sfSprite_create();
	sfSprite_setTexture(spritebtnminuseff, btnminuseff, true);
	sfSprite_setPosition(spritebtnminuseff, pos.posbtnminus);
		//volumebtn+
	sfTexture* btnplus = sfTexture_createFromFile("Texture\\plus.png", &btnRep);
	sfSprite* spritebtnplus = sfSprite_create();
	sfSprite_setTexture(spritebtnplus, btnplus, true);
	sfSprite_setPosition(spritebtnplus, pos.posbtnplus);
	sfTexture* btnpluseff = sfTexture_createFromFile("Texture\\pluseff.png", &btnRep);
	sfSprite* spritebtnpluseff = sfSprite_create();
	sfSprite_setTexture(spritebtnpluseff, btnpluseff, true);
	sfSprite_setPosition(spritebtnpluseff, pos.posbtnplus);
		//stopbtn
	sfTexture* btnstop = sfTexture_createFromFile("Texture\\stopbtn.png", &btnRep);
	sfSprite* spritebtnstop = sfSprite_create();
	sfSprite_setTexture(spritebtnstop, btnstop, true);
	sfSprite_setPosition(spritebtnstop, pos.posbtnstop);
	sfTexture* btnstopeff = sfTexture_createFromFile("Texture\\stopbtneff.png", &btnRep);
	sfSprite* spritebtnstopeff = sfSprite_create();
	sfSprite_setTexture(spritebtnstopeff, btnstopeff, true);
	sfSprite_setPosition(spritebtnstopeff, pos.posbtnstop);

	//get sprite sizes
	sfVector2u sizesprbtnleft = sfTexture_getSize(btnleft);
	sfVector2u sizesprbtnpause = sfTexture_getSize(btnpause);
	sfVector2u sizesprbtnminus = sfTexture_getSize(btnminus);
	sfVector2u sizesprbtnplus = sfTexture_getSize(btnplus);
	sfVector2u sizesprbtnright = sfTexture_getSize(btnright);
	sfVector2u sizesprbtnreply = sfTexture_getSize(btnreply);
	sfVector2u sizesprbtnstop = sfTexture_getSize(btnstop);

	while (sfWindow_isOpen(main_window))
	{
		sfEvent Event;
		while (sfRenderWindow_pollEvent(main_window, &Event)) 
		{
			if (Event.type == sfEvtClosed) {
				sfRenderWindow_close(main_window);
			}

				//button reaction
			sfVector2i posm = sfMouse_getPosition(main_window); //mouse position
			
				//speed
			if ((posm.x > pos.posbtnleft.x && posm.x < (pos.posbtnleft.x + sizesprbtnleft.x) && posm.y > pos.posbtnleft.y && posm.y < (pos.posbtnleft.y + sizesprbtnleft.y))) {
				isLeftBtn = 1;
				if (sfMouse_isButtonPressed(sfMouseLeft)) {
					isLeftBtn = 0;
					speed -= 0.1;
					sfSound_setPitch(sound, speed);
				}
			}
			else isLeftBtn = 0;
			if ((posm.x > pos.posbtnright.x && posm.x < (pos.posbtnright.x + sizesprbtnright.x) && posm.y > pos.posbtnright.y && posm.y < (pos.posbtnright.y + sizesprbtnright.y))) {
				isRightBtn = 1;
				if (sfMouse_isButtonPressed(sfMouseLeft)) {
					isRightBtn = 0;
					speed += 0.1;
					sfSound_setPitch(sound, speed);
				} 
			}
			else isRightBtn = 0;
				//loop
			if ((posm.x > pos.posbtnreply.x && posm.x < (pos.posbtnreply.x + sizesprbtnreply.x) && posm.y > pos.posbtnreply.y && posm.y < (pos.posbtnreply.y + sizesprbtnreply.y)) && sfMouse_isButtonPressed(sfMouseLeft)) {
				isloop = !isloop;
				sfSound_setLoop(sound, isloop);
			}
				//volume
			if ((posm.x > pos.posbtnminus.x && posm.x < (pos.posbtnminus.x + sizesprbtnminus.x) && posm.y > pos.posbtnminus.y && posm.y < (pos.posbtnminus.y + sizesprbtnminus.y))) {
				isMinusBtn = 1;
				if (sfMouse_isButtonPressed(sfMouseLeft)) {
					isMinusBtn = 0;
					volume -= 10;
					if (volume < 0)
						volume = 0;
					sfSound_setVolume(sound, volume);
				}
			}
			else isMinusBtn = 0;
			if ((posm.x > pos.posbtnplus.x && posm.x < (pos.posbtnplus.x + sizesprbtnplus.x) && posm.y > pos.posbtnplus.y && posm.y < (pos.posbtnplus.y + sizesprbtnplus.y))) {
				isPlus = 1;
				if (sfMouse_isButtonPressed(sfMouseLeft)) {
					isPlus = 0;
					volume += 10;
					if (volume > 100)
						volume = 100;
					sfSound_setVolume(sound, volume);
				}
			}
			else isPlus = 0;
				//play and pause
			if (sfKeyboard_isKeyPressed(sfKeySpace)) {
				if (!isPlaying)
					sfSound_play(sound);
				else
					sfSound_pause(sound);
				isPlaying = !isPlaying;
				sfSleep(sfSeconds(0.5));
			}
			if ((posm.x > pos.posbtnpause.x && posm.x < (pos.posbtnpause.x + sizesprbtnpause.x) && posm.y > pos.posbtnpause.y && posm.y < (pos.posbtnpause.y + sizesprbtnpause.y))) {
				if (isPlaying == 0) isPlay = 1;
				if (isPlaying == 1) isPause = 1;
				if (sfMouse_isButtonPressed(sfMouseLeft)) {
					if (!isPlaying)
						sfSound_play(sound);
					else
						sfSound_pause(sound);
					isPlaying = !isPlaying;
				}
			}
			else { 
				if (isPlaying == 0) isPlay = 0;
				if (isPlaying == 1) isPause = 0;
			}
				//stop
			if ((posm.x > pos.posbtnstop.x && posm.x < (pos.posbtnstop.x + sizesprbtnstop.x) && posm.y > pos.posbtnstop.y && posm.y < (pos.posbtnstop.y + sizesprbtnstop.y))) {
				isStop = 1;
				if (sfMouse_isButtonPressed(sfMouseLeft)) {
					isStop = 0;
					sfSound_stop(sound);
					isPlaying = 0;
				}
			}
			else isStop = 0;
				//sound shift
			if (sfKeyboard_isKeyPressed(sfKeyRight)) {
				sfTime spos = sfSound_getPlayingOffset(sound);
				current_soundPos = sfTime_asSeconds(spos);
				current_soundPos = current_soundPos + shift;
				spos = sfSeconds(current_soundPos);
				sfSound_setPlayingOffset(sound, spos);
			}
			if (sfKeyboard_isKeyPressed(sfKeyLeft)) {
				sfTime spos = sfSound_getPlayingOffset(sound);
				current_soundPos = sfTime_asSeconds(spos);
				current_soundPos = current_soundPos - shift;
				if (current_soundPos < 0) current_soundPos = 0;
				spos = sfSeconds(current_soundPos);
				sfSound_setPlayingOffset(sound, spos);
			}
		}
		if (sfSound_getStatus(sound) == sfStopped) {
			isPlaying = 0;
		}

			//Render Textures and Window
		sfRenderWindow_clear(main_window, bactgr);

		if (isLeftBtn == 0) sfRenderWindow_drawSprite(main_window, spritebtnleft, NULL);
		else if (isLeftBtn == 1) sfRenderWindow_drawSprite(main_window, spritebtnlefteff, NULL);
		if (isPlus == 0) sfRenderWindow_drawSprite(main_window, spritebtnplus, NULL);
		else if (isPlus == 1) sfRenderWindow_drawSprite(main_window, spritebtnpluseff, NULL);
		if (isMinusBtn == 0) sfRenderWindow_drawSprite(main_window, spritebtnminus, NULL);
		else if (isMinusBtn == 1) sfRenderWindow_drawSprite(main_window, spritebtnminuseff, NULL);
		if (isRightBtn == 0) sfRenderWindow_drawSprite(main_window, spritebtnright, NULL);
		else if (isRightBtn == 1) sfRenderWindow_drawSprite(main_window, spritebtnrighteff, NULL);
		if (isStop == 0) sfRenderWindow_drawSprite(main_window, spritebtnstop, NULL);
		else if (isStop == 1) sfRenderWindow_drawSprite(main_window, spritebtnstopeff, NULL);
		if (isPlaying == 0) {
			if (isPlay == 0) sfRenderWindow_drawSprite(main_window, spritebtnpause, NULL);
			else if (isPlay == 1) sfRenderWindow_drawSprite(main_window, spritebtnpauseeff, NULL);
		}
		else if (isPlaying == 1) { 
			if (isPause == 0) sfRenderWindow_drawSprite(main_window, spritebtnplay, NULL);
			else if (isPause == 1) sfRenderWindow_drawSprite(main_window, spritebtnplayeff, NULL);
		}
		if(isloop == 0) sfRenderWindow_drawSprite(main_window, spritebtnreply, NULL);
		else if(isloop == 1) sfRenderWindow_drawSprite(main_window, spritebtnreplyeff, NULL);
		sfRenderWindow_display(main_window);
	}
	sfRenderWindow_destroy(main_window);
}

int main(int argc, char* argv[])
{
	sfSoundBuffer* buffer = sfSoundBuffer_createFromFile(argv[1]);
	if (!buffer)
	{
		return -1;
	}
	sfSound* sound = sfSound_create();
	sfSound_setBuffer(sound, buffer);
	window_display(sound);
	sfSound_stop(sound);
	return 0;
}