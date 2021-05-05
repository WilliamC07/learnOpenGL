//
// Created by William Cao on 5/3/21.
//

#ifndef TESTGLFW_ERRORCHECKER_H
#define TESTGLFW_ERRORCHECKER_H

#include <glad/glad.h>
#include <iostream>

// Use this macro to use the ErrorChecker class
#define ERROR_CHECKER ErrorChecker errorChecker(__LINE__, __FILE__, __FUNCTION__);

/**
 * GL error are like C errno.
 *
 * To use this class, use the macro ERROR_CHECKER
 * Creates an instance of this class at the start of every function that calls a GL
 * function. First, this class will check to make sure there weren't any earlier errors.
 * When the function ends (and the destructor is automatically called), it will check to
 * see if any errors were created.
 *
 * Disadvantages:
 * - Does not tell the exact line number where the error came from.
 *
 * Advantage:
 * - Alternative is create a macro that acts as a function wrapper on every single GL
 * function to check if there is an error. This can get cumbersome, and if
 * you forget to do it in a line, you might get false positives.
 *
 */
class ErrorChecker {
  private:
  const int _lineNumber;
  const char *_functionName, *_fileName;

  public:
  /**
   * Must not have any errors. If there are, that means an earlier GL function called
   * gave an error.
   */
  ErrorChecker(int lineNumber, const char *functionName, const char *fileName) :
    _lineNumber{lineNumber},
    _functionName{functionName},
    _fileName(fileName) {
    GLenum error{glGetError()};
    if (error != GL_NO_ERROR) {
      std::cout << "Error occurred earlier in the program.\n"
                << "Error: " << error << "\n"
                << "Stopping at " << _fileName << ": " << _functionName
                << " (" << _lineNumber << ")"
                << std::endl;
      exit(1);
    }
  }

  ~ErrorChecker() {
    bool anyErrors{false};
    // print all the errors
    while (GLenum error = glGetError()) {
      std::cout << "OpenGL Error: " << error << "\n";
      anyErrors = true;
    }

    // TODO: eventually replace with some logger
    if (anyErrors) {
      std::cout << "Error at " << _fileName << " (" << _lineNumber << ")"
                << ": " << _functionName << std::endl;
      exit(1);
    }
  }
};


#endif //TESTGLFW_ERRORCHECKER_H
