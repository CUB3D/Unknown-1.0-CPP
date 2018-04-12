// Unknown Test.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"

#include <iostream>
#include "Unknown.h"
#include "Image.h"
#include "Input.h"
#include "Loader.h"
#include "UI2D.h"
#include "Log.h"
#include "PythonScript.h"

#include "Scene/SceneManager.h"
#include "Event/EventManager.h"


#ifdef _WIN32
int _tmain(int argc, _TCHAR* argv[])
#else
int main(int argc, char* argv[])
#endif
{
	//UK_CREATE_WINDOW();

    UK_PYTHON_LOAD_SCRIPT("Test");

	//UK_INIT_GAME();

	return 0;
}
