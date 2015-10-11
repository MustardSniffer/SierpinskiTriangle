#include "AppClass.h"
#include <assert.h>

// Initialize the window
void AppClass::InitWindow( String a_sWindowName )
{
    super::InitWindow( "Sierpinksi Triangle | Richard Selneck and Michelle Leadley" );
}

// Initialize custom variables
void AppClass::InitVariables()
{
    //Reserve Memory for a MyMeshClass object
    assert( ( _mesh = std::make_shared<MyMesh>() ) != nullptr && "Failed to allocate memory for the mesh!" );

    // Add the triangle points
    _mesh->AddVertexPosition( vector3(  0.0f,  0.5f, 0.0f ) );
    _mesh->AddVertexPosition( vector3( -0.5f, -0.5f, 0.0f ) );
    _mesh->AddVertexPosition( vector3(  0.5f, -0.5f, 0.0f ) );

    // Add the triangle colors
    _mesh->AddVertexColor( REGREEN );
    _mesh->AddVertexColor( RERED );
    _mesh->AddVertexColor( REBLUE );

    // Compile the triangle mesh
    _mesh->CompileOpenGL3X();


    // Create the instance matrices
    _matrices.resize( 200 );
    for ( int i = 0; i < static_cast<int>( _matrices.size() ); ++i )
    {
        _matrices[ i ] = glm::translate( vector3( 0.0f, 0.0f, 1.0f * -i ) )
                       * glm::rotate( i * 5.0f, REAXISZ );
    }
}

// Update the scene
void AppClass::Update()
{
    // Update the timer
    m_pSystem->UpdateTime();

    // Update the camera as either an arc-ball camera or an FPS camera
    if ( m_bArcBall )
    {
        m_qArcBall = ArcBall();
    }
    else if ( m_bFPC )
    {
        CameraRotation();
    }

    // Recalculate the camera's view matrix
    m_pCamera->CalculateView();

    // Print out the FPS
    printf( "FPS: %d            \r", m_pSystem->GetFPS() );
}

// Render the scene
void AppClass::Display()
{
    // Clear the window
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Draw the grid
    m_pGrid->Render( 1.0f, REAXIS::XZ );

    // Instance render the mesh
    _mesh->RenderList( glm::value_ptr( _matrices[ 0 ] ), static_cast<int>( _matrices.size() ) );

    // Swap the OpenGL buffers
    m_pGLSystem->GLSwapBuffers();
}
