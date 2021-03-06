% Automatically generated by BMC, the braille music compiler
\version "2.14.2"
\include "articulate.ly"
music =
  <<
    \new PianoStaff <<
      \new Staff = "RH" {
        \clef "treble"
        \key g \major
        \time 12/8
        b'4.~-2 b'16[ c'' d'' c'' d'' e''] a'4.~ a'16[ b' c'' b' c'' d''] | % 1
        << {g'4. g''~ g''8-"5-4" a''16 g'' fis'' g'' a''8 r r}\\{b'4.~-2 b'16[ c''-1 d''-3 c'' d'' e''] a'4.~ a'16[ b' c'' b' c'' d'']} >> | % 2
        << {r8 d''16-5 c'' b' a' b'8-1 c''16-3 b' a' b' g'8 e''-3 d''-"1-2" c'' fis'' a''}\\{g'4. g''~-5 g''8-"5-4" a''16 g'' fis''-3 g'' a''8 r r} >> | % 3
        << {b'4-1 g''8 g''4 fis''8 r r b'' a''4-"4-5" d''8~-2}\\{r8 d''16-4 c'' b' a' b'8 c''16-1 b'-2 a' b' g'8 e''-3 d''-2 c'' fis''-4 a''-5} >> | % 4
        << {d''16 e''-4 d'' c'' b'8 e'' b' d''-"2-1" cis'' d'' e''~-"2-1" e'' cis''-2 a'}\\{b'4 g''8 g''4 fis''8 r r b'' a''4-"4-5" d''8~} >> | % 5
        << {r8 r d''-4 g'4.~ g'8 fis'-1 g'-"1-2" e' a'16 g' fis'-2 e'}\\{d''16 e'' d'' c''-1 b'8 e'' b' d''-4 cis'' d'' e''~ e'' cis'' a'-3} >> | % 6
        << {d'8-2 e'16-1 fis' g'-1 a' b'8 d'' cis'' d''4.~ d''8 cis'' r}\\{r8 r d'' g'4.~ g'8 fis' g'-2 e' a'16 g' fis'-3 e'} >> | % 7
        << {d''4.~ d''16[ a'-1 g'-2 fis' g'-2 e'] fis'2.}\\{d'8 e'16 fis' g'-1 a' b'8 d''-5 cis''-4 d''2. } >> \bar ":|:" % 8
        << { r4. a''~-2 a''16[ b'' c''' a'' b'' c'''] b''[ a'' g'' fis''-4 e'' dis'']}\\{R1*3/2} >> | % 9
        << {e''8-1 fis''-3 g''~ g'' fis'' e'' dis''4.~-1 dis''4 r8}\\{r4. a''~ a''16[ b''-4 c''' a''-2 b'' c'''] b''-5[ a'' g'' fis'' e'' dis''-2]} >> | % 10
        << {r4. a'~ a'8 b'16-3 a' g' fis' g'-1[ a' b' g' a' b']}\\{e''8 fis'' g''~ g'' fis'' e''-5 dis''4.~-"4-5" dis''4 r8} >> | % 11
        << {e'8 fis'16 g'-1 a'-3 b' c''8 e' dis' e'4. r}\\{r4. a'~ a'8 b'16-5 a' g' fis' g'-1[ a' b' g' a' b']} >> | % 12
        << {e''4.~ e''16[ fis''-4 g'' e'' fis'' g''] c''[ d'' e'' c'' d''-4 e''] a'[ b' c'' a' b' c'']}\\{e'8 fis'16 g'-1 a' b'-1 c''8  e' dis' e'4. r} >> | % 13
        << { b'16[ c'' d'' b' c'' d''] g'4.~ g'8 g''4~ g''8 fis'' a''~}\\{e''4.~ e''16[ fis''-4 g'' e'' fis'' g''] c''[ d'' e'' c'' d'' e''] a'[ b' c''-3 a' b'-2 c''-1]} >> | % 14
        << {a''8 g''-4 f''-5 e''16[ d'' c'' e''-5 d'' c''] b'4-"2-1" b''8 a''4 c'''8}\\{b'16[ c''-1 d''-2 b' c'' d''] g'4.~ g'8 g''4~-"5-3" g''8 fis'' a''~-3} >> | % 15
        << {b''4 d'''8 g'' a'' fis''-4 g''2.}\\{a''8 g''-1 f''-2 e''16[ d''-2 c'' e'' d''-1 c''] b'2. } >> \bar ":|" % 16
      }
      \new Staff = "LH" {
        \clef "bass"
        \key g \major
        \time 12/8
        g,8 b, d g b-2 e-5 fis,-4 a, d fis-2 a d | % 1
        e,8-5 g, b, e b,-3 cis d, fis, a, d fis-2 a, | % 2
        b,16-3 a, b, c d8~ d16[ g, a, b, c d] e-2[ d-1 c b, c e] fis,-4[ a,-1 g, fis, e, d,] | % 3
        g,16[ fis, g, a, b,-4 c] d[ e a,-4 b, c a,] b, a,-1 g, fis, g,8~ g,16[ fis, e, d, e, fis,] | % 4
        g,16[ fis, g, a, g, fis,] e,[ fis, g, e, fis, g,] a,[ g,-4 a, b, a, g,] fis,[ fis g-2 fis-1 e fis] | % 5
        b,16-3[ a, b, c d b,-4] cis[ d e d cis b,] a,[ e d cis d b,] cis[ a, b, cis d e] | % 6
        fis16-2[ b, cis d e-1 fis-3] g[ fis e-1 d e ais,-4] b,[ cis d cis b,-1 a,] g,[ fis, g, b, a, g,] | % 7
        fis,16 a,-1 g, fis, e, d, g,8 e, a, d,16[ fis, a, d a, fis,] d,4.  \bar ":|:" % 8
         d8 fis a d' c'16 b a-1 g fis8 a d g a b-3 | % 9
        c'16[ d' c' b a-1 g] fis e fis g a fis b8 fis-4 g a16[ c' b a-1 g fis] | % 10
        g16[ a g fis e-1 d] c[ b, a, b, c a,] b,8 fis b~ b g-3 e | % 11
        c'16[ d'-2 c' b a-1 g] fis[ e fis b a b] e8 g b e' e-3 d | % 12
        c8 c' b-3 a4.~ a8 c' a-3 fis d d' | % 13
        g16-3 a g-1 f e d c8 e-1 c-2 a,16 b, c a, b, c d8 d, fis-4 | % 14
        g16 a b g-5 a b c'8 e' a d'16[ c' b d'-1 c' b] c'[ b a-1 g fis a] | % 15
        g16 fis e-1 d c b, c8 a, d g,16[ b, d g d b,] g,4.  \bar ":|" % 16
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
