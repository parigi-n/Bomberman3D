#include "Binding.hh"

Binding::Binding(irr::EKEY_CODE upKey, irr::EKEY_CODE downKey, irr::EKEY_CODE leftKey, irr::EKEY_CODE rightKey, irr::EKEY_CODE actionKey)
{
  this->upKey = upKey;
  this->downKey = downKey;
  this->leftKey = leftKey;
  this->rightKey = rightKey;
  this->actionKey = actionKey;
}

Binding::Binding()
{
}

const irr::EKEY_CODE&	Binding::up() const
{
  return (this->upKey);
}

const irr::EKEY_CODE&	Binding::down() const
{
  return (this->downKey);
}

const irr::EKEY_CODE&	Binding::left() const
{
  return (this->leftKey);
}

const irr::EKEY_CODE&	Binding::right () const
{
  return (this->rightKey);
}

const irr::EKEY_CODE&	Binding::action() const
{
  return (this->actionKey);
}
