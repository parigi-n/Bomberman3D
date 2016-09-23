#include "Exception.hh"

void openError(const std::string file, irr::IrrlichtDevice *device)
{
  std::cerr << "\033[1;31m" << "[FATAL ERROR] " << "\033[0m" << "Could not open file \"" << file << "\". Program exited." << std::endl;
  device->closeDevice();
  exit(-1);
}

void openError(const std::string file)
{
  std::cerr << "\033[1;31m" << "[FATAL ERROR] " << "\033[0m" << "Could not open file \"" << file << "\". Program exited." << std::endl;
  exit(-1);
}

void messageError(const std::string message, irr::IrrlichtDevice *device)
{
  std::cerr << "\033[1;31m" << "[FATAL ERROR] " << "\033[0m" << "\"" << message << "\". Program exited." << std::endl;
  device->closeDevice();
  exit(-1);
}

void messageError(const std::string message)
{
  std::cerr << "\033[1;31m" << "[FATAL ERROR] " << "\033[0m" << "\"" << message << "\". Program exited." << std::endl;
  exit(-1);
}
