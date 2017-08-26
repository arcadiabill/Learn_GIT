// wrapping the entire file in an anonymous function
(function () {

/**
 * Define GS global object. This will serve as the namespace for all
 * GS specific JavaScript.
 */
var GS;
if (typeof GS === "undefined") {
	GS = {};
} else if (typeof GS !== "object") {
	throw new Error("GS already exists but is not an object.");
} else {
	throw new Error("GS already exists as an object.");
}

/* Extend Object.prototype to aid in prototypal inheritance.
 * Courtesy of Douglas Crockford, http://www.crockford.com/
 * Usage: var newObject = oldObject.beget();
 */
Object.prototype.beget = function () {
	function F() {}
	F.prototype = this;
	return new F();
};

/* Extend Object.prototype to allow for object creation with new data.
 * Behavior is similar to that of a classical inheritance constructor function.
 * Usage: var newObject = oldObject.create({property: value, ... });
 */
Object.prototype.create = function (data) {
	// create new object on this object
	//var copy = this.beget();
	function F() {}
	F.prototype = this;
	copy = new F();

	// iterate through the properties of the data object which has
	// been passed into this function
	for (var property in data) {
		if (data.hasOwnProperty(property)) {
			// ensure that this object defines the current property
			if (this.hasOwnProperty(property)) {
				// assign the current property's value to the new employee
				copy[property] = data[property];
			}
		}
	}

	return copy;
};

GS.TypeA = {
	name: null,
	ranking: [],
	matchedTo: null,
	highestTypeB: 0,
	toString: function () {return this.name;}
};

GS.TypeB = {
	name: null,
	ranking: [],
	matchedTo: null,
	toString: function () {return this.name;}
};

GS.globals = {
};

GS.lineNumber = 1;

/**
 * Output a string of text wrapped in a <p>.
 */
GS.print = function (str, parent) {
	var textElem = document.createElement('p');
	textElem.appendChild(document.createTextNode(GS.lineNumber++ + ': ' + str));
	parent.appendChild(textElem);
};

/**
 * Output the pairing results.
 */
GS.printPairs = function (typeAs, typeBs, parent) {
	for (var a = 0; a < typeAs.length; a++) {
		GS.print(typeAs[a].name + ' is paired with ' + typeBs[typeAs[a].matchedTo].name, parent);
	}
}

/**
 * Returns the number of unpaired typeAs.
 */
GS.totalUnmatched = function (typeAs) {
	var result = 0;
	for (var a = 0; a < typeAs.length; a++) {
		if (typeAs[a].matchedTo == null) {
			result += 1;
		}
	}
	return result;
};

/**
 * Gale-Shapley algorithm for stable matching.
 */
GS.match = function (typeAs, typeBs, verbose) {
	var round = 1;
	var verboseResults = document.getElementById('verbose_results');
	while (GS.totalUnmatched(typeAs) > 0 && round <= 50) {
		var result = '';
		if (verbose) GS.print('Round ' + round, verboseResults);
		for (var a = 0; a < typeAs.length; a++) {
			(function () {
				var A = typeAs[a];
				// choose the highest typeB that a has not proposed to
				var b = typeAs[a].ranking[typeAs[a].highestTypeB];
				var B = typeBs[b];
				if (verbose) GS.print(A + ' prefers ' + B, verboseResults);
				// if b does not have a match, then pair a and b
				if (typeBs[b].matchedTo == null) {
					if (verbose) GS.print(B + ' is previously unmatched', verboseResults);
					typeAs[a].matchedTo = b;
					typeBs[b].matchedTo = a;
					if (verbose) GS.print(A + ' becomes paired with ' + B, verboseResults);
				}
				// if b is already paired with a, then do nothing
				else if (typeBs[b].matchedTo == a) {
					// do nothing
					if (verbose) GS.print(B + ' is already matched to ' + A, verboseResults);
				}
				// otherwise, b already is paired, but it is not to a
				else {
					var a_ = typeBs[b].matchedTo;
					var A_ = typeAs[a_];
					if (verbose) GS.print(B + ' is already paired to ' + A_, verboseResults);
					if (verbose) GS.print(B + ' ranks ' + A_ + ' as ' + typeBs[b].ranking[a_], verboseResults);
					if (verbose) GS.print(B + ' ranks ' + A + ' as ' + typeBs[b].ranking[a], verboseResults);
					// if b's current pair (a_) ranks b higher than a, then a should look for another pair
					if (typeBs[b].ranking[a_] < typeBs[b].ranking[a]) {
						// do not ask this typeB again
						typeAs[a].highestTypeB++;
						if (verbose) GS.print(A + ' moves on to ' + typeBs[typeAs[a].ranking[typeAs[a].highestTypeB]], verboseResults);
					}
					// otherwise, pair a with b, and a_ should be paired with somebody else
					else {
						typeAs[a].matchedTo = b;
						typeBs[b].matchedTo = a;
						typeAs[a_].matchedTo = null;
						if (verbose) GS.print(A + ' becomes paired with ' + B, verboseResults);
						if (verbose) GS.print(A_ + ' becomes single', verboseResults);
						typeAs[a_].highestTypeB++;
						if (verbose) GS.print(A_ + ' moves on to ' + typeBs[typeAs[a_].ranking[typeAs[a_].highestTypeB]], verboseResults);
					}
				}
			}());
		}
		round++;
	}
};

GS.Dom = {
	match: function () {
		var results = document.getElementById('results');
		if (results) results.parentNode.removeChild(results);
		var verboseResults = document.getElementById('verbose_results');
		if (verboseResults) verboseResults.parentNode.removeChild(verboseResults);
		var typeAs = [];
		var typeBs = [];
		var boySelects;
		var girlSelects;
		var boyName;
		var girlName;
		var n = GS.globals.n;
		var typeA = GS.globals.typeA;
		var typeB = GS.globals.typeB;
		for (var i = 0; i < n; i++) {
			boySelects = GS.Dom.getElementsByClassName(typeA + '_rank', document.getElementById(typeA + '_' + i));
			var ranking = [];
			for (var j = 0; j < boySelects.length; j++) {
				ranking.push(boySelects[j].selectedIndex);
			}
			boyName = document.getElementById(typeA + '_name_' + i).value;
			typeAs.push(GS.TypeA.create({ranking: ranking, name: boyName}));
			girlSelects = GS.Dom.getElementsByClassName(typeB + '_rank', document.getElementById(typeB + '_' + i));
			var ranking = [];
			for (var j = 0; j < girlSelects.length; j++) {
				ranking.push(girlSelects[j].selectedIndex);
			}
			girlName = document.getElementById(typeB + '_name_' + i).value;
			typeBs.push(GS.TypeB.create({ranking: ranking, name: girlName}));
		}
		if (document.getElementById('verbose').checked) {
			var verboseResults = document.createElement('div');
			verboseResults.setAttribute('id', 'verbose_results');
			var verboseResultsHeader = document.createElement('h2');
			verboseResultsHeader.setAttribute('id', 'verbose_results_header');
			verboseResultsHeader.appendChild(document.createTextNode('Verbose Results'));
			verboseResults.appendChild(verboseResultsHeader);
			document.getElementById('generated').appendChild(verboseResults);
			GS.match(typeAs, typeBs, true);
		} else {
			GS.match(typeAs, typeBs, false);
		}
		var results = document.createElement('div');
		results.setAttribute('id', 'results');
		var resultsHeader = document.createElement('h2');
		resultsHeader.setAttribute('id', 'results_header');
		resultsHeader.appendChild(document.createTextNode('Results'));
		results.appendChild(resultsHeader);
		document.getElementById('generated').appendChild(results);
		GS.printPairs(typeAs, typeBs, results);
	},
	setup: function () {
		var n = document.getElementById('n').value;
		GS.globals.n = n;

		var typeA = document.getElementById('type_a').value.replace(/ /g, '_');
		var typeB = document.getElementById('type_b').value.replace(/ /g, '_');
		GS.globals.typeA = typeA;
		GS.globals.typeB = typeB;
		if (typeA.length == 0 || typeB.length == 0) {
			window.alert('You must enter two type names');
			return;
		} else if (typeA == typeB) {
			window.alert('The two types (' + typeA + ', ' + typeB + ') must be different');
			return;
		}
		
		var setup = document.getElementById('setup');
		setup.removeEventListener('click', GS.Dom.setup, false);
		setup.firstChild.data = 'Reset';
		setup.addEventListener('click', GS.Dom.reset, false);

		var generated = document.createElement('div');
		generated.setAttribute('id', 'generated');
		var typeAs = document.createElement('div');
		typeAs.setAttribute('id', typeA + 's');
		var typeAsHeader = document.createElement('h2');
		typeAsHeader.appendChild(document.createTextNode(typeA));
		typeAs.appendChild(typeAsHeader);
		var typeBs = document.createElement('div');
		typeBs.setAttribute('id', typeB + 's');
		var typeBsHeader = document.createElement('h2');
		typeBsHeader.appendChild(document.createTextNode(typeB));
		typeBs.appendChild(typeBsHeader);
		for (var i = 0; i < n; i++) {
			GS.Dom.input(typeAs, i, true);
			GS.Dom.input(typeBs, i, false);
		}
		var matchControls = document.createElement('div');
		matchControls.setAttribute('id', 'match_controls');
		var match = document.createElement('button');
		match.setAttribute('id', 'match')
		match.appendChild(document.createTextNode('Match'));
		match.addEventListener('click', GS.Dom.match, false);
		var verbose = document.createElement('input');
		verbose.setAttribute('type', 'checkbox');
		verbose.setAttribute('id', 'verbose');
		var verboseLabel = document.createElement('label');
		verboseLabel.setAttribute('htmlFor', 'verbose');
		verboseLabel.appendChild(document.createTextNode('Verbose Output?'));
		matchControls.appendChild(match);
		matchControls.appendChild(verbose);
		matchControls.appendChild(verboseLabel);
		generated.appendChild(typeAs);
		generated.appendChild(typeBs);
		generated.appendChild(matchControls);
		document.body.appendChild(generated);
	},
	reset: function () {
		if (window.confirm('Are you sure?')) {
			var generated = document.getElementById('generated');
			generated.parentNode.removeChild(generated);
			var setup = document.getElementById('setup');
			setup.removeEventListener('click', GS.Dom.reset, false);
			setup.firstChild.data = 'Setup';
			setup.addEventListener('click', GS.Dom.setup, false);
		}
	},
	last: function (e) {
		var typeA = GS.globals.typeA;
		if (this.getAttribute('id').match(typeA)) {
			GS.globals.lastTypeA = this.selectedIndex;
		} else {
			GS.globals.lastTypeB = this.selectedIndex;
		}
	},
	update: function (e) {
		var typeA = GS.globals.typeA;
		var typeB = GS.globals.typeB;
		var toValue = this.selectedIndex;
		var id = this.getAttribute('id');
		var rank;
		var postfix;
		var selectsClass;
		var last;
		var selects;
		if (id.match(typeA)) {
			last = GS.globals.lastTypeA;
			postfix = '_rank_';
			selectClass = typeA + '_rank';
		} else {
			last = GS.globals.lastTypeB;
			postfix = '_rank_';
			selectClass = typeB + '_rank';
		}
		rank = id.slice(id.search(postfix) + postfix.length, id.length);
		selects = GS.Dom.getElementsByClassName(selectClass, this.parentNode);
		for (var i = 0; i < selects.length; i++) {
			if (rank != i && selects[i].selectedIndex == toValue) {
				selects[i].selectedIndex = last;
			}
		}
	},
	updateName: function (e) {
		var typeA = GS.globals.typeA;
		var typeB = GS.globals.typeB;
		var toValue = this.value;
		var id = this.getAttribute('id');
		var number;
		var selects;
		var selectClass;
		var prefix;
		if (id.match(typeA)) {
			prefix = typeA + '_name_';
			selectClass = typeB + '_rank';
		} else {
			prefix = typeB + '_name_';
			selectClass = typeA + '_rank';
		}
		number = id.replace(prefix, '');
		selects = GS.Dom.getElementsByClassName(selectClass);
		for (var i = 0; i < selects.length; i++) {
			selects[i].options[number].text = toValue;
		}
	},
	input: function (parent, number, isTypeA) {
		var n = GS.globals.n;
		var typeA = GS.globals.typeA;
		var typeB = GS.globals.typeB;
		var type = document.createElement('div');
		type.setAttribute('className', 'type');
		isTypeA ? type.setAttribute('id', typeA + '_' + number) : type.setAttribute('id', typeB + '_' + number);
		var name = document.createElement('input');
		name.setAttribute('type', 'text');
		isTypeA ? name.setAttribute('id', typeA + '_name_' + number) : name.setAttribute('id', typeB + '_name_' + number);
		isTypeA ? name.setAttribute('value', typeA + number) : name.setAttribute('value', typeB + number);
		name.addEventListener('change', GS.Dom.updateName, false);
		type.appendChild(name);
		for (var rank = 0; rank < n; rank++) {
			var select = document.createElement('select');
			for (var choice = 0; choice < n; choice++) {
				var option = document.createElement('option');
				option.setAttribute('value', choice);
				isTypeA ? option.text = typeB + choice : option.text = typeA + choice;
				select.add(option, null);
			}
			number + rank >= n ? select.selectedIndex = number + rank - n : select.selectedIndex = number + rank;
			isTypeA ? select.setAttribute('id', typeA + number + '_rank_' + rank) : select.setAttribute('id', typeB + '_' + number + '_rank_' + rank);
			isTypeA ? select.setAttribute('class', typeA + '_rank ' + typeA + '_rank_' + rank) : select.setAttribute('class', typeB + '_rank ' + typeB + '_rank_' + rank);
			select.addEventListener('change', GS.Dom.update, false);
			select.addEventListener('focus', GS.Dom.last, false);
			type.appendChild(select);
		}
		parent.appendChild(type);
	},
	getElementsByClassName: function (className, node, tag) {
		if ( node == null ) {
			node = document;
		}
		if (node.getElementsByClassName) {
			return node.getElementsByClassName(className);
		}
		else {
			var classElements = new Array();
			if ( tag == null ) {
				tag = '*';
			}
			var els = node.getElementsByTagName(tag);
			var elsLen = els.length;
			var pattern = new RegExp('(^|\\s)' + className + '(\\s|$)');
			for (var i = 0, j = 0; i < elsLen; i++) {
				if (pattern.test(els[i].className)) {
					classElements[j] = els[i];
					j++;
				}
			}
			return classElements;
		}
	}
};

window.onload = function () {
	var setup = document.getElementById('setup');
	setup.addEventListener('click', GS.Dom.setup, false);
};

})(); // end of anonymous function wrapper