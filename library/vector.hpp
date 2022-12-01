#ifndef VECTOR_CPP
#define VECTOR_CPP

#include<cmath>
#include<cstdlib>

class Vector2{
public:
  float x, y;
  Vector2(float x = .0f, float y = .0f) {
    this->x = x;
    this->y = y;
  }
  Vector2* set(float x, float y) {
    this->x = x;
    this->y = y;
    return this;
  }
  Vector2* set(Vector2 *vector) {
    this->x = vector->x;
    this->y = vector->y;
    return this;
  }
  Vector2* add(Vector2 *vector) {
    this->x += vector->x;
    this->y += vector->y;
    return this;
  }
  Vector2* subtract(Vector2* vector) {
    this->x -= vector->x;
    this->y -= vector->y;
    return this;
  }
  Vector2* scalar(Vector2* vector) {
    this->x *= vector->x;
    this->y *= vector->y;
    return this;
  }
  Vector2* divide(Vector2* vector) {
    this->x /= vector->x;
    this->y /= vector->y;
    return this;
  }
  float dot(Vector2* vector){
    return this->x * vector->x + this->y * vector->y;
  }
  float cross(Vector2* vector){
    return this->x * vector->y - this->y * vector->x;
  }
  float mag(){
    return std::sqrt(this->magSq());
  }
  float magSq(){
    return this->x * this->x + this->y * this->y;
  }
  Vector2* normalise(){
    const float magnitude = this->mag();
    return this->scale(magnitude == 0 ? 0 : 1 / magnitude);
  }
  Vector2* scale(float value) {
    this->x *= value;
    this->y *= value;
    return this;
  }
  Vector2* scaleX(float value) {
    this->x *= value;
    return this;
  }
  Vector2* scaleY(float value) {
    this->y *= value;
    return this;
  }
  Vector2* invert(){
    return this->scale(-1);
  }
  Vector2* floor(){
    this->x = std::floor(this->x);
    this->y = std::floor(this->y);
    return this;
  }
  Vector2* signVector(){
    return new Vector2(std::signbit(this->x) == 0 ? 1 : -1, std::signbit(this->y) == 0 ? 1 : -1);
  }
  Vector2* normalVector(){
    Vector2* vector = new Vector2(-this->y, this->x);
    return vector->normalise();
  }
  static Vector2* from(Vector2* vector) {
    return new Vector2(vector->x, vector->y);
  }
  static Vector2* zero(){
    return new Vector2(0, 0);
  }
  static Vector2* unit(){
    return new Vector2(1, 1);
  }
  static Vector2* random(){
    const float dirX = std::floor(std::rand()*2) == 0 ? 1 : -1;
    const float dirY = std::floor(std::rand()*2) == 0 ? 1 : -1;
    return new Vector2(std::rand() * dirX, std::rand() * dirY);
  }
  static Vector2* floor(Vector2* vector){
    return Vector2::from(vector)->floor();
  }
  static Vector2* normalise(Vector2* vector){
    return Vector2::from(vector)->normalise();
  }
  static Vector2* scale(Vector2* vector, float value) {
    return Vector2::from(vector)->scale(value);
  }
  static Vector2* scaleX(Vector2* vector, float value) {
    return Vector2::from(vector)->scaleX(value);
  }
  static Vector2* scaleY(Vector2* vector, float value) {
    return Vector2::from(vector)->scaleY(value);
  }
  static float distanceSq(Vector2* v1, Vector2* v2) {
    const float dy = v1->y - v2->y;
    const float dx = v1->x - v2->x;
    return dy * dy + dx * dx;
  }
  static float distance(Vector2* v1, Vector2* v2) {
    return std::sqrt(Vector2::distanceSq(v1, v2));
  }
  static Vector2* add(Vector2* v1, Vector2* v2) {
    return new Vector2(v1->x + v2->x, v1->y + v2->y);
  }
  static Vector2* subtract(Vector2* v1, Vector2* v2) {
    return new Vector2(v1->x - v2->x, v1->y - v2->y);
  }
  static Vector2* moveTowards(Vector2* vector, Vector2* target, float maxDistance){
    Vector2* result = Vector2::zero();
    const float dx = target->x - vector->x;
    const float dy = target->y - vector->y;
    const float value = (dx*dx) + (dy*dy);

    if ((value == 0) || ((maxDistance >= 0) && (value <= maxDistance*maxDistance)))
      result = target;

    const float dist = std::sqrt(value);

    result->x = vector->x + dx/dist*maxDistance;
    result->y = vector->y + dy/dist*maxDistance;
    return result;
  }
};

#endif