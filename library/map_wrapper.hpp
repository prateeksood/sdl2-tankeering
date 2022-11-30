#include <string>
#include <map>

#define of :

template <typename T>
class MapWrapper{
private:
  std::map<const char *, T> data;

public:
  MapWrapper(){}
  T &operator[](const char *key){
    return data.at(key);
  }
  const size_t size() const {
    return data.size();
  }
  bool has(const char *key){
    return data.find(key) != data.end();
  }
  template <typename ...Args>
  void set(const char * key, Args &&...args){
    data.emplace(
      std::piecewise_construct,
      std::forward_as_tuple(key),
      std::forward_as_tuple(args...)
    );
  }
  void forEach(void (*callback)(T &, const char *)){
    for(auto it = data.begin(); it != data.end(); it++)
      callback(it->second, it->first);
  }

};