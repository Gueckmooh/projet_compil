#ifndef __ASML_NODE_H__
#define __ASML_NODE_H__

using namespace std;

namespace asml {
  class asml_node {
  public:
    static const int UNARY = 1;
    static const int BINARY = 2;

    virtual ~asml_node (void) {};
    virtual int get_type (void);
  protected:
    int type_id;
  };

} // TODO

#endif //__ASML_NODE_H__
