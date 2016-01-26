import java.awt.geom.Line2D;

public class Tri2D
{
	/* Zack Ream
	 * Ex10.12 - Class 'Triangle2D'
	 * 
	 * This program tests the methods and properties of the Triangle2D class, as
	 * well as the MyPoint class.
	 * 
	 * It will create a new Triangle2D and return its area and perimeter. It
	 * will then check whether it contains a certain point, a certain triangle,
	 * or overlaps another triangle. */

	public static void main(String[] args)
	{
		// create variables
		Triangle2D t1 = new Triangle2D(new MyPoint(2.5, 2), new MyPoint(4.2, 3), new MyPoint(5, 3.5));
		double area = t1.getArea();
		double perimeter = t1.getPerimeter();
		boolean containsPoint, containsTriangle, overlapsTriangle;

		// test requested properties
		containsPoint = t1.contains(new MyPoint(3, 3));
		containsTriangle = t1.contains(new Triangle2D(new MyPoint(2.9, 2), new MyPoint(4, 1), new MyPoint(1, 3.4)));
		overlapsTriangle = t1.overlaps(new Triangle2D(new MyPoint(2, 5.5), new MyPoint(4, -3), new MyPoint(2, 6.5)));

		// output result, using the ternary operator to select the proper string
		System.out.println("For Triangle (2.5,2),(4.2,3),(5,3.5)...");
		System.out.printf(" Its Area = %f\n Its Perimeter = %f\n", area, perimeter);
		System.out.printf(" It %s point (3, 3).\n", containsPoint ? "contains" : "doesn't contain");
		System.out.printf(" It %s triangle (2.9,2),(4,1),(1,3.4).\n", containsTriangle ? "contains" : "doesn't contain");
		System.out.printf(" It %s with triangle (2,5.5),(4,-3),(2,6.5).", overlapsTriangle ? "overlaps" : "doesn't overlap");
	}

}

class Triangle2D
{
	/* Zack Ream
	 * Ex10.12 - Class 'Triangle2D'
	 * 
	 * This class implements a planar triangle, consisting of three (x,y)
	 * points.
	 * 
	 * It has a no-arg constructor that defaults to verticies (0,0),(1,1),(2,5).
	 * It has a three-arg constructor that accepts input for the three points.
	 * There are get- and set- methods for each of the three points.
	 * There are getArea and getPerimeter methods, self-explanatory. */

	// initialize points
	private MyPoint p1, p2, p3;

	// get and set methods for the three points
	public MyPoint getP1()
	{
		return p1;
	}

	public MyPoint getP2()
	{
		return p2;
	}

	public MyPoint getP3()
	{
		return p3;
	}

	public void setP1(MyPoint p)
	{
		this.p1 = p;
	}

	public void setP2(MyPoint p)
	{
		this.p2 = p;
	}

	public void setP3(MyPoint p)
	{
		this.p3 = p;
	}

	// constructor to set the points based on input
	public Triangle2D(MyPoint newP1, MyPoint newP2, MyPoint newP3)
	{
		this.p1 = newP1;
		this.p2 = newP2;
		this.p3 = newP3;
	}

	// constructor that calls the three-arg constructor using default values.
	public Triangle2D()
	{
		this(new MyPoint(0, 0), new MyPoint(1, 1), new MyPoint(2, 5));
	}

	// return the area. It first finds the length of each of the three sides
	// (A,B,C), and uses the formula to return the area.
	public double getArea()
	{
		double S, A, B, C, area;
		A = this.p1.distance(this.p2);
		B = this.p2.distance(this.p3);
		C = this.p3.distance(this.p1);
		S = .5 * (A + B + C);
		area = Math.sqrt(S * (S - A) * (S - B) * (S - C));
		return area;
	}

	// return the perimeter. It first finds the length of each of the three
	// sides, and adds them together to find the perimeter.
	public double getPerimeter()
	{
		double A, B, C, perimeter;
		A = this.p1.distance(this.p2);
		B = this.p2.distance(this.p3);
		C = this.p3.distance(this.p1);
		perimeter = A + B + C;
		return perimeter;
	}

	public boolean contains(Triangle2D t)
	{
		/* Returns true if the triangle we are given is completely contained
		 * within this triangle.
		 * If this triangle contains all three vertices of the passed
		 * Triangle2D, then this triangle contains the passed triangle2D. */

		return (this.contains(t.getP1()) && this.contains(t.getP2()) && this.contains(t.getP3()));
	}

