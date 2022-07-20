
#include "Game.h"

bool Game::init(const char* title, int xpos, int ypos, int width, int height, int flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		m_wHeight = height;
		m_wWidth = width;
		if (m_pWindow != 0) {
			m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);

			if (m_pRenderer != 0) {
				SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 255);

				SDL_Surface* pTempSurface = SDL_LoadBMP("assets/rider.bmp");
				if (pTempSurface) {
					printf("Texture Create Succes!");
					//보조기억장치에 있는 파일을 주 기억장치로 불러옴(SDL_LoadBMP)
					//주 기억장치에서 화면에 표시하도록 GPU에 올려출력하는 기능을 가진 texture을 생성
					m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
					SDL_FreeSurface(pTempSurface);

					SDL_QueryTexture(m_pTexture
						, NULL
						, NULL
						, &m_sourceRectangle.w
						, &m_sourceRectangle.h
					);//texture의 크기 구하기(정하기?)

					m_destinationRectangle.w = m_sourceRectangle.w;
					m_destinationRectangle.h = m_sourceRectangle.h;
					m_destinationRectangle.x = m_sourceRectangle.x = 0;
					m_destinationRectangle.y = m_sourceRectangle.y = 0;
					//크기 모두 0으로 설정
				}
				else {
					printf("Texture Create Fail");
					return false;
					
				}

			}
			else {
				return false; // 랜더러 생성 실패
			}
		}
		else {
			return false; // 윈도우 생성 실패
		}
	}
	else {
		return false; // SDL 초기화 실패
	}

	m_bRunning = true;
	return true;
}
void Game::update()
{
	//printf("Update!");
	//SDL_SetRenderDrawColor(m_pRenderer, rand() % 256, rand() % 256, rand() % 256, 255);
	SDL_Delay(10);

	
}

void Game::render()
{
	//printf("Render!");
	SDL_RenderClear(m_pRenderer);
	if (m_destinationRectangle.x < m_wWidth- m_destinationRectangle.w) {
		m_destinationRectangle.x++;//우측으로 이동
	}
	else {
		m_destinationRectangle.x--;//우측으로 이동
	}
	SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRectangle, &m_destinationRectangle);
	SDL_RenderPresent(m_pRenderer);
}

bool Game::running()
{
	return m_bRunning;
}

void Game::handleEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			m_bRunning = false;
			break;
		default:
			break;
		}
	}
}

void Game::clean()
{
	SDL_DestroyWindow(m_pWindow);
	SDL_DestroyRenderer(m_pRenderer);
	SDL_Quit();
}
