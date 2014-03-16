/* xpObservable.hpp  */

#ifndef XPOBSERVABLE_HPP
#define XPOBSERVABLE_HPP

#include <xpObserver.hpp>

class XPObservable
{
   public:
      /* Constructors   */
      virtual ~XPObservable(){}

      /* Methods  */
      virtual void addXPObserver(std::shared_ptr<XPObserver> obs) = 0;
      virtual void removeXPObserver(std::shared_ptr<XPObserver> obs) = 0;
      virtual void needXPLimit(std::shared_ptr<XPObserver> obs) = 0;
};

#endif
