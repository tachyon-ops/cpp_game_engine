#ifndef ENGINE_PHYSICS_RIGIDBODY_H
#define ENGINE_PHYSICS_RIGIDBODY_H

#include "Vector2D.hpp"

#define UNIT_MASS 1.0f
#define GRAVITY 9.8f

class RigidBody {
public:
  RigidBody() {
    m_Mass = UNIT_MASS;
    m_Gravity = GRAVITY;
  };

  // Setters for Mass and Gravity
  inline void SetMass(float mass) { m_Mass = mass; };
  inline void SetGravity(float gravity) { m_Gravity = gravity; };

  // Force
  inline void ApplyForce(Vector2D force) { m_Force = force; };
  inline void ApplyForceX(float Fx) { m_Force.X = Fx; };
  inline void ApplyForceY(float Fy) { m_Force.Y = Fy; };
  inline void UnsetForce() { m_Force = Vector2D(0, 0); };

  // Friction
  inline void ApplyFriction(Vector2D friction) { m_Friction = friction; };
  inline void UnsetFriction() { m_Friction = Vector2D(0, 0); };

  // Getters
  inline float GetMass() { return m_Mass; };
  inline Vector2D GetPosition() { return m_Position; };
  inline Vector2D GetVelocity() { return m_Velocity; };
  inline Vector2D GetAcceleration() { return m_Acceleration; };

  // Update method
  void Update(float dt) {
    // force + friction = m * a;
    // a = (force + friction)/m
    m_Acceleration.X = (m_Force.X + m_Friction.X) / m_Mass;
    m_Acceleration.Y = m_Gravity + m_Force.Y / m_Mass;
    m_Velocity = m_Acceleration * dt;
    m_Position = m_Velocity * dt;
  };

private:
  float m_Mass;
  float m_Gravity;

  Vector2D m_Force;
  Vector2D m_Friction;

  Vector2D m_Position;
  Vector2D m_Velocity;
  Vector2D m_Acceleration;
};

#endif