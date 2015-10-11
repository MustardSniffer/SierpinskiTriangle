#include "AppClass.h"

void AppClass::InitWindow( String a_sWindowName )
{
    //Using Base InitWindow method
    super::InitWindow( "Instance Rendering - Example" );
}

void AppClass::InitVariables( void )
{
    //Reserve Memory for a MyMeshClass object
    m_pMesh = new MyMesh();

    m_pMesh->AddVertexPosition( vector3( 0.0f, 0.0f, 0.0f ) );
    m_pMesh->AddVertexPosition( vector3( 1.0f, 0.0f, 0.0f ) );
    m_pMesh->AddVertexPosition( vector3( 0.0f, 1.0f, 0.0f ) );

    m_pMesh->AddVertexColor( REGREEN );
    m_pMesh->AddVertexColor( RERED );
    m_pMesh->AddVertexColor( REBLUE );

    m_pMesh->CompileOpenGL3X();

    _matrices.resize( 200 );
    for ( int i = 0; i < static_cast<int>( _matrices.size() ); ++i )
    {
        _matrices[ i ] = glm::translate( vector3( 0.01f * -i, 0.0f, 1.0f * -i ) )
                       * glm::rotate( i * 5.0f, REAXISZ );
    }
}

void AppClass::Update( void )
{
    //Update the system so it knows how much time has passed since the last call
    m_pSystem->UpdateTime();

    //Is the arcball active?
    if ( m_bArcBall == true )
        m_qArcBall = ArcBall();

    //Is the first person camera active?
    if ( m_bFPC == true )
        CameraRotation();

    //Calculate Camera
    m_pCamera->CalculateView();

    //print info into the console
    printf( "FPS: %d            \r", m_pSystem->GetFPS() );//print the Frames per Second
}

void AppClass::Display( void )
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // clear the window

    m_pGrid->Render( 1.0f, REAXIS::XZ ); //renders the grid with a 100 scale

    // Instance render the mesh
    m_pMesh->RenderList( glm::value_ptr( _matrices[ 0 ] ), static_cast<int>( _matrices.size() ) );

    m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}
