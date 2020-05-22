#ifndef _GTK_ACCOUNTING_FILTER_PARSER_H_
#define _GTK_ACCOUNTING_FILTER_PARSER_H_

#include <gtk-accounting/dispatch/DispatchInterface.h>
#include <gtk-accounting/filter/Filter.h>
#include <gtk-accounting/log/LogChannel.h>

#include <vector>
#include <functional>
#include <expat.h>

namespace acc
{

using FilterCallback = std::function<void(const std::vector<Filter> &filters)>;

class FilterParser
{
 public:
  FilterParser(DispatchInterface &dispatcher);

  FilterParser(const FilterParser &) = delete;
  FilterParser(FilterParser &&) = delete;
  FilterParser &operator=(const FilterParser &) = delete;
  FilterParser &operator=(FilterParser &&) = delete;

 public:
  void parse(FilterCallback callback);

 private:
  void parseInternal(FilterCallback callback);

 private:
  static void XMLCALL startElem(void *data, const char *elem, const char **attr);
  static void XMLCALL endElem(void *data, const char *elem);
  static void XMLCALL dataHandle(void *data, const char *value, int len);

 private:
  LogChannel m_log;
  DispatchInterface &m_dispatcher;
  std::vector<Filter> m_filters;
  int m_depth;
  Filter m_current;
  bool m_error;

  const uint8_t OBJ_DEPTH = 2;
  const uint8_t ATTR_DEPTH = 3;
  const uint8_t VALUE_DEPTH = 4;

 private:
  class State
  {
   public:
    virtual void processElem(FilterParser &parser, const char **attr);
    virtual void processData(FilterParser &parser, const std::string &value);
    virtual void endElem(FilterParser &parser, const char *elem);
    void changeState(State *state, FilterParser &parser);
  };

  class Setter
  {
   public:
    virtual void setMin(FilterParser &parser, const std::string &min);
    virtual void setMax(FilterParser &parser, const std::string &max);
  };

  class NoElem : public State, public Setter
  {
  };

  class FilterState : public State
  {
    void processElem(FilterParser &parser, const char **attr);
  };

  class Date : public State, public Setter
  {
   public:
    void processElem(FilterParser &parser, const char **attr);
    void setMin(FilterParser &parser, const std::string &min);
    void setMax(FilterParser &parser, const std::string &max);
    void endElem(FilterParser &parser, const char *elem);
  };

  class Amount : public State, public Setter
  {
   public:
    void processElem(FilterParser &parser, const char **attr);
    void setMin(FilterParser &parser, const std::string &min);
    void setMax(FilterParser &parser, const std::string &max);
    void endElem(FilterParser &parser, const char *elem);
  };

  class Pattern : public State, public Setter
  {
   public:
    void processData(FilterParser &parser, const std::string &value);
  };

  class Min : public State
  {
   public:
    void processData(FilterParser &parser, const std::string &value);
  };

  class Max : public State
  {
   public:
    void processData(FilterParser &parser, const std::string &value);
  };

  State *findState(std::string elem);

  State *m_state;
  Setter *m_setter;
  NoElem m_noElem;
  FilterState m_filterState;
  Date m_date;
  Amount m_amount;
  Pattern m_pattern;
  Min m_min;
  Max m_max;

  friend class State;
};

}  // namespace acc
#endif  // _GTK_ACCOUNTING_FILTER_PARSER_H_
