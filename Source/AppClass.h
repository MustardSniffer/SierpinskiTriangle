
/*----------------------------------------------
Programmer: Alberto Bobadilla (labigm@gmail.com)
Date: 2015/08
----------------------------------------------*/
#ifndef __APPLICATION_H_
#define __APPLICATION_H_

#include "RE\ReEngAppClass.h"
#include "MyMesh.h"
#include <memory>
#include <SFML\Graphics.hpp>
#include <vector>
//#include <chrono>

using namespace ReEng; //Using ReEng namespace to use all the classes in the dll

class AppClass : public ReEngAppClass
{
    typedef ReEngAppClass super;

    std::shared_ptr<MyMesh> _mesh;
    std::vector<matrix4> _matrices;
    int _iterations;
    float _triangleScale;

    /// <summary>
    /// Generates three triangles for the Sierpinski triangle.
    /// </summary>
    /// <param name="matrices">The list of matrices to add to.</param>
    /// <param name="center">The center of the three triangles.</param>
    /// <param name="scale">The scale to create the triangles at.</param>
    /// <param name="iterations">The number of iterations.</param>
    static void GenerateThreeTriangles( std::vector<matrix4>& matrices, vector3 center, float scale );

    /// <summary>
    /// The recursive helper for generating three triangles for the Sierpinski iteration.
    /// </summary>
    /// <param name="matrices">The list of matrices to add to.</param>
    /// <param name="center">The center of the three triangles.</param>
    /// <param name="scale">The scale to create the triangles at.</param>
    /// <param name="iterations"></param>
    static void RecursiveGenerateThreeTriangles( std::vector<matrix4>& matrices, vector3 center, float scale, int iterations );

    /// <summary>
    /// Calculates all Sierpinski triangle matrics.
    /// </summary>
    /// <param name="matrices">The matrices.</param>
    /// <param name="scale">The whole triangle scale</param>
    /// <param name="iterations">The total number of iterations.</param>
    static void CalculateSierpinksiTriangleMatrices( std::vector<matrix4>& matrices, float scale, int iterations );

    /// <summary>
    /// Sets the total number of Sierpinski iterations.
    /// </summary>
    /// <param name="newIterations">The new number of iterations.</param>
    /// <param name="newScale">The new scale.</param>
    void SetNumberOfIterations( int newIterations, float newScale );

public:
    /* Constructor */
    AppClass( HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow );

    /*
    InitWindow
    Initialize ReEng variables necessary to create the window
    */
    virtual void InitWindow( String a_sWindowName );

    /*
    InitVariables
    Initializes user specific variables, this is executed right after InitApplicationVariables,
    the purpose of this member function is to initialize member variables specific for this lesson
    */
    virtual void InitVariables();

    /*
    Update
    Updates the scene
    */
    virtual void Update();

    /*
    Display
    Displays the scene
    */
    virtual void Display();

    /*
    ProcessKeyboard
    Manage the response of key presses
    */
    virtual void ProcessKeyboard();

    /*
    ProcessMouse
    Manage the response of key presses and mouse position
    */
    virtual void ProcessMouse();
};

#endif //__APPLICATION_H_