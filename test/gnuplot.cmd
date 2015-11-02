set xrange [0:200]
set yrange [0:200]
unset mouse
set title 'The set of raw points in the set' font 'Arial,12'
set style line 1 pointtype 7 linecolor rgb 'red'
set style line 2 pointtype 7 linecolor rgb 'green'
set style line 3 pointtype 7 linecolor rgb 'black'
plot '-' ls 1 with points notitle
57 194
124 156
177 96
198 168
121 76
32 172
23 26
36 16
55 113
146 48
145 108
26 60
17 129
186 72
6 190
11 13
133 135
169 110
182 117
77 102
e
pause -1 'Hit OK to move to the next state!'
set title 'The points partitioned into an upper and lower hull' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 2 with points notitle, '-' ls 3 with linespoints notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
e
57 194
e
6 190
198 168
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
17 129
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
17 129
23 26
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
23 26
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
23 26
26 60
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
23 26
26 60
32 172
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
23 26
26 60
32 172
36 16
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
23 26
26 60
36 16
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
23 26
36 16
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
36 16
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
36 16
55 113
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
36 16
55 113
77 102
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
36 16
77 102
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
36 16
77 102
121 76
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
36 16
121 76
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
36 16
121 76
124 156
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
36 16
121 76
124 156
133 135
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
36 16
121 76
133 135
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
36 16
121 76
133 135
145 108
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
36 16
121 76
145 108
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
36 16
121 76
145 108
146 48
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
36 16
121 76
146 48
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
36 16
146 48
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
36 16
146 48
169 110
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
36 16
146 48
169 110
177 96
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
36 16
146 48
177 96
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
36 16
146 48
177 96
182 117
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
36 16
146 48
177 96
182 117
186 72
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
36 16
146 48
177 96
186 72
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
36 16
146 48
186 72
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
36 16
146 48
186 72
198 168
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
36 16
146 48
186 72
198 168
e
57 194
6 190
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
36 16
146 48
186 72
198 168
e
198 168
57 194
6 190
e
57 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Complete' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
11 13
17 129
23 26
26 60
32 172
36 16
55 113
77 102
121 76
124 156
133 135
145 108
146 48
169 110
177 96
182 117
186 72
198 168
e
6 190
11 13
36 16
146 48
186 72
198 168
e
198 168
57 194
6 190
e
57 194
e
pause -1 'Hit OK to move to the next state!'
