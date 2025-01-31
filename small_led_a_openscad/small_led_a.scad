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

module cut()
{
cube([0.7, 1.8, 3], center=true);
}

module rcut()
{
cube([1.8, 0.7, 3], center=true);
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
cylinder(d=0.7, h = 3, $fn =30, center=true);
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

translate([0,-7+3.9,1])
{
//cube([1,1,1], center=true);
}

mask();
