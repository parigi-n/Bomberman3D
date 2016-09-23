#ifndef EXCEPTION_HH
#define EXCEPTION_HH

#include <irrlicht.h>
#include <string>
#include <iostream>

void openError(const std::string file, irr::IrrlichtDevice *device);
void openError(const std::string file);
void messageError(const std::string message, irr::IrrlichtDevice *device);
void messageError(const std::string message);

#endif
