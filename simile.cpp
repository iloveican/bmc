// Copyright (C) 2011  Mario Lang <mlang@delysid.org>
//
// Distributed under the terms of the GNU General Public License version 3.
// (see accompanying file LICENSE.txt or copy at
//  http://www.gnu.org/licenses/gpl-3.0-standalone.html)

#include "simile_def.hpp"

namespace music { namespace braille {

typedef std::wstring::const_iterator iterator_type;
template struct simile_grammar<iterator_type>;

}}
