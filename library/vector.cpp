#ifndef VECTOR_CPP
#define VECTOR_CPP

#include <cmath>
#include <cstdlib>
#include <iostream>
#include "raylib.h"

class Vector: public Vector2{
public:
  Vector(float x = .0f, float y = .0f): Vector2{x, y}{}
  Vector* set(float x, float y) {
    this->x = x;
    this->y = y;
    return this;
  }
  Vector* set(int x, int y) {
    this->x = (float) x;
    this->y = (float) y;
    return this;
  }
  Vector* set(Vector *vector) {
    this->x = vector->x;
    this->y = vector->y;
    return this;
  }
  Vector* add(Vector *vector) {
    this->x += vector->x;
    this->y += vector->y;
    return this;
  }
  Vector* subtract(Vector *vector) {
    this->x -= vector->x;
    this->y -= vector->y;
    return this;
  }
  Vector* scalar(Vector *vector) {
    this->x *= vector->x;
    this->y *= vector->y;
    return this;
  }
  Vector* divide(Vector *vector) {
    this->x /= vector->x;
    this->y /= vector->y;
    return this;
  }
  float dot(Vector *vector){
    return this->x * vector->x + this->y * vector->y;
  }
  float cross(Vector *vector){
    return this->x * vector->y - this->y * vector->x;
  }
  float mag(){
    return std::sqrt(this->magSq());
  }
  float magSq(){
    return this->x * this->x + this->y * this->y;
  }
  Vector* normalise(){
    const float magnitude = this->mag();
    return this->scale(magnitude == 0 ? 0 : 1 / magnitude);
  }
  Vector* scale(float value) {
    this->x *= value;
    this->y *= value;
    return this;
  }
  Vector* scaleX(float value) {
    this->x *= value;
    return this;
  }
  Vector* scaleY(float value) {
    this->y *= value;
    return this;
  }
  Vector* invert(){
    return this->scale(-1);
  }
  Vector* floor(){
    this->x = std::floor(this->x);
    this->y = std::floor(this->y);
    return this;
  }
  Vector signVector(){
    return Vector(
      std::signbit(this->x) == false ? 1.0f : -1.0f,
      std::signbit(this->y) == false ? 1.0f : -1.0f);
  }
  Vector normalVector(){
    Vector vector = Vector(-this->y, this->x);
    vector.normalise();
    return vector;
  }
  Vector2 toVector2(){
    return Vector2{this->x, this->y};
  }
  static Vector from(Vector *vector) {
    return Vector(vector->x, vector->y);
  }
  static Vector zero(){
    return Vector(0, 0);
  }
  static Vector unit(){
    return Vector(1, 1);
  }
  static Vector random(){
    const float dirX = std::floor(std::rand()*2) == 0 ? 1.0f : -1.0f;
    const float dirY = std::floor(std::rand()*2) == 0 ? 1.0f : -1.0f;
    return Vector(std::rand() * dirX, std::rand() * dirY);
  }
  static Vector floor(Vector *vector){
    return *Vector::from(vector).floor();
  }
  static Vector normalise(Vector *vector){
    return *Vector::from(vector).normalise();
  }
  static Vector scale(Vector *vector, float value) {
    return *Vector::from(vector).scale(value);
  }
  static Vector scaleX(Vector *vector, float value) {
    return *Vector::from(vector).scaleX(value);
  }
  static Vector scaleY(Vector *vector, float value) {
    return *Vector::from(vector).scaleY(value);
  }
  static float distanceSq(Vector* v1, Vector* v2) {
    const float dy = v1->y - v2->y;
    const float dx = v1->x - v2->x;
    return dy * dy + dx * dx;
  }
  static float distance(Vector* v1, Vector* v2) {
    return std::sqrt(Vector::distanceSq(v1, v2));
  }
  static Vector add(Vector* v1, Vector* v2) {
    return Vector(v1->x + v2->x, v1->y + v2->y);
  }
  static Vector subtract(Vector* v1, Vector* v2) {
    return Vector(v1->x - v2->x, v1->y - v2->y);
  }
  static Vector moveTowards(Vector *vector, Vector* target, float maxDistance){
    Vector result = Vector::zero();
    const float dx = target->x - vector->x;
    const float dy = target->y - vector->y;
    const float value = (dx*dx) + (dy*dy);

    if ((value == 0) || ((maxDistance >= 0) && (value <= maxDistance*maxDistance)))
      result = *target;

    const float dist = std::sqrt(value);

    result.x = vector->x + dx/dist*maxDistance;
    result.y = vector->y + dy/dist*maxDistance;
    return result;
  }

  static void log(Vector *vector){
    std::cout << "Vector{x: " << vector->x << ", y: " << vector->y << "}";
  }
};

#endif