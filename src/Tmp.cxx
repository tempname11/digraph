#ifndef ___SRC_TMP___
#define ___SRC_TMP___
namespace Tmp {//////

constexpr size_t size = 256;
typedef char Buf[size];

namespace _private_ {
  Buf tmp;
}

template<typename F>
void with(F const &lambda) {
  lambda(_private_::tmp);
}

}////// namespace Tmp
#endif//___SRC_TMP___
