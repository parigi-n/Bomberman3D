#ifndef IAI_HH_
# define IAI_HH_

# include "Map.hh"
# include "Entity.hh"

class	IAI
{
public:
  virtual Action::Action	Play() = 0;
};

#endif // IAI_HH_
