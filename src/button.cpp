#include "button.h"

Button::Button() : 
	m_sizeIncrease(10)
{
}

//********************************************************

Button::~Button()
{
    SDL_DestroyTexture(m_text);
    SDL_DestroyTexture(m_texture);
}

//********************************************************

void Button::init(SDL_Renderer* t_renderer, TTF_Font* t_ttf, std::string t_btnName, float t_xPos, float t_yPos)
{
    m_textureRect.x = t_xPos;
    m_textureRect.y = t_yPos;

    initButtonTexture(t_renderer);
    initButtonText(t_renderer, t_ttf, t_btnName);
}

//********************************************************

void Button::setEntity(ECS::Entity& t_entity)
{
}

//********************************************************

void Button::draw(SDL_Renderer* t_renderer)
{
    SDL_RenderCopy(t_renderer, m_texture, NULL, &m_textureRect);
    SDL_RenderCopy(t_renderer, m_text, NULL, &m_textRect);
}

//********************************************************

bool Button::contains(int t_x, int t_y)
{
    if (t_x > m_textureRect.x && t_x < m_textureRect.x + m_textureRect.w)
        return (t_y > m_textureRect.y && t_y < m_textureRect.y + m_textureRect.h);

    return false;
}

//********************************************************

void Button::gainFocus()
{
    m_textureRect.w += m_sizeIncrease;
    m_textureRect.h += m_sizeIncrease;
    m_textureRect.x -= m_sizeIncrease / 2;
    m_textureRect.y -= m_sizeIncrease / 2;
}

//********************************************************

void Button::loseFocus()
{
    m_textureRect.w -= m_sizeIncrease;
    m_textureRect.h -= m_sizeIncrease;
    m_textureRect.x += m_sizeIncrease / 2;
    m_textureRect.y += m_sizeIncrease / 2;
}

//********************************************************

void Button::activate()
{
    if (m_debug != nullptr)
        m_debugFunc(m_debug);
}

//********************************************************

void Button::addDebugFunction(std::function<void(DebugInfo*)> t_func, DebugInfo* t_caller)
{
    m_debugFunc = t_func;
    m_debug = t_caller;
}

//********************************************************

void Button::initButtonTexture(SDL_Renderer* t_renderer)
{
    SDL_Surface* tempSurf = IMG_Load("assets/Button.png"); // load in the texture

    if (tempSurf == nullptr)
        printf(SDL_GetError());

    m_texture = SDL_CreateTextureFromSurface(t_renderer, tempSurf);

    SDL_QueryTexture(m_texture, NULL, NULL, &m_textureRect.w, &m_textureRect.h);

    if (m_texture == nullptr)
        printf(SDL_GetError());

    SDL_FreeSurface(tempSurf);
}

//********************************************************

void Button::initButtonText(SDL_Renderer* t_renderer, TTF_Font* t_ttf, std::string t_btnName)
{
    SDL_Surface* tempSurf = TTF_RenderText_Solid(t_ttf, t_btnName.c_str(), SDL_Color{ 255,255,255 });

    m_text = SDL_CreateTextureFromSurface(t_renderer, tempSurf);

    SDL_QueryTexture(m_text, NULL, NULL, &m_textRect.w, &m_textRect.h);

    m_textRect.x = m_textureRect.x + (m_textureRect.w / 2.0f) - (m_textRect.w / 2.0f);
    m_textRect.y = m_textureRect.y + (m_textureRect.h / 2.0f) - (m_textRect.h / 2.0f);

    if (m_text == nullptr)
        printf(SDL_GetError());

    SDL_FreeSurface(tempSurf);
}
