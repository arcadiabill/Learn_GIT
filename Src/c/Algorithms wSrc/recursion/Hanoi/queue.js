<!--

// queue.js - javascript implementation of a queue
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

// ADT Queue object
// queue() creates a generic circular queue object
// Member functions:
//     empty() - returns true if this queue is empty
//     front() - returns the object waiting at the front of the queue
//     max()   - returns the maximum number of objects this queue can contain
//     push()  - pushes an object into the back of the queue
//     pop()   - pops an object off the front of the queue
//     reset() - empties the queue object
//     size()  - returns the number of objects currently enqueued
function queue(nMax)
{
    this.queuefront = 0;
    this.queueback = 0;
    this.queuemax = nMax;
    this.queuesize = 0;
    this.elements = new Array(nMax);
    this.reset = qReset;
    this.max = qMax;
    this.empty = qEmpty;
    this.size = qSize;
    this.front = qFront;
    this.push = qPush;
    this.pop = qPop;
}

function qReset(nMax)
{
    if (nMax != null)
        if (nMax > 0 && this.queuemax != nMax)
        {
            delete this.elements;
            this.elements = new Array((this.queuemax = nMax));
        }
    this.queuefront = this.queueback = 0;
    this.queuesize = 0;
}

function qMax()
{
    return this.queuemax;
}

function qEmpty()
{
    return !this.queuesize;
}

function qSize()
{
    return this.queuesize;
}

function qFront()
{
    if (this.empty())
        throw "Queue underflow";
    else
        return this.elements[this.queuefront];
}

function qPush(obj)
{
    tempback = this.queueback;
    if (++tempback == this.queuemax)
        tempback = 0;
    if (this.queuesize == this.queuemax)
        throw "Queue overflow";
    else
    {
        this.queuesize++;
        this.elements[this.queueback] = obj;
        this.queueback = tempback;
    }
}

function qPop()
{
    if (this.empty())
        throw "Queue underflow";
    else
    {
        this.queuesize--;
        if (++this.queuefront == this.queuemax)
            this.queuefront = 0;
    }
}

-->

