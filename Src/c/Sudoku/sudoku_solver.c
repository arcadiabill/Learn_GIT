/* sudoku_solver.c
*
* Main program.
*
* Copyright (C) 2015 Giulio Zambon - http://zambon.com.au/
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "backtrack.h"
#include "box_line.h"
#include "cleanup.h"
#include "count_candidates.h"
#include "count_solved.h"
#include "def.h"
#include "display.h"
#include "display_strats_in_clear.h"
#include "display_string.h"
#include "hidden_pair.h"
#include "hidden_triple.h"
#include "inconsistent_grid.h"
#include "init.h"
#include "lines_2.h"
#include "lines_3.h"
#include "lines_4.h"
#include "naked_pair.h"
#include "naked_quad.h"
#include "naked_triple.h"
#include "pointing_line.h"
#include "rectangle.h"
#include "solve.h"
#include "unique_loop.h"
#include "xy_chain.h"
#include "y_wing.h"
