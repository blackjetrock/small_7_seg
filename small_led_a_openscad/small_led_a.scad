module pre()
{
cube([57, 14, 2], center=true);
}

module rem()
{
    translate([-7*3.5-2.5/2, 3.9-7, 0])
    {
for(i=[0:3.5:14*3.5])
{    
translate([i, 0, 0])
{
digit();
}
}
}
}

// Clearance so diffuser fits inside mask holes.

w = 0.1;

module cut()
{
cube([0.7-w, 1.8-w, 3], center=true);
}

module rcut()
{
cube([1.8-w, 0.7-w, 3], center=true);
}

module digit()
{
    
translate([1.2, -1.4, 0])
    {
    rcut();
    }

translate([1.2, 1.4, 0])
    {
    rcut();
    }

translate([1.2, 4.2, 0])
    {
    rcut();
    }
    
cut();
translate([2.4, 0, 0])
{
    cut();
}    
translate([2.9, 4.8, 0])
{
cylinder(d=0.7-w, h = 3, $fn =30, center=true);
}

translate([0, 2.8, 0])
{
cut();
translate([2.4, 0, 0])
{
    cut();
}    
}
}

module mask()
{
    difference()
    {
        pre();
        rem();
    }
}

dh = 0.9;
dd = 0.2;

module diffuser()
{
translate([0, 0, 2/2+dh/2-dd])
    {
    cube([57, 14, dh], center=true);
    }
}

domask = 0;
dodiff = 1;

if(domask)
{
mask();
}

if(dodiff)
{
difference()
    {
        diffuser();
        mask();
    }
}
