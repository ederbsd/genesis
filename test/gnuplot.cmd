set xrange [0:200]
set yrange [0:200]
unset mouse
set title 'The set of raw points in the set' font 'Arial,12'
set style line 1 pointtype 7 linecolor rgb 'red'
set style line 2 pointtype 7 linecolor rgb 'green'
set style line 3 pointtype 7 linecolor rgb 'black'
plot '-' ls 1 with points notitle
83 167
100 152
107 56
108 161
67 197
119 194
150 40
54 197
175 108
132 17
12 84
197 29
197 79
187 93
170 112
18 52
29 118
154 86
124 12
197 191
e
pause -1 'Hit OK to move to the next state!'
set title 'The points partitioned into an upper and lower hull' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 2 with points notitle, '-' ls 3 with linespoints notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
12 84
197 191
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
107 56
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
107 56
124 12
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
132 17
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
132 17
150 40
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
132 17
150 40
154 86
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
132 17
150 40
154 86
170 112
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
132 17
150 40
170 112
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
132 17
150 40
170 112
175 108
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
132 17
150 40
175 108
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
132 17
150 40
175 108
187 93
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
132 17
150 40
187 93
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
132 17
150 40
187 93
197 29
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
132 17
150 40
197 29
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
132 17
197 29
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
197 29
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
197 29
197 79
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
197 29
197 79
197 191
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
197 29
197 191
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
197 29
197 191
e
29 118
12 84
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
197 29
197 191
e
54 197
29 118
12 84
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
197 29
197 191
e
54 197
12 84
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
197 29
197 191
e
67 197
54 197
12 84
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
197 29
197 191
e
83 167
67 197
54 197
12 84
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
197 29
197 191
e
100 152
83 167
67 197
54 197
12 84
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
197 29
197 191
e
100 152
67 197
54 197
12 84
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
197 29
197 191
e
108 161
100 152
67 197
54 197
12 84
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
197 29
197 191
e
108 161
67 197
54 197
12 84
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
197 29
197 191
e
119 194
108 161
67 197
54 197
12 84
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
197 29
197 191
e
119 194
67 197
54 197
12 84
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Adding a new point' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
197 29
197 191
e
197 191
119 194
67 197
54 197
12 84
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: BackTracking' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
197 29
197 191
e
197 191
67 197
54 197
12 84
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
set title 'The hull in state: Complete' font 'Arial,12'
plot '-' ls 1 with points notitle, '-' ls 3 with linespoints notitle, '-' ls 3 with linespoints notitle, '-' ls 2 with points notitle
18 52
107 56
124 12
132 17
150 40
154 86
170 112
175 108
187 93
197 29
197 79
197 191
e
12 84
18 52
124 12
197 29
197 191
e
197 191
67 197
54 197
12 84
e
29 118
54 197
67 197
83 167
100 152
108 161
119 194
e
pause -1 'Hit OK to move to the next state!'
