#ifndef TCP_GRAPHER_H
#define TCP_GRAPHER_H

class tcp_grapher {
public:
  tcp_grapher(int max_window, double C, double alpha, double beta);
  int get_next();
  int get_max_window();
private:
  double curr_window;
  int t;
  int max_window;
  double C;
  double w_max;
  double beta;
  double max_hit;
};

#endif // TCP_GRAPHER_H
