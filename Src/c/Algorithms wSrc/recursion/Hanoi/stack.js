<!--

// stack.js - javascript implementation of a stack
//
// Copyright (C) 2003-04 Mark Jundo P. Documento
//
// This program is free software; you can redistribute it and/or modify it under the terms
// of the GNU General Public License as published by the Free Software Foundation;
// either version 2 of the License, or (at your option) any later version.
//
// This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
// without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
// See the GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License along with this program;
// if not, write to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston,
// MA 02111-1307 USA.
//---------------------------------------------------------------------------

// ADT Stack object
// stack() creates a generic stack object
// Member functions:
//     empty() - returns true if this stack is empty
//     top()   - returns the object waiting at the top of the stack
//     max()   - returns the maximum number of objects this stack can contain
//     push()  - pushes an object into the top of the stack
//     pop()   - pops an object off the top of the stack
//     reset() - empties the stack object
//     size()  - returns the number of objects currently stacked
function stack(nMax)
{
    this.stacktop = 0;
    this.stackmax = nMax;
    this.elements = new Array(nMax);
    this.reset = sReset;
    this.max = sMax;
    this.empty = sEmpty;
    this.size = sSize;
    this.top = sTop;
    this.push = sPush;
    this.pop = sPop;
}

function sReset(nMax)
{
    if (nMax != null)
        if (nMax > 0 && this.queuemax != nMax)
        {
            delete this.elements;
            this.elements = new Array((this.queuemax = nMax));
        }
    this.stacktop = 0;
}

function sMax()
{
    return this.stackmax;
}

function sEmpty()
{
    return !this.stacktop;
}

function sSize()
{
    return this.stacktop;
}

function sTop()
{
    return this.elements[this.stacktop - 1];
}

function sPush(obj)
{
    if (this.stacktop == this.stackmax)
        alert("Stack overflow error!");
    else
        this.elements[this.stacktop++] = obj;
}

function sPop()
{
    if (!this.stacktop)
        alert("Stack underflow error!");
    else
        this.stacktop--;
}

-->
