// #include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <glog/logging.h>

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

// Override Default constructor is not allowed when =default keyword used.
// NonCopyableClass::NonCopyableClass() {
//   LOG(INFO) << "Default constructor is called!";
// }
// error: definition of explicitly-defaulted ‘NonCopyableClass::NonCopyableClass()’

int main(int argc, char* argv[])
{
  // Initialize Google’s logging library.
  google::InitGoogleLogging(argv[0]);
  google::ParseCommandLineFlags(&argc, &argv, true);
  FLAGS_alsologtostderr = true;

  auto a = new NonCopyableClass();

  // NonCopyableClass other(non_copyable_class);
  // error: use of deleted function ‘NonCopyableClass::NonCopyableClass(const NonCopyableClass&)’

  // NonCopyableClass other2 = non_copyable_class;
  // error: use of deleted function ‘NonCopyableClass::NonCopyableClass(const NonCopyableClass&)’

  return EXIT_SUCCESS;
}
