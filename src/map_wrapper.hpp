#include <string>
#include <map>

#define of :

template <typename T>
class MapWrapper{
private:
  std::map<std::string, T> data;

public:
  MapWrapper(){}
  T &operator[](std::string key){
    return data[key];
  }
  void forEach(void (*callback)(T &, const std::string)){
    for(std::pair<const std::string, T &> _data of data)
      callback(_data.second, _data.first);
  }

};