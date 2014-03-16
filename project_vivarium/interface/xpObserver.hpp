/* xpObserver.hpp */

#ifndef XPOBSERVER_HPP
#define XPOBSERVER_HPP

#include <string>

class XPObserver
{
   public:
      /* constructors   */
      virtual ~XPObserver(){}

      /* Methods  */
      virtual std::shared_ptr<long> getNextXPLimit(short lvl, std::string cat) = 0;
};

#endif
