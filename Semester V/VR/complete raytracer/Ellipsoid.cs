using System;

namespace rt
{
    public class Ellipsoid : Geometry
    {
        private Vector Center { get; } // center of the ellipsoid in 3D space
        private Vector SemiAxesLength { get; }
        private Vector SemiAxesLengthSquared => new Vector(
            SemiAxesLength.X * SemiAxesLength.X,
            SemiAxesLength.Y * SemiAxesLength.Y,
            SemiAxesLength.Z * SemiAxesLength.Z
        ); // Computed property for squared semi-axes lengths
        //Useful for normalizing points and vectors relative to the ellipsoid shape during intersection calculations.
        private double Radius { get; }

        private const double Epsilon = 1e-10; // small constant used for numerical stabilty (when comparing floating-point)

        public Ellipsoid(Vector center, Vector semiAxesLength, double radius, Material material, Color color)
            : base(material, color) //material for lighting reflection etc
        {
            Center = center;
            SemiAxesLength = semiAxesLength;
            Radius = radius;
        }

        public Ellipsoid(Vector center, Vector semiAxesLength, double radius, Color color)
            : base(color)
        {
            Center = center;
            SemiAxesLength = semiAxesLength;
            Radius = radius;
        }

        private Vector NormalizeToSemiAxes(Vector input)
        { //useful for scaling a point to an ideal sphere shape for easier calculations
            return new Vector(
                input.X / SemiAxesLength.X,
                input.Y / SemiAxesLength.Y,
                input.Z / SemiAxesLength.Z
            );
        }

        private Vector NormalizeToSquaredSemiAxes(Vector input)
        { // same here but for for squared semi-axes 
            return new Vector(
                input.X / SemiAxesLengthSquared.X,
                input.Y / SemiAxesLengthSquared.Y,
                input.Z / SemiAxesLengthSquared.Z
            );
        }

        public (double? First, double? Last) GetFirstAndLastIntersection(Line line)
        { // calculates the intersection points of a line (ray) with the ellipsoid
            var directionNormalized = NormalizeToSemiAxes(line.Dx);
            var originToCenterNormalized = NormalizeToSemiAxes(line.X0 - Center); 
            // normalize the vector from the ellipsoid center to the starting point of the line relative to the semi-axes lengths.

            double a = directionNormalized.Length2();
            double b = 2 * (directionNormalized * originToCenterNormalized);
            double c = originToCenterNormalized.Length2() - Radius * Radius;
            //ray-ellipsoid intersection => solve quadratic equation

            double discriminant = b * b - 4 * a * c;

            if (discriminant < Epsilon) return (null, null); // no intersection => we retain nothing

            if (Math.Abs(discriminant) < Epsilon) // case of repeated root ( 0.00..1) 
            {
                double t = -b / (2 * a);
                return (t, null); // return only a valid root
            }

            double sqrtDiscriminant = Math.Sqrt(discriminant);
            double inv2A = 1 / (2 * a);
            double root1 = (-b - sqrtDiscriminant) * inv2A;
            double root2 = (-b + sqrtDiscriminant) * inv2A;
            // compute and return the roots of the quadratic equation
            return (root1, root2);
        }

        public override Intersection GetIntersection(Line line, double minDist, double maxDist, bool? onlyFirst = false)
        {
            var (firstRoot, lastRoot) = GetFirstAndLastIntersection(line);

            if (firstRoot == null) return Intersection.NONE;

            double? validRoot = firstRoot >= minDist ? firstRoot : lastRoot;  // take the closest point
            if (validRoot == null || validRoot > maxDist) return Intersection.NONE;//select valid intersection root if in range (minDist, maxDist)

            double t = validRoot.Value; // distance
            var position = line.CoordinateToPosition(t); // convert distance to 3D position
            var normal = NormalizeToSquaredSemiAxes((position - Center) * 2).Normalize();
            //vector from center to the intersection point, normalized to the squared semi-axes lengths
            bool isVisible = t >= minDist && t <= maxDist; // check if the intersection is visible

            return new Intersection(
                valid: true,
                visible: isVisible,
                geometry: this,
                line: line,
                t: t,
                normal: normal,
                material: Material,
                color: Color
            );
        }
    }
}
