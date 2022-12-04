#pragma once
#include <string>
#include <map>

template <typename K, typename T>
class MapWrapper{
private:
  std::map<K, T> data;

public:
  MapWrapper(){}
  T &operator[](K key){
    return data.at(key);
  }
  const size_t size() const {
    return data.size();
  }
  bool has(K key){
    return data.find(key) != data.end();
  }
  template <typename ...Args>
  void set(K key, Args &&...args){
    data.emplace(
      std::piecewise_construct,
      std::forward_as_tuple(key),
      std::forward_as_tuple(args...)
    );
  }
  void forEach(void (*callback)(T &, K)){
    for(auto it = data.begin(); it != data.end(); it++)
      callback(it->second, it->first);
  }

};