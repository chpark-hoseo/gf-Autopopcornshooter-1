
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
					//���������ġ�� �ִ� ������ �� �����ġ�� �ҷ���(SDL_LoadBMP)
					//�� �����ġ���� ȭ�鿡 ǥ���ϵ��� GPU�� �÷�����ϴ� ����� ���� texture�� ����
					m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
					SDL_FreeSurface(pTempSurface);

					SDL_QueryTexture(m_pTexture
						, NULL
						, NULL
						, &m_sourceRectangle.w
						, &m_sourceRectangle.h
					);//texture�� ũ�� ���ϱ�(���ϱ�?)

					m_destinationRectangle.w = m_sourceRectangle.w;
					m_destinationRectangle.h = m_sourceRectangle.h;
					m_destinationRectangle.x = m_sourceRectangle.x = 0;
					m_destinationRectangle.y = m_sourceRectangle.y = 0;
					//ũ�� ��� 0���� ����
				}
				else {
					printf("Texture Create Fail");
					return false;
					
				}

			}
			else {
				return false; // ������ ���� ����
			}
		}
		else {
			return false; // ������ ���� ����
		}
	}
	else {
		return false; // SDL �ʱ�ȭ ����
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
		m_destinationRectangle.x++;//�������� �̵�
	}
	else {
		m_destinationRectangle.x--;//�������� �̵�
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
