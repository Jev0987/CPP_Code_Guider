/*
 * @Descripttion: 
 * @Author: jev
 * @Date: 2025-12-03
 */

#include <string>
namespace
{
#ifndef _WIN32
template <typename T>
std::string get_type_name()
{
  int status = 0;
  std::unique_ptr<char[], void (*)(void *)> res{
    abi::__cxa_demangle(typeid(T).name(), nullptr, nullptr, &status), std::free};
  return (status == 0) ? res.get() : typeid(T).name();
}
#else
// not supported on Windows, use typeid directly
template <typename T>
std::string get_type_name()
{
  return typeid(T).name();
}
#endif
}  // namespace