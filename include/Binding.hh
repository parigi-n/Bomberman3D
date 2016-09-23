#ifndef BINDING_HH
# define BINDING_HH

# include <irrlicht.h>
# include "Item.hh"

class Binding
{
public:
  Binding(irr::EKEY_CODE upKey, irr::EKEY_CODE downKey, irr::EKEY_CODE leftKey,
	  irr::EKEY_CODE rightKey, irr::EKEY_CODE actionKey);
  Binding();
  const irr::EKEY_CODE&	up() const;
  const irr::EKEY_CODE&	down() const;
  const irr::EKEY_CODE&	left() const;
  const irr::EKEY_CODE&	right () const;
  const irr::EKEY_CODE&	action() const;
private:
  irr::EKEY_CODE	upKey;
  irr::EKEY_CODE	downKey;
  irr::EKEY_CODE	leftKey;
  irr::EKEY_CODE	rightKey;
  irr::EKEY_CODE	actionKey;
};

#endif
