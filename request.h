#pragma once
#ifndef REQUEST_H
#define REQUEST_H

#include "abstract_request.h"

#include <string>

using namespace std;

typedef void (*logFunction)(string test);

class Request : public AbstractRequest {
  int value;
  logFunction outFnc;
  public :
  void setValue(int value) {this->value = value;}
  void setOutput (logFunction fnc) {outFnc = fnc;}
  void process();
  void finish();
};
#endif
