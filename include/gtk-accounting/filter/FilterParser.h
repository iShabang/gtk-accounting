#ifndef _GTK_ACCOUNTING_FILTER_PARSER_H_
#define _GTK_ACCOUNTING_FILTER_PARSER_H_

#include <expat.h>
#include <gtk-accounting/dispatch/DispatchInterface.h>
#include <gtk-accounting/filter/Filter.h>
#include <gtk-accounting/log/LogChannel.h>

#include <vector>

namespace acc
{
class FilterParser
{
 public:
  FilterParser(DispatchInterface &dispatcher);

  FilterParser(const FilterParser &) = delete;
  FilterParser(FilterParser &&) = delete;
  FilterParser &operator=(const FilterParser &) = delete;
  FilterParser &operator=(FilterParser &&) = delete;

 private:
  void parse();

 public:
  static void XMLCALL startElem(void *data, const char *elem, const char **attr);
  static void XMLCALL endElem(void *data, const char *elem);
  static void XMLCALL dataHandle(void *data, const char *value, int len);

 private:
  LogChannel m_log;
  std::vector<Filter> m_filters;
  int m_depth;
  Filter m_current;
  bool m_error;

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

  class NoElem : public State
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
  };

  class Amount : public State, public Setter
  {
   public:
    void processElem(FilterParser &parser, const char **attr);
    void setMin(FilterParser &parser, const std::string &min);
    void setMax(FilterParser &parser, const std::string &max);
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
