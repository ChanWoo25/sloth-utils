#pragma once

class NonCopyableClass
{
public:
  /* This is to explicitly say
    "I will use the default functions and operators implemented by the compiler
    because deep copying is not required."
    Readers of the code may receive a clear indication that this class is OK for shallow copying. */
  NonCopyableClass() = default;
  ~NonCopyableClass() = default;

  NonCopyableClass(const NonCopyableClass& other) = delete;            // disable copy constructor
  NonCopyableClass& operator=(const NonCopyableClass& other) = delete; // disable assignment operator
};
