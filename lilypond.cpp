// Copyright (C) 2012  Mario Lang <mlang@delysid.org>
//
// Distributed under the terms of the GNU General Public License version 3.
// (see accompanying file LICENSE.txt or copy at
//  http://www.gnu.org/licenses/gpl-3.0-standalone.html)

#include "lilypond.hpp"
#include <algorithm>
#include <iterator>

namespace music { namespace lilypond {

generator::generator( std::ostream& os
                    , bool layout
                    , bool midi
                    , bool include_locations)
: os(os)
, layout(layout)
, midi(midi)
, include_locations(include_locations)
{
  os << "% Automatically generated by BMC, the braille music compiler"
     << std::endl;
  os << "\\version" << " " << "\"2.14.2\"" << std::endl;
}

void generator::operator() (braille::ambiguous::score const& score) const
{
  os << "\\score {" << std::endl;

  os << "  " << "<<" << std::endl;
  for (auto const& part: score.parts) (*this)(part, score);
  os << "  " << ">>" << std::endl << std::endl;

  if (layout) os << "  " << "\\layout { }" << std::endl;
  if (midi)   os << "  " << "\\midi { }" << std::endl;

  os << "}" << std::endl;
}

struct repeat_info: public boost::static_visitor<void>
{
  bool begin, end;
  repeat_info(braille::ambiguous::staff_element const& staff_element)
  : begin(false)
  , end(false)
  { boost::apply_visitor(*this, staff_element); }  

  result_type operator() (braille::ambiguous::measure const& measure)
  {
    for (auto const& voice: measure.voices)
      for (auto const& partial_measure: voice)
        for (auto const& partial_voice: partial_measure)
          std::for_each(partial_voice.begin(), partial_voice.end(),
                        boost::apply_visitor(*this));
  }
  result_type operator() (braille::ambiguous::key_and_time_signature const&) {}

