//
// (c) 2024 S-Patriarch
//

#include <cstdlib>
#include <cstdint>
#include <iostream>
//------------------------------------------------------------------------------
void unpack_bools(std::uint8_t p, bool& b1, bool& b2, 
                  bool& b3, bool& b4, bool& b5, 
                  bool& b6, bool& b7, bool& b8) 
   // функция распаковывает 1 байт на 8 значений типа bool
{
   b1 = (p>>7)&1;
   b2 = (p>>6)&1;
   b3 = (p>>5)&1;
   b4 = (p>>4)&1;
   b5 = (p>>3)&1;
   b6 = (p>>2)&1;
   b7 = (p>>1)&1;
   b8 = p&1;
}
////////////////////////////////////////////////////////////////////////////////
int main()
{
   using std::cout;

   std::uint8_t p {170};
   bool b1, b2, b3, b4, b5, b6, b7, b8;

   ::unpack_bools(p,b1,b2,b3,b4,b5,b6,b7,b8);

   cout << "Unpacked values:\n";
   cout << "- b1: " << b1 << '\n';
   cout << "- b2: " << b2 << '\n';
   cout << "- b3: " << b3 << '\n';
   cout << "- b4: " << b4 << '\n';
   cout << "- b5: " << b5 << '\n';
   cout << "- b6: " << b6 << '\n';
   cout << "- b7: " << b7 << '\n';
   cout << "- b8: " << b8 << '\n';

   std::exit(EXIT_SUCCESS);
}
