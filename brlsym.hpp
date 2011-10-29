// Copyright (C) 2011  Mario Lang <mlang@delysid.org>
//
// Distributed under the terms of the GNU General Public License version 3.
// (see accompanying file LICENSE.txt or copy at
//  http://www.gnu.org/licenses/gpl-3.0-standalone.html)

#ifndef BMC_BRLSYM_HPP
#define BMC_BRLSYM_HPP

#include "config.hpp"
#include <boost/spirit/include/qi_symbols.hpp>
#include "ambiguous.hpp"
#include "ttb/ttb.h"
#include "ttb/unicode.h"

namespace music { namespace braille {

// A special version of qi::symbols<> which transparently translates its input
// to Unicode braille.

struct tst_braillify {
  template <typename Char>
  Char operator()(Char ch) const {
    return ch < 0X20? ch: UNICODE_BRAILLE_ROW | (convertCharacterToDots(textTable, ch)&0X3F);
  }
};

template <typename T = boost::spirit::unused_type>
struct brl_symbols : boost::spirit::qi::symbols<wchar_t, T, boost::spirit::qi::tst<wchar_t, T>, tst_braillify>
{};

// A number of generally useful symbol tables for parsing braille music code

#define BMC_DEFINE_SYMBOL_TABLE(Return, Type, Name) \
  struct Type : brl_symbols<Return> { Type(); }; \
  extern Type Name;

BMC_DEFINE_SYMBOL_TABLE(unsigned, upper_digit_symbols, upper_digit_sign)
BMC_DEFINE_SYMBOL_TABLE(unsigned, lower_digit_symbols, lower_digit_sign)
BMC_DEFINE_SYMBOL_TABLE(boost::spirit::unused_type, dots_123_symbols, dots_123)
BMC_DEFINE_SYMBOL_TABLE(accidental, accidental_symbols, accidental_sign)
BMC_DEFINE_SYMBOL_TABLE(unsigned, octave_symbols, octave_sign)
typedef std::pair<diatonic_step, ambiguous::value> step_and_value;
BMC_DEFINE_SYMBOL_TABLE(step_and_value,
                        step_and_value_symbols, step_and_value_sign)
BMC_DEFINE_SYMBOL_TABLE(ambiguous::value, rest_symbols, rest_sign)
BMC_DEFINE_SYMBOL_TABLE(interval, interval_symbols, interval_sign)
BMC_DEFINE_SYMBOL_TABLE(unsigned, finger_symbols, finger_sign)
BMC_DEFINE_SYMBOL_TABLE(ambiguous::value_distinction,
                        value_distinction_symbols, value_distinction_sign)
BMC_DEFINE_SYMBOL_TABLE(music::articulation, articulation_symbols, articulation_sign)
BMC_DEFINE_SYMBOL_TABLE(boost::spirit::unused_type, tie_symbol, tie_sign)
BMC_DEFINE_SYMBOL_TABLE(ambiguous::barline, barline_symbols, barline_sign)

#undef BMC_DEFINE_SYMBOL_TABLE
}}

#endif
