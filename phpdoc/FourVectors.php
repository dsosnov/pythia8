<html>
<head>
<title>Four-Vectors</title>
</head>
<body>

<script language=javascript type=text/javascript>
function stopRKey(evt) {
var evt = (evt) ? evt : ((event) ? event : null);
var node = (evt.target) ? evt.target :((evt.srcElement) ? evt.srcElement : null);
if ((evt.keyCode == 13) && (node.type=="text"))
{return false;}
}

document.onkeypress = stopRKey;
</script>
<?php
if($_POST['saved'] == 1) {
if($_POST['filepath'] != "files/") {
echo "<font color='red'>SETTINGS SAVED TO FILE</font><br/><br/>"; }
else {
echo "<font color='red'>NO FILE SELECTED YET.. PLEASE DO SO </font><a href='SaveSettings.php'>HERE</a><br/><br/>"; }
}
?>

<form method='post' action='FourVectors.php'>

<h2>Four-Vectors</h2>

The <code>Vec4</code> class gives an implementation of four-vectors. 
The member function names are based on the assumption that these 
represent momentum vectors. Thus one can get or set 
<code>px()</code>, <code>py()</code>, <code>pz()</code> and 
<code>e()</code>, but not <i>x, y, z</i> or <i>t</i>. (When 
production vertices are defined in the particle class, this is 
partly circumvented by new methods that hide a <code>Vec4</code>.) 
Derived quantities like the <code>pT()</code>, the <code>pAbs()</code>, 
and the <code>theta()</code> and <code>phi()</code> angles 
may be read out. The names should be self-explanatory, so we refer 
to the header class.

<p/>
A set of overloaded operators are defined for four-vectors, so that 
one may naturally add, subtract, multiply or divide four-vectors with 
each other or with double numbers, for all the cases that are 
meaningful.

<p/>
The <code>Particle</code> object contains a <code>Vec4 p</code> that 
stores the particle four-momentum, and another <code>Vec4 vProd</code> 
for the production vertex. Therefore a user would not normally access the 
<code>Vec4</code> class directly, but by using the similarly-named methods 
of the <code>Particle</code> class. (The latter also stores the particle mass 
separately, offering an element of redundancy, helpful in avoiding some 
roundoff errors.) However, for simple analysis tasks it may be convenient 
to use <code>Vec4</code>, e.g., to define the four-vector sum of a set of 
particles.

<p/>
Simple rotations and boosts of the four-vectors are easily obtained
with member functions. For a longer sequence of rotations and boosts, 
and where several <code>Vec4</code> are involved for the same set of 
operations, a more efficient approach is to define a 
<code>RotBstMatrix</code>, which forms a separate auxiliary class. 
This matrix can be built up from the successive set of operations to be 
performed and, once defined, it can be applied on as many 
<code>Vec4</code> as required. 

</body>
</html>

<!-- Copyright C 2007 Torbjorn Sjostrand -->