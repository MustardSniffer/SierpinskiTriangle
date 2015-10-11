#include "AppClass.h"

void AppClass::ProcessKeyboard( void )
{
    bool bModifier = false;
    float fSpeed = 0.01f;

#define ON_KEY_PRESS_RELEASE(key, pressed_action, released_action) { \
            static bool bLast##key = false; \
            bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::key); \
            if(pressed) { \
                if ( !bLast##key ) pressed_action; \
                                    } \
                                                else if ( bLast##key ) released_action;\
            bLast##key = pressed; \
            }

    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::LShift ) || sf::Keyboard::isKeyPressed( sf::Keyboard::RShift ) )
        bModifier = true;



    // Move the camera
    if ( bModifier )
    {
        fSpeed *= 10.0f;
    }
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::W ) )
    {
        m_pCamera->MoveForward( fSpeed );
    }
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::S ) )
    {
        m_pCamera->MoveForward( -fSpeed );
    }
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::A ) )
    {
        m_pCamera->MoveSideways( -fSpeed );
    }
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::D ) )
    {
        m_pCamera->MoveSideways( fSpeed );
    }
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::E ) )
    {
        m_pCamera->MoveVertical( fSpeed );
    }
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Q ) )
    {
        m_pCamera->MoveVertical( -fSpeed );
    }
    m_pCamera->CalculateView();

    // Check if we should scale the triangles
    float newScale = _triangleScale;
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) )
    {
        newScale += 0.05f;
    }
    if ( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) )
    {
        newScale -= 0.05f;
    }

    // Quit on escape being pressed
    ON_KEY_PRESS_RELEASE( Escape, NULL, PostMessage( m_pWindow->GetHandler(), WM_QUIT, NULL, NULL ) );

    // Add or subtract from the number of iterations and change the scale
    int newIterations = _iterations;
    ON_KEY_PRESS_RELEASE( Add,      (void)0, ++newIterations );
    ON_KEY_PRESS_RELEASE( Subtract, (void)0, --newIterations );

    // Check if we need to update the number of subdivisions
    if ( newScale != _triangleScale || newIterations != _iterations )
    {
        SetNumberOfIterations( newIterations, newScale );
    }
}

void AppClass::ProcessMouse( void )
{
    m_bArcBall = false;
    m_bFPC = false;

    if ( sf::Mouse::isButtonPressed( sf::Mouse::Button::Middle ) )
        m_bArcBall = true;

    if ( sf::Mouse::isButtonPressed( sf::Mouse::Button::Right ) )
        m_bFPC = true;
}
