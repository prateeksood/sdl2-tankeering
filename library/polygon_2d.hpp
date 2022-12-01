#pragma once
#include <iostream>
#include <cmath>

typedef struct Vector2{
  int x, y;
  Vector2(): x(0), y(0){}
  Vector2(int x, int y): x(x), y(y){}
} Vector2;

class Line2D{
public:
  Vector2 point[2];
  Line2D(): point{ { 0, 0 }, { 0, 0 } }{}
  Line2D(Vector2 p0, Vector2 p1): point{ { p0.x, p0.y }, { p1.x, p1.y } }{}
  Line2D(int x1, int y1, int x2, int y2): point{ { x1, y1 }, { x2, y2 } }{}

  static bool isColliding(Line2D *line1, Line2D *line2){
    float denominator = ((line1->point[1].x - line1->point[0].x) * (line2->point[1].y - line2->point[0].y)) - ((line1->point[1].y - line1->point[0].y) * (line2->point[1].x - line2->point[0].x));
    float numerator1 = ((line1->point[0].y - line2->point[0].y) * (line2->point[1].x - line2->point[0].x)) - ((line1->point[0].x - line2->point[0].x) * (line2->point[1].y - line2->point[0].y));
    float numerator2 = ((line1->point[0].y - line2->point[0].y) * (line1->point[1].x - line1->point[0].x)) - ((line1->point[0].x - line2->point[0].x) * (line1->point[1].y - line1->point[0].y));

    if (denominator == 0)
      return numerator1 == 0 && numerator2 == 0;

    float r = numerator1 / denominator;
    float s = numerator2 / denominator;

    return (r >= 0 && r <= 1) && (s >= 0 && s <= 1);
  }
};

template <unsigned int sides>
class RegularPolygon2D{
private:
  float radius;
  unsigned int sideLength;
  float rotation = 0;
  Line2D edge[sides];
public:
  Vector2 position;
private:
  void generateEdges(){
    float step = M_PI * 2 / sides;
    // creating verticies
    Vector2 vertex[sides];
    int c = 0;
    for(float i = 0; i < M_PI * 2; i += step){
      int vx = cos(i + rotation) * radius + position.x;
      int vy = sin(i + rotation) * radius + position.y;
      vertex[c++] = { vx, vy };
    }
    // creating edges
    for(int e = 0; e < sides; e++){
      edge[e] = { Line2D(vertex[e], vertex[(e + 1) % sides]) };
    }
  }
public:
  RegularPolygon2D(int x, int y, unsigned int sideLength): sideLength(sideLength), position(x, y){
    radius = sideLength / (2 * cos(getAngle() / 2));
    generateEdges();
  }
  auto getSideLength(){
    return sideLength;
  }
  Vector2 &getVertex(unsigned int vertex){
    return edge[vertex].point[0];
  }
  Line2D &getEdge(unsigned int index){
    return edge[index];
  }
  void setRadius(unsigned int radius){
    this->radius = radius;
    sideLength = radius * cos(getAngle() / 2) * 2;
    generateEdges();
  }
  void setSideLength(unsigned int length){
    sideLength = length;
    radius = sideLength / (2 * cos(getAngle() / 2));
    generateEdges();
  }
  void setRotation(float angle){
    rotation = angle;
    generateEdges();
  }

  constexpr unsigned int getSides(){
    return sides;
  }
  inline float getAngle(){
    return (sides - 2) * M_PI / sides;
  }

  template <unsigned int S>
  bool isColliding(RegularPolygon2D<S> *polygon){
    for(int i = 0; i < sides; i++){
      for(int j = 0; j < polygon->getSides(); j++){
        if(Line2D::isColliding(&this->edge[i], &polygon->getEdge(j)))
          return true;
      }
    }
    return false;
  }

};