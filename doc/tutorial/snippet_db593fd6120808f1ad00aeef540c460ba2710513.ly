% Automatically generated by BMC, the braille music compiler
\version "2.14.2"
\include "articulate.ly"
\header {
  tagline = ""
}
music =
  <<
    \new PianoStaff <<
      \new Staff = "RH" {
        \clef "treble"
        \time 4/4
        <c'' b'>1 | % 1
        <c'' a'>1 | % 2
        <c'' g'>1 | % 3
        <c'' f'>1 | % 4
        <c'' e'>1 | % 5
        <c'' d'>1 | % 6
        <c'' c'>1 | % 7
      }
      \new Staff = "LH" {
        \clef "bass"
        \time 4/4
        r1 | % 1
        r1 | % 2
        r1 | % 3
        r1 | % 4
        r1 | % 5
        r1 | % 6
        r1 | % 7
      }
    >>
  >>

\score {
  \music
  \layout { }
}
\score {
  \unfoldRepeats \articulate \music
  \midi { }
}