  void operator() (braille::ambiguous::barline const& barline)
  {
    switch (barline) {
    case braille::ambiguous::begin_repeat: begin = true; break;
    case braille::ambiguous::end_repeat: end = true; break;
    }
  }
  void operator() (braille::ambiguous::simile const&) const
  { }
  void operator() (braille::ambiguous::value_distinction const&) const
  { }
  void operator() (braille::hand_sign const&) const
  { }
  void operator() (braille::ambiguous::rest const&) const
  { }
  void operator() (braille::ambiguous::note const&) const
  { }
  void operator() (braille::ambiguous::chord const&) const
  { }
};

void generator::operator() ( braille::ambiguous::part const& part
                           , braille::ambiguous::score const& score
                           ) const
{
  std::string indent("    ");
  if (part.size() == 2) {
    os << indent << "\\new PianoStaff <<" << std::endl;
    indent += "  ";
  }
  for (size_t staff_index = 0; staff_index < part.size(); ++staff_index) {
    os << indent << "\\new Staff {" << std::endl;

    switch (staff_index) {
    case 0: os << indent << "  "; ly_clef("treble"); break;
    case 1: os << indent << "  "; ly_clef("bass"); break;
    default: BOOST_ASSERT(false);
    }
    os << std::endl;

    if (score.key_sig != 0) {
      os << indent << "  "; ly_key(score.key_sig); os << std::endl;
    }

    if (score.time_sig)
      os << indent << "  " << "\\time" << " " << *score.time_sig << std::endl;

    unsigned int measure_number = 1;
    if (not part[staff_index].empty()) {
      rational first_measure_duration(duration(part[staff_index].front()));
      if ((not score.time_sig and first_measure_duration != 1) or
          (score.time_sig and *score.time_sig != first_measure_duration)) {
        os << indent << "  "; ly_partial(first_measure_duration); os << std::endl;
        measure_number = 0; // count from zero if we are dealing with upbeat
      }
    }

    for (size_t measure_index = 0; measure_index < part[staff_index].size();
         ++measure_index)
    {
      braille::ambiguous::staff_element const& this_measure = part[staff_index][measure_index];

      os << indent << "  "; boost::apply_visitor(*this, this_measure);

      bool barcheck = true;
      repeat_info this_repeat(this_measure);
      if (measure_index < part[staff_index].size() - 1) {
        braille::ambiguous::staff_element const& next_measure =
          part[staff_index][measure_index + 1];
        repeat_info next_repeat(next_measure);
        if (this_repeat.end and next_repeat.begin) {
          os << " " << "\\bar \":|:\"" << " ";
          barcheck = false;
        } else if (next_repeat.begin) {
          os << " " << "\\bar \"|:\"" << " ";
          barcheck = false;
        }
      }
      if (barcheck and this_repeat.end) {
        os << " " << "\\bar \":|\"" << " ";
        barcheck = false;
      }
      if (barcheck) os << " | ";
      os << "% " << measure_number++ << std::endl;
    }
    os << indent << "}" << std::endl;
  }
  if (part.size() == 2) os << "    " << ">>" << std::endl;
}

generator::result_type
generator::operator() (braille::ambiguous::key_and_time_signature const& key_and_time_sig) const
{
}

generator::result_type
generator::operator() (braille::ambiguous::measure const& measure) const
{
  if (measure.voices.size() == 1) {
    (*this)(measure.voices.front());
  } else {
    os << "<< ";
    for (size_t voice_index = 0; voice_index < measure.voices.size();
         ++voice_index)
    {
      os << "{"; (*this)(measure.voices[voice_index]); os << "}";
      if (voice_index != measure.voices.size() - 1) os << "\\\\";
    }
    os << " >>";
  }
}

void generator::operator() (braille::ambiguous::voice const& voice) const
{
  for (size_t partial_measure_index = 0; partial_measure_index < voice.size();
       ++partial_measure_index)
  {
    (*this)(voice[partial_measure_index]);
    if (partial_measure_index != voice.size() - 1) os << " ";
  }
}

void
generator::operator() (braille::ambiguous::partial_measure const& partial_measure) const
{
  if (partial_measure.size() == 1) {
    (*this)(partial_measure.front());
  } else {
    os << "<< ";
    for (size_t voice_index = 0; voice_index < partial_measure.size();
         ++voice_index)
    {
      os << "{"; (*this)(partial_measure[voice_index]); os << "}";
      if (voice_index != partial_measure.size() - 1) os << "\\\\";
    }
    os << " >>";
  }
}

void
generator::operator() (braille::ambiguous::partial_voice const& partial_voice) const
{
  for (size_t element_index = 0; element_index < partial_voice.size();
       ++element_index)
  {
    boost::apply_visitor(*this, partial_voice[element_index]);
    if (element_index != partial_voice.size() - 1) os << " ";
  }
}

generator::result_type
generator::operator() (braille::ambiguous::barline const&) const
{
}

generator::result_type
generator::operator() (braille::ambiguous::simile const&) const
{
  BOOST_ASSERT(false);
}

generator::result_type
generator::operator() (braille::ambiguous::value_distinction const&) const
{
}

generator::result_type
generator::operator() (braille::hand_sign const&) const
{
}

generator::result_type
generator::operator() (braille::ambiguous::rest const& rest) const
{
  os << "r";
  if (rest.whole_measure) os << "1";
  else ly_rhythm(rest);
  if (include_locations) {
    os << "%{" << rest.line << ":" << rest.column << "%}";
  }
}

generator::result_type
generator::operator() (braille::ambiguous::note const& note) const
{
  for (articulation const& articulation: note.articulations) {
    switch (articulation) {
    case appoggiatura:             os << "\\appoggiatura "; break;
    case short_appoggiatura:       os << "\\acciaccatura "; break;
    case mordent:                  os << "\\mordent ";      break;
    case turn_above_or_below_note: os << "\\turn ";         break;
    }
  }
  ly_pitch_step(note.step);
  ly_accidental(note.alter);
  ly_octave(note.octave);
  ly_rhythm(note);
  if (note.tie) os << "~";
  for (articulation const& articulation: note.articulations) {
    switch (articulation) {
    default:                         break;
    case accent:         os << "->"; break;
    case staccato:       os << "-."; break;
    case staccatissimo:  os << "-|"; break;
    case mezzo_staccato: os << "-_"; break;
    }
  }
  ly_finger(note.fingers);
  if (include_locations) {
    os << "%{" << note.line << ":" << note.column << "%}";
  }
}

generator::result_type
generator::operator() (braille::ambiguous::chord const& chord) const
{
  os << "<";
  ly_pitch_step(chord.base.step);
  ly_accidental(chord.base.alter);
  ly_octave(chord.base.octave);
  if (chord.base.tie) os << "~";
  ly_finger(chord.base.fingers);
  for (braille::ambiguous::interval const& interval: chord.intervals) {
    os << " ";
    ly_pitch_step(interval.step);
    ly_accidental(interval.alter);
    ly_octave(interval.octave);
    if (interval.tie) os << "~";
    ly_finger(interval.fingers);
  }
  os << ">";
  ly_rhythm(chord.base);
}

void generator::ly_accidental(int alteration) const
{
  while (alteration < 0) { os << "es"; ++alteration; }
  while (alteration > 0) { os << "is"; --alteration; }
}

void generator::ly_clef(std::string const& clef) const
{
  os << "\\clef \"" << clef << "\"";
}

class print_fingering: public boost::static_visitor<std::ostream&>
{
  std::ostream& os;
public:
  print_fingering(std::ostream& os): os(os) {}
  result_type operator() (braille::finger_change const& change) const
  { return os << "-\"" << change.first << "-" << change.second << "\""; }
  result_type operator() (unsigned finger) const
  { return os << "-" << finger; }
};

void generator::ly_finger(braille::fingering_list const& fingers) const
{
  print_fingering write_to_stream(os);
  std::for_each(fingers.begin(), fingers.end(),
                boost::apply_visitor(write_to_stream));
}

void generator::ly_key(key_signature const& key) const
{
  char const *flats[] = { "f", "bes", "ees", "aes", "des", "ges", "ces" };
  char const *sharps[] = { "g", "d", "a", "e", "b", "fis", "cis" };
  os << "\\key" << " ";
  if (key > 0) os << sharps[key - 1];
  else if (key < 0) os << flats[-key - 1];
  else os << "c";
  os << " " << "\\major";
}

void generator::ly_rhythm(braille::ambiguous::rhythmic_data const& rhythm) const
{
  if (rhythm.type.numerator() == 1) os << rhythm.type.denominator();
  std::fill_n(std::ostream_iterator<char>(os), rhythm.dots, '.');
}

void generator::ly_octave(int octave) const
{
  int const default_octave = 4;
  while (octave > default_octave) { os << "'"; --octave; };
  while (octave < default_octave) { os << ","; ++octave; };
}

void generator::ly_partial(rational const& duration) const
{
  os << "\\partial" << " " << duration.denominator();
  if (duration.numerator() != 1) os << "*" << duration.numerator();
  os << " ";
}

void generator::ly_pitch_step(diatonic_step step) const
{
  static char const* steps = "cdefgab";
  os << steps[step];
}

}}
