#include <gtk-accounting/filter/FilterParser.h>
#include <string.h>

#include <fstream>

namespace acc
{
const int BUFF_SIZE = 1024;

FilterParser::FilterParser(DispatchInterface &dispatcher, const std::string &path)
    : m_log("FilterParser"), m_dispatcher(dispatcher), m_path(path), m_state(&m_noElem), m_setter(&m_noElem)
{
}


/******************************************************************************
 * PUBLIC METHODS
 *****************************************************************************/
void FilterParser::parse(FilterCallback callback)
{
  m_dispatcher.queueEvent([this,callback](){ parseInternal(callback); });
}

/******************************************************************************
 * PRIVATE INTERNAL METHODS
 *****************************************************************************/
void FilterParser::parseInternal(FilterCallback callback)
{
  std::ifstream input(m_path);
  if (!input)
  {
    LOG(ERROR, m_log) << "Failed to open " << m_path << " for parsing";
    return;
  }

  m_error = false;
  m_depth = 0;

  XML_Parser parser = XML_ParserCreate(nullptr);
  XML_SetUserData(parser, this);
  XML_SetElementHandler(parser, startElem, endElem);
  XML_SetCharacterDataHandler(parser, dataHandle);

  char buffer[BUFF_SIZE];
  std::fill(buffer, buffer + BUFF_SIZE, 0);

  while (input.good() && !input.eof())
  {
    input.read(buffer, BUFF_SIZE);
    bool isFinal = input.eof() || input.gcount() < 1;
    LOG(DEBUG, m_log) << "FilterParser::parse(): eof: " << input.eof()
                      << " count: " << input.gcount();
    int error = XML_Parse(parser, buffer, input.gcount(), isFinal);
    if (error == XML_STATUS_ERROR)
    {
      LOG(DEBUG, m_log) << "FilterParser::parse() expat error: "
                        << XML_ErrorString(XML_GetErrorCode(parser))
                        << ". line: " << XML_GetCurrentLineNumber(parser);
    }
  }

  LOG(DEBUG, m_log) << "FilterParser::parse(): parsing finished";

  XML_ParserFree(parser);
  input.close();

  callback(m_filters);
  m_filters.clear();
}

FilterParser::State *FilterParser::findState(std::string elem)
{
  State *state = &m_noElem;
  if (elem == "Date")
    state = &m_date;
  else if (elem == "Amount")
    state = &m_amount;
  else if (elem == "Pattern")
    state = &m_pattern;
  else if (elem == "Min")
    state = &m_min;
  else if (elem == "Max")
    state = &m_max;
  else if (elem == "Filter")
    state = &m_filterState;
  return state;
}

/******************************************************************************
 * EXPAT CALLBACKS
 *****************************************************************************/
void XMLCALL FilterParser::startElem(void *data, const char *elem, const char **attr)
{
  FilterParser *parser = static_cast<FilterParser *>(data);
  ++parser->m_depth;
  parser->m_state->changeState(parser->findState(elem), *parser);
  parser->m_state->processElem(*parser,attr);
}

void XMLCALL FilterParser::endElem(void *data, const char *elem)
{
  FilterParser *parser = static_cast<FilterParser *>(data);
  --parser->m_depth;
  if (strcmp(elem, "Filter") == 0)
  {
    if (!parser->m_error)
    {
      LOG(DEBUG, parser->m_log) << "FilterParser::endElem(): pushing filter";
      parser->m_filters.push_back(parser->m_current);
    }
    parser->m_error = false;
  }

}

void XMLCALL FilterParser::dataHandle(void *data, const char *value, int len)
{
  FilterParser *parser = static_cast<FilterParser *>(data);

  std::string temp(value, len);
  parser->m_state->processData(*parser, temp);
}

/******************************************************************************
 * STATE IMPLEMENTATION
 *****************************************************************************/
void FilterParser::State::processElem(FilterParser &parser, const char **attr)
{
  (void)attr;
  (void)parser;
}

void FilterParser::State::endElem(FilterParser &parser, const char *elem)
{
  (void)parser;
  (void)elem;
}

void FilterParser::State::processData(FilterParser &parser, const std::string &value)
{
  (void)parser;
  (void)value;
}

void FilterParser::State::changeState(State *state, FilterParser &parser)
{
  parser.m_state = state;
}

/******************************************************************************
 * SETTER IMPLEMENTATION
 *****************************************************************************/
void FilterParser::Setter::setMin(FilterParser &parser, const std::string &min)
{
  (void)parser;
  (void)min;
}

void FilterParser::Setter::setMax(FilterParser &parser, const std::string &max)
{
  (void)parser;
  (void)max;
}

/******************************************************************************
 * FILTER STATE IMPLEMENTATION
 *****************************************************************************/
void FilterParser::FilterState::processElem(FilterParser &parser, const char **attr)
{
  if (parser.m_depth == parser.OBJ_DEPTH)
  {
    parser.m_current = Filter();
    std::string name = "unnamed";
    if (attr[0] && strcmp(attr[0], "name") == 0 && attr[1]) name = attr[1];
    parser.m_current.name = name;
  }
  else
  {
    LOG(DEBUG, parser.m_log) << "FilterState::processElem(): Invalid Filter depth";
    parser.m_error = true;
  }
}

/******************************************************************************
 * DATE STATE IMPLEMENTATION
 *****************************************************************************/
void FilterParser::Date::processElem(FilterParser &parser, const char **attr)
{
  (void)attr;

  if (parser.m_depth == parser.ATTR_DEPTH)
    parser.m_setter = this;
  else
    parser.m_error = true;
}

void FilterParser::Date::endElem(FilterParser &parser, const char *elem)
{
  (void)elem;
  parser.m_setter = &parser.m_noElem;
}

void FilterParser::Date::setMin(FilterParser &parser, const std::string &min)
{
  parser.m_current.dateMin = min;
}

void FilterParser::Date::setMax(FilterParser &parser, const std::string &max)
{
  parser.m_current.dateMax = max;
}

/******************************************************************************
 * AMOUNT STATE IMPLEMENTATION
 *****************************************************************************/
void FilterParser::Amount::processElem(FilterParser &parser, const char **attr)
{
  (void)attr;
  if (parser.m_depth == parser.ATTR_DEPTH)
    parser.m_setter = this;
  else
    parser.m_error = true;
}

void FilterParser::Amount::endElem(FilterParser &parser, const char *elem)
{
  (void)elem;
  parser.m_setter = &parser.m_noElem;
}

void FilterParser::Amount::setMin(FilterParser &parser, const std::string &min)
{
  parser.m_current.amountMin = min;
}

void FilterParser::Amount::setMax(FilterParser &parser, const std::string &max)
{
  parser.m_current.amountMax = max;
}

/******************************************************************************
 * NAME STATE IMPLEMENTATION
 *****************************************************************************/
void FilterParser::Pattern::processData(FilterParser &parser, const std::string &value)
{
  if (parser.m_depth == parser.ATTR_DEPTH)
  {
    parser.m_current.pattern = value;
  }
}

/******************************************************************************
 * MIN STATE IMPLEMENTATION
 *****************************************************************************/
void FilterParser::Min::processData(FilterParser &parser, const std::string &value)
{
  if (parser.m_depth == parser.VALUE_DEPTH)
  {
    parser.m_setter->setMin(parser, value);
  }
}

/******************************************************************************
 * MIN STATE IMPLEMENTATION
 *****************************************************************************/
void FilterParser::Max::processData(FilterParser &parser, const std::string &value)
{
  if (parser.m_depth == parser.VALUE_DEPTH)
  {
    parser.m_setter->setMax(parser, value);
  }
}

}  // namespace acc