	public boolean contains(MyPoint p)
	{
		/* Returns true if the point we are given is completely contained within
		 * this triangle.
		 * 
		 * This method tests the line from P to each of the triangle vertices,
		 * counting how many triangle sides it intersects. If each line
		 * intersects only 2 sides each, the point lies inside the triangle.
		 * 
		 * Calls sideIntersectionCount */

		// test line from 'p' to 'p1'
		if (sideIntersectionCount(new Line2D.Double(p.getX(), p.getY(), p1.getX(), p1.getY())) != 2)
		{
			return false;
		}

		// test line from 'p' to 'p2'
		if (sideIntersectionCount(new Line2D.Double(p.getX(), p.getY(), p2.getX(), p2.getY())) != 2)
		{
			return false;
		}

		// test line from 'p' to 'p3'
		if (sideIntersectionCount(new Line2D.Double(p.getX(), p.getY(), p3.getX(), p3.getY())) != 2)
		{
			return false;
		}

		return true;

	}

	public boolean overlaps(Triangle2D tri)
	{
		/* Returns true if this triangle overlaps at all the passed triangle;
		 * that is, if they intersect at any place.
		 * 
		 * They intersect if any side of the passed triangle intersect with any
		 * side of this triangle.
		 * 
		 * Uses sideIntersectionCount */

		int numberOfIntersections = 0;
		// test side P1-P2 of the passed triangle
		numberOfIntersections += sideIntersectionCount(new Line2D.Double(tri.p1.getX(), tri.p1.getY(), tri.p2.getX(), tri.p2.getY()));
		// test side P2-P3 of the passed triangle
		numberOfIntersections += sideIntersectionCount(new Line2D.Double(tri.p2.getX(), tri.p2.getY(), tri.p3.getX(), tri.p3.getY()));
		// test side P1-P3 of the passed triangle
		numberOfIntersections += sideIntersectionCount(new Line2D.Double(tri.p1.getX(), tri.p1.getY(), tri.p3.getX(), tri.p3.getY()));

		return (numberOfIntersections > 0);
	}

	private int sideIntersectionCount(Line2D line)
	{
		/* Used by other methods, to count intersections of a line with this
		 * triangle's sides.
		 * 
		 * Generates a Line2D for each triangle side. Tests how many times the
		 * passed line intersects any of the triangle sides. Returns the total
		 * intersection count. */

		// generate Line2D's for triangle sides
		Line2D.Double sideA = new Line2D.Double(this.p1.getX(), this.p1.getY(), this.p2.getX(), this.p2.getY());
		Line2D.Double sideB = new Line2D.Double(this.p2.getX(), this.p2.getY(), this.p3.getX(), this.p3.getY());
		Line2D.Double sideC = new Line2D.Double(this.p1.getX(), this.p1.getY(), this.p3.getX(), this.p3.getY());

		int intersections = 0;

		// test sideA
		if (line.intersectsLine(sideA))
		{
			intersections++;
		}

		// test sideB
		if (line.intersectsLine(sideB))
		{
			intersections++;
		}

		// test sideC
		if (line.intersectsLine(sideC))
		{
			intersections++;
		}

		return intersections;
	}

}

class MyPoint
{
	/* Class 'myPoint' - Ex. 10.4
	 * Zack Ream
	 * 
	 * This class implements a geometric point, used in the Triangle2D class in
	 * EX10_12.
	 * 
	 * It has a no-arg constructor that defaults to (0,0).
	 * It has a two-arg constructor that accepts input for (x,y).
	 * There are get (not set) methods for x and y.
	 * There is an overloaded distance method:
	 * 1. Find the distance between this point and another myPoint.
	 * 2. Find the distance between this point and an inputted (x,y). */

	// initialize point coordinates
	private double x, y;

	// constructor that sets (x,y) to new passed arguments
	public MyPoint(double newX, double newY)
	{
		this.x = newX;
		this.y = newY;
	}

	// calls the two-arg constructor using default (0,0) values
	public MyPoint()
	{
		this(0, 0);
	}

	// get- methods for x and y
	public double getX()
	{
		return this.x;
	}

	public double getY()
	{
		return this.y;
	}

	// return the distance between this point and a point (x2,y2)
	// it uses the distance formula
	public double distance(double x2, double y2)
	{
		double dist;
		dist = Math.sqrt(Math.pow(x2 - this.x, 2) + Math.pow(y2 - this.y, 2));
		return dist;
	}

	// return the distance between this point and another myPoint p2
	// it calls the two-arg method using p2's (x,y) values.
	public double distance(MyPoint p2)
	{
		return distance(p2.getX(), p2.getY());
	}
}