#include "AppClass.h"
#include <assert.h>

#define DRAW_ALL_INSTANCES false

// Magic constants (????) and directions
static const float UP_SCALE   = 0.435f;
static const float DIAG_SCALE = 0.705f;
static const vector3 Direction_UP         = glm::normalize( vector3(  0,  1, 0 ) );
static const vector3 Direction_DOWN_LEFT  = glm::normalize( vector3( -1, -1, 0 ) );
static const vector3 Direction_DOWN_RIGHT = glm::normalize( vector3(  1, -1, 0 ) );

// Generates three triangles based off of the given center and scale
void AppClass::GenerateThreeTriangles( std::vector<matrix4>& matrices, vector3 center, float scale )
{
    matrix4 scaleMatrix = glm::scale( scale, scale, scale );
    matrices.push_back( glm::translate( center + scale * UP_SCALE * Direction_UP )           * scaleMatrix );
    matrices.push_back( glm::translate( center + scale * DIAG_SCALE * Direction_DOWN_LEFT )  * scaleMatrix );
    matrices.push_back( glm::translate( center + scale * DIAG_SCALE * Direction_DOWN_RIGHT ) * scaleMatrix );
}

// The recursive helper for generating three triangles
void AppClass::RecursiveGenerateThreeTriangles( std::vector<matrix4>& matrices, vector3 center, float scale, int iterations )
{
    if ( iterations <= 1 )
    {
        GenerateThreeTriangles( matrices, center, scale );
    }
    else
    {
        RecursiveGenerateThreeTriangles( matrices, center + scale * UP_SCALE   * Direction_UP,         scale * 0.5f, iterations - 1 );
        RecursiveGenerateThreeTriangles( matrices, center + scale * DIAG_SCALE * Direction_DOWN_LEFT,  scale * 0.5f, iterations - 1 );
        RecursiveGenerateThreeTriangles( matrices, center + scale * DIAG_SCALE * Direction_DOWN_RIGHT, scale * 0.5f, iterations - 1 );
    }
}

// Calculates the world matrices of a smaller triangle to draw a Sierpinski triangle in the given number of iterations
void AppClass::CalculateSierpinksiTriangleMatrices( std::vector<matrix4>& matrices, float scale, int iterations )
{
    // Clear the matrix array and reserve memory
    matrices.clear();

    // Generate the triangles!
    if ( iterations <= 0 )
    {
        scale *= 2.0f;
        matrices.push_back( glm::scale( scale, scale, scale ) );
    }
    else
    {
        RecursiveGenerateThreeTriangles( matrices, vector3( 0, 0, 0 ), scale, iterations );
    }
}

// Create a new app class
AppClass::AppClass( HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow )
    : super( hInstance, lpCmdLine, nCmdShow )
    , _iterations( 3 )
    , _triangleScale( 1.0f )
{
}

// Initialize the window
void AppClass::InitWindow( String a_sWindowName )
{
    super::InitWindow( "Sierpinksi Triangle | Richard Selneck and Michelle Leadley" );
}

// Initialize custom variables
void AppClass::InitVariables()
{
    //Reserve Memory for a MyMeshClass object
    _mesh = std::make_shared<MyMesh>();
    assert( _mesh.get() != nullptr && "Failed to allocate memory for the mesh!" );

    // Add the triangle points
    const float length = 1.0f;
    const float height = length * glm::sqrt( 3.0f ) / 2.0f;
    _mesh->AddVertexPosition( vector3(  0.0f,           0.5f * height, 0.0f ) );
    _mesh->AddVertexPosition( vector3( -0.5f * length, -0.5f * length, 0.0f ) );
    _mesh->AddVertexPosition( vector3(  0.5f * length, -0.5f * length, 0.0f ) );

    // Add the triangle colors
    _mesh->AddVertexColor( REWHITE );
    _mesh->AddVertexColor( REWHITE );
    _mesh->AddVertexColor( REWHITE );

    // Compile the triangle mesh
    _mesh->CompileOpenGL3X();


    // Create the instance matrices
    SetNumberOfIterations( 3, 2.0f );


    /* _matrices.resize( 200 );
    for ( int i = 0; i < static_cast<int>( _matrices.size() ); ++i )
    {
        _matrices[ i ] = glm::translate( vector3( 0.0f, 0.0f, 1.0f * -i ) )
                       * glm::rotate( i * 5.0f, REAXISZ );
    } */
}

// Sets the number of Sierpinski iterations
void AppClass::SetNumberOfIterations( int newIterations, float newScale )
{
    if ( DRAW_ALL_INSTANCES )
    {
        _iterations = glm::clamp( newIterations, 0, 12 );
        _triangleScale = glm::clamp( newScale, 0.5f, 20.0f );
    }
    else
    {
        _iterations = glm::clamp( newIterations, 0, 5 );
        _triangleScale = glm::clamp( newScale, 0.5f, 8.0f );
    }
    CalculateSierpinksiTriangleMatrices( _matrices, _triangleScale, _iterations );
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
}

// Draws all instances of a mesh
static void DrawAllInstancesOfMesh( MyMesh* mesh, std::vector<matrix4>& matrices )
{
    const int count = static_cast<int>( matrices.size() );
    int index = 0;
    int drawCount = 0;
    while ( index < count )
    {
        // Get the number of instances to draw, then draw them
        int numToDraw = glm::min( count, 250 );
        mesh->RenderList( glm::value_ptr( matrices[ index ] ), numToDraw );
        drawCount++;

        // Increment the index
        index += numToDraw;
    }

    printf( "\rNumber of draw calls: %d        ", drawCount );
}

// Render the scene
void AppClass::Display()
{
    // Clear the window
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    // Draw the grid
    //m_pGrid->Render( 1.0f, REAXIS::XZ );

    // Instance render the mesh
    if ( DRAW_ALL_INSTANCES )
    {
        // Draw all instances (will be several draw calls)
        DrawAllInstancesOfMesh( _mesh.get(), _matrices );
    }
    else
    {
        // Draw 250 instances (one draw call)
        _mesh->RenderList( glm::value_ptr( _matrices[ 0 ] ), static_cast<int>( _matrices.size() ) );
    }

    // Swap the OpenGL buffers
    m_pGLSystem->GLSwapBuffers();
}
