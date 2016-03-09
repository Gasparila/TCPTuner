#include "tcp_grapher.h"
#include <cmath>
#include <iostream>
using namespace std;

tcp_grapher::tcp_grapher(int max_window, double C, double alpha, double beta) :
  curr_window(max_window),
  t(0),
  max_window(max_window),
  C(C),
  w_max(max_window * alpha / 512.0),
  beta(beta / 1024),
  max_hit(0) {
}

int tcp_grapher::get_max_window() {
  return max_hit;
}

int tcp_grapher::get_next() {
  if (curr_window >= max_window) {
    curr_window *= beta;
    t = 0;
  }
  else {
    double K = cbrt(w_max * (1-beta) / C);
    double delta = (t - K);
    curr_window = max(curr_window, C * delta * delta * delta + w_max);
    t++;
  }
  max_hit = max(curr_window, max_hit);
  return curr_window;
}
